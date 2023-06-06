#include <iostream>
#include "matrix.h"

void Matrix::fillMatrix(){
    for( int i = 0; i < n * n; i++ ){
        newTile(i);
    }
}

void Matrix::newTile(int i){
    m[i] = rand()%3;
}

void Matrix::initArr(std::vector<int> & vec){
    for( int i = 0; i < n * n; i++ ){
        vec[i] = -1;
    }
}

bool Matrix::newGraph(int node){
    for(int i = 0; i < ctrg; i++)
        if(graph[i] == node)
        return false;
    return true;
}

void Matrix::draw(std::vector<int> const & vec){
    for(int i = 0; i < n; i++ ){
        std::cout<<"|";
        for( int j = i * n; j < i * n + n; j++ ){
            std::cout << vec[j] << "|";
        }
        std::cout<<std::endl;
    }
}

bool Matrix::neighbour(int e1, int e2){
    if(!(sameType(e1, e2))){
        return false;
    }
    else{
        for(int i = 1; i <= 5; i++){
            if(i != 2){
                if(e2-i >= 0 && e2-i == e1){
                    return true;
                }
                if(e2+i >= 0 && e2+i == e1){
                    return true;
                }
            }
        }
    }
    return false;
}

bool Matrix::sameType(int e1, int e2){          //2 sorszámú elem ugyanabba a típusba tartozik-e? (matrix vectorbeli sorsz.)
    int pt1 = -1, pt2 = -1;
    where(pt1, pt2, e1);
    if(pt1 == -1 || pt2 == -1)
        std::cout<<"Matrix::sameType: Hibas intervallumot kapott Matrix::where-tol!"<<std::endl;
    for(; pt1 != pt2; pt1++)
        if(graph[pt1] == e2)
            return true;
    return false;
}

void Matrix::where(int &pt1, int &pt2, int e){
    int i, nr = -1;
    for(i = 0; graph[i] != e; i++)                      //ha gráfokat tartalmazó vektorban megtaláltuk a keresett elemet
        ;                                               //üres
    nr = i;                                             //elmentjük az indexét
    //std::cout<<"Ezt keressuk: "<<nr<<std::endl;
    for(i = 0; nr >= ptr[i] && ptr[i] != -1; i++){      //megnézzük, hogy ez az index melyik 2 ptr közti gráf része: ha a ptr köv. eleme már nagyobb indexre mutat
        ;                                               //üres
    }
    pt1 = ptr[i-1];                                   //ez mindig legalább a 0 index és maximum 15
    pt2 = ptr[i];                                     //ez mindig legalább az 1 index
    if(pt2 == -1)                                     //maximum -1, ekkor átállítjuk az utolsó indexre (15)
        pt2 = 15;
    //std::cout<<"Pt1: "<<pt1<<std::endl;
    //std::cout<<"Pt2: "<<pt2<<std::endl;
}

void Matrix::bfs(){                     //gráfot felderítő algoritmus

    int j = 0;
    int node = -1;
    int graphStart = ptr[getCtrP()-1];              //a ptrtömb szerinti legutóbbi gráf kezdőeleme

    while(node != graph[ctrg-1]){                   //amíg a node nem egyenlő a gráf legutolsó elemével
        node = graph[graphStart + j];               //következő körben a gráftömbben eltárolt következő elem szomszédait vizsgáljuk
        j++;

        if(node >= n){                          //ha nem az első sor
            if(node % n != 0)                   //ha nem a bal oszlop
                nodeCheck(node, node-n-1);      //megvizsgáljuk a bal felső elemét

            nodeCheck(node, node-n);            //megvizsgáljuk a felette levő elemet

            if(node % n != n-1)                 //ha nem a jobb oszlop
                nodeCheck(node, node-n+1);      //megvizsgáljuk a jobb felső elemét
        }

        if(node % n != 0)                       //ha nem a bal szélső oszlop
            nodeCheck(node, node-1);            //megvizsgáljuk a bal szomszédot

        if(node % n != n-1)                     //ha nem a jobb szélső oszlop
            nodeCheck(node, node+1);            //megvizsgáljuk a jobb szomszédot

        if(node <= (n * n - n)){                 //ha nem az utolsó sor
            if(node % n != 0)                    //ha nem a bal oszlop
                nodeCheck(node, node+n-1);       //megvizsgáljuk a bal alsó elemet

            nodeCheck(node, node+n);             //megvizsgáljuk az alatta álló elemet

            if(node % n != n-1)                  //ha nem a jobb oszlop
                nodeCheck(node, node+n+1);       //megvizsgáljuk a jobb alsó elemet
        }
    }
}

void Matrix::nodeCheck(int no1, int no2){       //összehasonlítja 2 csomópont értékét
    if(newGraph(no2))                           //ha az új node még nincs felvéve a gráfba
        if(m[no1] == m[no2])                    //és ugyanazt tartalmazzák
            graph[ctrg++] = (no2);              //felveszi
}

void Matrix::graphCheck(){
    for(int i = 0; i < (n * n); i++){   //minden node-ra vizsgáljuk, hogy ez a sorszámú elem benne van-e a gráftömbben
        if(newGraph(i)){                //ha nincs
            ptr[ctrp] = ctrg;           //a pointertömb következő elemét beállítjuk a gráftömb következő elemére, ahol az új gráf kezdődni fog
            ctrp++;
            graph[ctrg] = i;            //a gráftömb következő üres helyére elmentjük az új elem mátrixbeli sorszámát
            ctrg++;
            bfs();                     //és elkezdjük vizsgálni a szomszédait (a ptrtömb szerinti utolsó gráfot deríti fel)
        }
    }
}
