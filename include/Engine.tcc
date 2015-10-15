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
        auto it = listeners.find(std::type_index(typeid(T)));
        if (it == listeners.end())
            return;

        T event(args...);
        for (auto listener : it->second)
            dynamic_cast<EventListener<T>*>(listener)->Listen(event);
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
        std::type_index index(typeid(T));
        auto it = listeners.find(index);
        if (it == listeners.end())
            it = listeners.insert(std::pair<std::type_index, std::vector<EventListener<>*>>(index, std::vector<EventListener<>*>())).first;

        auto insertPosition = std::lower_bound(it->second.begin(), it->second.end(), listener, [](const EventListener<>* first, const EventListener<>* second)
                                               {
                                                    return dynamic_cast<const EventListener<T>*>(first)->GetPriority() < dynamic_cast<const EventListener<T>*>(second)->GetPriority();
                                               });
        it->second.insert(insertPosition, listener);
    }
}

#endif // ENGINE_TCC_INCLUDED
