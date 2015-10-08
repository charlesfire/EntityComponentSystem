#include "EntityFamily.hpp"

#include <algorithm>
#include "Entity.hpp"

using namespace ECS;

EntityFamily::EntityFamily() : conditions(), entities()
{

}

EntityFamily::~EntityFamily()
{
    for (auto condition : conditions)
        delete condition;
    conditions.clear();
}

bool EntityFamily::AddEntity(Entity& entity)
{
    auto it = std::find(std::begin(entities), std::end(entities), &entity);
    if (it != std::end(entities))
        return false;
    for (auto condition : conditions)
        if (!(*condition)(entity))
            return false;
    entities.push_back(&entity);
    return true;
}

bool EntityFamily::RemoveEntity(const Entity& entity)
{
    auto it = std::find(std::begin(entities), std::end(entities), &entity);
    if (it != std::end(entities))
    {
        entities.erase(it);
        return true;
    }
    return false;
}

size_t EntityFamily::size()const
{
    return entities.size();
}

