#pragma once

#include "stdafx.hpp"

#pragma warning(disable: 26819 6262 26451)
#include "stb/stb_image.h"
#pragma warning(default: 26819 6262 26451)

#include "Helix/Rendering/Texture/Texture.hpp"
#include "Helix/Rendering/Model/Mesh.hpp"
#include "Helix/Rendering/Model/Model.hpp"
#include "Helix/IO/Importer/Model/ModelImporter.hpp"

namespace hlx
{
	class IO
	{
	public:
		class Affix
		{
		public:
			Affix(const std::filesystem::path relativePath)
			{
				HLX_CORE_INFO("Appended \"{0}\" to current path", relativePath.string().c_str());
				IO::m_subdirectories.push_back(relativePath);
			}
			~Affix()
			{
				auto& relativePath = m_subdirectories.at(m_subdirectories.size() - 1);
				HLX_CORE_INFO("Detached \"{0}\" from current path", relativePath.string().c_str());
				IO::m_subdirectories.pop_back();
			}
		};

		static void init()
		{
			m_root = std::filesystem::current_path().parent_path().lexically_normal();
			HLX_CORE_INFO("IO initalized");
			HLX_CORE_INFO("CWD: \"{0}\"", m_root.string().c_str());
		}

		static inline bool checkFileExists(const std::filesystem::path& path) { return std::filesystem::exists(path);  }
		static inline bool checkDirectoryExists(const std::filesystem::path& path) { return std::filesystem::exists(path); }

		static inline const std::filesystem::path& getRoot() { return m_root; }
		static inline void setRoot(const std::filesystem::path& root) { m_root = root; }

		static inline std::filesystem::path getCurrentWorkingDirectory() { return std::filesystem::current_path(); }
		static inline std::filesystem::path getCoalescedPath(std::filesystem::path path = "")
		{
			std::filesystem::path coalesced = m_root;
			std::for_each(m_subdirectories.begin(), m_subdirectories.end(), [&](const std::filesystem::path& _) { coalesced /= _; });

			return (coalesced / path).lexically_normal();
		}

		template<typename T, typename... Args>
		static inline std::shared_ptr<T> load(const std::filesystem::path& path, Args... args)
		{
			HLX_CORE_ASSERT(false, "Invalid file format");
		}
		template<> static inline std::shared_ptr<std::string> load<std::string>(const std::filesystem::path& path)
		{
			std::filesystem::path fullPath;

			if (path.is_absolute()) fullPath = path;
			else fullPath = getCoalescedPath(path);

			if (!checkFileExists(fullPath))
			{
				logError(fullPath);
				return nullptr;
			}
			if (m_textFiles.find(fullPath) != m_textFiles.end()) return m_textFiles[fullPath];



			std::ifstream file(fullPath);
			auto result = std::make_shared<std::string>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

			m_textFiles.insert(std::make_pair(fullPath, result));
			file.close();

			return m_textFiles[fullPath];
		}
		template<> static inline std::shared_ptr<Shader> load(const std::filesystem::path& path)
		{
			std::filesystem::path fullPath;

			if (path.is_absolute()) fullPath = path;
			else fullPath = getCoalescedPath(path);

			if (!checkFileExists(fullPath))
			{
				logError(fullPath);
				return nullptr;
			}
			if (m_shaders.find(fullPath) != m_shaders.end()) return m_shaders[fullPath];

			
			
			const std::string vertexDelimiter = "@vertex\n";
			const std::string geometryDelimiter = "@geometry\n";
			const std::string fragmentDelimiter = "@fragment\n";

			auto content = load<std::string>(fullPath);
			auto vertexPosition = content->find(vertexDelimiter);
			auto geometryPosition = content->find(geometryDelimiter);
			auto fragmentPosition = content->find(fragmentDelimiter);

			
			
			std::string vertex = content->substr(vertexPosition, fragmentPosition);
			std::string fragment = content->substr(fragmentPosition, std::string::npos);
			
			vertex.erase(0, vertexDelimiter.length());
			fragment.erase(0, fragmentDelimiter.length());


			
			auto shader = Shader::create(vertex, fragment);
			m_shaders.insert(std::make_pair(fullPath, shader));
			
			return shader;

			// "AI will kill us"
			// AI:
			//if (position == std::string::npos)
			//{
			//	vertex = content->substr(0, position);
			//	fragment = content->substr(position + 9);
			//}
			//else
			//{
			//	vertex = content->substr(0, position);
			//	fragment = content->substr(position + 9);
			//}
		}
		template<> static inline std::shared_ptr<Texture> load<Texture>(const std::filesystem::path& path)
		{
			std::filesystem::path fullPath;

			if (path.is_absolute()) fullPath = path;
			else fullPath = getCoalescedPath(path);

			if (!checkFileExists(fullPath))
			{
				logError(fullPath);
				return load<Texture>("textures/missing.png");
			}
			if (m_textures.find(fullPath) != m_textures.end()) return m_textures[fullPath];



			int width, height, channels;
			unsigned char* data;

			stbi_set_flip_vertically_on_load(true);
			data = stbi_load(fullPath.string().c_str(), &width, & height, &channels, 4);
			
			if (!data)
			{
				logError(fullPath);
				return load<Texture>("textures/missing.png");
			}
			
			TextureBlueprint blueprint{ TextureType::Texture2D, glm::uvec2{width, height} };
			auto texture = Texture::create(blueprint, data);
			stbi_image_free(data);


			
			m_textures.emplace(fullPath, std::move(texture));
			return m_textures.find(fullPath)->second;
		}
		template<> static inline std::shared_ptr<Model> load<Model>(const std::filesystem::path& path)
		{
			std::filesystem::path fullPath{};
			std::filesystem::path directory{};

			if (path.is_absolute()) fullPath = path; //todo: fix brol
			else fullPath = getCoalescedPath(path);
			if (fullPath.has_parent_path()) directory = fullPath.parent_path();

			if (m_models.find(fullPath) != m_models.end()) return m_models[fullPath];
			if (!checkFileExists(fullPath))
			{
				logError(fullPath);
				return nullptr;
			}

			//TODO: api agnostic flags
			constexpr auto importerFlags = aiProcess_Triangulate | aiProcess_GenUVCoords | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_OptimizeMeshes | aiProcess_OptimizeGraph;

			auto model = m_modelImporter.loadModel(fullPath, importerFlags);
			if (!model) return nullptr;
			
			m_models.emplace(fullPath, std::move(model));
			return m_models.find(fullPath)->second;
		}

	private:
		static void logError(std::filesystem::path path)
		{
			const std::string filename = path.filename().string();
			const std::string parent = path.remove_filename().generic_string();
			HLX_CORE_WARNING("File \"{0}\" was not found at location \"{1}\"", filename, parent);
		}

		static inline std::filesystem::path m_root;
		static inline std::vector<std::filesystem::path> m_subdirectories;

		static inline ModelImporter m_modelImporter;

		static inline std::unordered_map<std::filesystem::path, std::shared_ptr<std::string>> m_textFiles;
		static inline std::unordered_map<std::filesystem::path, std::shared_ptr<Shader>> m_shaders;
		static inline std::unordered_map<std::filesystem::path, std::shared_ptr<Texture>> m_textures;
		static inline std::unordered_map<std::filesystem::path, std::shared_ptr<Model>> m_models;
	};
}
