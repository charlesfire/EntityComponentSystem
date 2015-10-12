#ifndef COMPONENTMAPPER_TCC_INCLUDED
#define COMPONENTMAPPER_TCC_INCLUDED

namespace ECS
{
    template<class T> template<class ...Types>
    T& ComponentMapper<T>::AddComponent(const unsigned int uuid, const Types&... args)
    {
        if (!componentsMap.count(uuid))
            componentsMap[uuid] = T(&args...);
        return componentsMap.at(uuid);
    }

    template<class T>
    T& ComponentMapper<T>::GetComponent(unsigned int uuid)const
    {
        return componentsMap.at(uuid);
    }

    template<class T>
    bool ComponentMapper<T>::HasComponent(const unsigned int uuid)const
    {
        return componentsMap.count(uuid);
    }

    template<class T>
    void ComponentMapper<T>::RemoveComponent(const unsigned int uuid)
    {
        componentsMap.erase(uuid);
    }
}

#endif // COMPONENTMAPPER_TCC_INCLUDED
