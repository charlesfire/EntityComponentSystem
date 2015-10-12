#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <type_traits>
#include "ComponentAddedEvent.hpp"
#include "ComponentRemovedEvent.hpp"
#include "Engine.hpp"

namespace ECS
{
    class Component;

    class Entity final
    {
        friend const Entity& Engine::AddEntity();
        public:
            Entity() = delete;
            Entity(const Entity& other);
            virtual ~Entity() = default;
            Entity& operator=(const Entity& other);
            bool operator==(const Entity& other);

            template<class T, class ...Args>
            T& AddComponent(const Args&... args);

            template<class T>
            T& GetComponent()const;

            unsigned int GetUUID()const;

            template<class T>
            bool Has()const;

            template<class T, class ...Types>
            bool HasAllOf()const;

            template<class T, class ...Types>
            bool HasNoneOf()const;

            template<class T>
            bool HasNot()const;

            template<class T, class ...Types>
            bool HasOneOf()const;

            template<class T>
            void RemoveComponent();
        private:
            Entity(ECS::Engine& engine);

            ECS::Engine* engine;
            static unsigned int counter;
            unsigned int uuid;
    };
}

#include "Entity.tcc"

#endif // ENTITY_HPP
