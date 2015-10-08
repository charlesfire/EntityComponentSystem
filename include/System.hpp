#ifndef SYSTEM_HPP
#define SYSTEM_HPP

namespace ECS
{
    class System
    {
        public:
            virtual ~System() = default;
            virtual void Init() = 0;
            virtual void Update(const float deltaTime) = 0;
        protected:
            System() = default;
    };
}

#endif // SYSTEM_HPP
