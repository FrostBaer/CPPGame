#include <iostream>
#include <stdlib.h> //rand, srand
#include <time.h>
#include <SFML/Graphics.hpp>
#include "hero.h"
#include "matrix.h"
#include "graphics.h"
#include "gui.h"

int main()
{
    srand(time(NULL));
    Graphics::getInstance();
    Gui::getInstance();

    while(Graphics::window->isOpen()){
        sf::Event event;
        while(Graphics::window->pollEvent(event)){
            if((event.type == sf::Event::Closed) || Graphics::screenCnt == -1){
            Graphics::window->close();
            }
            if(Graphics::screenCnt == 0){
                Gui::getInstance().getS0().draw();
            }
            if(Graphics::screenCnt == 1 ){
                Gui::getInstance().getS1().draw();
            }
            if(Graphics::screenCnt == 2 ){
                Gui::getInstance().getS2().draw();
            }
            if(Graphics::screenCnt == 3){
                Gui::getInstance().getS3().draw();
            }
            if(Graphics::screenCnt == 4){
                Gui::getInstance().getS4().draw();
            }
            if(Graphics::screenCnt == 5){
                Gui::getInstance().getS5().draw();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && (Graphics::screenCnt != 0 && Graphics::screenCnt != 1)){
                Gui::getInstance().getS2().setFirst(true);
                Gui::getInstance().getS3().setFirst(true);
                Gui::getInstance().getS5().setFirst(true);
                Graphics::screenCnt = 1;
            }
        }
    }

    return 0;
}
