//
//  arista.h
//  proyect
//
//  Created by Oscar Sandoval on 2/16/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#ifndef arista_h
#define arista_h
#include <iostream>
class Arista{
private:
    int peso;
    int active;
public:
    Arista();
    void setPeso(std::string&);
    void setActive(int);
    int &getPeso();
    int& getActive();
};
#endif /* arista_h */
