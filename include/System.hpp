#ifndef SYSTEM_HPP
#define SYSTEM_HPP

namespace ECS
{
    class Engine;

    class System
    {
        public:
            virtual ~System() = default;
            virtual void Init() = 0;
            virtual void Update(const float deltaTime) = 0;
        protected:
            System(Engine& engine) : engine(&engine) {}
            Engine* engine;
        private:
            System() = delete;
    };
}

#endif // SYSTEM_HPP
