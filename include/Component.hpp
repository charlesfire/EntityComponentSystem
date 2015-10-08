#ifndef COMPONENT_HPP
#define COMPONENT_HPP

namespace ECS
{
    class Component
    {
        public:
            virtual ~Component() = default;
        protected:
            Component() = default;
    };
}

#endif // COMPONENT_HPP
