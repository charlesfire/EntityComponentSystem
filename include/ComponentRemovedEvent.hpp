#ifndef COMPONENTREMOVEDEVENT_HPP
#define COMPONENTREMOVEDEVENT_HPP

#include "Event.hpp"

namespace ECS
{
    class Entity;

    class ComponentRemovedEvent final : public Event
    {
        public:
            ComponentRemovedEvent() = delete;
            ComponentRemovedEvent(const Entity& entity);
            virtual ~ComponentRemovedEvent();
            const Entity& GetEntity()const;
        private:
            Entity* entity;
    };
}

#endif // COMPONENTREMOVEDEVENT_HPP
