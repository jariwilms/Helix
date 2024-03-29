#include "stdafx.hpp"

#include "OpenGLRenderer.hpp"

namespace hlx
{
    OpenGLRenderer::OpenGLRenderer()
    {
        std::vector<FrameBuffer::TextureManifest> gBufferTextureManifest
        {
            { "Position", FrameBuffer::Attachment::Color, TextureBlueprint{ Texture::Format::RGB16_SFLOAT, Texture::Filter::Trilinear, Texture::Wrapping::Repeat } },
            { "Albedo",   FrameBuffer::Attachment::Color, TextureBlueprint{ Texture::Format::RGBA8_SRGB,   Texture::Filter::Trilinear, Texture::Wrapping::Repeat } },
            { "Normal",   FrameBuffer::Attachment::Color, TextureBlueprint{ Texture::Format::RGB16_SFLOAT, Texture::Filter::Trilinear, Texture::Wrapping::Repeat } },
            { "ARM",      FrameBuffer::Attachment::Color, TextureBlueprint{ Texture::Format::RGB16_UNORM,  Texture::Filter::Trilinear, Texture::Wrapping::Repeat } },
        };
        std::vector<FrameBuffer::RenderBufferManifest> gBufferRenderBufferManifest
        {
            { "DepthStencil", FrameBuffer::Attachment::DepthStencil, RenderBufferBlueprint{ RenderBuffer::Format::Depth24Stencil8 } }, 
        };

        FrameBufferBlueprint frameBufferBlueprint{ gBufferTextureManifest, gBufferRenderBufferManifest };
        m_gBufferMultisample = frameBufferBlueprint.build_multisample(Vector2f{ 1280, 720 }, 2u);
        m_gBuffer            = frameBufferBlueprint.build(Vector2f{ 1280, 720 });



        std::vector<FrameBuffer::TextureManifest> shadowMapBufferTextureManifest
        {
            { "Color", FrameBuffer::Attachment::Depth, TextureBlueprint{ Texture::Format::D24_UNORM } }, 
        };

        FrameBufferBlueprint shadowMapBufferBlueprint{ shadowMapBufferTextureManifest, {} };
        m_shadowMapBuffer = shadowMapBufferBlueprint.build(Vector2f{ 1024, 1024 });



        std::vector<FrameBuffer::TextureManifest> ppBufferTextureManifest
        {
            { "Color", FrameBuffer::Attachment::Color, TextureBlueprint{ Texture::Format::RGB16_UNORM } }, 
        };
        std::vector<FrameBuffer::RenderBufferManifest> ppBufferRenderBufferManifest
        {
            { "Depth", FrameBuffer::Attachment::DepthStencil, RenderBufferBlueprint{ RenderBuffer::Format::Depth24Stencil8 } }, 
        };

        FrameBufferBlueprint ppBufferBlueprint{ ppBufferTextureManifest, ppBufferRenderBufferManifest };
        for (auto& ppBuffer : m_ppBuffers)
        {
            ppBuffer = ppBufferBlueprint.build({ 1280, 720 });
        }





        //Buffer for lights, TODO: pass actual light count to lighting shader instead of const value
        const auto lightCount = 8;
        m_matricesBuffer = std::make_shared<OpenGLUniformBuffer<UMatrices>>(0, UMatrices{});
        m_materialBuffer = std::make_shared<OpenGLUniformBuffer<UMaterial>>(1, UMaterial{});
        m_lightBuffer    = std::make_shared<OpenGLUniformArrayBuffer<ULight>>(2, lightCount);
        m_cameraBuffer   = std::make_shared<OpenGLUniformBuffer<UCamera>>(3, UCamera{});
        




        m_pipelines.emplace("Mesh",     GFX_DEPRECATED::create_pipeline("shaders/compiled/mesh.vert.spv",         "shaders/compiled/mesh.frag.spv"));
        /*m_pipelines.emplace("Lighting", gfx::create_pipeline("shaders/compiled/lighting_pbr.vert.spv", "shaders/compiled/lighting_pbr.frag.spv"));*/
        m_pipelines.emplace("Lighting", GFX_DEPRECATED::create_pipeline("shaders/compiled/lighting_blinn-phong.vert.spv", "shaders/compiled/lighting_blinn-phong.frag.spv"));
        m_pipelines.emplace("Skybox",   GFX_DEPRECATED::create_pipeline("shaders/compiled/skybox.vert.spv",       "shaders/compiled/skybox.frag.spv"));
        m_pipelines.emplace("Shadow",   GFX_DEPRECATED::create_pipeline("shaders/compiled/shadow.vert.spv",       "shaders/compiled/shadow.frag.spv"));




        //TODO: global state control class (set + remember current state so unnecessary (and maybe expensive) changes do not need to be made
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
    }

    void OpenGLRenderer::start(const RenderInfo& renderInfo)
    {
        const auto& camera           = renderInfo.camera;
        const auto& transform        = renderInfo.cameraTransform;
        const auto& viewMatrix       = glm::lookAt(transform.position, transform.position + transform.forward(), transform.up());
        const auto& projectionMatrix = camera.projection_matrix();

        std::array<ULight, 8> uLights{};
        const auto& lights = renderInfo.lights;
        std::transform(lights.begin(), lights.end(), uLights.begin(), [](const std::tuple<Light, Vector3f>& _)
            {
                const auto& [light, position] = _;

                return ULight
                {
                    Vector4f{ position, 0.0f },
                    Vector4f{ light.color, 0.0f },
                };
            });

        m_matricesBuffer->copy_tuple(offsetof(UMatrices, view), std::make_tuple(viewMatrix, projectionMatrix));
        m_cameraBuffer->copy(UCamera{ Vector4f{ transform.position, 0.0f } });
        m_lightBuffer->copy(uLights);

        




        m_mmt.clear();






        m_gBufferMultisample->bind(FrameBuffer::Target::Write);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
    }
    void OpenGLRenderer::finish()
    {
        m_pipelines.at("Mesh")->bind();
        for (const auto& mmt : m_mmt)
        {
            const auto& [mesh, material, transform] = mmt;

            m_matricesBuffer->copy_tuple(offsetof(UMatrices, model), std::make_tuple(transform.matrix()));
            m_matricesBuffer->copy_tuple(offsetof(UMatrices, normal), std::make_tuple(glm::transpose(glm::inverse(transform.matrix()))));

            const auto& vao = mesh->vertex_array();
            vao->bind();
            if (vao->indexed()) vao->index_buffer()->bind();

            m_materialBuffer->copy(UMaterial{ material->color, material->roughness, material->metallic });
            material->albedoMap->bind(0);
            material->normalMap->bind(1);
            material->armMap->bind(2);
            material->emissionMap->bind(3);

            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(vao->index_buffer()->count()), GL_UNSIGNED_INT, nullptr);
        }
        



        
        glDisable(GL_CULL_FACE);

        //Multisampled framebuffer textures can not be sampled like a regular framebuffer, so we have to copy it into a regular framebuffer
        const auto& glBufferMultisample = std::static_pointer_cast<OpenGLFrameBufferMultisample>(m_gBufferMultisample);
        const auto& glBuffer            = std::static_pointer_cast<OpenGLFrameBuffer>(m_gBuffer);

        const auto width{ 1280 };
        const auto height{ 720 };
        for (auto i{ 0u }; i < 4; ++i)
        {
            glNamedFramebufferReadBuffer(glBufferMultisample->id(), GL_COLOR_ATTACHMENT0 + i);
            glNamedFramebufferDrawBuffer(glBuffer->id(), GL_COLOR_ATTACHMENT0 + i);
            glBlitNamedFramebuffer(glBufferMultisample->id(), glBuffer->id(), 0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
        }
        glBlitNamedFramebuffer(glBufferMultisample->id(), glBuffer->id(), 0, 0, width, height, 0, 0, width, height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);




        
        //Lighting pass render into ppBuffer
        glDisable(GL_BLEND);

        m_pipelines.at("Lighting")->bind();
        m_ppBuffers[0]->bind(FrameBuffer::Target::Write);
        m_gBuffer->bind_texture("Position", 0);
        m_gBuffer->bind_texture("Albedo",   1);
        m_gBuffer->bind_texture("Normal",   2);
        m_gBuffer->bind_texture("ARM",      3);

        glDisable(GL_DEPTH_TEST);
        Geometry::Plane::mesh()->vertex_array()->bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glEnable(GL_BLEND);



        const auto& glPPBuffer = std::static_pointer_cast<OpenGLFrameBuffer>(m_ppBuffers[0]);



        //Skybox pass after copying depth information from gBuffer
        const auto& skybox = RenderSettings::lighting.skybox;
        if (skybox)
        {
            const auto& vertexArray = Geometry::Cube::mesh()->vertex_array();
            vertexArray->bind();

            m_pipelines.at("Skybox")->bind();
            skybox->bind(0);


            glEnable(GL_DEPTH_TEST);
            glBlitNamedFramebuffer(glBuffer->id(), glPPBuffer->id(), 0, 0, width, height, 0, 0, width, height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(vertexArray->index_buffer()->size()), GL_UNSIGNED_INT, nullptr);
            glDisable(GL_DEPTH_TEST);
        }



        glBlitNamedFramebuffer(glPPBuffer->id(), 0, 0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
        //glNamedFramebufferReadBuffer(glBuffer->id(), GL_COLOR_ATTACHMENT0 + 1);
        //glBlitNamedFramebuffer(glBuffer->id(), 0, 0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    }

    void OpenGLRenderer::render(const std::shared_ptr<const Mesh> mesh, const std::shared_ptr<const Material> material, const Transform& transform)
    {
        m_mmt.emplace_back(mesh, material, transform);
    }
}
