#include "ComponentAddedEvent.hpp"

#include "Entity.hpp"

using namespace ECS;

ComponentAddedEvent::ComponentAddedEvent(Component& addedComponent, const Entity& entity) : addedComponent(&addedComponent), entity(new Entity(entity))
{

}

ComponentAddedEvent::~ComponentAddedEvent()
{
    delete entity;
}

const Component& ComponentAddedEvent::GetAddedComponent()const
{
    return *addedComponent;
}

const Entity& ComponentAddedEvent::GetEntity()const
{
    return *entity;
}
