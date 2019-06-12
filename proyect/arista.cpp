//
//  arista.cpp
//  proyect
//
//  Created by Oscar Sandoval on 2/21/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#include "arista.hpp"
Arista::Arista():active(0),peso(NULL){
    
}
void Arista::setPeso(std::string & peso){
    try{
        this->peso=stoi(peso);
    }catch(std::invalid_argument& ex){
        throw std::invalid_argument(ex.what());
    }
}
void Arista::setActive(int active){
    this->active=active;
}
int& Arista::getPeso(){
    return peso;
}
int& Arista::getActive(){
    return active;
}
