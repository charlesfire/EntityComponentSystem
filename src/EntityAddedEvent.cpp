#include "EntityAddedEvent.hpp"

using namespace ECS;

EntityAddedEvent::EntityAddedEvent(const Entity& entity) : addedEntity(addedEntity)
{

}

const Entity& EntityAddedEvent::GetAddedEntity()const
{
    return addedEntity;
}
