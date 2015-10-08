#ifndef ENTITYFAMILY_HPP
#define ENTITYFAMILY_HPP

#include <vector>
#include "Entity.hpp"

namespace ECS
{
    class EntityFamily final
    {
        class ICondition
        {
            public:
                virtual ~ICondition() = default;
                virtual bool operator()(const Entity& entity)const = 0;
        };

        template<class T>
        class ConditionHas : public ICondition
        {
            public:
                virtual bool operator()(const Entity& entity)const
                {
                    return entity.Has<T>();
                }
        };

        template<class T, class ...Types>
        class ConditionHasAllOf : public ICondition
        {
            public:
                virtual bool operator()(const Entity& entity)const
                {
                    return entity.HasAllOf<T, Types...>();
                }
        };

        template<class T, class ...Types>
        class ConditionHasNoneOf : public ICondition
        {
            public:
                virtual bool operator()(const Entity& entity)const
                {
                    return entity.HasNoneOf<T, Types...>();
                }
        };

        template<class T>
        class ConditionHasNot : public ICondition
        {
            public:
                virtual bool operator()(const Entity& entity)const
                {
                    return entity.HasNot<T>();
                }
        };

        template<class T, class ...Types>
        class ConditionHasOneOf : public ICondition
        {
            public:
                virtual bool operator()(const Entity& entity)const
                {
                    return entity.HasOneOf<T, Types...>();
                }
        };

        public:
            EntityFamily();
            virtual ~EntityFamily();

            bool AddEntity(Entity& entity);

            template<class T>
            EntityFamily& Has()
            {
                conditions.push_back(new ConditionHas<T>());
                return *this;
            }

            template<class T, class ...Types>
            EntityFamily& HasAllOf()
            {
                conditions.push_back(new ConditionHasAllOf<T, Types...>());
                return *this;
            }

            template<class T, class ...Types>
            EntityFamily& HasNoneOf()
            {

                conditions.push_back(new ConditionHasNoneOf<T, Types...>());
                return *this;
            }

            template<class T>
            EntityFamily& HasNot()
            {
                conditions.push_back(new ConditionHasNot<T>());
                return *this;
            }

            template<class T, class ...Types>
            EntityFamily& HasOneOf()
            {
                conditions.push_back(new ConditionHasOneOf<T, Types...>());
                return *this;
            }

            bool RemoveEntity(const Entity& entity);
            std::size_t size()const;
        private:
            std::vector<ICondition*> conditions;
            std::vector<Entity*> entities;
    };
}

#endif // ENTITYFAMILY_HPP
