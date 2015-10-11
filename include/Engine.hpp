#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <algorithm>
#include <typeinfo>
#include <type_traits>
#include <unordered_map>
#include <vector>
#include "EventListener.hpp"
#include "ComponentMapper.hpp"

namespace ECS
{
    class Entity;
    class System;

    class Engine final
    {
        public:
            Engine();
            ~Engine();

            /*template<class T, class ...Args>
            const T& AddComponent(const Entity& entity, const Args&... args);*/
            const Entity& AddEntity();
            void AddEventListener(EventListener<>* listener);

            template<class T, class ...Args>
            const T& AddSystem(const Args&... args);

            template<class T, class ...Args>
            void EmitEvent(const Args&... args);

            template<class T>
            ComponentMapper<T>& GetComponentMapper(const Entity& entity)const;

            void Update(const float deltaTime)const;
            bool RemoveEntity(const Entity& entity);
            bool RemoveSystem(const System& system);
        private:
            std::vector<Entity> entities;
            std::vector<EventListener<>*> listeners;
            std::unordered_map<const std::type_info*, IComponentMapper> mappers;
            std::vector<System*> systems;
    };
}

#include "Engine.tcc"

#endif // ENGINE_HPP
