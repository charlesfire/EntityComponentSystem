#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <type_traits>
#include <vector>
#include "EventListener.hpp"

namespace ECS
{
    class Entity;
    class System;

    class Engine final
    {
        public:
            Engine();
            ~Engine();
            const Entity& AddEntity();
            void AddEventListener(EventListener<>* listener);

            template<class T, class ...Args>
            const T& AddSystem(const Args&... args)
            {
                T* system = new T(args...);
                systems.push_back(system);
                return *system;
            }

            template<class T, class ...Args>
            void EmitEvent(const Args&... args)
            {
                T event(args...);
                for (auto listener : listeners)
                {
                    EventListener<T>* castedListener = dynamic_cast<EventListener<T>*>(listener);
                    if (castedListener != nullptr)
                        castedListener->Listen(event);
                }
            }

            void Update(const float deltaTime)const;
            bool RemoveEntity(const Entity& entity);
            bool RemoveSystem(const System& system);
        private:
            std::vector<Entity*> entities;
            std::vector<EventListener<>*> listeners;
            std::vector<System*> systems;
    };
}

#endif // ENGINE_HPP
