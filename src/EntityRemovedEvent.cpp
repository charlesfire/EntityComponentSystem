#include "EntityRemovedEvent.hpp"

using namespace ECS;

EntityRemovedEvent::EntityRemovedEvent(const Entity& removedEntity) : removedEntity(removedEntity)
{

}

const Entity& EntityRemovedEvent::GetRemovedEntity()const
{
    return removedEntity;
}
