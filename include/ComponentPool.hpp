#ifndef COMPONENTPOOL_HPP
#define COMPONENTPOOL_HPP

#include <type_traits>
#include <unordered_map>

namespace ECS
{
    class Component;
    class Entity;

    template<class T>
    class ComponentPool final
    {
        static_assert(std::is_base_of<Component, T>(), "A ComponentPool can only hold components.");
        public:
            template<class ...Types>
            T& AddComponent(const unsigned int uuid, const Types&... args)
            {
                if (!componentsMap.count(uuid))
                    componentsMap[uuid] = T(&args...);
                return componentsMap.at(uuid);
            }

            static ComponentPool<T>& GetInstance()
            {
                static ComponentPool<T> instance;
                return instance;
            }

            T& GetComponent(unsigned int uuid)const
            {
                return componentsMap.at(uuid);
            }

            bool HasComponent(const unsigned int uuid)const
            {
                return componentsMap.count(uuid);
            }

            void RemoveComponent(const unsigned int uuid)
            {
                componentsMap.remove(uuid);
            }

            ComponentPool<T>() : componentsMap() {}
            virtual ~ComponentPool() = default;
        private:
            std::unordered_map<unsigned int, T> componentsMap;
    };
}

#endif // COMPONENTPOOL_HPP
