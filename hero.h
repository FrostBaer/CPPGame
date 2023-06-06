#ifndef HERO_H_INCLUDED
#define HERO_H_INCLUDED
#include <string.h>
#include "resource.h"
#include "graphics.h"

class FightError{
public:
    static const int EXC_WEAPON = 0;
    static const int EXC_WINNER = 1;
    static const int EXC_BOTH = 2;
};

class Hero{
protected:
    Resource level;
    Resource weapon;
    Resource rune;
    Resource potion;
    Resource gold;
    int winner;
    std::string name;
    sf::Sprite* sp;

public:
    //constructor
    Hero(int _w = 0, int _r = 0, int _p = 0, std::string _d = "", sf::Sprite* _sp = NULL)
        : level(100, 1), weapon( _w, _w), rune( _r, _r), potion( _p, _p), gold(1000000), winner(0), name(_d){
        this->sp = _sp;
        printf("Hero created!");
    }

    //destructor
    virtual ~Hero(){ printf("Hero deleted\n"); }

    //getters
    int getLevel() { return level.getCurrent(); }
    int getMaxLevel() { return level.getMax(); }
    int getWeapon() { return weapon.getCurrent(); }
    int getMaxWeapon() { return weapon.getMax(); }
    int getRune() { return rune.getCurrent(); }
    int getMaxRune() { return rune.getMax(); }
    int getPotion() { return potion.getCurrent(); }
    int getMaxPotion() { return potion.getMax(); }
    int getGold() { return gold.getCurrent(); }
    int getMaxGold() { return gold.getMax(); }
    int getWinner() { return winner; }
    std::string getName() { return name; }
    sf::Sprite* getSprite() { return sp; }

    //setters
    void setLevel(int _current);
    void setWeapon(int _current);
    void setMaxWeapon (int m) { weapon.setMax( m ); }
    void setRune(int _current);
    void setMaxRune (int m) { rune.setMax( m ); }
    void setPotion(int _current);
    void setMaxPotion (int m) { potion.setMax( m ); }
    void setGold(int _current);
    void setWinner(int i) { winner = i; }
    void setName(std::string _desc) { name = _desc; }

    //hero interactions
    std::string IntToString ( int Number );
    std::vector<std::string>* heroToString();
    Hero& createOpponent();
    void createFight();
    Hero* fight(Hero& h);
    void attack(Hero& h1, Hero& h2);
    void turn(Hero& h1, Hero& h2);
    void fightResults(Hero& h);
    void levelUp();
};

class Wizard:public Hero{
public:
    Wizard():Hero(10, 2000, 8000, "Wizard", Graphics::getInstance().getWizard()){}
};

class Warrior:public Hero{
public:
    Warrior():Hero(10, 1500, 10000, "Warrior", Graphics::getInstance().getWarrior()){}
};

class Assassin:public Hero{
public:
    Assassin():Hero(10, 1000, 15000, "Assassin", Graphics::getInstance().getAssassin()){}
};
#endif // HERO_H_INCLUDED
