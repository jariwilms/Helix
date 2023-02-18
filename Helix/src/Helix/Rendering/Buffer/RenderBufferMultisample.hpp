#pragma once

#include "stdafx.hpp"

#include "RenderBuffer.hpp"

namespace hlx
{
    class RenderBufferMultisample : public RenderBuffer
    {
    public:
        virtual ~RenderBufferMultisample() = default;

        unsigned int samples() const
        {
            return m_samples;
        }

    protected:
        RenderBufferMultisample(RenderBuffer::Type type, RenderBuffer::Layout layout, const Vector2u& dimensions, unsigned int samples)
            : RenderBuffer{ type, layout, dimensions }, m_samples{ samples } {}

        unsigned int m_samples{};
    };
}