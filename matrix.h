#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED
#include <stdlib.h> //rand, srand
#include <time.h>
#include <vector>

class ResCodes{
public:
    static const int RES_WEAPON = 0;
    static const int RES_RUNE = 1;
    static const int RES_POTION = 2;
};

class Matrix{
    int n;
    int ctrp;
    int ctrg;
    std::vector<int> m;
    std::vector<int> ptr;
    std::vector<int> graph;
public:
    explicit Matrix(int _n): n(4), ctrp(0), ctrg(0), m(n*n), ptr(n*n), graph(n*n){
        this->fillMatrix();
        initArr(ptr);
        initArr(graph);
        graphCheck();
    }

    Matrix(const Matrix& mx):n(mx.n), ctrp(0), ctrg(0), m(n*n), ptr(n*n), graph(n*n){
        this->m = mx.m;
        initArr(ptr);
        initArr(graph);
        graphCheck();
    }

    int getN(){ return n; }
    std::vector<int> const &getM() const { return m; }
    std::vector<int> const &getPtr() const { return ptr; }
    std::vector<int> const &getGraph() const { return graph; }
    int getCtrP() { return ctrp; }
    int getCtrG() { return ctrg; }

    void fillMatrix();
    void newTile(int);
    void initArr(std::vector<int> & vec);
    void draw(std::vector<int> const & vec);
    void graphCheck();
    bool newGraph(int node);
    void bfs();
    void nodeCheck(int no1, int no2);
    bool neighbour(int, int);
    bool sameType(int, int);
    void where(int&, int&, int);
};

#endif // MATRIX_H_INCLUDED
