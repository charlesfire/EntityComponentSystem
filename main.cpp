#include <iostream>
#include <typeinfo>
#include "Engine.hpp"
#include "Entity.hpp"
#include "PrintEvent.hpp"
#include "PrintingSystem.hpp"
#include "PrintComponent.hpp"
#include "Family.hpp"

int main()
{
    try
    {
        ECS::Engine eng;
        PrintingSystem sys = eng.AddSystem<PrintingSystem>();
        ECS::Entity ent = eng.AddEntity();
        ECS::Entity ent2 = eng.AddEntity();
        ent2 = ent;
        PrintComponent printComp = ent.AddComponent<PrintComponent>();
        eng.AddEventListener(&sys);
        eng.EmitEvent<PrintEvent>();

        ECS::Family fam;
        fam.HasAllOf<PrintComponent>();
        fam.AddEntity(ent);
        std::cout << fam.size() << std::endl;
        fam.AddEntity(ent2);
        std::cout << fam.size() << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Error :" << std::endl;
        std::cout << e.what() << std::endl;
    }
    return 0;
}
