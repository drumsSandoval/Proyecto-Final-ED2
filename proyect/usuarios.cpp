//
//  usuarios.cpp
//  proyect
//
//  Created by Oscar Sandoval on 2/4/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#include "usuarios.hpp"
#include <fstream>
#include <stdexcept>
#include "perfiles.hpp"
#include "ventas.hpp"
using namespace std;
Usuario::Usuario(){
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Usuarios.txt");
    if(!archive.good()){
        string myStr;
        myStr="ADMIN";
        setUserName(myStr);
        myStr="ADMIN";
        setPassword(myStr);
        myStr="1";
        profileCode=1;
        myStr="ADMINISTRADOR";
        setName(myStr);
        myStr="1";
        setOfficeCode(myStr);
        setActivate(1);
        insert();
    }
}
//Setters
void Usuario::setCode(int & code){
    this->code=code;
}
void Usuario::setOfficeCode(std::string &officeCode){
    try{
        this->officeCode=stoi(officeCode);
    }catch(invalid_argument & ex){
        throw invalid_argument("Ingrese un codigo  de oficina valido");
    }
}
void Usuario::setOfficeCode(int c){
    this->officeCode = c;
}

void Usuario::setProfileCode(int p){
    this->profileCode = p;
}

bool Usuario::setProfileCode(std::string &profile){
    int aux;
    try{
        aux=stoi(profile);
    }catch(invalid_argument & ex){
        throw invalid_argument("Ingrese un codigo de perfil valido");
    }
    Perimisos a;
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/PermisosPerfiles.txt");
    
    while(!archive.eof()){
        archive.read((char*)&a,sizeof(Perimisos));
        if(aux==a.code&&aux!=1){
            this->profileCode=aux;
            return true;
        }
    }
    return false;
}
void Usuario::setUserName(std::string &userName){
    for(int i=0;i<30;i++){
        this->userName[i]='\0';
    }
    for(int i=0;i<userName.length();i++)
        this->userName[i]=userName[i];
}
void Usuario::setPassword(std::string &password){
    for(int i=0;i<10;i++){
        this->password[i]='\0';
    }
    for(int i=0;i<password.length();i++)
        this->password[i]=password[i];
}
void Usuario::setName(std::string &name){
    for(int i=0;i<30;i++){
        this->name[i]='\0';
    }
    for(int i=0;i<name.length();i++)
        this->name[i]=name[i];
}
void Usuario::setActivate(int activate){
    this->activate=activate;
}
int Usuario::getCode()const{
    return code;
}
string Usuario::getName(int user)const{
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Usuarios.txt");
    long aux;
    if(!archive.good()){
        return "fail";
       
    }
    char ax[20];
    while(!archive.eof()){
        archive.read((char*)&activate, sizeof(int));
        archive.read((char*)&aux,sizeof(long));
        archive.read((char*)&ax,aux);
        ax[aux] = '\0';
        archive.read((char*)&aux,sizeof(long));
        archive.read((char*)&userName,aux);
        archive.read((char*)&aux,sizeof(long));
        archive.read((char*)&password,aux);
        archive.read((char*)&profileCode, sizeof(int));
        archive.read((char*)&officeCode, sizeof(int));
        archive.read((char*)&code, sizeof(int));
        if(archive.eof())break;
        if(code==user){
            archive.close();
            return ax;
        }
    }
    archive.close();
    return "usuario";
}

int Usuario::getOffice(int user)const{
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Usuarios.txt");
    long aux;
    if(!archive.good()){
        return -1;
        
    }
    char ax[20];
    while(!archive.eof()){
        archive.read((char*)&activate, sizeof(int));
        archive.read((char*)&aux,sizeof(long));
        archive.read((char*)&ax,aux);
        ax[aux] = '\0';
        archive.read((char*)&aux,sizeof(long));
        archive.read((char*)&userName,aux);
        archive.read((char*)&aux,sizeof(long));
        archive.read((char*)&password,aux);
        archive.read((char*)&profileCode, sizeof(int));
        archive.read((char*)&officeCode, sizeof(int));
        archive.read((char*)&code, sizeof(int));
        if(archive.eof())break;
        if(code==user){
            archive.close();
            return officeCode;
        }
    }
    archive.close();
    return -1;
}

string Usuario::getPassword()const{
    string myStr;
    for(int i=0;password[i];i++)
        myStr+=password[i];
    return myStr;
}
string Usuario::getUserName()const{
    string myStr;
    for(int i=0;userName[i];i++)
        myStr+=userName[i];
    return myStr;
}
int Usuario::getOfficceCode()const{
    return officeCode;
}
int Usuario::getProfileCode()const{
    return profileCode;
}
int Usuario::getActivate()const{
    return activate;
}
void Usuario::insert(){
    ifstream read("/Users/oscarsandoval/Desktop/proyect/Usuarios.txt");
    long aux;
    char m[30];
    if(!read.good())
        code=1;
    else{
        while(!read.eof()){
            read.read((char*)&aux, sizeof(int));
            read.read((char*)&aux,sizeof(long));
            read.read((char*)&m,aux);
            read.read((char*)&aux,sizeof(long));
            read.read((char*)&m,aux);
            read.read((char*)&aux,sizeof(long));
            read.read((char*)&m,aux);
            read.read((char*)&aux,sizeof(int));
            read.read((char*)&aux,sizeof(int));
            read.read((char*)&code,sizeof(int));
            if(read.eof())break;
        }
        read.close();
        code++;
    }
    ofstream archive("/Users/oscarsandoval/Desktop/proyect/Usuarios.txt",ios::app);
    long b;
    activate=1;
    archive.write((char*)&activate,sizeof(int));
    b=strlen(name);
    name[b]='\0';
    archive.write((char*)&b,sizeof(long));
    archive.write((char*)&name,b);
    b=strlen(userName);
    userName[b]='\0';
    archive.write((char*)&b,sizeof(long));
    archive.write((char*)&userName,b);
    b=strlen(password);
    password[b]='\0';
    archive.write((char*)&b,sizeof(long));
    archive.write((char*)&password,b);
    archive.write((char*)&profileCode,sizeof(int));
    archive.write((char*)&officeCode,sizeof(int));
    archive.write((char*)&code,sizeof(int));
    archive.close();
}

void Usuario::toString(Console& graphics){
    //  name / username /password /profile code / office code /code
    //char/char/char/int/int/int
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Usuarios.txt");
    long aux;
    if(!archive.good()){
        graphics.moveTo(3, 15);
        cout<<"No hay usuarios registrados\n";
        cin.get();
        return ;//myStr;
    }
    graphics.setColor(graphics.FG_LIGHT_PURPLE);
    graphics.moveTo(3, 15);
    cout<<"\t┌───────────────────────────────────────────────────┐\n";
    graphics.moveTo(4, 15);
    cout<<"\t│             USURARIOS REGISTRADOS                 │\n";
    graphics.moveTo(5, 15);
    cout<<"\t└───────────────────────────────────────────────────┘\n";
    int auxf,auxe;
    auxf=7; auxe=12;
    graphics.setColor(graphics.FG_GRAY);
    graphics.moveTo(6, 5);
    cout<<"     CODE\t\tNOMBRE\t\tPERFIL\t\tOFICINA";
    graphics.setColor(graphics.FG_WHITE);
    while(!archive.eof()){
        archive.read((char*)&activate, sizeof(int));
        archive.read((char*)&aux,sizeof(long));
        archive.read((char*)&name,aux);
        name[aux]='\0';
        archive.read((char*)&aux,sizeof(long));
        archive.read((char*)&userName,aux);
        userName[aux]='\0';
        archive.read((char*)&aux,sizeof(long));
        archive.read((char*)&password,aux);
        password[aux]='\0';
        archive.read((char*)&profileCode, sizeof(int));
        archive.read((char*)&officeCode, sizeof(int));
        archive.read((char*)&code, sizeof(int));
        if(archive.eof())break;
        if(activate==1){
            graphics.moveTo(auxf,auxe);
            cout<<code;
            auxe=21;
            graphics.moveTo(auxf,auxe);
            cout<<name;
            auxe=44;
            graphics.moveTo(auxf,auxe);
            cout<<profileCode;
            auxe=59;
            graphics.moveTo(auxf,auxe);
            cout<<officeCode;
            auxf++;
            auxe=12;
        }
    }
    archive.close();
    cin.get();
}

void Usuario::search(int& user,Console& graphics){
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Usuarios.txt");
    string myStr;
    long aux;
    if(!archive.good()){
        graphics.moveTo(5, 15);
        graphics.setColor(graphics.FG_DARK_BLUE);
        cout<<"\t┌───────────────────────────────────────────────────┐\n";
        graphics.moveTo(6, 15);
        cout<<"\t│       NO   HAY   USUARIOS   REGISTRADOS           │\n";
        graphics.moveTo(7, 15);
        cout<<"\t└───────────────────────────────────────────────────┘\n";
        cin.get();
    }
    while(!archive.eof()){
        archive.read((char*)&activate, sizeof(int));
        archive.read((char*)&aux,sizeof(long));
        archive.read((char*)&name,aux);
        name[aux]='\0';
        archive.read((char*)&aux,sizeof(long));
        archive.read((char*)&userName,aux);
        userName[aux]='\0';
        archive.read((char*)&aux,sizeof(long));
        archive.read((char*)&password,aux);
        password[aux]='\0';
        archive.read((char*)&profileCode, sizeof(int));
        archive.read((char*)&officeCode, sizeof(int));
        archive.read((char*)&code, sizeof(int));
        if(archive.eof())break;
        if(code==user){
            if(activate==1){
                graphics.moveTo(4, 15);
                graphics.setColor(graphics.FG_LIGHT_BLUE);
                cout<<"\t┌───────────────────────────────────────────────────┐\n";
                graphics.moveTo(5, 15);
                cout<<"\t│                USUARIO    ENCONTRADO              │\n";
                graphics.moveTo(6, 15);
                cout<<"\t└───────────────────────────────────────────────────┘\n";
                graphics.setColor(graphics.FG_WHITE);
                graphics.moveTo(8, 18);
                cout<<"\t\tUsuario enontrado\n\n";
                graphics.moveTo(9, 18);
                cout<<"Nombre : "<<name;
                graphics.moveTo(10, 18);
                cout<<"Nombre de usuario : " <<userName;
                graphics.moveTo(11, 18);
                cout<<"Perfil : "<<profileCode;
                graphics.moveTo(12, 18);
                cout<<"Oficina : "<<officeCode;
                graphics.moveTo(13, 18);
                cout<<"Codigo : "<<code;
                cin.get();
                archive.close();
                return;
            }
        }
    }
    graphics.moveTo(4, 15);
    graphics.setColor(graphics.FG_DARK_RED);
    cout<<"\t┌───────────────────────────────────────────────────┐\n";
    graphics.moveTo(5, 15);
    cout<<"\t│                USUARIO  NO   ENCONTRADO           │\n";
    graphics.moveTo(6, 15);
    cout<<"\t└───────────────────────────────────────────────────┘\n";
    archive.close();
}

string Usuario::modify(int &user,Console& graphics){
    ifstream archive1("/Users/oscarsandoval/Desktop/proyect/Usuarios.txt");
    ofstream archive("/Users/oscarsandoval/Desktop/proyect/Aux.txt",ios::out);
    string myStr;
    bool band2=false;
    long aux;
    if(!archive1.good()){
        myStr="No hay Usuarios registrados\n";
        return myStr;
    }
    while(!archive1.eof()){
        archive1.read((char*)&activate, sizeof(int));
        archive1.read((char*)&aux,sizeof(long));
        archive1.read((char*)&name,aux);
        name[aux]='\0';
        archive1.read((char*)&aux,sizeof(long));
        archive1.read((char*)&userName,aux);
        userName[aux]='\0';
        archive1.read((char*)&aux,sizeof(long));
        archive1.read((char*)&password,aux);
        password[aux]='\0';
        archive1.read((char*)&profileCode, sizeof(int));
        archive1.read((char*)&officeCode, sizeof(int));
        archive1.read((char*)&code, sizeof(int));
        if(archive1.eof())break;
        if(code==user){
            if(activate==1){
                bool band;
                band2=true;
                system("clear");
                cout<<"Modificar Usuario : "<<endl
                <<"Nombre : ";
                getline(cin,myStr);
                for(int i = 0;myStr[i];++i)
                    myStr[i] = toupper(myStr[i]);
                setName(myStr);
                cout<<"Nombre de Usuario : ";
                getline(cin,myStr);
                for(int i = 0;myStr[i];++i)
                    myStr[i] = toupper(myStr[i]);
                setUserName(myStr);
                do{
                    band=false;
                    cout<<"Codigo de Oficina : ";
                    getline(cin,myStr);
                    try{
                        setOfficeCode(myStr);
                    }catch(invalid_argument &ex){
                        system("clear");
                        cerr<<ex.what();
                        band=true;
                    }
                }while(band==true);
                cout<<"Password : ";
                getline(cin,myStr);
                for(int i = 0;myStr[i];++i)
                    myStr[i] = toupper(myStr[i]);
                setPassword(myStr);
            }
        }
        long b;
        archive.write((char*)&activate,sizeof(int));
        b=strlen(name);
        name[b]='\0';
        archive.write((char*)&b,sizeof(long));
        archive.write((char*)&name,b);
        b=strlen(userName);
        userName[b]='\0';
        archive.write((char*)&b,sizeof(long));
        archive.write((char*)&userName,b);
        b=strlen(password);
        password[b]='\0';
        archive.write((char*)&b,sizeof(long));
        archive.write((char*)&password,b);
        archive.write((char*)&profileCode,sizeof(int));
        archive.write((char*)&officeCode,sizeof(int));
        archive.write((char*)&code,sizeof(int));
    }
    archive.close();
    archive1.close();
    std::remove("/Users/oscarsandoval/Desktop/proyect/Usuarios.txt");
    rename("/Users/oscarsandoval/Desktop/proyect/Aux.txt","/Users/oscarsandoval/Desktop/proyect/Usuarios.txt");
    if(band2==false)
        return "No se encontro el usuario\n";
    return "Usuario Modificado\n";
}
string Usuario::remove(int & user){
    if(!isValidRemove(user)){
        return "No es posible eliminar este usuario tiene ventas Registradas" ;
    }
    if(user==1){
        return "\nNo es posible eliminar al ADMINISTRADOR\n";
    }
    ifstream archive1("/Users/oscarsandoval/Desktop/proyect/Usuarios.txt");
    ofstream archive("/Users/oscarsandoval/Desktop/proyect/Aux.txt",ios::out);
    string myStr;
    bool band=false;
    long aux;
    if(!archive1.good()){
        myStr="No hay Usuarios registrados\n";
        return myStr;
    }
    while(!archive1.eof()){
        archive1.read((char*)&activate, sizeof(int));
        archive1.read((char*)&aux,sizeof(long));
        archive1.read((char*)&name,aux);
        name[aux]='\0';
        archive1.read((char*)&aux,sizeof(long));
        archive1.read((char*)&userName,aux);
        userName[aux]='\0';
        archive1.read((char*)&aux,sizeof(long));
        archive1.read((char*)&password,aux);
        password[aux]='\0';
        archive1.read((char*)&profileCode, sizeof(int));
        archive1.read((char*)&officeCode, sizeof(int));
        archive1.read((char*)&code, sizeof(int));
        if(archive1.eof())break;
        if(code==user){
             if(activate==1){
                 band=true;
             }
        }
        else{
            long b;
            archive.write((char*)&activate,sizeof(int));
            b=strlen(name);
            name[b]='\0';
            archive.write((char*)&b,sizeof(long));
            archive.write((char*)&name,b);
            b=strlen(userName);
            userName[b]='\0';
            archive.write((char*)&b,sizeof(long));
            archive.write((char*)&userName,b);
            b=strlen(password);
            password[b]='\0';
            archive.write((char*)&b,sizeof(long));
            archive.write((char*)&password,b);
            archive.write((char*)&profileCode,sizeof(int));
            archive.write((char*)&officeCode,sizeof(int));
            archive.write((char*)&code,sizeof(int));
        }
    }
    archive.close();
    archive1.close();
    std::remove("/Users/oscarsandoval/Desktop/proyect/Usuarios.txt");
    rename("/Users/oscarsandoval/Desktop/proyect/Aux.txt","/Users/oscarsandoval/Desktop/proyect/Usuarios.txt");
    if(band==false)
        return "No se encontro el usuario\n";
    return "Usuario Eliminado";
}
string Usuario::logicRemove(int &user){
    if(user==1){
        return "\nNo es posible eliminar al ADMINISTRADOR\n";
    }
    ifstream archive1("/Users/oscarsandoval/Desktop/proyect/Usuarios.txt");
    ofstream archive("/Users/oscarsandoval/Desktop/proyect/Aux.txt",ios::out);
    string myStr;
    bool band=false;
    long aux;
    if(user==1){
        return "No se puede eliminar al patron\n ";
    }
    if(!archive1.good()){
        myStr="No hay usuarios registrados\n";
        return myStr;
    }
    while(!archive1.eof()){
        archive1.read((char*)&activate, sizeof(int));
        archive1.read((char*)&aux,sizeof(long));
        archive1.read((char*)&name,aux);
        name[aux]='\0';
        archive1.read((char*)&aux,sizeof(long));
        archive1.read((char*)&userName,aux);
        userName[aux]='\0';
        archive1.read((char*)&aux,sizeof(long));
        archive1.read((char*)&password,aux);
        password[aux]='\0';
        archive1.read((char*)&profileCode, sizeof(int));
        archive1.read((char*)&officeCode, sizeof(int));
        archive1.read((char*)&code, sizeof(int));
        if(archive1.eof())break;
        if(code==user){
            if(activate==1){
                band=true;
                activate=0;
            }
        }
        long b;
        archive.write((char*)&activate,sizeof(int));
        b=strlen(name);
        name[b]='\0';
        archive.write((char*)&b,sizeof(long));
        archive.write((char*)&name,b);
        b=strlen(userName);
        userName[b]='\0';
        archive.write((char*)&b,sizeof(long));
        archive.write((char*)&userName,b);
        b=strlen(password);
        password[b]='\0';
        archive.write((char*)&b,sizeof(long));
        archive.write((char*)&password,b);
        archive.write((char*)&profileCode,sizeof(int));
        archive.write((char*)&officeCode,sizeof(int));
        archive.write((char*)&code,sizeof(int));
    }
    archive.close();
    archive1.close();
    std::remove("/Users/oscarsandoval/Desktop/proyect/Usuarios.txt");
    rename("/Users/oscarsandoval/Desktop/proyect/Aux.txt","/Users/oscarsandoval/Desktop/proyect/Usuarios.txt");
    if(band==false)
        return "No se encontro el usuario\n";
    return "Usuario Eliminado";
}
string Usuario::active(int &user){
    ifstream archive1("/Users/oscarsandoval/Desktop/proyect/Usuarios.txt");
    ofstream archive("/Users/oscarsandoval/Desktop/proyect/Aux.txt",ios::out);
    string myStr;
    bool band=false;
    long aux;
    if(!archive1.good()){
        myStr="No hay Usuarios registrados\n";
        return myStr;
    }
    while(!archive1.eof()){
        archive1.read((char*)&activate, sizeof(int));
        archive1.read((char*)&aux,sizeof(long));
        archive1.read((char*)&name,aux);
        name[aux]='\0';
        archive1.read((char*)&aux,sizeof(long));
        archive1.read((char*)&userName,aux);
        userName[aux]='\0';
        archive1.read((char*)&aux,sizeof(long));
        archive1.read((char*)&password,aux);
        password[aux]='\0';
        archive1.read((char*)&profileCode, sizeof(int));
        archive1.read((char*)&officeCode, sizeof(int));
        archive1.read((char*)&code, sizeof(int));
        if(archive1.eof())break;
        if(code==user){
            if(activate==0){
                band=true;
                activate=1;
            }
        }
        long b;
        archive.write((char*)&activate,sizeof(int));
        b=strlen(name);
        name[b]='\0';
        archive.write((char*)&b,sizeof(long));
        archive.write((char*)&name,b);
        b=strlen(userName);
        userName[b]='\0';
        archive.write((char*)&b,sizeof(long));
        archive.write((char*)&userName,b);
        b=strlen(password);
        password[b]='\0';
        archive.write((char*)&b,sizeof(long));
        archive.write((char*)&password,b);
        archive.write((char*)&profileCode,sizeof(int));
        archive.write((char*)&officeCode,sizeof(int));
        archive.write((char*)&code,sizeof(int));
    }
    archive.close();
    archive1.close();
    std::remove("/Users/oscarsandoval/Desktop/proyect/Usuarios.txt");
    rename("/Users/oscarsandoval/Desktop/proyect/Aux.txt","/Users/oscarsandoval/Desktop/proyect/Usuarios.txt");
    if(band==false)
        return "No se encontro el usuario\n";
    return "Usuario Activado\n";
}

string Usuario::getUserName(int user){
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Usuarios.txt");
    string myStr;
    long aux;
    while(!archive.eof()){
        archive.read((char*)&activate, sizeof(int));
        archive.read((char*)&aux,sizeof(long));
        archive.read((char*)&name,aux);
        name[aux]='\0';
        archive.read((char*)&aux,sizeof(long));
        archive.read((char*)&userName,aux);
        userName[aux]='\0';
        archive.read((char*)&aux,sizeof(long));
        archive.read((char*)&password,aux);
        password[aux]='\0';
        archive.read((char*)&profileCode, sizeof(int));
        archive.read((char*)&officeCode, sizeof(int));
        archive.read((char*)&code, sizeof(int));
        if(archive.eof())break;
        if(code==user){
            if(activate==1){
                return name;
            }
        }
    }
    return " ";
}

bool Usuario::isValidRemove(int &a){
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Ventas.txt");
    Venta venta;
    int pos(0);
    long aux;
    if(!archive.good())
        return true;

    while(!archive.eof()){
        archive.seekg(pos);
        archive.read((char*)&aux, sizeof(aux));
        if(archive.eof())break;
        if(aux>0){
            for(int i(0);i<aux;++i){
                archive.read((char*)&venta, sizeof(venta));
                if(venta.idUsuario==a)
                    return false;
            }
        }
        pos=pos+(sizeof(Venta)*4+sizeof(long));
    }
    return true;
}
