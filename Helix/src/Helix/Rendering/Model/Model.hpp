#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Mesh/Mesh.hpp"

namespace hlx
{
    class Model
    {
    public:
        Model() = default;

        std::vector<Mesh> meshes{};
    };
}
