#include "Entity.hpp"

using namespace ECS;

unsigned int Entity::counter = 0;

Entity::Entity(Engine& engine) : uuid(Entity::counter++), engine(&engine)
{

}

unsigned int Entity::GetUUID()const
{
    return uuid;
}
