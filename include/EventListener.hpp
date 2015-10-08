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

    template<class T, class ...Types>
    class EventListener<T, Types...> : public EventListener<Types...>
    {
        static_assert(std::is_base_of<Event, T>(), "An EventListener can only listen to events.");
        public:
            virtual ~EventListener() = default;
            virtual void Listen(T& event) = 0;
    };
}

#endif // EVENTLISTENER_HPP
