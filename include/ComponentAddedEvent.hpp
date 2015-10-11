#ifndef COMPONENTADDEDEVENT_HPP
#define COMPONENTADDEDEVENT_HPP

#include "Event.hpp"

namespace ECS
{
    class Component;
    class Entity;

    class ComponentAddedEvent final : public Event
    {
        public:
            ComponentAddedEvent() = delete;
            ComponentAddedEvent(Component& addedComponent, const Entity& entity);
            virtual ~ComponentAddedEvent();
            const Component& GetAddedComponent()const;
            const Entity& GetEntity()const;
        private:
            Component* addedComponent;
            Entity* entity;
    };
}

#endif // COMPONENTADDEDEVENT_HPP
