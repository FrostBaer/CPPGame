#include "gui.h"

Hero* Screen::MyHero;

bool ScreenMatrix::sameElement(int e){
    for(size_t i = 0; i < clicked.size(); i++)
        if(clicked[i] == e)
            return true;
    return false;
}

void ScreenInfo::draw(){
    Graphics::getInstance().drawInfo();
}

void ScreenFightInfo::draw(){
    if(Gui::getInstance().getS5().getFirst()){
        Hero* h = &(getHero()->createOpponent());
        Gui::getInstance().getS3().setOpp(h);
        Graphics::getInstance().drawFightInfo(*(getHero()->heroToString()), *(Gui::getInstance().getS3().getOpp().heroToString()));
        Gui::getInstance().getS5().setFirst(false);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
        Graphics::screenCnt = 3;
    }
}

void ScreenNewHero::draw(){
    Graphics::getInstance().drawNewHero();

    if(Graphics::getInstance().mousePressedOnSprite(Graphics::getInstance().getWarrior()->getPosition())){
        std::cout << "New Warrior created!" << std::endl;
        Warrior* h = new Warrior;
        setHero(h);
        Graphics::getInstance().screenCnt = 1;
        return;
    }
    if(Graphics::getInstance().mousePressedOnSprite(Graphics::getInstance().getWizard()->getPosition())){
        std::cout << "New Wizard created!" << std::endl;
        Wizard* h = new Wizard;
        setHero(h);
        Graphics::getInstance().screenCnt = 1;
        return;
    }
    if(Graphics::getInstance().mousePressedOnSprite(Graphics::getInstance().getAssassin()->getPosition())){
        std::cout << "New Assassin created!" << std::endl;
        Assassin* h = new Assassin;
        setHero(h);
        Graphics::getInstance().screenCnt = 1;
        return;
    }
}

void ScreenHeroMenu::draw(){
    Graphics::getInstance().drawHeroMenu(*(getHero()->heroToString()));
    if(Graphics::getInstance().mousePressedOnSprite(Graphics::getInstance().getMatrix()->getPosition())){
        std::cout << "Creating matrix.." << std::endl;
        Graphics::getInstance().screenCnt = 2;
        return;
    }
    if(Graphics::getInstance().mousePressedOnSprite(Graphics::getInstance().getAttack()->getPosition())){
        std::cout << "Creating fight.." << std::endl;
        Graphics::getInstance().screenCnt = 5;
        return;
    }
    if(Graphics::getInstance().mousePressedOnSprite(Graphics::getInstance().getInfo()->getPosition())){
        Graphics::getInstance().screenCnt = 4;
        return;
    }
}

void ScreenMatrix::draw(){
    if(Gui::getInstance().getS2().getFirst()){
        Matrix* mat = new Matrix(4);
        setMatrix(mat);
        Graphics::getInstance().drawMatrix(*mx);
        Gui::getInstance().getS2().setFirst(false);
//        std::cout<<"Matrix: "<<std::endl;
//        mx->draw(mx->getM());
//        std::cout<<"Graf: "<<std::endl;
//        mx->draw(mx->getGraph());
//        std::cout<<"Ptr: "<<std::endl;
//        mx->draw(mx->getPtr());
    }

    if(getNewTiles()){
    //azok a mátrixbeli elemek, amik megegyeznek a clickedben tároltakkal
    //legyenek újragenerálva, rajzoljuk ki
        setNewTiles(false);
        for(size_t i = 0; i < getClicked().size(); i++){
            getMx()->newTile(getClicked()[i]);
        }
        getClicked().clear();

        Matrix* mat = new Matrix(*mx);
        setMatrix(mat);
        Graphics::getInstance().drawMatrix(*mx);

//        std::cout<<"Uj matrix: "<<std::endl;
//        getMx()->draw(getMx()->getM());
//        std::cout<<"Uj graph: "<<std::endl;
//        getMx()->draw(getMx()->getGraph());
//        std::cout<<"Uj ptr: "<<std::endl;
//        getMx()->draw(getMx()->getPtr());
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
    //a clicked tárolót ürítsük, newTiles = true,
    //ahány db volt, annyi megfelelő resource-ot adjunk a hero-nak
        if(getClicked().size() < 3)
            std::cout<<"Choose 3 tiles!"<<std::endl;
        else{
            //std::cout<<"Enter"<<std::endl;
            setNewTiles(true);
            switch(clickedType){
                case(ResCodes::RES_WEAPON):
                    getHero()->setWeapon(getHero()->getWeapon()+getClicked().size());
                break;
                case(ResCodes::RES_RUNE):
                    getHero()->setRune(getHero()->getRune()+(getClicked().size()*100));
                break;
                case(ResCodes::RES_POTION):
                    getHero()->setPotion(getHero()->getPotion()+(getClicked().size()*1000));
                break;
            }
        }
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        sf::Vector2i mousePos = sf::Mouse::getPosition(*Graphics::window);
        for(size_t i = 0; i < Gui::getInstance().getS2().positions.size(); i++){
            if(Graphics::getInstance().mousePressedOnSprite(Gui::getInstance().getS2().positions[i], mousePos)){
                clickedType = mx->getM()[i];
                switch(mx->getM()[i]){
                    case(ResCodes::RES_WEAPON):
                        //std::cout<<"Clicked on Weapon!"<<std::endl;
                        //az elem mátrixbeli sorszámát dobjuk a clicked-be (vector<int>)
                        setClicked(i);
                        break;
                    case(ResCodes::RES_POTION):
                        //std::cout<<"Clicked on Potion!"<<std::endl;
                        setClicked(i);
                        break;
                    case(ResCodes::RES_RUNE):
                        //std::cout<<"Clicked on Rune!"<<std::endl;
                        setClicked(i);
                        break;
                    default:
                        std::cout<<"ScreenMatrix::draw hiba!"<<std::endl;
                }
            }
        }
    }
}

void ScreenFight::draw(){
    if(Gui::getInstance().getS3().getFirst()){
        getHero()->fightResults(getOpp());
        if(getHero()->getWinner() >= 3 ){
            getHero()->levelUp();
        }
    Gui::getInstance().getS3().setFirst(false);
    }
}
