#pragma once

#include "Fox/ECS/Entity/Entity.hpp"
#include "Fox/ECS/Registry.hpp"
#include "Fox/ECS/Components/RelationshipComponent.hpp"
#include "Fox/ECS/Components/TransformComponent.hpp"

namespace fox
{
    class Actor : public Entity
    {
    public:
        explicit Actor()
            : Entity{ Registry::create() }
        {
            add_component<RelationshipComponent>();
            add_component<TransformComponent>();
        }
        virtual ~Actor() override
        {
            Registry::destroy(m_id);
        }

        template<typename... T>
        bool has_component()
        {
            return Registry::has_component<T...>(m_id);
        }
        template<typename T, typename... Args>
        T& add_component(Args&&... args)
        {
            return Registry::add_component<T>(m_id, *this, std::forward<Args>(args)...);
        }
        template<typename T>
        T& get_component()
        {
            return Registry::get_component<T>(m_id);
        }
        template<typename T>
        void remove_component()
        {
            Registry::remove_component<T>(m_id);
        }
        template<> void remove_component<RelationshipComponent>() = delete;
        template<> void remove_component<TransformComponent>() = delete;
    };
}
