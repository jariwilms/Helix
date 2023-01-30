#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/RendererAPI.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLFrameBuffer.hpp"
#include "Helix/Rendering/Shader/Pipeline.hpp"
#include "Helix/Rendering/Mesh/Mesh.hpp"
#include "Helix/IO/IO.hpp"
#include "Helix/Rendering/Blueprint/FrameBufferBlueprint.hpp"

namespace hlx
{
    class OpenGLRenderer : public RendererAPI
    {
    public:
        OpenGLRenderer();
        ~OpenGLRenderer() = default;

        void start(const RenderInfo& renderInfo) override;
        void finish() override;

        void render_mesh(const std::shared_ptr<Mesh> mesh) override;

    private:
        std::shared_ptr<FrameBuffer> m_gBuffer{};
        std::unordered_map<std::string, std::shared_ptr<Pipeline>> m_pipelines{}; 

        std::shared_ptr<UniformBuffer<UMatrices>> m_matricesBuffer{};
        std::shared_ptr<UniformBuffer<UMaterial>> m_materialBuffer{};          //TODO: Convert UniformArrayBuffer
        std::shared_ptr<UniformBuffer<ULight>> m_lightBuffer{};                //TODO: Convert UniformArrayBuffer
        std::shared_ptr<UniformBuffer<UCamera>> m_cameraBuffer{};              //TODO: Remove?

        std::span<const Light> m_lights{};
    };
}
