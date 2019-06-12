//
//  grafo.h
//  proyect
//
//  Created by Oscar Sandoval on 2/16/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#ifndef grafo_h
#define grafo_h
#include "arista.hpp"
#include "vertice.hpp"
#include "console.hpp"
#include "listaEstatica.hpp"
#include "queu.hpp"
#include "stack.hpp"
class Grafo{
private:
    Vertice vertice[10];
    Arista arista[10][10];
    unsigned counter;
    void widthTravel(int,Console&);
    void depthTravel(int,Console&);
    int start(Console&);
    int getPos(Vertice);
    void busquedaAnchura(int&,int&,Console&);
    void busquedaProfundidad(int&,int&,Console&);
    void desplegarRuta(Stack<Vertice>&,Stack<Vertice>&,int&,Console&);
public:
    Grafo();
    int isValidData(std::string);
    bool isEmpty();
    void printData(Console&);
    void insertData(std::string,std::string);
    void modifyData(std::string,std::string);
    void modifyAristas(std::string&);
    void remove(std::string);
    void travel(Console&);
    void busquedas(Console&);
};
#endif /* grafo_h */
