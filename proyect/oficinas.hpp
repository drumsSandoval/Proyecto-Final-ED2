//
//  oficinas.hpp
//  proyect
//
//  Created by Oscar Sandoval on 4/26/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#ifndef oficinas_h
#define oficinas_h
#include "usuarios.hpp"
typedef std::pair<int, int> diaMes;
typedef std::pair<diaMes, int> fecha;
class Oficina{
public:
    char name[30];
    int code;
    char address[40];
    bool active;
};
class Oficinas{
private:
    Oficina office;
    void modificarCodigoUsuarios(int&,int);
public:
    Oficinas();
    void setName(std::string&);
    bool setCode(std::string&);
    void setAddress(std::string&);
    std::string getName();
    int getCode();
    std::string getName(int&);
    std::string getAddress();
    bool isEmpty();
    bool isValidCode(std::string&);
    bool isValidDelete(int,int);
    //CRUD
    void insert();
    void printOffices(Console&);
    void search(Console&,std::string&);
    void modify(Console&,std::string&);
    void deleteOffice(std::string&,int);
    void deleteOfficeLogic(std::string&);
    void cortePorDia(Console&,std::string&);
    void cortePorRangoDeFechas(Console&);
    std::string getDate(int&,int&,int&);
    void printCorteOficina(Console&);
    fecha firstDate(Console&);
    fecha secondDate(Console&);
    int getOffice(Console&);
};

#endif /* oficinas_h */
