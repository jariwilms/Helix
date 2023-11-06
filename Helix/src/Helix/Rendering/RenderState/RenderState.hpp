#pragma once

#include "stdafx.hpp"

namespace hlx::gfx::api
{
    class RenderState
    {
    public:
        enum class Parameter
        {
            ClearColor, 
            DepthFunction, 
            DepthTestingAlpha, 
            FaceCulling, 
            FaceCullingAlpha, 
            FrontFace, 
        };
        enum class DepthFunction
        {
            Never, 
            Less, 
            Equal, 
            LessEqual, 
            Greater, 
            NotEqual, 
            GreaterEqual, 
            Always, 
        };
        enum class FaceCulling
        {
            Front, 
            Back, 
            FrontBack, 
        };
        enum class FrontFace
        {
            Clockwise, 
            CounterClockwise, 
        };

    protected:
        RenderState() = default;

        static inline bool          s_depthTestingAlpha{};
        static inline bool          s_cullingFaceAlpha{};
        static inline FaceCulling   s_faceCulling{};
        static inline DepthFunction s_depthFunction{};
        static inline FrontFace     s_frontFace{};
        static inline Vector4f      s_clearColor{};
    };
}
