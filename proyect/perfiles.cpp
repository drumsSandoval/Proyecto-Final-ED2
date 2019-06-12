//
//  perfil.cpp
//  proyect
//
//  Created by Oscar Sandoval on 2/4/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//
#include "perfiles.hpp"
#include <string>
#include <fstream>
#include "list.hpp"
using namespace std;
Perfiles::Perfiles(){
    string myStr;
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Perfiles.txt",ios::end);
    if(!archive.good()){
        perfil.code=1;
        myStr="ADMINISTRADOR";
        setName(myStr);
        access.code=1;
        access.activar=1;
        access.agregar=1;
        access.buscar=1;
        access.modificar=1;
        access.eliminar=1;
        access.mostrar=1;
        insert();
        cout<<"Access : "<<access.code<<access.activar<<access.agregar<<endl;
    }
    long pos;
    pos=archive.tellg();
    archive.seekg(pos-24);
    archive.read((char*)&perfil.code,sizeof(int));
    archive.close();
}
//Setters
void Perfiles::setActivater(int a){
    this->perfil.activate=a;
}
void Perfiles::setCode(){
    perfil.code+=1;
}
void Perfiles::setName(std::string &name){
    for(int i=0;i<20;i++){
        this->perfil.name[i]='\0';
    }
    for(int i=0;name[i];i++){
        this->perfil.name[i]=name[i];
    }
}
//Getters
int Perfiles::getCode()const{
    return perfil.code;
}
string Perfiles::getName(){
    string myStr;
    myStr="";
    for(int i=0;perfil.name[i];i++){
        myStr+=perfil.name[i];
    }
    return myStr;
}
//Metodos chingones
void Perfiles::insert(){
    setActivater(1);
    ofstream archive("/Users/oscarsandoval/Desktop/proyect/Perfiles.txt",ios::app);
    archive.write((char*)&perfil,sizeof(perfil));
    archive.close();
    ofstream archive2("/Users/oscarsandoval/Desktop/proyect/PermisosPerfiles.txt",ios::app);
    archive2.write((char*)&access,sizeof(access));
    archive2.close();
}
void Perfiles::print(Console& graphics){
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Perfiles.txt");
    if(!archive.good()){
        cout<<"No hay registros de Perfiles\n";
        return;
    }
    system("clear");
    graphics.moveTo(2,4);
    cout<<"┌─────────────────────────────────────────────────────────────────────────┐";
    for(int i=3;i<=24;i++){
        graphics.moveTo(i,4);
        cout<<"│";
        graphics.moveTo(i, 78);
        cout<<"│";
    }
    graphics.moveTo(24,4);
    cout<<"└─────────────────────────────────────────────────────────────────────────┘";
    graphics.setColor(graphics.FG_WHITE);
    
    graphics.setColor(graphics.FG_DARK_YELLOW);
    graphics.moveTo(3, 15);
    cout<<"\t\t SELECCIONE UN PERFIL DE USUARIO  : ";
    graphics.setColor(graphics.FG_LIGHT_BLUE);
    graphics.moveTo(5, 5);
    cout<<"\t\tNombre\t\tCodigo";
    graphics.setColor(graphics.FG_WHITE);
    int i(6), j;
    while(!archive.eof()){
        archive.read((char*)&perfil,sizeof(perfil));
        if(archive.eof())break;
        if(perfil.activate==1){
            j=18;
            graphics.moveTo(i, 12);
            cout<<i-5<<")";
            graphics.moveTo(i, j);
            cout<<perfil.name;
            j+=17;
            graphics.moveTo(i, j);
            cout<<perfil.code;
            i++;
        }
    }
    archive.close();
    cin.get();
}
void Perfiles::printUsers(Console& graphics){
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Perfiles.txt");
    if(!archive.good()){
        cout<<"No hay registros de Perfiles\n";
        return;
    }
    
    while(!archive.eof()){
        archive.read((char*)&perfil,sizeof(perfil));
        if(archive.eof())break;
        if(perfil.code!=1){
            if(perfil.activate==1){
                cout<<"\tPerfil : "<<perfil.name<<endl;
                cout<<"\tCodigo : "<<perfil.code<<endl<<endl;
            }
        }
    }
    archive.close();
}
string Perfiles::search(string& user){
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Perfiles.txt");
    string myStr;
    while(!archive.eof()){
        archive.read((char*)&perfil,sizeof(perfil));
        if(archive.eof())break;
        if(perfil.name==user){
            if(perfil.activate==1){
                myStr+="\tPerfil : ";myStr+=perfil.name;
                myStr+="\tCodigo : ";myStr+=to_string(perfil.code);
                return myStr;
            }
        }
    }
    return myStr;
}
string Perfiles::modify(int user,Console& graphics){
    if(user==1)
        throw invalid_argument("\tNo es posible Modificar al ADMINISTRADOR\n");
    string myStr;
    fstream archive("/Users/oscarsandoval/Desktop/proyect/Perfiles.txt",ios::in|ios::out);
    while(!archive.eof()){
        //archive.seekg(pos);
        archive.read((char*)&perfil,sizeof(perfil));
        if(user==perfil.code){
            if(perfil.activate==1){
                // archive.seekg(pos-4);
                long aux;
                aux=archive.tellg();
                archive.seekg(aux-28);
                cout<<"\t\tUsuario encontrado "<<endl<<endl;
                cout<<"Nuevo nombre : ";
                getline(cin,myStr);
                setName(myStr);
                archive.write((char*)&perfil,sizeof(perfil));
                activeUsers(user);
                return "Usuario Actualizado\n";
            }
            else{
                return "No se encontro el Perfil\n";
            }
        }
    }
    return "Perfil no encontrado";
}
string Perfiles::remove(int user){
    if(user==1)
        throw invalid_argument("\tNo es posible Eliminar al ADMINISTRADOR\n");
    if(!isValidRemove(user)){
        return "No es posible eliminar, existen usuarios con este codigo\n";
    }
    string myStr;
    ofstream aux("/Users/oscarsandoval/Desktop/proyect/Aux.txt",ios::out);
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Perfiles.txt");
    bool band=false;
    while(!archive.eof()){
        archive.read((char*)&perfil,sizeof(perfil));
        if(archive.eof())break;
        if(perfil.code==user){
            if(perfil.activate==1){
                band=true;
            }
            else{
                aux.write((char*)&perfil,sizeof(perfil));
            }
        }
        else{
            aux.write((char*)&perfil,sizeof(perfil));
        }
    }
    archive.close();
    aux.close();
    std::remove("/Users/oscarsandoval/Desktop/proyect/Perfiles.txt");
    rename("/Users/oscarsandoval/Desktop/proyect/Aux.txt","/Users/oscarsandoval/Desktop/proyect/Perfiles.txt");
    if(band==true){
        return "Perfil eliminado con exito\n";
    }
    return "Perfil no encontrado\n";

}
string Perfiles::logicRemove(int user){
    /*
    ifstream aux("/Users/oscarsandoval/Desktop/proyect/Perfiles.txt",ios::end);
    long pos,end;
    string myStr;
    pos=4;
    end=aux.tellg();
    aux.close();*/
    if(user==1)
        throw invalid_argument("\tNo es posible Eliminar al ADMINISTRADOR\n");
    fstream archive("/Users/oscarsandoval/Desktop/proyect/Perfiles.txt",ios::in|ios::out);
    while(!archive.eof()){
        //archive.seekg(pos);
        archive.read((char*)&perfil,sizeof(perfil));
        if(user==perfil.code){
           // archive.seekg(pos-4);
            //archive.read((char*)&perfil.activate,sizeof(int));
            if(perfil.activate==1){
               // archive.seekg(pos-4);
                long aux;
                aux=archive.tellg();
                archive.seekg(aux-28);
                setActivater(0);
                archive.write((char*)&perfil,sizeof(perfil));
                desactiveUsers(user);
                return "Usuario eliminado\n";
            }
            else{
                return "No se encontro el Perfil\n";
            }
        }
       // pos+=24;
    }
    return "Perfil no encontrado";
}
string Perfiles::active(int user){
    fstream archive("/Users/oscarsandoval/Desktop/proyect/Perfiles.txt",ios::in|ios::out);
    while(!archive.eof()){
        //archive.seekg(pos);
        archive.read((char*)&perfil,sizeof(perfil));
        if(user==perfil.code){
            // archive.seekg(pos-4);
            //archive.read((char*)&perfil.activate,sizeof(int));
            if(perfil.activate==0){
                // archive.seekg(pos-4);
                long aux;
                aux=archive.tellg();
                archive.seekg(aux-28);
                setActivater(1);
                archive.write((char*)&perfil,sizeof(perfil));
                activeUsers(user);
                return "Usuario Activado\n";
            }
            else{
                return "No se encontro el Perfil\n";
            }
        }
        // pos+=24;
    }
    return "Perfil no encontrado";
}
void Perfiles::modifyAccess(int user,Console& graphics){
    if(user==1)
        throw invalid_argument("\tNo es posible Modificar al ADMINISTRADOR\n");
    
    ifstream aux("/Users/oscarsandoval/Desktop/proyect/PermisosPerfiles",ios::end);
    long pos,end;
    string myStr;
    pos=0;
    end=aux.tellg();
    aux.close();
    fstream archive("/Users/oscarsandoval/Desktop/project/PermisosPerfiles",ios::in|ios::out);
    system("clear");
    while(pos<=end){
        archive.seekg(pos);
        archive.read((char*)&access.code,sizeof(int));
        if(user==access.code){
            archive.seekg(pos-4);
            bool band;
            string myStr;
            do{
                band=false;
                cout<<"\tPermisos para el perfil : "<<access.code<<endl;
                cout<<" : Registrar usuarios : S/N"<<endl;
                getline(cin,myStr);
                if(myStr=="S"||myStr=="s"){
                    access.agregar=1;
                }
                else if(myStr=="N"||myStr=="n"){
                    access.agregar=0;
                }
                else{
                    system("cls");
                    band=true;
                }
            }while(band==true);
            do{
                band=false;
                cout<<" : Ver usuarios : S/N"<<endl;
                getline(cin,myStr);
                if(myStr=="S"||myStr=="s"){
                    access.mostrar=1;
                }
                else if(myStr=="N"||myStr=="n"){
                    access.mostrar=0;
                }
                else{
                    system("cls");
                    band=true;
                }
            }while(band==true);
            do{
                band=false;
                cout<<" : Modificar Usuarios : S/N"<<endl;
                getline(cin,myStr);
                if(myStr=="S"||myStr=="s"){
                    access.modificar=1;
                }
                else if(myStr=="N"||myStr=="n"){
                    access.modificar=0;
                }
                else{
                    system("cls");
                    band=true;
                }
            }while(band==true);
            do{
                band=false;
                cout<<" : Eliminar usuarios : S/N"<<endl;
                getline(cin,myStr);
                if(myStr=="S"||myStr=="s"){
                    access.eliminar=1;
                }
                else if(myStr=="N"||myStr=="n"){
                    access.eliminar=0;
                }
                else{
                    system("cls");
                    band=true;
                }
            }while(band==true);
            do{
                band=false;
                cout<<" : Activar usuarios : S/N"<<endl;
                getline(cin,myStr);
                if(myStr=="S"||myStr=="s"){
                    access.activar=1;
                }
                else if(myStr=="N"||myStr=="n"){
                    access.activar=0;
                }
                else{
                    system("cls");
                    band=true;
                }
            }while(band==true);
            archive.write((char*)&access,sizeof(Perimisos));
            cout<<"Informacion actualizada con exito"<<endl;
            return;
        }
        pos+=28;
    }
    cout<<"No se encontro Perfil"<<endl;
}
bool Perfiles::isValidRemove(int & code){
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Usuarios.txt");
    long aux;
    int profile;
    int active;
    char a[30];
    if(!archive.good()){
        return true;
    }
    while(!archive.eof()){
        archive.read((char*)&active, sizeof(int));
        archive.read((char*)&aux,sizeof(long));
        archive.read((char*)&a,aux);
        archive.read((char*)&aux,sizeof(long));
        archive.read((char*)a,aux);
        archive.read((char*)&aux,sizeof(long));
        archive.read((char*)&a,aux);
        archive.read((char*)&profile, sizeof(int));
        archive.read((char*)&aux, sizeof(int));
        archive.read((char*)&aux, sizeof(int));
        if(archive.eof())break;
        if(code==profile){
            if(active==1){
                return false;
            }
        }
    }
    return true;
}
void Perfiles::desactiveUsers(int& user){
    ifstream archive1("/Users/oscarsandoval/Desktop/proyect/Usuarios.txt");
    ofstream archive("/Users/oscarsandoval/Desktop/proyect/Aux.txt",ios::out);
    string myStr;
    int activate,profileCode,officeCode,code;
    char name[30],userName[30], password[30];
    long aux;
    if(!archive1.good()){
        return;
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
        if(profileCode==user){
            if(activate==1){
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
}
void Perfiles::activeUsers(int& user){
    ifstream archive1("/Users/oscarsandoval/Desktop/proyect/Usuarios.txt");
    ofstream archive("/Users/oscarsandoval/Desktop/proyect/Aux.txt",ios::out);
    string myStr;
    int activate,profileCode,officeCode,code;
    char name[30],userName[30], password[30];
    long aux;
    if(!archive1.good()){
        return;
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
        if(profileCode==user){
            if(activate==0){
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
}

int Perfiles::getProfileCode(Console & graphics){
    ifstream archive;
    string myStr;
    bool band;
    do{
        system("clear");
        graphics.moveTo(2,4);
        cout<<"┌─────────────────────────────────────────────────────────────────────────┐";
        for(int i=3;i<=24;i++){
            graphics.moveTo(i,4);
            cout<<"│";
            graphics.moveTo(i, 78);
            cout<<"│";
        }
        graphics.moveTo(24,4);
        cout<<"└─────────────────────────────────────────────────────────────────────────┘";
        graphics.setColor(graphics.FG_WHITE);
        band=false;
        graphics.setColor(graphics.FG_DARK_YELLOW);
        graphics.moveTo(3, 15);
        cout<<"\t\t SELECCIONE UN PERFIL DE USUARIO  : ";
        graphics.setColor(graphics.FG_LIGHT_BLUE);
        graphics.moveTo(5, 5);
        cout<<"\t\tNombre\t\tCodigo";
        graphics.setColor(graphics.FG_WHITE);
        int i(6), j;
        List<int> codes;
        archive.open("/Users/oscarsandoval/Desktop/proyect/Perfiles.txt");
        while(!archive.eof()){
            j=18;
            archive.read((char*)&perfil, sizeof(Perfil));
            if(archive.eof())break;
            if(perfil.code==1)continue;
            if(perfil.activate==0)continue;
            graphics.moveTo(i, 12);
            cout<<i-5<<")";
            graphics.moveTo(i, j);
            cout<<perfil.name;
            j+=17;
            graphics.moveTo(i, j);
            cout<<perfil.code;
            codes.insertData(codes.getLastPos(), perfil.code);
            i++;
        }
        archive.close();
        graphics.moveTo(i, 15);
        cout<<"Elige un codigo : ";
        getline(cin,myStr);
        try{
            if(stoi(myStr)>0 && stoi(myStr)<=codes.size()+1){
                return codes[stoi(myStr)-1];
            }
            band=true;
        }catch(invalid_argument& ex){
            band=true;;
            graphics.moveTo(20, 15);
            graphics.setColor(graphics.FG_DARK_RED);
            cout<<"Ingrese una opcion valida";
            cin.get();
        }
    }while(band);
    return -1;
}
