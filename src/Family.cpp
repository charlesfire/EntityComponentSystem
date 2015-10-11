#include "Family.hpp"

#include <algorithm>
#include "Entity.hpp"

using namespace ECS;

Family::Family() : conditions(), entities()
{

}

Family::~Family()
{
    for (auto condition : conditions)
        delete condition;
    conditions.clear();
}

bool Family::AddEntity(Entity& entity)
{
    auto it = std::find(std::begin(entities), std::end(entities), entity);
    if (it != std::end(entities))
        return false;
    for (auto condition : conditions)
        if (!(*condition)(entity))
            return false;
    entities.push_back(entity);
    return true;
}

void Family::AddEntities(const std::vector<Entity>& entitiesToAdd)
{
    for (auto entity : entitiesToAdd)
        AddEntity(entity);
}

Family::iterator Family::begin()
{
    return entities.begin();
}

Family::iterator Family::end()
{
    return entities.end();
}

bool Family::RemoveEntity(const Entity& entity)
{
    auto it = std::find(std::begin(entities), std::end(entities), entity);
    if (it != std::end(entities))
    {
        entities.erase(it);
        return true;
    }
    return false;
}

void Family::RemoveEntities(const std::vector<Entity>& entitiesToRemove)
{
    for (auto entity : entitiesToRemove)
        RemoveEntity(entity);
}

size_t Family::size()const
{
    return entities.size();
}

