#ifndef ENGINE_TCC_INCLUDED
#define ENGINE_TCC_INCLUDED

namespace ECS
{
    template<class T, class ...Args>
    const T& Engine::AddSystem(const Args&... args)
    {
        T* system = new T(args...);
        systems.push_back(system);
        return *system;
    }

    template<class T, class ...Args>
    void Engine::EmitEvent(const Args&... args)
    {
        T event(args...);
        for (auto listener : listeners)
        {
            EventListener<T>* castedListener = dynamic_cast<EventListener<T>*>(listener);
            if (castedListener != nullptr)
                castedListener->Listen(event);
        }
    }

    template<class T>
    ComponentMapper<T>& Engine::GetComponentMapper(const Entity& entity)const
    {
        if (std::find(entities.begin(), entities.end(), entity) == entities.end())
            throw 1; //ToDo : Add exception...

        auto type = typeid(ComponentMapper<T>);
        if (mappers.find(&type) == mappers.end())
            mappers.insert(type, ComponentMapper<T>());
        return *static_cast<ComponentMapper<T>*>(mappers.at(&type));
    }
}

#endif // ENGINE_TCC_INCLUDED
