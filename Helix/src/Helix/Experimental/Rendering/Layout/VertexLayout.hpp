#pragma once

#include "stdafx.hpp"

#include "Helix/Experimental/Rendering/API/API.hpp"
#include "Helix/Core/Library/Template/Concepts.hpp"

namespace hlx::gfx::api
{
    template<typename T, u32 COUNT, bool NORM = false> requires std::is_fundamental_v<T> && NonZero<decltype(COUNT), COUNT>
    class Layout
    {
    public:
        using type = T;

        static inline const u32  count        = COUNT;
        static inline const bool isNormalized = NORM;
    };

    template<GraphicsAPI G>
    struct Attribute;

    template<GraphicsAPI G, typename... T>
    class VertexLayout;
}
