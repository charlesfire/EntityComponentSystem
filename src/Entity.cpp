#include "Entity.hpp"

using namespace ECS;

unsigned int Entity::counter = 0;

Entity::Entity(Engine& engine) : engine(&engine), uuid(Entity::counter++)
{

}

Entity::Entity(const Entity& other) : engine(other.engine), uuid(other.uuid)
{

}

unsigned int Entity::GetUUID()const
{
    return uuid;
}

Entity& Entity::operator=(const Entity& other)
{
    engine = other.engine;
    uuid = other.uuid;
    return *this;
}


bool Entity::operator==(const Entity& other)
{
    return uuid == other.uuid;
}
