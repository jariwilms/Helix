#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Application.hpp"
#include "Helix/Core/Library/Time/Time.hpp"
#include "Helix/Core/Library/Utility/Utility.hpp"
#include "Helix/ECS/Components/Components.hpp"
#include "Helix/ECS/Entity/Entity.hpp"
#include "Helix/ECS/Registry.hpp"
#include "Helix/Input/Input.hpp"
#include "Helix/IO/IO.hpp"
#include "Helix/IO/Import/Model/ModelImporter.hpp"
#include "Helix/Prefab/Rendering/Geometry/Geometry.hpp"
#include "Helix/Prefab/Rendering/Geometry/Cube.hpp"
#include "Helix/Rendering/API/GraphicsAPI.hpp"
#include "Helix/Rendering/Blueprint/FrameBufferBlueprint.hpp"
#include "Helix/Rendering/Blueprint/TextureBlueprint.hpp"
#include "Helix/Rendering/Renderer.hpp"
#include "Helix/Scene/Scene.hpp"
#include "Helix/Window/Window.hpp"
#include "Helix/Rendering/API/OpenGL/Texture/OpenGLCubemapTexture.hpp"
#include "Helix/Core/Library/Data/CyclicBuffer.hpp"
#include "Helix/Rendering/RenderSettings.hpp"

#include "Helix/Test/Test.hpp"
#include "Helix/Experimental/Texture/Texture.hpp"

#include "Helix/IO/Import/Model/ModelImporter.hpp"

using namespace hlx;



//Mip levels with base included (+1)
unsigned int mip_count(const Vector2u& dimensions)
{
    return static_cast<unsigned int>(std::floor(std::log2(std::max(dimensions.x, dimensions.y)))) + 1u;
}



Transform transform_product(TransformComponent& tc)
{
    auto& owner = tc.owner;
    auto& rc = Registry::get_component<RelationshipComponent>(owner.id());

    if (rc.parent.has_value())
    {
        auto& ptc = Registry::get_component<TransformComponent>(rc.parent.value());
        return transform_product(ptc) * tc;
    }
    else
    {
        return tc;
    }
};
std::shared_ptr<Actor> model_to_scene_graph(Scene* scene, std::shared_ptr<Model> model, std::shared_ptr<Actor> parent, Model::Node* node)
{
    auto actor = scene->create_actor();
    scene->set_parent(parent, actor);
    
    auto& transformComponent = actor->get_component<TransformComponent>();
    if (node->localTransform.has_value())
    {
        Transform& t = transformComponent;
        t = node->localTransform.value();
    }

    if (node->meshPrimitive.has_value())
    {
        const auto& mp = node->meshPrimitive.value();
        auto& meshR = actor->add_component<MeshRendererComponent>();
        meshR.mesh = model->meshes[mp.meshIndex];
        meshR.material = model->materials[mp.materialIndex];
    }

    for (auto& child : node->children)
    {
        model_to_scene_graph(scene, model, actor, &child);
    }

    return actor;
};

int main(int argc, char** argv)
{
    Application application{ argc, argv };

    const std::string windowIdentifier{ "Window 1" };
    const std::string windowTitle{ "Helix" };
    const Vector2u windowDimensions{ 1280, 720 };
    const auto window = WindowManager::create(windowIdentifier, windowTitle, windowDimensions);

    IO::init();
    Geometry::init();
    Renderer::init();
    ModelImporter::init();

    //unsigned int id{};
    //glCreateTextures(GL_TEXTURE_2D, 1, &id);



    auto scene = std::make_shared<Scene>();
    auto observer = scene->create_actor();
    auto& camera = observer->add_component<CameraComponent>();
    auto& cameraTransform = observer->get_component<TransformComponent>();
    cameraTransform.translate(Vector3f{ 0.0f, 0.0f, 3.0f });



    hlx::ModelImporter modelImporter{};
    auto box = modelImporter.import(R"(models/sponza_gltf/glTF/Sponza.gltf)");
    auto boxActor = model_to_scene_graph(scene.get(), box, nullptr, box->rootNode.get());




    
    const Vector2u skyboxDimensions{ 2048, 2048 };
    TextureBlueprint skyboxBlueprint{};
    std::string skyboxDirectory{ "textures/skybox2/" };
    std::array<std::string, 6> skyboxFileNames{ "right.png", "left.png", "bottom.png", "top.png", "front.png", "back.png", };
    std::array<std::shared_ptr<const std::vector<byte>>, 6> skyboxImages
    {
        IO::load<Image>(skyboxDirectory + skyboxFileNames.at(0))->read(),
        IO::load<Image>(skyboxDirectory + skyboxFileNames.at(1))->read(),
        IO::load<Image>(skyboxDirectory + skyboxFileNames.at(2))->read(),
        IO::load<Image>(skyboxDirectory + skyboxFileNames.at(3))->read(),
        IO::load<Image>(skyboxDirectory + skyboxFileNames.at(4))->read(),
        IO::load<Image>(skyboxDirectory + skyboxFileNames.at(5))->read(),
    };
    std::array<std::span<const byte>, 6> def
    {
        *skyboxImages[0],
        *skyboxImages[1],
        *skyboxImages[2],
        *skyboxImages[3],
        *skyboxImages[4],
        *skyboxImages[5],
    };

    RenderSettings::lighting.skybox = std::make_shared<OpenGLCubemapTexture>(Texture::Format::RGBA, Texture::ColorDepth::_8bit, skyboxDimensions, Texture::Filter::Trilinear, Texture::Wrapping::ClampToEdge, Texture::Wrapping::ClampToEdge, Texture::Wrapping::ClampToEdge, 4, false, Texture::Format::RGBA, def);











    std::vector<std::tuple<Light, Vector3f>> lights{ 32 };



    Time::reset();
    CyclicBuffer<float, 128> frametimes{};
	while (!glfwWindowShouldClose(reinterpret_cast<GLFWwindow*>(window->native_window())))
	{
        Time::advance();

        auto speed{ 10.0f };
        if (Input::key_pressed(Key::LeftShift)) speed *= 10.0f;
        if (Input::key_pressed(Key::LeftControl)) speed /= 5.0f;
        if (Input::key_pressed(Key::W)) cameraTransform.position += cameraTransform.forward() * speed * Time::delta();
        if (Input::key_pressed(Key::S)) cameraTransform.position -= cameraTransform.forward() * speed * Time::delta();
        if (Input::key_pressed(Key::A)) cameraTransform.position -= cameraTransform.right()   * speed * Time::delta();
        if (Input::key_pressed(Key::D)) cameraTransform.position += cameraTransform.right()   * speed * Time::delta();
        if (Input::key_pressed(Key::E)) cameraTransform.position += cameraTransform.up()      * speed * Time::delta();
        if (Input::key_pressed(Key::Q)) cameraTransform.position -= cameraTransform.up()      * speed * Time::delta();

        if (Input::button_pressed(Button::Button1)) //RMB
        {
            static Vector3f rotation{};
            const auto rel = Input::cursor_position_relative() / 10.0f;
            rotation += Vector3f{ rel.y, rel.x, 0.0f };

            cameraTransform.rotation = Quaternion{ glm::radians(rotation) };
        }

        //The render system starts running here and submits all models/meshes to the renderer
        //So, TODO: RenderSystem::update, which calls the code below
        Renderer::start(RendererAPI::RenderInfo{ camera, cameraTransform, lights });
        auto group = Registry::view<TransformComponent, MeshRendererComponent>();
        group.each([](auto entity, TransformComponent& transform, MeshRendererComponent& meshRenderer)
            {
                Renderer::render(meshRenderer.mesh, meshRenderer.material, transform_product(transform));
            });
        Renderer::finish();
        


		window->refresh();
        frametimes.push_back(Time::delta());
	}

    float avgFrameTime = std::accumulate(frametimes.begin(), frametimes.end(), 0.0f) / static_cast<float>(frametimes.size());
    std::system("CLS");
    std::cout << "Average frametime: " << avgFrameTime << '\n';
    std::cout << "Average framerate: " << 1.0f / avgFrameTime << '\n';

    return 0;
}
