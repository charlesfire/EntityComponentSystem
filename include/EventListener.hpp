#ifndef EVENTLISTENER_HPP
#define EVENTLISTENER_HPP

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
            virtual ~EventListener() = default;
            virtual void Listen(T& event) = 0;
            int GetPriority()const {return priority;}
        protected:
            int priority;
    };

    template<class T, class U, class ...Types>
    class EventListener<T, U, Types...> : public virtual EventListener<T>, public EventListener<U, Types...>
    {
        static_assert(std::is_base_of<Event, T>(), "An EventListener can only listen to events.");
        public:
            virtual ~EventListener() = default;
    };
}

#endif // EVENTLISTENER_HPP
