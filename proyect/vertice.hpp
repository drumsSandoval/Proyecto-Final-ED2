//
//  vertice.hpp
//  proyect
//
//  Created by Oscar Sandoval on 2/17/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#ifndef vertice_h
#define vertice_h
#include <iostream>
class Vertice{
private:
    char data[10];
    char name[20];
    int active;
public:
    Vertice();
    void setData(std::string);
    void setName(std::string);
    void setActive(int);
    std::string getData();
    std::string getName();
    int& getActive();
    bool operator == (Vertice& v)const;
    bool operator !=(Vertice&)const;
    Vertice operator = (const Vertice v);
    friend std::ostream & operator <<(std::ostream &os,Vertice&);
};
#endif /* vertice_h */
