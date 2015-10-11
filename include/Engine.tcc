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
    ComponentMapper<T>& Engine::GetComponentMapper()
    {
        std::type_index index(typeid(ComponentMapper<T>));
        if (mappers.find(index) == mappers.end())
            mappers[index] = new ComponentMapper<T>();
        return *static_cast<ComponentMapper<T>*>(mappers.at(index));
    }
}

#endif // ENGINE_TCC_INCLUDED
