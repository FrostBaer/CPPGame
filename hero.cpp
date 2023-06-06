#include <iostream>
#include <sstream> //intToString miatt
#include "hero.h"


//a kivételkezelést bent hagyom, hogy lássam, melyik resource-ról van szó
void Hero::setLevel(int _current) {
     level.setCurrent(_current);
//    catch (const char* exc){
//        std::cerr << "Exception in " << __FILE__ << " \tline: "<< __LINE__ <<"\nException text: "<< exc << std::endl;
//    }
}

void Hero::setWeapon(int _current) {
    weapon.setCurrent(_current);
//    catch (const char* exc){
//        std::cerr << "Exception in " << __FILE__ << " \tline: "<< __LINE__ <<"\nException text: "<< exc << std::endl;
//    }
}

void Hero::setRune(int _current) {
    rune.setCurrent(_current);
//    catch (const char* exc){
//        std::cerr << "Exception in " << __FILE__ << " \tline: "<< __LINE__ <<"\nException text: "<< exc << std::endl;
//    }
}

void Hero::setPotion(int _current) {
    potion.setCurrent(_current);
//    catch (const char* exc){
//        std::cerr << "Exception in " << __FILE__ << " \tline: "<< __LINE__ <<"\nException text: "<< exc << std::endl;
//    }
}

void Hero::setGold(int _current) {
    gold.setCurrent(_current);
//    catch (const char* exc){
//        std::cerr << "Exception in " << __FILE__ << " \tline: "<< __LINE__ <<"\nException text: "<< exc << std::endl;
//    }
}


Hero& Hero::createOpponent(){
    int n = rand()%3;
    Hero* op;
    switch(n){
    case 0:
        op = new Wizard;
        break;
    case 1:
        op = new Warrior;
        break;
    case 2:
        op = new Assassin;
        break;
    }

    op->setLevel(this->getLevel());
    op->setGold(this->getGold()+100);
    op->setWeapon(op->getWeapon() + op->getLevel()*2*((rand()%5+5)*0.1)); //+2 maxweapon/lvl
    op->setRune((op->getRune() + op->getLevel()*200)*((rand()%5+5)*0.1)); //+200 maxrune/lvl
    op->setPotion((op->getPotion() + op->getLevel()*2000)*((rand()%5+5)*0.1)); //+2000 maxPotion/lvl

    return *op;
}

void Hero::attack(Hero& h1, Hero& h2){
    h2.setPotion(h2.getPotion()-h1.getRune());
    h1.setWeapon(h1.getWeapon()-1);
    std::cout << h2.getName() << "'s potion: "<< h2.getPotion() <<std::endl;
}

void Hero::turn(Hero& h1, Hero& h2){
    if(h1.getWeapon() == 0){
        throw FightError::EXC_WEAPON;
    }

    Hero::attack(h1, h2);
    if(h2.getPotion() <= 0){
        throw FightError::EXC_WINNER;
    }
}

Hero* Hero::fight(Hero& h){
//    if (this->getPotion() == 0 || h.getPotion() == 0)
//        throw "Error, potion can not be 0!";
    //az alacsonyabb szintű hős kezd
    Hero* h1 = new Hero;
    h1 = this->getLevel() < h.getLevel() ? this : &h;
    Hero* h2 = new Hero;
    h2 = this->getLevel() < h.getLevel() ? &h : this;
    std::cout << h1->getName() << "'s rune: " << h1->getRune() << std::endl;
    std::cout << h2->getName() << "'s rune: " << h2->getRune() << std::endl;

    while( h1->getWeapon() != 0 || h2->getWeapon() != 0 ){
        std::cout <<"\n"<< h1->getName()<< "'s turn" << std::endl;
        try{ turn(*h1, *h2); }
        catch(int exc){
            if(exc == 0) { std::cout << h1->getName()<<"'s weapon: "<< h1->getWeapon() <<std::endl; }
            if(exc == 1)
                return h1;
        }
        std::cout <<"\n"<< h2->getName()<< "'s turn" << std::endl;
        try{ turn(*h2, *h1); }
        catch(int exc){
            if(exc == 0) { std::cout << h2->getName()<<"'s weapon: "<< h2->getWeapon() <<std::endl; }
            if(exc == 1)
                return h2;
        }
    }
    throw FightError::EXC_BOTH;
 }

 void Hero::fightResults(Hero& h){
    if(this != &h){
        try{
            Graphics::getInstance().drawFight(*this->sp, *h.sp);

            Hero* winner = this->fight(h);
            if( winner == this ){
                Graphics::getInstance().drawResult(1);
                this->setGold(this->getGold()+h.getGold()*0.2);
                this->winner++;
                h.setGold(h.getGold()*0.8);
                }

            else if( winner == &h ){
                Graphics::getInstance().drawResult(2);
                h.setGold(h.getGold()+this->getGold()*0.2);
                h.winner++;
                this->setGold(this->getGold()*0.8);
            }
            std::cout << "The winner is "<< winner->getName()<<std::endl;
            this->setRune(this->getRune()*0.75);
            h.setRune(h.getRune()*0.75);
        }
        catch(const char* exc){
            std::cerr << exc <<std::endl;
        }
        catch(int){
            Graphics::getInstance().drawResult(0);
            std::cout<< "The fight is over, nobody has died!" <<std::endl;
            this->setRune(this->getRune()*0.75);
            h.setRune(h.getRune()*0.75);
        }
    }
 }

void Hero::levelUp(){
    setLevel(getLevel()+1);
    setMaxWeapon( getMaxWeapon()+2 );
    setMaxRune( getMaxRune()+20 );
    setMaxPotion( getMaxPotion()+200 );
    setGold(gold.getCurrent()+2000);
    if(getLevel()<=10){
        setWeapon(weapon.getMax());
        setRune(rune.getMax());
        setPotion(potion.getMax());
    }
    setWinner(0);
}

 std::string Hero::IntToString( int Number ){ ///Ez a fgv a stackoverflowról származik
     std::ostringstream os;
     os << Number;
     return os.str();
}

 std::vector<std::string>* Hero::heroToString(){
    std::vector<std::string> *s = new std::vector<std::string>;
    s->push_back(IntToString(this->getLevel()));
    s->push_back(IntToString(this->getWeapon()));
    s->push_back(IntToString(this->getRune()));
    s->push_back(IntToString(this->getPotion()));
    s->push_back(IntToString(this->getGold()));
    s->push_back(this->getName());
    return s;
 }
