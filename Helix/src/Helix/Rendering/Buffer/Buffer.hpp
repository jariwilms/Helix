#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Interface/IBindable.hpp"

namespace hlx
{
    template<typename T>
    class Buffer
    {
    public:
        enum class AccessFlag
        {
            Read,
            Write,
        };

        virtual ~Buffer() = default;

        virtual void bind()     const = 0;
        virtual void unbind()   const = 0;
        virtual bool is_bound() const = 0;

        void copy(std::span<const T> data)
        {
            const auto dataSize = data.size() * sizeof(T);

            if (data.size() * sizeof(T) != m_size) throw std::range_error{ "Data size is not equal to buffer size!" };

            copy(data.data());
        }
        void copy_range(unsigned int offset, std::span<const T> data)
        {
            const auto dataSize = data.size() * sizeof(T);
            const auto offsetSize = offset * sizeof(T);

            if (dataSize + offsetSize > m_size) throw std::range_error{ "Data size is greater than buffer range!" };

            copy_range(dataSize, offsetSize, data.data());
        }

        size_t       size()  const
        {
            return m_size;
        }
        unsigned int count() const
        {
            return static_cast<unsigned int>(m_size / sizeof(T));
        }

    protected:
        Buffer(unsigned int tCount)
            : m_size{ tCount * sizeof(T) } {}

        virtual void copy(const void* data) = 0;
        virtual void copy_range(size_t size, size_t offset, const void* data) = 0;

        size_t m_size{};
    };
}
