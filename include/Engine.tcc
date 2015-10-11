#ifndef ENGINE_TCC_INCLUDED
#define ENGINE_TCC_INCLUDED

namespace ECS
{
    template<class T, class ...Args>
    const T& Engine::AddSystem(const Args&... args)
    {
        static_assert(std::is_base_of<System, T>(), "Systems must derive from System class.");
        T* system = new T(args...);
        systems.push_back(system);
        return *system;
    }

    template<class T, class ...Args>
    void Engine::EmitEvent(Args&... args)
    {
        static_assert(std::is_base_of<Event, T>(), "Engine could only emit Event.");
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
        static_assert(std::is_base_of<Component, T>(), "A ComponentMapper can only hold components.");
        std::type_index index(typeid(ComponentMapper<T>));
        if (mappers.find(index) == mappers.end())
            mappers[index] = new ComponentMapper<T>();
        return *static_cast<ComponentMapper<T>*>(mappers.at(index));
    }
}

#endif // ENGINE_TCC_INCLUDED
