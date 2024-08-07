#pragma once

#include "stdafx.hpp"

namespace fox
{
    class System
    {
    public:
        virtual ~System() = default;

        virtual void update() = 0;

    protected:
        System() = default;
    };
}
