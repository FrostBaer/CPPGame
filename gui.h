#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED
#include "graphics.h"
#include "hero.h"
#include "matrix.h"

///screen kezelés ötlet innen: https://github.com/SFML/SFML/wiki/Tutorial:-Manage-different-Screens
///singleton design pattern innen: https://stackoverflow.com/questions/1008019/c-singleton-design-pattern

class Screen{
    static Hero* MyHero;
public:
    Screen(){ printf("New screen created!\n"); }
    virtual ~Screen() { printf("Screen deleted!\n"); }
    virtual void draw() = 0;
    Hero* getHero(){ return MyHero; }
    void setHero(Hero* h) { MyHero = h; }
};

class ScreenInfo : public Screen{
public:
    void draw();
};

class ScreenFightInfo : public Screen{
    bool first;
public:
    ScreenFightInfo() : first(true){}
    void draw();
    bool getFirst(){ return first; }
    void setFirst(bool b){ first = b; }
};

class ScreenNewHero : public Screen{
public:
    void draw();
};

class ScreenHeroMenu : public Screen{
public:
    void draw();
};

class ScreenMatrix : public Screen{
    bool first;
    bool newTiles;
    int clickedType;
    std::vector<int> clicked;
    std::vector<sf::Vector2f> positions;
    Matrix* mx;
public:
    ScreenMatrix(Matrix* _m = NULL) : first(true), newTiles(false), clickedType(-1), mx(_m){}
    void draw();
    bool sameElement(int);

    bool getFirst(){ return first; }
    bool getNewTiles(){ return newTiles; }
    std::vector<int> &getClicked() { return clicked; }
    std::vector<sf::Vector2f> &getPos() { return positions; }
    Matrix* getMx(){ return mx; }

    void setFirst(bool b){ first = b; }
    void setNewTiles(bool b){ newTiles = b; }
    void setPos(sf::Vector2f const & p){ positions.push_back(p); }
    void setMatrix(Matrix* _m){ mx = _m; }
    void setClicked(int e) {
        if(!(clicked.empty())){
            if(sameElement(e)){
                return;
            }
            if(!(mx->neighbour(e, clicked[clicked.size()-1]))){
                clicked.clear();
            }
        }
        clicked.push_back(e);
        //lecseréljük a képet
        Graphics::getInstance().drawMatrix();

        for(size_t i = 0; i < clicked.size(); i++){
            std::cout<<clicked[i]<<", ";
        }
        std::cout<<std::endl;
    }
};

class ScreenFight : public Screen{
    bool first;
    Hero* opponent;
public:
    ScreenFight() : first(true){}
    void draw();
    bool getFirst(){ return first; }
    void setFirst(bool b){ first = b; }
    Hero &getOpp(){ return *opponent; }
    void setOpp(Hero* h){ opponent = h; }
};

class Gui{
    ScreenNewHero *s0;
    ScreenHeroMenu *s1;
    ScreenMatrix *s2;
    ScreenFight *s3;
    ScreenInfo *s4;
    ScreenFightInfo *s5;

    Gui(){
        s0 = new ScreenNewHero;
        s1 = new ScreenHeroMenu;
        s2 = new ScreenMatrix;
        s3 = new ScreenFight;
        s4 = new ScreenInfo;
        s5 = new ScreenFightInfo;
    }

public:
    static Gui& getInstance(){
        static Gui g;
        return g;
    }

    ~Gui(){
        delete s0;
        delete s1;
        delete s2;
        delete s3;
        delete s4;
        delete s5;
    }

    ScreenNewHero& getS0() const { return *s0; }
    ScreenHeroMenu& getS1() const { return *s1; }
    ScreenMatrix& getS2() const { return *s2; }
    ScreenFight& getS3() const { return *s3; }
    ScreenInfo& getS4() const { return *s4; }
    ScreenFightInfo& getS5() const { return *s5; }
};

#endif // IO_H_INCLUDED
