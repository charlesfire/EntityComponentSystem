#include "ComponentRemovedEvent.hpp"

#include "Entity.hpp"

using namespace ECS;

ComponentRemovedEvent::ComponentRemovedEvent(const Entity& entity) : entity(new Entity(entity))
{

}

ComponentRemovedEvent::~ComponentRemovedEvent()
{
    delete entity;
}

const Entity& ComponentRemovedEvent::GetEntity()const
{
    return *entity;
}
