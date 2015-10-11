#ifndef ENTITYREMOVEDEVENT_HPP
#define ENTITYREMOVEDEVENT_HPP

#include "Entity.hpp"
#include "Event.hpp"

namespace ECS
{
    class EntityRemovedEvent final : public Event
    {
        public:
            EntityRemovedEvent() = delete;
            EntityRemovedEvent(const Entity& removedEntity);
            virtual ~EntityRemovedEvent() = default;
            const Entity& GetRemovedEntity()const;
        private:
            Entity removedEntity;
    };
}

#endif // ENTITYREMOVEDEVENT_HPP
