#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <type_traits>
#include "ComponentPool.hpp"
#include "Engine.hpp"

namespace ECS
{
    class Component;

    class Entity final
    {
        friend const Entity& Engine::AddEntity();
        public:
            virtual ~Entity() = default;
            Entity(const Entity& other);
            Entity& operator=(const Entity& other);
            bool operator==(const Entity& other);

            template<class T, class ...Types>
            T& AddComponent(const Types&... args)
            {
                static_assert(std::is_base_of<Component, T>(), "An Entity can only have components.");
                return ComponentPool<T>::GetInstance().AddComponent(uuid, &args...);
            }

            template<class T>
            T& GetComponent()const
            {
                static_assert(std::is_base_of<Component, T>(), "An Entity can only have components.");
                return ComponentPool<T>::GetInstance().GetComponent(uuid);
            }

            unsigned int GetUUID()const;

            template<class T>
            bool Has()const
            {
                static_assert(std::is_base_of<Component, T>(), "An Entity can only have components.");
                return ComponentPool<T>::GetInstance().HasComponent(uuid);
            }

            template<class T, class ...Types>
            bool HasAllOf()const
            {
                static_assert(std::is_base_of<Component, T>(), "An Entity can only have components.");
                if (std::is_same<T, Component>())
                    return true;
                return ComponentPool<T>::GetInstance().HasComponent(uuid) && HasAllOf<Types..., Component>();
            }

            template<class T, class ...Types>
            bool HasNoneOf()const
            {
                static_assert(std::is_base_of<Component, T>(), "An Entity can only have components.");
                return !HasOneOf<T, Types...>();
            }

            template<class T>
            bool HasNot()const
            {
                return !Has<T>();
            }

            template<class T, class ...Types>
            bool HasOneOf()const
            {
                static_assert(std::is_base_of<Component, T>(), "An Entity can only have components.");
                if (std::is_same<T, Component>())
                    return false;
                return ComponentPool<T>::GetInstance().HasComponent(uuid) || HasOneOf<Types..., Component>();
            }

            template<class T>
            void RemoveComponent()
            {
                static_assert(std::is_base_of<Component, T>(), "Can't remove non-component type from Entity.");
                ComponentPool<T>::GetInstance().RemoveComponent(uuid);
            }
        private:
            Entity() = delete;
            Entity(Engine& engine);
            Engine* engine;
            static unsigned int counter;
            unsigned int uuid;
    };
}

#endif // ENTITY_HPP
