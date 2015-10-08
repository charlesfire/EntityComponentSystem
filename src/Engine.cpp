#include "Engine.hpp"

#include <algorithm>
#include "Entity.hpp"
#include "System.hpp"

using namespace ECS;

Engine::Engine() : entities(), listeners(), systems()
{

}

Engine::~Engine()
{
    for (auto system : systems)
        delete system;
    systems.clear();
    for (auto entity : entities)
        delete entity;
    entities.clear();
}

const Entity& Engine::AddEntity()
{
    entities.push_back(new Entity(*this));
    return *entities.at(entities.size() - 1);
}

void Engine::AddEventListener(EventListener<>* listener)
{
    listeners.push_back(listener);
}

void Engine::Update(const float deltaTime)const
{
    for (auto system : systems)
        system->Update(deltaTime);
}

bool Engine::RemoveEntity(const Entity& entity)
{
    auto it = std::find(std::begin(entities), std::end(entities), &entity);
    if (it != std::end(entities))
    {
        delete *it;
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
