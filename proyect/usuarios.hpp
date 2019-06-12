//
//  usuarios.hpp
//  proyect
//
//  Created by Oscar Sandoval on 2/4/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#ifndef usuarios_hpp
#define usuarios_hpp
#include "perfiles.hpp"
#include "console.hpp"
class Usuario{
private:
    int activate;
    int code;
    int officeCode;
    int profileCode;
    char userName[30];
    char password[10];
    char name[30];
public:
    Usuario();
    //setters
    void setCode(int&);
    void setOfficeCode(std::string&);
    void setOfficeCode(int);
    bool setProfileCode(std::string&);
    void setProfileCode(int);
    void setUserName(std::string&);
    void setPassword(std::string&);
    void setName(std::string&);
    void setActivate(int);
    //Getters
    int getCode()const;
    int getOfficceCode()const;
    int getProfileCode()const;
    std::string getUserName()const;
    std::string getUserName(int);
    std::string getPassword()const;
    std::string getName(int)const;
    int getOffice(int)const;
    int getActivate()const;
    //Metodos chidos
    //Agregar usuarios
    void insert();
    void toString(Console&);
    void search(int&,Console&);
    bool isValidRemove(int&);
    std::string modify(int&,Console&);
    std::string remove(int&);
    std::string logicRemove(int&);
    std::string active(int&);
};
#endif /* usuarios_hpp */
