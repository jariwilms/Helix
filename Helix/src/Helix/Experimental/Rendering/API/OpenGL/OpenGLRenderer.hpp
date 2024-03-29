#pragma once

#include "stdafx.hpp"

#include "Helix/Experimental/Rendering/Renderer.hpp"
#include "Helix/Experimental/Rendering/Rendering.hpp"

namespace hlx::gfx::api
{
    template<>
    class GRenderer<GraphicsAPI::OpenGL> : public Renderer
    {
    public:
        GRenderer()
        {
            //const u8 samples{ 4 };
            //const u32 lightCount{ 8 };
            //const Vector2u dimensions{ 1280, 720 };
            //const Vector2u shadowMapDimensions{ 1024, 1024 };

            //std::array<FrameBuffer::Manifest, 5> gBufferManifest
            //{
            //    FrameBuffer::Manifest{ "Position",     FrameBuffer::Attachment::Color,        FrameBuffer::Resample::Yes, TextureBlueprint{ Texture::Format::RGB16_SFLOAT, Texture::Filter::Trilinear, Texture::Wrapping::Repeat } },
            //    FrameBuffer::Manifest{ "Albedo",       FrameBuffer::Attachment::Color,        FrameBuffer::Resample::Yes, TextureBlueprint{ Texture::Format::RGBA8_SRGB,   Texture::Filter::Trilinear, Texture::Wrapping::Repeat } },
            //    FrameBuffer::Manifest{ "Normal",       FrameBuffer::Attachment::Color,        FrameBuffer::Resample::Yes, TextureBlueprint{ Texture::Format::RGB16_SFLOAT, Texture::Filter::Trilinear, Texture::Wrapping::Repeat } },
            //    FrameBuffer::Manifest{ "ARM",          FrameBuffer::Attachment::Color,        FrameBuffer::Resample::Yes, TextureBlueprint{ Texture::Format::RGB16_UNORM,  Texture::Filter::Trilinear, Texture::Wrapping::Repeat } },

            //    FrameBuffer::Manifest{ "DepthStencil", FrameBuffer::Attachment::DepthStencil, FrameBuffer::Resample::No,  TextureBlueprint{ Texture::Format::D24_UNORM_S8_UINT } },
            //};
            //std::array<FrameBuffer::Manifest, 1> sBufferManifest
            //{
            //    FrameBuffer::Manifest{ "Depth", FrameBuffer::Attachment::Depth, FrameBuffer::Resample::Yes, TextureBlueprint{ Texture::Format::D24_UNORM } },
            //};
            //std::array<FrameBuffer::Manifest, 2> ppBufferManifest
            //{
            //    FrameBuffer::Manifest{ "Color", FrameBuffer::Attachment::Color,        FrameBuffer::Resample::Yes, TextureBlueprint{ Texture::Format::RGB16_UNORM } },
            //    FrameBuffer::Manifest{ "Depth", FrameBuffer::Attachment::DepthStencil, FrameBuffer::Resample::No,  TextureBlueprint{ Texture::Format::D24_UNORM_S8_UINT} },
            //};

            //m_gBuffer            = std::make_unique<FrameBuffer>(dimensions, gBufferManifest);
            //m_gBufferMultisample = std::make_unique<FrameBufferMultisample>(dimensions, samples, gBufferManifest);
            //m_sBuffer            = std::make_unique<FrameBuffer>(shadowMapDimensions, sBufferManifest);
            //for (auto& ppBuffer : m_ppBuffers)
            //{
            //    ppBuffer = std::make_unique<FrameBuffer>(dimensions, ppBufferManifest);
            //}

            //

            //m_matricesBuffer = std::make_unique<UniformBuffer<UMatrices>>();
            //m_materialBuffer = std::make_unique<UniformBuffer<UMaterial>>();
            //m_cameraBuffer   = std::make_unique<UniformBuffer<UCamera>>();
            //m_lightBuffer    = std::make_unique<UniformArrayBuffer<Buffer::Access::Dynamic, ULight>>(2u);



            //const auto& meshShader     = std::make_shared<Shader>("shaders/compiled/mesh.vert.spv");
            //const auto& lightingShader = std::make_shared<Shader>();
            //const auto& skyboxShader   = std::make_shared<Shader>();
            //const auto& shadowShader   = std::make_shared<Shader>();



            //m_pipelines.emplace("Mesh",     std::make_unique<Pipeline>("shaders/compiled/mesh.vert.spv",                 "shaders/compiled/mesh.frag.spv"));
            //m_pipelines.emplace("Lighting", std::make_unique<Pipeline>("shaders/compiled/lighting_blinn-phong.vert.spv", "shaders/compiled/lighting_blinn-phong.frag.spv"));
            //m_pipelines.emplace("Skybox",   std::make_unique<Pipeline>("shaders/compiled/skybox.vert.spv",               "shaders/compiled/skybox.frag.spv"));
            //m_pipelines.emplace("Shadow",   std::make_unique<Pipeline>("shaders/compiled/shadow.vert.spv",               "shaders/compiled/shadow.frag.spv"));



            //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            //glDepthFunc(GL_LEQUAL);
            //glEnable(GL_CULL_FACE);
            //glCullFace(GL_BACK);
            //glFrontFace(GL_CCW);
        }
        ~GRenderer()
        {

        }

        void start()
        {

        }
        void finish()
        {

        }

        void render(const std::shared_ptr<const Mesh> mesh, const std::shared_ptr<const Material> material, const Transform& transform)
        {

        }

    private:
        //std::unique_ptr<FrameBuffer> m_gBuffer{};
        //std::unique_ptr<FrameBuffer> m_sBuffer{};
        //std::array<std::unique_ptr<FrameBuffer>, 2> m_ppBuffers{};
        //std::unique_ptr<FrameBufferMultisample> m_gBufferMultisample{};

        //std::unique_ptr<UniformBuffer<UMatrices>> m_matricesBuffer{};
        //std::unique_ptr<UniformBuffer<UMaterial>> m_materialBuffer{};
        //std::unique_ptr<UniformBuffer<UCamera>> m_cameraBuffer{};
        //std::unique_ptr<UniformArrayBuffer<Buffer::Access::Dynamic, ULight>> m_lightBuffer{};

        //std::unordered_map<std::string, std::unique_ptr<Pipeline>> m_pipelines{};

        //std::vector<std::tuple<const std::shared_ptr<const Mesh>, const std::shared_ptr<const Material>, const Transform&>> m_mmt{};
    };
}
