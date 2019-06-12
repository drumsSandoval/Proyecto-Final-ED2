//
//  perfil.hpp
//  proyect
//
//  Created by Oscar Sandoval on 2/4/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#ifndef perfil_h
#define perfil_h
#include <iostream>
#include "console.hpp"
class Perfil{
public:
    int activate;
    int code;
    char name[20];
};
class Perimisos{
public:
    int code;
    int agregar;
    int mostrar;
    int buscar;
    int modificar;
    int eliminar;
    int activar;
};
class Perfiles{
private:
    Perfil perfil;
public:
    Perimisos access;
    Perfiles();
    //Setters
    void setActivater(int);
    void setCode();
    void setName(std::string&);
    //Getters
    int getCode()const;
    std::string getName();
    //Metodos perrones
    void insert();
    void print(Console&);
    void printUsers(Console&);
    std::string search(std::string&);
    std::string modify(int,Console&);
    std::string remove(int);
    std::string logicRemove(int);
    std::string active(int);
    void modifyAccess(int,Console&);
    bool isValidRemove(int&);
    void desactiveUsers(int&);
    void activeUsers(int&);
    int getProfileCode(Console&);
};
#endif /* perfil_h */
