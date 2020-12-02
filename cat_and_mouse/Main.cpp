//#include <Actor.h>
//#include <Level.h>
//#include <Controller.h>
//#include <Shapes.h>
//#include <Common/Units.h>

//#include <SDL2/SDL_keycode.h>

//#include "Cat.h"
//#include "Mouse.h"

#include <iostream>

int main()
{

    std::cout << "hi";
    std::cin.get();
    return 0;
    /*Shared<Model> box = Cube(10, Color(1.0, 1.0, 1.0, 1.0));

    Cat cat = Cat(box);
    Mouse mouse = Mouse(box);

    Controller controller = Controller();
    controller.SetStickKeyboard("move", SDLK_w, SDLK_s, SDLK_d, SDLK_a);
    controller.BindStickX("move", cat, &Cat::OnRight);
    controller.BindStickY("move", cat, &Cat::OnUp);
    //Level lvl = Level(Cat);
    //lvl.Start();*/
}