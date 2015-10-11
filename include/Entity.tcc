#ifndef ENTITY_TCC_INCLUDED
#define ENTITY_TCC_INCLUDED

namespace ECS
{
    template<class T, class ...Args>
    T& Entity::AddComponent(const Args&... args)
    {
        static_assert(std::is_base_of<Component, T>(), "An Entity can only have components.");
        return engine->GetComponentMapper<T>().AddComponent(uuid);
    }

    template<class T>
    T& Entity::GetComponent()const
    {
        static_assert(std::is_base_of<Component, T>(), "An Entity can only have components.");
        return engine->GetComponentMapper<T>().GetComponent(uuid);
    }

    template<class T>
    bool Entity::Has()const
    {
        static_assert(std::is_base_of<Component, T>(), "An Entity can only have components.");
        return engine->GetComponentMapper<T>().HasComponent(uuid);
    }

    template<class T, class ...Types>
    bool Entity::HasAllOf()const
    {
        static_assert(std::is_base_of<Component, T>(), "An Entity can only have components.");
        if (std::is_same<T, Component>())
            return true;
        return engine->GetComponentMapper<T>().HasComponent(uuid) && HasAllOf<Types..., Component>();
    }

    template<class T, class ...Types>
    bool Entity::HasNoneOf()const
    {
        static_assert(std::is_base_of<Component, T>(), "An Entity can only have components.");
        return !HasOneOf<T, Types...>();
    }

    template<class T>
    bool Entity::HasNot()const
    {
        return !Has<T>();
    }

    template<class T, class ...Types>
    bool Entity::HasOneOf()const
    {
        static_assert(std::is_base_of<Component, T>(), "An Entity can only have components.");
        if (std::is_same<T, Component>())
            return false;
        return engine->GetComponentMapper<T>().HasComponent(uuid) || HasOneOf<Types..., Component>();
    }

    template<class T>
    void Entity::RemoveComponent()
    {
        static_assert(std::is_base_of<Component, T>(), "Can't remove non-component type from Entity.");
        engine->GetComponentMapper<T>().RemoveComponent(uuid);;
    }
}

#endif // ENTITY_TCC_INCLUDED
