#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "stb/stb_image.h"

#include "Helix/Rendering/Object/BufferObject.hpp"
#include "Helix/Rendering/API/OpenGL/OpenGLRenderContext.hpp"
#include "Helix/Rendering/Blueprint/TextureBlueprint.hpp"

namespace hlx
{
	class Texture : public BufferObject
	{
	public:
		virtual ~Texture() = default;

		static std::shared_ptr<Texture> create(const std::filesystem::path& path);
		static std::shared_ptr<Texture> create(TextureBlueprint blueprint, const unsigned char* data = nullptr);

		virtual void bindUnit(unsigned int index) const = 0;

		inline TextureType getType() const { return m_type; }
		inline TextureLayout getLayout() const { return m_layout; }

		inline glm::uvec3 getDimensions() const { return m_dimensions; }
		inline unsigned int getChannels() const { return m_channels; }

		inline unsigned int getMipmapLevels() const { return m_mipmapLevels; }

		inline bool isFlipped() const { return m_isFlipped; }
		inline bool isMutable() const { return m_isMutable; }

	protected:
		Texture() : m_type{}, m_layout{}, m_dimensions{}, m_channels{}, m_mipmapLevels{}, m_isFlipped{}, m_isMutable{} {}

		TextureType m_type;
		TextureLayout m_layout;

		glm::uvec3 m_dimensions;
		unsigned int m_channels;

		unsigned int m_mipmapLevels;

		bool m_isFlipped;
		bool m_isMutable;
	};
}
