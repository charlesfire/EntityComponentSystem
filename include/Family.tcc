#ifndef FAMILY_TCC_INCLUDED
#define FAMILY_TCC_INCLUDED

namespace ECS
{
    template<class T>
    bool Family::ConditionHas<T>::operator()(const Entity& entity)const
    {
        return entity.Has<T>();
    }

    template<class T, class ...Types>
    bool Family::ConditionHasAllOf<T, Types...>::operator()(const Entity& entity)const
	{
	    return entity.HasAllOf<T, Types...>();
	}

    template<class T, class ...Types>
    bool Family::ConditionHasNoneOf<T, Types...>::operator()(const Entity& entity)const
	{
	    return entity.HasNoneOf<T, Types...>();
	}

    template<class T>
    bool Family::ConditionHasNot<T>::operator()(const Entity& entity)const
	{
	    return entity.HasNot<T>();
	}

    template<class T, class ...Types>
    bool Family::ConditionHasOneOf<T, Types...>::operator()(const Entity& entity)const
	{
	    return entity.HasOneOf<T, Types...>();
	}

	template<class T>
	Family& Family::Has()
	{
	    AddCondition<ConditionHas<T>>();
	    return *this;
	}

	template<class T, class ...Types>
	Family& Family::HasAllOf()
	{
	    AddCondition<ConditionHasAllOf<T, Types...>>();
	    return *this;
	}

	template<class T, class ...Types>
	Family& Family::HasNoneOf()
	{
	    AddCondition<ConditionHasNoneOf<T, Types...>>();
	    return *this;
	}

	template<class T>
	Family& Family::HasNot()
	{
	    AddCondition<ConditionHasNot<T>>();
	    return *this;
	}

	template<class T, class ...Types>
	Family& Family::HasOneOf()
	{
	    AddCondition<ConditionHasOneOf<T, Types...>>();
	    return *this;
	}

	template<class T>
	void Family::AddCondition()
	{
	    static_assert(std::is_base_of<ICondition, T>(), "Condition must inherit from ICondition.");
	    conditions.push_back(new T());
	    ICondition* condition = conditions.at(conditions.size() - 1);
	    for (auto entity : entities)
            if (!(*condition)(entity))
                RemoveEntity(entity);
	}
}

#endif // FAMILY_TCC_INCLUDED
