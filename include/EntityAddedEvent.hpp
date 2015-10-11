#ifndef ENTITYADDEDEVENT_HPP
#define ENTITYADDEDEVENT_HPP

#include "Entity.hpp"
#include "Event.hpp"

namespace ECS
{
    class EntityAddedEvent final : public Event
    {
        public:
            EntityAddedEvent() = delete;
            EntityAddedEvent(const Entity& addedEntity);
            virtual ~EntityAddedEvent() = default;
            const Entity& GetAddedEntity()const;
        private:
            Entity addedEntity;
    };
}

#endif // ENTITYADDEDEVENT_HPP
