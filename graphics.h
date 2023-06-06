#ifndef GRAP_H_INCLUDED
#define GRAP_H_INCLUDED
#include <iostream>
#include <string.h>
#include <SFML/Graphics.hpp>
#include "matrix.h"

///singleton design pattern innen: https://stackoverflow.com/questions/1008019/c-singleton-design-pattern

class Containers {
public:
    static std::vector<sf::Sprite*> sResources;
    static std::vector<sf::Sprite*> sHeroes;
    static std::vector<sf::Sprite*> sInteractions;
    static std::vector<sf::Sprite*> sSmall;
    static std::vector<sf::Sprite*> sColor;
};

class Graphics{
private:
    sf::Sprite* sWeapon;
    sf::Sprite* sPotion;
    sf::Sprite* sRune;
    sf::Sprite* sGold;
    sf::Sprite* sLevel;
    sf::Sprite* sAssassin;
    sf::Sprite* sWizard;
    sf::Sprite* sWarrior;
    sf::Sprite* sAttack;
    sf::Sprite* sMatrix;
    sf::Sprite* sWin;
    sf::Sprite* sLose;
    sf::Sprite* sTie;
    sf::Sprite* sInfo;
    sf::Sprite* sWeapon2;
    sf::Sprite* sPotion2;
    sf::Sprite* sRune2;
    sf::Sprite* sSLevel;
    sf::Sprite* sSWeapon;
    sf::Sprite* sSPotion;
    sf::Sprite* sSRune;
    sf::Sprite* sSGold;

    Graphics();
    Graphics(Graphics const&);
    void operator=(Graphics const&);
    void createSprite(sf::Sprite* sp, std::string img);
    void deleteSprite(std::vector<sf::Sprite*>&);

public:
    static int screenCnt;
    static sf::RenderWindow* window;
    static sf::Font* font;
    static sf::Text* text;

    static const int WinSizeX = 512;
    static const int WinSizeY = 512;
    static const int ImgSizeX = 100;
    static const int ImgSizeY = 100;

    class Position{
    public:
        int x, y, gap;
        Position(int _x, int _y, int _g):x(_x), y(_y), gap(_g){}
        ~Position(){}
    };

    static Graphics& getInstance(){
        static Graphics grap;
        return grap;
    }
    sf::Sprite* getWeapon() const { return sWeapon; }
    sf::Sprite* getPotion() const { return sPotion; }
    sf::Sprite* getRune() const { return sRune; }
    sf::Sprite* getGold() const { return sGold; }
    sf::Sprite* getLevel() const { return sLevel; }
    sf::Sprite* getAssassin() const { return sAssassin; }
    sf::Sprite* getWizard() const { return sWizard; }
    sf::Sprite* getWarrior() const { return sWarrior; }
    sf::Sprite* getAttack() const { return sAttack; }
    sf::Sprite* getMatrix() const { return sMatrix; }
    sf::Sprite* getWin() const { return sWin; }
    sf::Sprite* getLose() const { return sLose; }
    sf::Sprite* getTie() const { return sTie; }
    sf::Sprite* getInfo() const { return sInfo; }
    sf::Sprite* getWeapon2() const { return sWeapon2; }
    sf::Sprite* getPotion2() const { return sPotion2; }
    sf::Sprite* getRune2() const { return sRune2; }
    sf::Sprite* getSWeapon() const { return sSWeapon; }
    sf::Sprite* getSPotion() const { return sSPotion; }
    sf::Sprite* getSRune() const { return sSRune; }
    sf::Sprite* getSGold() const { return sSGold; }
    sf::Sprite* getSLevel() const { return sSLevel; }

    ~Graphics();

    bool mousePressedOnSprite(sf::Vector2f);
    bool mousePressedOnSprite(sf::Vector2f&, sf::Vector2i&);
    void drawFight(sf::Sprite& s1, sf::Sprite& s2);
    void drawResult(short r);
    void drawFightInfo(std::vector<std::string>&, std::vector<std::string>&);
    void drawHeroMenu(std::vector<std::string>&);
    void drawElement(std::vector<sf::Sprite*>&, Position&, sf::RenderWindow&);
    void drawString(std::vector<std::string>&, Position&, sf::RenderWindow&);
    void drawString(std::vector<std::string>&, Position&, sf::RenderWindow&, size_t);
    void drawNewHero();
    void drawMatrix(Matrix& m);
    void drawMatrix();
    void drawInfo();
};

#endif // GRAP_H_INCLUDE
