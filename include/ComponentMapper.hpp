#ifndef COMPONENTMAPPER_HPP
#define COMPONENTMAPPER_HPP

#include <type_traits>
#include <unordered_map>

namespace ECS
{
    class Component;

    class IComponentMapper
    {
        public:
            virtual ~IComponentMapper() = default;
        protected:
            IComponentMapper() = default;
    };

    template<class T>
    class ComponentMapper final
    {
        static_assert(std::is_base_of<Component, T>(), "A ComponentMapper can only hold components.");
        public:
            ComponentMapper() : componentsMap() {}
            virtual ~ComponentMapper() = default;

            template<class ...Types>
            T& AddComponent(const unsigned int uuid, const Types&... args);
            T& GetComponent(unsigned int uuid)const;
            bool HasComponent(const unsigned int uuid)const;
            void RemoveComponent(const unsigned int uuid);
        private:
            std::unordered_map<unsigned int, T> componentsMap;
    };
}

#include "ComponentMapper.tcc"

#endif // COMPONENTMAPPER_HPP
