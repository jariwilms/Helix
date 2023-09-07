#pragma once

#include "stdafx.hpp"

namespace hlx::utl
{
    //https://stackoverflow.com/questions/70524923/c-convert-any-number-of-nested-vector-of-vector-to-equivalent-vector-of-span
    template<typename T>
    auto to_span(const std::vector<T>& v)
    {
        return std::span{ v };
    }
    template<typename T>
    auto to_span(const std::vector<std::vector<T>>& v)
    {
        using value_type = decltype(to_span(v.at(0)));

        std::vector<value_type> r{};
        for (const auto& _ : v)
        {
            r.push_back(to_span(_));
        }

        return to_span(r);
    }
}
