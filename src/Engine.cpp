#include "Engine.hpp"

#include <algorithm>
#include "Entity.hpp"
#include "EntityAddedEvent.hpp"
#include "EntityRemovedEvent.hpp"
#include "System.hpp"

using namespace ECS;

Engine::Engine() : entities(), listeners(), mappers(), systems()
{

}

Engine::~Engine()
{
    entities.clear();
    listeners.clear();
    for (auto mapperPair : mappers)
        delete mapperPair.second;
    mappers.clear();
    for (auto system : systems)
        delete system;
    systems.clear();
}

const Entity& Engine::AddEntity()
{
    entities.push_back(Entity(*this));
    Entity* addedEntity = &entities.at(entities.size() - 1);
    EmitEvent<EntityAddedEvent>(*addedEntity);
    return *addedEntity;
}

void Engine::Update(const float deltaTime)const
{
    for (auto system : systems)
        system->Update(deltaTime);
}

bool Engine::RemoveEntity(const Entity& entity)
{
    auto it = std::find(std::begin(entities), std::end(entities), entity);
    if (it != std::end(entities))
    {
        EmitEvent<EntityRemovedEvent>(*it);
        entities.erase(it);
        return true;
    }
    return false;
}

bool Engine::RemoveSystem(const System& system)
{
    auto it = std::find(std::begin(systems), std::end(systems), &system);
    if (it != std::end(systems))
    {
        delete *it;
        systems.erase(it);
        return true;
    }
    return false;
}
