#ifndef EVENTLISTENER_HPP
#define EVENTLISTENER_HPP

#include <initializer_list>
#include <type_traits>

namespace ECS
{
    class Event;

    template<class ...Types>
    class EventListener
    {
        public:
            virtual ~EventListener() = default;
        protected:
            EventListener() = default;
    };

    template<class T>
    class EventListener<T> : public virtual EventListener<>
    {
        static_assert(std::is_base_of<Event, T>(), "An EventListener can only listen to events.");
        public:
            EventListener() : priority(0) {}
            EventListener(int priority) : priority(priority) {}
            virtual ~EventListener() = default;
            virtual void Listen(T& event) = 0;
            int GetPriority()const {return priority;}
        protected:
            void SetPriority(const int priority) {this->priority = priority;}
        private:
            int priority;
    };

    template<class T, class U, class ...Types>
    class EventListener<T, U, Types...> : public EventListener<T>, public EventListener<U, Types...>
    {
        static_assert(std::is_base_of<Event, T>(), "An EventListener can only listen to events.");
        public:
            EventListener();

            template<class ...Args>
            EventListener(int priority, Args... args) : EventListener<T>(priority), EventListener<U, Types...>(args...) {}
            virtual ~EventListener() = default;
    };
}

#endif // EVENTLISTENER_HPP
