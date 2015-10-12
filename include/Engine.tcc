#ifndef ENGINE_TCC_INCLUDED
#define ENGINE_TCC_INCLUDED

namespace ECS
{
    template<class T, class ...Args>
    const T& Engine::AddSystem(const Args&... args)
    {
        static_assert(std::is_base_of<System, T>(), "Systems must derive from System class.");
        T* system = new T(args..., *this);
        systems.push_back(system);
        system->Init();
        return *system;
    }

    template<class T, class ...Args>
    void Engine::EmitEvent(Args&... args)
    {
        static_assert(std::is_base_of<Event, T>(), "Engine could only emit Event.");
        T event(args...);
        auto range = listeners.equal_range(std::type_index(typeid(T)));
        for (auto it(range.first); it != range.second; it++)
            dynamic_cast<EventListener<T>*>(it->second)->Listen(event);
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

    template<class T>
    void Engine::RegisterEventListener(EventListener<T>* listener)
    {
        listeners.insert(std::pair<std::type_index, EventListener<>*>(std::type_index(typeid(T)), listener));
    }
}

#endif // ENGINE_TCC_INCLUDED
