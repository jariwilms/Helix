#pragma once

#include "stdafx.hpp"

#include "Helix/ECS/Components/Components.hpp"
#include "Helix/Rendering/API/RendererAPI.hpp"
#include "Helix/Rendering/API/OpenGL/OpenGLRenderer.hpp"
#include "Helix/Rendering/RenderState.hpp"
#include "Helix/Rendering/Geometry/Geometry.hpp"

namespace hlx
{
    class Renderer
    {
    public:
        static void init()
        {
            RenderState::init();
            Geometry::init();
            s_rendererAPI = std::make_shared<OpenGLRenderer>();
        }

        static void start(const RendererAPI::RenderInfo& renderInfo)
        {
            s_rendererAPI->start(renderInfo);
        }
        static void finish()
        {
            s_rendererAPI->finish();
        }

        static void render(const std::shared_ptr<const Mesh> mesh, const std::shared_ptr<const Material> material, const Transform& transform)
        {
            s_rendererAPI->render(mesh, material, transform);
        }

    private:
        static inline std::shared_ptr<RendererAPI> s_rendererAPI{};
    };
}
