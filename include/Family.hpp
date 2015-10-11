#ifndef FAMILY_HPP
#define FAMILY_HPP

#include <type_traits>
#include <vector>
#include "Entity.hpp"

namespace ECS
{
    class Family final
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
                virtual bool operator()(const Entity& entity)const;
        };

        template<class T, class ...Types>
        class ConditionHasAllOf : public ICondition
        {
            public:
                virtual bool operator()(const Entity& entity)const;
        };

        template<class T, class ...Types>
        class ConditionHasNoneOf : public ICondition
        {
            public:
                virtual bool operator()(const Entity& entity)const;
        };

        template<class T>
        class ConditionHasNot : public ICondition
        {
            public:
                virtual bool operator()(const Entity& entity)const;
        };

        template<class T, class ...Types>
        class ConditionHasOneOf : public ICondition
        {
            public:
                virtual bool operator()(const Entity& entity)const;
        };

        public:
            typedef std::vector<Entity>::iterator iterator;

            Family();
            virtual ~Family();

            bool AddEntity(Entity& entity);
            void AddEntities(const std::vector<Entity>& entitiesToAdd);
            iterator begin();
            iterator end();

            template<class T>
            Family& Has();

            template<class T, class ...Types>
            Family& HasAllOf();

            template<class T, class ...Types>
            Family& HasNoneOf();

            template<class T>
            Family& HasNot();

            template<class T, class ...Types>
            Family& HasOneOf();
            bool RemoveEntity(const Entity& entity);
            void RemoveEntities(const std::vector<Entity>& entitiesToRemove);
            std::size_t size()const;
        private:
            template<class T>
            void AddCondition();

            std::vector<ICondition*> conditions;
            std::vector<Entity> entities;
    };
}

#include "Family.tcc"

#endif // FAMILY_HPP
