#include <iostream>
#include <typeinfo>
#include <map>
#include <algorithm>
#include <set>
#include "Engine.hpp"
#include "Entity.hpp"
#include "PrintEvent.hpp"
#include "PrintingSystem.hpp"
#include "PrintComponent.hpp"
#include "Family.hpp"

struct IntHolder
{
    IntHolder(int i) : i(i) {}
    int i;
    inline bool operator<(const IntHolder& other)
    {
        return i < other.i;
    }
    friend bool operator<(const IntHolder& first, const IntHolder& second)
    {
        return first.i < second.i;
    }
};

int main()
{
    try
    {
        ECS::Engine eng;
        PrintingSystem sys = eng.AddSystem<PrintingSystem>();
        ECS::Entity ent = eng.AddEntity();
        ECS::Entity ent2 = eng.AddEntity();
        PrintComponent printComp = ent.AddComponent<PrintComponent>();
        eng.EmitEvent<PrintEvent>();

        ECS::Family fam;
        fam.AddEntity(ent);
        std::cout << fam.size() << std::endl;
        fam.AddEntity(ent2);
        std::cout << fam.size() << std::endl;
        fam.HasAllOf<PrintComponent>();
        std::cout << fam.size() << std::endl;

        ent.RemoveComponent<PrintComponent>();
        /*std::set<IntHolder> test;
        test.insert(IntHolder(1));
        test.insert(IntHolder(10));
        test.insert(IntHolder(13));
        test.insert(IntHolder(12));
        test.insert(IntHolder(15));
        test.insert(IntHolder(11));
        for (auto it : test)
            std::cout << it.i << std::endl;*/
    }
    catch (std::exception& e)
    {
        std::cout << "Error :" << std::endl;
        std::cout << e.what() << std::endl;
    }
    return 0;
}
