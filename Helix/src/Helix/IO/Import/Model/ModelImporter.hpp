#pragma once

#include "stdafx.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Helix/IO/IO.hpp"
#include "Helix/Rendering/API/GraphicsAPI.hpp"
#include "Helix/Rendering/Model/Model.hpp"

namespace hlx
{
    class ModelImporter
    {
    public:
        static inline std::shared_ptr<Pipeline> dpl{};

        static void init()
        {
            const std::string materialName{ "Default" };
            dpl = GraphicsAPI::create_plo("shaders/compiled/geometryvert.spv", "shaders/compiled/geometryfrag.spv");
            
            defaultMaterial = std::make_shared<DefaultMaterial>(materialName, dpl);
            defaultMaterial->albedo = GraphicsAPI::create_tex(Texture::Format::RGBA, Texture::ColorDepth::_8bit, Vector2u{ 1, 1 }, Texture::Filter::Point, Texture::Wrapping::Repeat, Texture::Wrapping::Repeat, 1, true, Texture::Format::R, std::vector<byte>{ 0xFF });
            defaultMaterial->normal = GraphicsAPI::create_tex(Texture::Format::RGBA, Texture::ColorDepth::_8bit, Vector2u{ 1, 1 }, Texture::Filter::Point, Texture::Wrapping::Repeat, Texture::Wrapping::Repeat, 1, true, Texture::Format::RGB, std::vector<byte>{ 0x00, 0x00, 0xFF });
        }

        static std::shared_ptr<Model> load(const std::filesystem::path& path)
        {
            const auto directory = path.parent_path();
            const auto aggregate = IO::root() / path.string();
            const auto agp = aggregate.parent_path();

            Assimp::Importer importer{};
            const auto pFlags = aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FixInfacingNormals | aiProcess_SortByPType | aiProcess_OptimizeGraph | aiProcess_OptimizeMeshes;

            const auto aiScene = importer.ReadFile(aggregate.string(), pFlags);
            if (!aiScene || aiScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !aiScene->mRootNode) throw std::runtime_error{ "Failed to load model!" };



            std::vector<std::shared_ptr<DefaultMaterial>> materials{};
            TextureBlueprint bp{};
            bp.filter = Texture::Filter::Trilinear;

            for (auto i = 0u; i < aiScene->mNumMaterials; ++i)
            {
                auto material = std::make_shared<DefaultMaterial>(path.string(), dpl);
                material->albedo = defaultAlbedoTexture;
                material->normal = defaultNormalTexture;

                const auto& aiMaterial = *aiScene->mMaterials[i];
                aiString materialName{};

                aiMaterial.Get(AI_MATKEY_NAME, materialName);
                if (materialName.length)
                {
                    aiString materialDiffuse{};
                    aiString materialNormal{};

                    material->name = materialName.C_Str();

                    aiMaterial.Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), materialDiffuse);
                    if (materialDiffuse.length)
                    {
                        const auto diffuseImage = std::make_shared<Image>(agp / materialDiffuse.C_Str());
                        const auto diffuseTexture = bp.build(diffuseImage, 1u, true);
                        material->albedo = diffuseTexture;
                    }

                    aiMaterial.Get(AI_MATKEY_TEXTURE(aiTextureType_NORMALS, 0), materialNormal);
                    if (materialNormal.length)
                    {
                        const auto normalImage = std::make_shared<Image>(agp / materialNormal.C_Str());
                        const auto normalTexture = bp.build(normalImage);
                        material->normal = normalTexture;
                    }

                    materials.emplace_back(std::move(material));
                }
            }
            if (materials.empty()) materials.emplace_back(defaultMaterial);



            auto layout3f = std::make_shared<VertexLayout>();
            layout3f->specify<float>(3);
            auto layout2f = std::make_shared<VertexLayout>();
            layout2f->specify<float>(2);



            auto model = std::make_shared<Model>();
            for (auto i = 0u; i < aiScene->mNumMeshes; ++i)
            {
                const auto& aiMesh = *aiScene->mMeshes[i];
                
                std::vector<Vector3f> vertices{};
                std::vector<Vector3f> normals{};
                std::vector<Vector2f> texCoords{};
                std::vector<unsigned int> indices{};

                for (auto j = 0u; j < aiMesh.mNumVertices; ++j)
                {
                    const auto vertex   = aiMesh.mVertices[j];
                    vertices.emplace_back(Vector3f{ vertex.x, vertex.y, vertex.z });

                    const auto normal   = aiMesh.mNormals[j];
                    normals.emplace_back(Vector3f{ normal.x, normal.y, normal.z });

                    const auto texCoord = aiMesh.mTextureCoords[0][j];
                    texCoords.emplace_back(static_cast<float>(texCoord.x), static_cast<float>(texCoord.y));
                }

                for (auto k = 0u; k < aiMesh.mNumFaces; ++k)
                {
                    const auto& face = aiMesh.mFaces[k];
                    
                    for (auto l = 0u; l < face.mNumIndices; ++l)
                    {
                        indices.emplace_back(face.mIndices[l]);
                    }
                }

                const auto verticesBuffer  = GraphicsAPI::create_vbo<Vector3f>(vertices);
                const auto normalsBuffer   = GraphicsAPI::create_vbo<Vector3f>(normals);
                const auto texCoordsBuffer = GraphicsAPI::create_vbo<Vector2f>(texCoords);
                const auto indicesBuffer = GraphicsAPI::create_ibo(indices);



                const auto vertexArray = GraphicsAPI::create_vao();
                vertexArray->tie(verticesBuffer, layout3f);
                vertexArray->tie(normalsBuffer, layout3f);
                vertexArray->tie(texCoordsBuffer, layout2f);
                vertexArray->tie(indicesBuffer);


                __debugbreak();
                //auto mesh = std::make_shared<Mesh>(vertexArray, materials[aiMesh.mMaterialIndex]);
                //model->meshes.emplace_back(std::move(mesh));
            }



            return model;
        }

        private:
            static inline std::shared_ptr<Texture2D> defaultAlbedoTexture{};
            static inline std::shared_ptr<Texture2D> defaultNormalTexture{};
            static inline std::shared_ptr<DefaultMaterial> defaultMaterial{};
    };
}
