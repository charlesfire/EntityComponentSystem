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
	    conditions.push_back(new ConditionHas<T>());
	    return *this;
	}

	template<class T, class ...Types>
	Family& Family::HasAllOf()
	{
	    conditions.push_back(new ConditionHasAllOf<T, Types...>());
	    return *this;
	}

	template<class T, class ...Types>
	Family& Family::HasNoneOf()
	{

	    conditions.push_back(new ConditionHasNoneOf<T, Types...>());
	    return *this;
	}

	template<class T>
	Family& Family::HasNot()
	{
	    conditions.push_back(new ConditionHasNot<T>());
	    return *this;
	}

	template<class T, class ...Types>
	Family& Family::HasOneOf()
	{
	    conditions.push_back(new ConditionHasOneOf<T, Types...>());
	    return *this;
	}
}

#endif // FAMILY_TCC_INCLUDED
