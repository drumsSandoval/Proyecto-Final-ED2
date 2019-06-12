//
//  menu.cpp
//  proyect
//
//  Created by Oscar Sandoval on 2/4/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#include "menu.hpp"
#include <unistd.h>
#include <thread>
#include <chrono>

Menu::Menu():venta(){
    int contador=0;
    inicio();
    do{
        system("clear");
        if(login()){
            system("clear");
            contador=0;
        }
        else{
            contador++;
            graphics.moveTo(21,30);
            cout<<"Usuario incorrecto";
        }
    }while(contador<3);
    
    
}

int Menu::isValidUser(string& user)const{
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Usuarios.txt");
    string myStr;
    char auxC[30], useName[30];
    long aux;
    int code;
    int activate;
    if(!archive.good()){
        return false;
    }
    while(!archive.eof()){
        archive.read((char*)&activate, sizeof(int));
        archive.read((char*)&aux,sizeof(long));
        archive.read((char*)&auxC,aux);
        auxC[aux]='\0';
        archive.read((char*)&aux,sizeof(long));
        archive.read((char*)&useName,aux);
        useName[aux]='\0';
        archive.read((char*)&aux,sizeof(long));
        archive.read((char*)&auxC,aux);
        auxC[aux]='\0';
        archive.read((char*)&code, sizeof(int));
        archive.read((char*)&aux, sizeof(int));
        archive.read((char*)&aux, sizeof(int));
        if(useName==user){
            archive.close();
            if(activate==1)
                return code;
            return -1;
        }
        if(archive.eof())break;
    }
    archive.close();
    return -1;
}

int Menu::isValidPassword(string & user, string& password)const{
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Usuarios.txt");
    string myStr;
    char auxC[30], useName[30];
    long aux;
    int code;
    if(!archive.good()){
        return false;
    }
    while(!archive.eof()){
        archive.read((char*)&aux, sizeof(int));
        archive.read((char*)&aux,sizeof(long));
        archive.read((char*)&auxC,aux);
        auxC[aux]='\0';
        archive.read((char*)&aux,sizeof(long));
        archive.read((char*)&auxC,aux);
        auxC[aux]='\0';
        archive.read((char*)&aux,sizeof(long));
        archive.read((char*)&useName,aux);
        useName[aux]='\0';
        archive.read((char*)&aux, sizeof(int));
        archive.read((char*)&aux, sizeof(int));
        archive.read((char*)&code, sizeof(int));
        if(auxC==user){
            if(useName==password){
                archive.close();
                return code;
            }
            return -1;
        }
        if(archive.eof())break;
    }
    archive.close();
    return false;
}

bool Menu::login(){
    string myStr,aux;
    int code,profile;
    graphics.setColor(graphics.FG_DARK_CYAN);
    window();
    graphics.setColor(graphics.FG_DARK_GREEN);
    graphics.moveTo(4,31);
    cout<<" ╦  ┌─┐┌─┐┬┌┐┌";
    graphics.moveTo(5,31);
    cout<<" ║  │ ││ ┬││││";
    graphics.moveTo(6,31);
    cout<<" ╩═╝└─┘└─┘┴┘└┘";
    graphics.moveTo(9,22);
    graphics.setColor(graphics.FG_WHITE);
    cout<<"┌────────────────────────────────┐";
    graphics.moveTo(10,22);
    cout<<"|                                |";
    graphics.moveTo(11,22);
    cout<<"└────────────────────────────────┘";
    graphics.moveTo(10,26);
    cout<<"Usuario :";
    getline(cin,myStr);
    for(int i = 0;myStr[i];++i)
        myStr[i] = toupper(myStr[i]);
    aux=myStr;
    profile=isValidUser(myStr);
    if(profile!=-1){
        graphics.moveTo(12, 22);
        cout<<"┌────────────────────────────────┐";
        graphics.moveTo(13,22);
        cout<<"|                                |";
        graphics.moveTo(14,22);
        cout<<"└────────────────────────────────┘";
        graphics.moveTo(13,25);
        cout<<"Password : ";
        graphics.setColor(graphics.FG_DARK_GRAY);
        getline(cin,myStr);
        for(int i = 0;myStr[i];++i)
            myStr[i] = toupper(myStr[i]);
        graphics.setColor(graphics.FG_WHITE);
        code=isValidPassword(aux,myStr);
        if(code!=-1){
            if(code==1&&profile==1){
                menuAdmin();
            }
            else{
                menuUsers(code,profile);
            }
            return true;
        }
    }
    return false;
}
void Menu::userAccess(Perimisos & access,int& profile){
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/PermisosPerfiles.txt");
    while(!archive.eof()){
        archive.read((char*)&access,sizeof(access));
        if(profile==access.code){
            return;
        }
    }
    cout<<"No lo encuentra"<<endl;
    
}

void Menu::menuUsuarios(int & code,int & profile){
    string myStr;
    bool band;
    Perimisos access;
    usuario.logicRemove(code);
    userAccess(access,profile);
    string online = usuario.getName(code);
    system("clear");
    do{
        graphics.setColor(graphics.FG_LIGHT_GREEN);
        window();
        graphics.moveTo(4, 43);
        cout<<"Sesion de :  "<<online<<endl;
        graphics.moveTo(5, 15);
        cout<<"\t\t\tMenu Usuarios"<<endl;
        graphics.moveTo(7, 15);
        cout<<"1)Agregar "<<endl;
        graphics.moveTo(8, 15);
        cout<<"2)Imprimir"<<endl;
        graphics.moveTo(9, 15);
        cout<<"3)Buscar"<<endl;
        graphics.moveTo(10, 15);
        cout<<"4)Modificar"<<endl;
        graphics.moveTo(11, 15);
        cout<<"5)Eliminar"<<endl;
        graphics.moveTo(12, 15);
        cout<<"6)Activar usuario"<<endl;
        graphics.moveTo(13, 15);
        cout<<"7)Salir"<<endl;
        graphics.moveTo(14, 15);
        cout<<"Elige una opcion : ";
        getline(cin,myStr);
        //Salir
        if(myStr=="7"){
            system("clear");
            cout<<"Adios Vaquero"<<endl;
        }
        //Agregar
        else if(myStr=="1"){
            if(access.agregar==1){
                ifstream archive("/Users/oscarsandoval/Desktop/proyect/PermisosPerfiles.txt",ios::end);
                if(archive.tellg()<=28){
                    graphics.moveTo(18, 40);
                    graphics.setColor(graphics.FG_DARK_RED);
                    cout<<"No hay perfiles disponibles"<<endl;
                    cin.get();
                }
                else{
                    graphics.setColor(graphics.FG_DARK_BLUE);
                    window();
                    graphics.moveTo(5, 15);
                    cout<<"\t\t\tAgregar Usuario : ";
                    graphics.moveTo(7, 15);
                    cout<<"Nombre : ";
                    getline(cin,myStr);
                    for(int i = 0;myStr[i];++i)
                        myStr[i] = toupper(myStr[i]);
                    usuario.setName(myStr);
                    graphics.moveTo(8, 15);
                    cout<<"Nombre de Usuario : ";
                    getline(cin,myStr);
                    for(int i = 0;myStr[i];++i)
                        myStr[i] = toupper(myStr[i]);
                    usuario.setUserName(myStr);
                    do{
                        band=false;
                        try{
                            usuario.setOfficeCode(oficina.getOffice(graphics));
                        }catch(invalid_argument &ex){
                            system("clear");
                            cerr<<ex.what();
                            band=true;
                        }
                    }while(band==true||usuario.getOfficceCode()==-1);
                    do{
                        band=false;
                        try{
                            usuario.setProfileCode(perfil.getProfileCode(graphics));
                        }catch(invalid_argument &ex){
                            system("clear");
                            cerr<<ex.what();
                            band=true;
                        }
                    }while(band==true||usuario.getProfileCode()==-1);
                    graphics.setColor(graphics.FG_DARK_YELLOW);
                    window();
                    graphics.moveTo(5, 15);
                    cout<<"\t\t\tAgregar Usuario : ";
                    graphics.moveTo(7, 15);
                    cout<<"Password : ";
                    getline(cin,myStr);
                    for(int i = 0;myStr[i];++i)
                        myStr[i] = toupper(myStr[i]);
                    usuario.setPassword(myStr);
                    usuario.insert();
                    graphics.moveTo(8, 15);
                    cout<<"Codigo de usuario : "<<usuario.getCode()<<endl;
                    cin.get();
                }
            }
            else{
                cout<<"Accion no permitida"<<endl;
            }
        }
        //Print
        else if(myStr=="2"){
            graphics.setColor(graphics.FG_LIGHT_GREEN);
            window();
            if(access.mostrar==1){
                usuario.toString(graphics);
            }
            else{
                graphics.moveTo(3, 15);
               cout<<"Accion no permitida"<<endl;
                cin.get();
            }
        }
        //Buscar
        else if(myStr=="3"){
            system("clear");
            if(access.buscar==1){
                int myInt;
                do{
                    band=false;
                    cout<<"\t\tBuscar Usuario"<<endl;
                    cout<<"Codigo del Usuario : "<<endl;
                    getline(cin,myStr);
                    try{
                        myInt=stoi(myStr);
                    }catch(invalid_argument &ex){
                        system("clear");
                        cerr<<ex.what();
                        band=true;
                    }
                }while(band==true);
                window();
                usuario.search(myInt,graphics);
            }
            else{
               cout<<"Accion no permitida"<<endl;
            }
        }
        //Modificar
        else if(myStr=="4"){
            system("clear");
            if(access.modificar==1){
                int myInt;
                do{
                    band=false;
                    cout<<"\t\tModificar Usuario"<<endl
                    <<"Codigo  : ";
                    getline(cin,myStr);
                    try{
                        myInt=stoi(myStr);
                    }catch(invalid_argument &ex){
                        system("clear");
                        cerr<<ex.what();
                        band=true;
                    }
                }while(band==true);
                cout<<usuario.modify(myInt,graphics)<<endl;
            }
            else{
                cout<<"Accion no permitida"<<endl;
            }
        }
        //Eliminar
        else if(myStr=="5"){
            // eliminar();
            system("clear");
            if(access.eliminar==1){
                int myInt;
                do{
                    band=false;
                    cout<<"\t\tEliminar Usuario : "<<endl
                    <<"Codigo de Usuario : ";
                    getline(cin,myStr);
                    try{
                        myInt=stoi(myStr);
                    }catch(invalid_argument &ex){
                        system("clear");
                        cerr<<ex.what();
                        band=true;
                    }
                }while(band==true);
                do{
                    system("clear");
                    cout<<"\t\tEliminar Usuario : "<<endl
                    <<"1)Eliminar logico"<<endl
                    <<"2)Eliminacion fisica"<<endl
                    <<"Elige una opcion : ";
                    getline(cin,myStr);
                    if(myStr=="1"){
                        cout<<usuario.logicRemove(myInt)<<endl;
                        cin.get();
                    }
                    if(myStr=="2"){
                        cout<<usuario.remove(myInt)<<endl;
                        cin.get();
                    }
                }while(myStr!="1"&&myStr!="2");
            }
            else{
                cout<<"Accion no permitida"<<endl;
            }
        }
        else if(myStr=="6"){
            if(access.activar==1){
                int myInt;
                do{
                    band=false;
                    cout<<"\t\tActivar Usuario : "<<endl
                    <<"Codigo de Usuario : ";
                    getline(cin,myStr);
                    try{
                        myInt=stoi(myStr);
                    }catch(invalid_argument &ex){
                        system("clear");
                        cerr<<ex.what();
                        band=true;
                    }
                }while(band==true);
                cout<<usuario.active(myInt);
                
            }
            else{
                cout<<"Acceso no permitido"<<endl;
                cin.get();
            }
        }
        //default
        else{
            system("clear");
            cout<<"Opcion no valida"<<endl;
            cin.get();
        }
    }while(myStr!="7");
    usuario.active(code);
}

//Menu Clientes
void Menu::menuClientes(int& code,int& profile){
    string myStr;
    Perimisos access;
    userAccess(access,profile);
    string online(usuario.getName(code));
    system("clear");
    do{
        graphics.setColor(graphics.FG_DARK_YELLOW);
        window();
        graphics.setColor(graphics.FG_WHITE);
        graphics.moveTo(4, 43);
        cout<<"Sesion de :  "<<online<<endl;
        graphics.moveTo(5, 15);
        cout<<"\t\t\tMenu Clientes";
        graphics.moveTo(7, 15);
        cout<<"1)Agregar cliente";
        graphics.moveTo(8, 15);
        cout<<"2)Imprimir";
        graphics.moveTo(9, 15);
        cout<<"3)Buscar";
        graphics.moveTo(10, 15);
        cout<<"4)Modificar";
        graphics.moveTo(11, 15);
        cout<<"5)Eliminar";
        graphics.moveTo(12, 15);
        cout<<"6)Activar Cliente";
        graphics.moveTo(13, 15);
        cout<<"7)Comprimir Archivo de Clientes";
        graphics.moveTo(14, 15);
        cout<<"8)Descomprimir Archivo de Clientes";
        graphics.moveTo(15, 15);
        cout<<"9)Salir";
        graphics.moveTo(16, 15);
        cout<<"Elige una opcion : ";
        getline(cin,myStr);
        //Salir
        if(myStr=="9"){
         
        }
        //Agregar
        else if(myStr=="1"){
            if(access.agregar==1){
                if(cliente.isValidInsert()){
                    graphics.moveTo(18, 40);
                    cout<<"Permiso denegado"<<endl;
                    cin.get();
                }else{
                    graphics.setColor(graphics.FG_LIGHT_GREEN);
                    window();
                    graphics.moveTo(5, 15);
                    cout<<"\t\tRegistar cliente"<<endl;
                    graphics.moveTo(7, 15);
                    cout<<"Nombre : ";
                    getline(cin,myStr);
                    for(int i = 0;myStr[i];++i)
                        myStr[i] = toupper(myStr[i]);
                    cliente.setName(myStr);
                    graphics.moveTo(8, 15);
                    cout<<"Telefono : ";
                    getline(cin,myStr);
                    cliente.setPhone(myStr);
                    graphics.moveTo(9, 15);
                    cout<<"Direccion : ";
                    getline(cin,myStr);
                    for(int i = 0;myStr[i];++i)
                        myStr[i] = toupper(myStr[i]);
                    cliente.setAddress(myStr);
                    cliente.insert();
                }
            }
            else{
                graphics.moveTo(18, 40);
                cout<<"Permiso denegado"<<endl;
                cin.get();
            }
        }
        //Print
        else if(myStr=="2"){
            if(access.mostrar==1){
                graphics.setColor(graphics.FG_LIGHT_GREEN);
                window();
                cliente.toString(graphics);
            }
            else{
                graphics.moveTo(18, 40);
                cout<<"Permiso denegado"<<endl;
                cin.get();
            }
        }
        //Buscar
        else if(myStr=="3"){
            if(access.buscar==1){
                if(!cliente.isEmpty()){
                    graphics.moveTo(18, 40);
                    cout<<"Accion no permitidda :,(";
                    cin.get();
                }else{
                    graphics.setColor(graphics.FG_LIGHT_GREEN);
                    window();
                    graphics.moveTo(7, 15);
                    cout<<"\t\tBuscar Cliente"<<endl;
                    graphics.moveTo(8, 15);
                    cout<<"Codigo del cliente : "<<endl;
                    getline(cin,myStr);
                    for(int i = 0;myStr[i];i++)
                        myStr[i] = toupper(myStr[i]);
                    graphics.setColor(graphics.FG_LIGHT_GREEN);
                    window();
                    try{
                        cliente.search(myStr,graphics);
                    }catch(invalid_argument &ex){
                        graphics.moveTo(13, 18);
                        cerr<<ex.what();
                        cin.get();
                    }
                }
            }
            else{
                graphics.moveTo(18, 40);
                cout<<"Permiso denegado"<<endl;
                cin.get();
            }
        }
        //Modificar
        else if(myStr=="4"){
            // modificar();
            if(access.modificar==1){
                if(!cliente.isEmpty()){
                    graphics.moveTo(18, 40);
                    cout<<"Accion no permitidda :,(";
                    cin.get();
                }else{
                    graphics.setColor(graphics.FG_LIGHT_GREEN);
                    window();
                    graphics.moveTo(5, 15);
                    cout<<"\t\tModificar Cliente";
                    graphics.moveTo(7, 15);
                    cout<<"Codigo de cliente : ";
                    getline(cin,myStr);
                    cliente.modify(myStr,graphics);
                }
            }
            else{
                graphics.moveTo(18, 40);
                cout<<"Permiso denegado"<<endl;
                cin.get();
            }
        }
        //Eliminar
        else if(myStr=="5"){
            // eliminar();
            if(access.eliminar==1){
                if(!cliente.isEmpty()){
                    graphics.moveTo(18, 40);
                    cout<<"Accion no permitidda :,(";
                    cin.get();
                }
                else{
                    graphics.setColor(graphics.FG_LIGHT_GREEN);
                    window();
                    string aux;
                    graphics.moveTo(5, 15);
                    cout<<"\t\tEliminar Cliente"<<endl;
                    graphics.moveTo(7, 15);
                    cout<<"Codigo de Cliente : ";
                    getline(cin,myStr);
                    graphics.setColor(graphics.FG_DARK_BLUE);
                    window();
                    graphics.moveTo(5, 15);
                    cout<<"\t\t\tEliminar cliente";
                    graphics.moveTo(6, 15);
                    cout<<"1)Eliminacion logica";
                    graphics.moveTo(7, 15);
                    cout<<"2)Eliminacion fisica";
                    graphics.moveTo(8, 15);
                    cout<<"Elige una opcion : ";
                    getline(cin,aux);
                    if(aux=="2"){
                        graphics.moveTo(18, 15);
                        cout<<cliente.remove(myStr)<<endl;
                        cin.get();
                    }
                    else if(aux=="1"){
                         graphics.moveTo(18, 15);
                        cout<<cliente.logicRemove(myStr)<<endl;
                        cin.get();
                    }
                    else{
                        graphics.moveTo(18, 15);
                        cout<<"Dato no valido"<<endl;
                        cin.get();
                    }
                }
            }
            else{
                graphics.moveTo(18, 15);
                cout<<"Permiso denegado"<<endl;
                cin.get();
            }
        }
        else if(myStr=="6"){
            if(access.activar==1){
                if(!cliente.isEmpty()){
                    graphics.moveTo(18, 40);
                    cout<<"Accion no permitidda :,(";
                    cin.get();
                }else{
                    cout<<"\t\tActivar Cliente"<<endl
                    <<"Codigo de Cliente : ";
                    getline(cin,myStr);
                    cout<<cliente.active(myStr);
                }
            }
            else{
                system("clear");
                cout<<"Permiso denegado"<<endl;
            }
        }else if(myStr=="7"){
            system("clear");
            if(!cliente.isEmpty()){
                graphics.moveTo(18, 40);
                cout<<"Accion no permitidda :,(";
                cin.get();
            }else{
                Huffman<data> huffman;
                List<data> list;
                List<int> listInt;
                cliente.comprimirArchivo(huffman, list, listInt);
                huffman.printTree();
                cin.get();
            }
            
        }else if(myStr=="8"){
            if(cliente.isEmpty()){
                graphics.moveTo(18, 40);
                cout<<"Accion no permitidda :-(";
                cin.get();
            }else{
                cliente.descomprimirArchivo();
            }
        }
        //default
        else{
            cout<<"Opcion no valida"<<endl;
        }
    }while(myStr!="9");
   // cliente.active(to_string(code));
}

void Menu::inicio(){
    graphics.clearScreen();
    //graphics.setColor(graphics.BG_DARK_GRAY);
    for(int i=0;i<24;i++){
        for(int j=0;j<80;j++){
            cout<<" ";
        }
        cout<<endl;
    }
    // graphics.setColor(graphics.BG_DARK_BLUE);
    graphics.moveTo(2,23);
    graphics.setColor(graphics.FG_LIGHT_BLUE);
    cout<<"┌┬┐┬─┐┌─┐┌┐┌┌─┐┌─┐┌─┐┬─┐┌┬┐┌─┐┌─┐";
    graphics.moveTo(3,23);
    cout<<" │ ├┬┘├─┤│││└─┐├─┘│ │├┬┘ │ ├┤ └─┐";
    graphics.moveTo(4,23);
    cout<<" ┴ ┴└─┴ ┴┘└┘└─┘┴  └─┘┴└─ ┴ └─┘└─┘";
    graphics.moveTo(5,25);
    this_thread::sleep_for(chrono::milliseconds(100));
    cout<<"┌┬┐┌─┐┬─┐┬─┐┌─┐┌─┐┌┬┐┬─┐┌─┐┌─┐";
    graphics.moveTo(6,25);
    cout<<" │ ├┤ ├┬┘├┬┘├┤ └─┐ │ ├┬┘├┤ └─┐";
    graphics.moveTo(7,25);
    cout<<" ┴ └─┘┴└─┴└─└─┘└─┘ ┴ ┴└─└─┘└─┘";
    graphics.setColor(graphics.FG_WHITE);
    //graphics.setColor(graphics.BG_DARK_GRAY);
    graphics.moveTo(11,12);
    graphics.setColor(graphics.FG_WHITE);
    cout<<"𝓢𝓮𝓶𝓲𝓷𝓪𝓻𝓲𝓸 𝓭𝓮 𝓼𝓸𝓵𝓾𝓬𝓲𝓸́𝓷 𝓭𝓮 𝓹𝓻𝓸𝓫𝓵𝓮𝓶𝓪𝓼 𝓭𝓮 𝓮𝓼𝓽𝓻𝓾𝓬𝓽𝓾𝓻𝓪 𝓭𝓮 𝓭𝓪𝓽𝓸𝓼 𝓲𝓲";
    graphics.moveTo(26,2);
    cout<<"𝓒𝓻𝓮𝓪𝓽𝓮𝓭 𝓫𝔂 𝓞𝓼𝓬𝓪𝓻 𝓢𝓪𝓷𝓭𝓸𝓿𝓪𝓵";
    graphics.setColor(graphics.FG_DARK_BLUE);
    // graphics.setColor(graphics.BG_DARK_RED);
    graphics.moveTo(13, 33);
    cout<<"···Cargando···"<<endl;
    // graphics.setColor(graphics.BG_DARK_GRAY);
    graphics.setColor(graphics.FG_DARK_GREEN);
    //this_thread::sleep_for(chrono::milliseconds(1000));
    //sleep(1)
    graphics.moveTo(14, 25);
    cout<<"Precione enter para continuar";
    graphics.moveTo(16,26);
    cout<<"                          __";
    graphics.moveTo(17, 26);
    cout<<" .-----------------------'  |";
    graphics.moveTo(18,26);
    cout<<" /| _ .---. .---. .---. .---.|";
    graphics.moveTo(19, 26);
    cout<<" |j||||___| |___| |___| |___||";
    graphics.moveTo(20,26);
    cout<<" |=|||=======================|";
    graphics.moveTo(21,26);
    cout<<" [_|j||(O)|__________|(O)|___]";
    cin.get();
    graphics.restore();
    graphics.restore();
    graphics.restore();
}

void Menu::menuPerfiles(int& code,int&profile){
    system("clear");
    string myStr;
    Perimisos access;
    userAccess(access,profile);
    bool band;
    do{
        graphics.setColor(graphics.FG_DARK_GREEN);
        window();
        graphics.moveTo(5, 15);
        cout<<"\t\t\tMenu Perfiles"<<endl;
        graphics.moveTo(6, 15);
        cout<<"1)Agregar"<<endl;
        graphics.moveTo(7, 15);
        cout<<"2)Mostrar"<<endl;
        graphics.moveTo(8, 15);
        cout<<"3)Buscar"<<endl;
        graphics.moveTo(9, 15);
        cout<<"4)Modificar"<<endl;
        graphics.moveTo(10, 15);
        cout<<"5)Eliminar"<<endl;
        graphics.moveTo(11, 15);
        cout<<"6)Activar Perfil"<<endl;
        graphics.moveTo(12, 15);
        cout<<"7)Salir"<<endl;
        graphics.moveTo(13, 15);
        cout<<"Elige una opcion : ";
        getline(cin,myStr);
        if(myStr=="1"){
            if(access.agregar==1){
                graphics.setColor(graphics.FG_DARK_CYAN);
                window();
                graphics.moveTo(5, 15);
                cout<<"\t\t\tAgregar Perfil";
                graphics.moveTo(6, 15);
                cout<<"Nombre del Perfil : ";
                getline(cin,myStr);
                for(int i = 0;myStr[i];++i)
                    myStr[i] = toupper(myStr[i]);
                perfil.setName(myStr);
                perfil.setCode();
                perfil.access.code=perfil.getCode();
                do{
                    band=false;
                    graphics.setColor(graphics.FG_DARK_CYAN);
                    window();
                    graphics.moveTo(6, 15);
                    cout<<"\tPermisos para el perfil : "<<endl;
                    graphics.moveTo(7, 15);
                    cout<<perfil.getName()<<" : Registrar usuarios : S/N"<<endl;
                    graphics.moveTo(8, 15);
                    getline(cin,myStr);
                    if(myStr=="S"||myStr=="s"){
                        perfil.access.agregar=1;
                    }
                    else if(myStr=="N"||myStr=="n"){
                        perfil.access.agregar=0;
                    }
                    else{
                        system("cls");
                        band=true;
                    }
                }while(band==true);
                do{
                    graphics.setColor(graphics.FG_DARK_CYAN);
                    window();
                    band=false;
                    graphics.moveTo(6, 15);
                    cout<<"\tPermisos para el perfil : "<<endl;
                    graphics.moveTo(7, 15);
                    cout<<perfil.getName()<<" : Buscar usuarios : S/N"<<endl;
                    graphics.moveTo(8, 15);
                    getline(cin,myStr);
                    if(myStr=="S"||myStr=="s"){
                        perfil.access.buscar=1;
                    }
                    else if(myStr=="N"||myStr=="n"){
                        perfil.access.buscar=0;
                    }
                    else{
                        system("cls");
                        band=true;
                    }
                }while(band==true);
                do{
                    graphics.setColor(graphics.FG_DARK_CYAN);
                    window();
                    band=false;
                    graphics.moveTo(6, 15);
                    cout<<"\tPermisos para el perfil : "<<endl;
                    graphics.moveTo(7, 15);
                    cout<<perfil.getName()<<" : Ver usuarios : S/N"<<endl;
                    graphics.moveTo(8, 15);
                    getline(cin,myStr);
                    if(myStr=="S"||myStr=="s"){
                        perfil.access.mostrar=1;
                    }
                    else if(myStr=="N"||myStr=="n"){
                        perfil.access.mostrar=0;
                    }
                    else{
                        system("cls");
                        band=true;
                    }
                }while(band==true);
                do{
                    band=false;
                    graphics.setColor(graphics.FG_DARK_CYAN);
                    window();
                    graphics.moveTo(6, 15);
                    cout<<"\tPermisos para el perfil : "<<endl;
                    graphics.moveTo(7, 15);
                    cout<<perfil.getName()<<" : Modificar Usuarios : S/N"<<endl;
                    graphics.moveTo(8, 15);
                    getline(cin,myStr);
                    if(myStr=="S"||myStr=="s"){
                        perfil.access.modificar=1;
                    }
                    else if(myStr=="N"||myStr=="n"){
                        perfil.access.modificar=0;
                    }
                    else{
                        system("cls");
                        band=true;
                    }
                }while(band==true);
                do{
                    graphics.setColor(graphics.FG_DARK_CYAN);
                    window();
                    band=false;
                    graphics.moveTo(6, 15);
                    cout<<"\tPermisos para el perfil : "<<endl;
                    graphics.moveTo(7, 15);
                    cout<<perfil.getName()<<" : Eliminar usuarios : S/N"<<endl;
                    graphics.moveTo(8, 15);
                    getline(cin,myStr);
                    if(myStr=="S"||myStr=="s"){
                        perfil.access.eliminar=1;
                    }
                    else if(myStr=="N"||myStr=="n"){
                        perfil.access.eliminar=0;
                    }
                    else{
                        system("cls");
                        band=true;
                    }
                }while(band==true);
                do{
                    graphics.setColor(graphics.FG_DARK_CYAN);
                    window();
                    band=false;
                    graphics.moveTo(6, 15);
                    cout<<"\tPermisos para el perfil : ";
                    graphics.moveTo(7, 15);
                    cout<<perfil.getName()<<" : Activar usuarios : S/N";
                    graphics.moveTo(8, 15);
                    getline(cin,myStr);
                    if(myStr=="S"||myStr=="s"){
                        perfil.access.activar=1;
                    }
                    else if(myStr=="N"||myStr=="n"){
                        perfil.access.activar=0;
                    }
                    else{
                        system("cls");
                        band=true;
                    }
                }while(band==true);
                perfil.insert();
                graphics.moveTo(9, 15);
                cout<<"Codigo de Perfil : "<<perfil.getCode();
                cin.get();
            }
            else{
                graphics.moveTo(15, 20);
                cout<<"Permiso denegado"<<endl;
                cin.get();
            }
        }
        else if(myStr=="2"){
            if(access.mostrar==1){
                perfil.print(graphics);
            }
            else{
                graphics.moveTo(15, 20);
                cout<<"Permiso denegado"<<endl;
                cin.get();
            }
        }
        else if(myStr=="3"){
            if(access.buscar==1){
                graphics.setColor(graphics.FG_DARK_CYAN);
                window();
                graphics.moveTo(5, 15);
                cout<<"\t\tBuscar Perfil : ";
                graphics.moveTo(6, 15);
                cout<<"Nombre del perfil  a buscar : ";
                getline(cin,myStr);
                for(int i = 0;myStr[i];++i)
                    myStr[i] = toupper(myStr[i]);
                graphics.moveTo(8, 15);
                try{
                    cout<<perfil.search(myStr);
                }catch(invalid_argument& ex){
                    cerr<<ex.what();
                }
                cin.get();
            }
            else{
                graphics.moveTo(15, 20);
                cout<<"Permiso denegado"<<endl;
                cin.get();
            }
        }
        else if(myStr=="4"){
            if(access.modificar==1){
                graphics.setColor(graphics.FG_DARK_CYAN);
                window();
                graphics.moveTo(5, 15);
                cout<<"\t\t\tModificar Perfil"<<endl;
                graphics.moveTo(6, 15);
                cout<<"1)Modificar Nombre"<<endl;
                graphics.moveTo(7, 15);
                cout<<"2)Modificar Permisos"<<endl;
                graphics.moveTo(8, 15);
                cout<<"3)Regresar"<<endl;
                graphics.moveTo(9, 15);
                cout<<"Elige una opcion : ";
                getline(cin,myStr);
                if(myStr=="1"){
                    do{
                        band=false;
                        graphics.setColor(graphics.FG_DARK_CYAN);
                        window();
                        graphics.moveTo(5, 15);
                        cout<<"\t\t\tModificar Perfil ";
                        graphics.moveTo(6, 15);
                        cout<<"Codigo de Perfil  : ";
                        getline(cin,myStr);
                        try{
                            graphics.moveTo(8, 15);
                            cout<<perfil.modify(stoi(myStr),graphics);
                            cin.get();
                        }catch(invalid_argument& ex){
                            graphics.moveTo(8, 15);
                            cerr<<ex.what()<<endl;
                            cin.get();
                            band=true;
                            if(myStr=="1")
                                band=false;
                        }
                    }while(band==true);
                }
                else if(myStr=="2"){
                    do{
                        band=false;
                        graphics.setColor(graphics.FG_DARK_CYAN);
                        window();
                        graphics.moveTo(5, 15);
                        cout<<"\t\t\tModificar Perfil "<<endl;
                        graphics.moveTo(6, 15);
                        cout<<"Codigo de Perfil  : ";
                        getline(cin,myStr);
                        try{
                            graphics.moveTo(8, 15);
                            perfil.modifyAccess(stoi(myStr),graphics);
                            cin.get();
                        }catch(invalid_argument& ex){
                            graphics.moveTo(8, 15);
                            cerr<<ex.what()<<endl;
                            cin.get();
                            band=true;
                            if(myStr=="1")
                                band=false;
                        }
                    }while(band==true);
                }
                else if(myStr=="3"){
                
                }
                else{
                    graphics.moveTo(15, 15);
                    cout<<"Opcion no valida"<<endl;
                    cin.get();
                }
            }
            else{
                graphics.moveTo(15, 20);
                cout<<"Permiso denegado"<<endl;
                cin.get();
            }
        }
        else if(myStr=="5"){
            if(access.eliminar==1){
                graphics.setColor(graphics.FG_DARK_CYAN);
                window();
                bool band;
                string aux;
                graphics.moveTo(5, 15);
                cout<<"\t\tEliminar Perfil";
                graphics.moveTo(6, 15);
                cout<<"1)Eliminacion logica";
                graphics.moveTo(7, 15);
                cout<<"2)Eliminacion fisica";
                graphics.moveTo(8, 15);
                cout<<"3)Regresar";
                graphics.moveTo(9, 15);
                cout<<"Elige una opcion : ";
                getline(cin,myStr);
                if(myStr=="1"){
                    do{
                        band=false;
                        graphics.setColor(graphics.FG_DARK_CYAN);
                        window();
                        graphics.moveTo(5, 15);
                        cout<<"\t\t\tEliminar Perfil ";
                        graphics.moveTo(6, 15);
                        cout<<"Codigo de Perfil  : ";
                        getline(cin,myStr);
                        try{
                            if(to_string(profile)!=myStr){
                                graphics.moveTo(8, 15);
                                cout<<perfil.logicRemove(stoi(myStr));
                                cin.get();
                            }
                            else{
                                graphics.moveTo(8, 15);
                                cout<<"No puede eliminar este perfil";
                                cin.get();
                            }
                        }catch(invalid_argument& ex){
                            graphics.moveTo(8, 15);
                            cerr<<ex.what()<<endl;
                            band=true;
                            if(myStr=="1")
                                band=false;
                            cin.get();
                        }
                    }while(band==true);
                }
                else if(myStr=="2"){
                    do{
                        graphics.setColor(graphics.FG_DARK_CYAN);
                        window();
                        band=false;
                        graphics.moveTo(5, 15);
                        cout<<"\t\t\tEliminar Perfil ";
                        graphics.moveTo(6, 15);
                        cout<<"Codigo de Perfil  : ";
                        getline(cin,myStr);
                        try{
                            graphics.moveTo(8, 15);
                            cout<<perfil.remove(stoi(myStr));
                            cin.get();
                        }catch(invalid_argument& ex){
                            graphics.moveTo(8, 15);
                            cerr<<ex.what()<<endl;
                            band=true;
                            if(myStr=="1")
                                band=false;
                            cin.get();
                        }
                    }while(band==true);
                }
                else if(myStr=="3"){
                    do{
                        graphics.setColor(graphics.FG_DARK_CYAN);
                        window();
                        band=false;
                        graphics.moveTo(5, 15);
                        cout<<"\t\t\tModificar Permisos de  Perfil "<<endl;
                        graphics.moveTo(6, 15);
                        cout<<"Codigo de Perfil  : ";
                        getline(cin,myStr);
                        try{
                            graphics.moveTo(8, 15);
                            perfil.modifyAccess(stoi(myStr),graphics);
                            cin.get();
                        }catch(invalid_argument& ex){
                            graphics.moveTo(8, 15);
                            cerr<<ex.what()<<endl;
                            band=true;
                            if(myStr=="1")
                                band=false;
                            cin.get();
                        }
                    }while(band==true);
                }
                else{
                    graphics.moveTo(8, 15);
                    cout<<"Opcion no valida"<<endl;
                    cin.get();
                }
            }
            else{
                graphics.moveTo(15, 20);
                cout<<"Permiso denegado"<<endl;
                cin.get();
            }
        }
        else if(myStr=="6"){
            if(access.activar==1){
                do{
                    graphics.setColor(graphics.FG_DARK_CYAN);
                    window();
                    band=false;
                    graphics.moveTo(5, 15);
                    cout<<"\t\t\tActivar Perfil "<<endl;
                    graphics.moveTo(6, 15);
                    cout<<"Codigo de perfil : ";
                    getline(cin,myStr);
                    try{
                        graphics.moveTo(8, 15);
                        cout<<perfil.active(stoi(myStr));
                        cin.get();
                    }catch(invalid_argument& ex){
                        graphics.moveTo(8, 15);
                        cerr<<ex.what()<<endl;
                        cin.get();
                        band=true;
                    }
                }while(band==true);
            }
            else{
                graphics.moveTo(15, 20);
                cout<<"Permiso denegado"<<endl;
                cin.get();
            }
        }
        else if(myStr=="7"){
        }
        else{
            cout<<"Opcion no valida"<<endl;
        }
    }while(myStr!="7");
}

void Menu::menuDestinos(int& code,int& profile){
    Perimisos access;
    List<Indices> listIndice;
    List<IndiceSecundario> listZona;
    List<nodo> listaInvertida; 
    Grafo grafo;
    bool band;
    string myStr;
    Destinos destino(listIndice,listZona,listaInvertida);
    userAccess(access, profile);
    destino.readGraph(grafo);
    string online = usuario.getName(code);
    do{
        graphics.setColor(graphics.FG_LIGHT_PURPLE);
        window();
        graphics.moveTo(4, 43);
        cout<<"Sesion de :  "<<online<<endl;
        graphics.moveTo(5, 15);
        cout<<"\t\t\tMenu Destinos: "<<endl;
        graphics.moveTo(7, 15);
        cout<<"\t1)Agregar Destino"<<endl;
        graphics.moveTo(8, 15);
        cout<<"\t2)Mostrar Destinos"<<endl;
        graphics.moveTo(9, 15);
        cout<<"\t3)Imprimir TDA"<<endl;
        graphics.moveTo(10, 15);
        cout<<"\t4)Consultar"<<endl;
        graphics.moveTo(11, 15);
        cout<<"\t5)Modificar"<<endl;
        graphics.moveTo(12, 15);
        cout<<"\t6)Eliminar"<<endl;
        graphics.moveTo(13, 15);
        cout<<"\t7)Activar Destino"<<endl;
        graphics.moveTo(14, 15);
        cout<<"\t8)Mostrar Grafo"<<endl;
        graphics.moveTo(15, 15);
        cout<<"\t9)Recorridos";
        graphics.moveTo(16, 15);
        cout<<"\t10)Rutas";
        graphics.moveTo(17, 15);
        cout<<"\t11)Buscar Zona";
        graphics.moveTo(18, 15);
        cout<<"\t12)Mostrar Lista Invertida";
        graphics.moveTo(19, 15);
        cout<<"\t13)Salir"<<endl;
        graphics.moveTo(20, 15);
        cout<<"\tElige una opcion : ";
        getline(cin, myStr);
        if(myStr=="1"){
            if(access.agregar==1){
                graphics.setColor(graphics.FG_DARK_CYAN);
                window();
                float aux;
                string d;
                graphics.moveTo(5, 15);
                cout<<"\t\tAgregar Destino : "<<endl;
                 graphics.moveTo(7, 15);
                cout<<"\tDestino : ";
                getline(cin,myStr);
                for(int i = 0;myStr[i];++i)
                    myStr[i] = toupper(myStr[i]);
                destino.setName(myStr);
                graphics.moveTo(8, 15);
                cout<<"\tNombre ruta : ";
                getline(cin,d);
                band=false;
                do{
                    if(band==false)
                        graphics.moveTo(9, 15);
                    else
                        graphics.moveTo(7, 15);
                    band=false;
                    cout<<"\tZona : ";
                    getline(cin,myStr);
                    for(int i = 0;myStr[i];++i)
                        myStr[i] = toupper(myStr[i]);
                    try{
                        destino.setZone(myStr);
                    }catch(invalid_argument& ex){
                        graphics.setColor(graphics.FG_DARK_RED);
                        window();
                        graphics.moveTo(20, 29);
                        graphics.setColor(graphics.FG_LIGHT_CYAN);
                        cout<<ex.what()<<endl;
                        band=true;
                    }
                }while(band==true);
                band=false;
                do{
                    if(band==false)
                        graphics.moveTo(10, 15);
                    else
                        graphics.moveTo(7, 15);
                    band=false;
                    cout<<"\tUbicacion : ";
                    getline(cin,myStr);
                    try{
                        aux=stof(myStr);
                    }catch(invalid_argument& ex){
                        graphics.setColor(graphics.FG_DARK_RED);
                        window();
                        graphics.moveTo(20, 29);
                        graphics.setColor(graphics.FG_LIGHT_CYAN);
                        cout<<ex.what()<<endl;
                        cin.get();
                        band=true;
                    }
                }while(band==true);
                cin.ignore();
                destino.setLocation(aux);
                destino.setCode();
                destino.insert(listIndice,listZona,listaInvertida);
                grafo.insertData(destino.getName(),d);
            }
            else{
                graphics.moveTo(20, 29);
                graphics.setColor(graphics.FG_LIGHT_CYAN);
                cout<<"Permiso denegado"<<endl;
                cin.get();
            }
        }
        else if(myStr=="2"){
            if(access.mostrar==1){
                system("clear");
                List<Destino> list2;
                try{
                    destino.sort(list2);
                }catch(invalid_argument& ex){
                    graphics.setColor(graphics.FG_DARK_RED);
                    graphics.moveTo(20, 29);
                    graphics.setColor(graphics.FG_LIGHT_CYAN);
                    cout<<ex.what()<<endl;
                    getline(cin,myStr);
                }
                graphics.setColor(graphics.FG_DARK_BLUE);
                window();
                graphics.setColor(graphics.FG_WHITE);
                list2.printDestinos(graphics);
                list2.deleteAll();
            }
            else{
                graphics.moveTo(20, 29);
                graphics.setColor(graphics.FG_LIGHT_CYAN);
                cout<<"Permiso denegado"<<endl;
                graphics.setColor(graphics.FG_WHITE);
            }
        }
        else if(myStr=="3"){
            system("clear");
            listIndice.printIndices(graphics);
        }
        else if(myStr=="4"){
            if(access.buscar==1){
                graphics.setColor(graphics.FG_GRAY);
                window();
                graphics.setColor(graphics.FG_WHITE);
                 graphics.moveTo(5, 15);
                cout<<"\t\tConsultar"<<endl;
                graphics.moveTo(7, 15);
                cout<<"Codigo del destino  : ";
                getline(cin,myStr);
                try{
                    graphics.setColor(graphics.FG_DARK_BLUE);
                    window();
                    destino.search(listIndice, myStr,graphics);
                }catch(invalid_argument& ex){
                    graphics.setColor(graphics.FG_DARK_RED);
                    graphics.moveTo(20, 29);
                    graphics.setColor(graphics.FG_LIGHT_CYAN);
                    cout<<ex.what()<<endl;
                    graphics.setColor(graphics.FG_WHITE);
                    getline(cin,myStr);
                }
            }
            else{
                graphics.moveTo(20, 29);
                graphics.setColor(graphics.FG_LIGHT_CYAN);
                cout<<"Permiso denegado"<<endl;
                graphics.setColor(graphics.FG_WHITE);
            }
        }
        else if(myStr=="5"){
            if(access.modificar==1){
                graphics.setColor(graphics.FG_LIGHT_YELLOW);
                window();
                graphics.setColor(graphics.FG_WHITE);
                graphics.moveTo(5, 15);
                cout<<"\t\tModificar Destino : "<<endl;
                graphics.moveTo(7, 15);
                cout<<"\t1)Modificar Informacion  "<<endl;
                graphics.moveTo(8, 15);
                cout<<"\t2)Modificar Ruta"<<endl;
                graphics.moveTo(9, 15);
                cout<<"\tElige una opcion : ";
                getline(cin,myStr);
                if(myStr=="1"){
                    graphics.setColor(graphics.FG_LIGHT_YELLOW);
                    window();
                    graphics.setColor(graphics.FG_WHITE);
                    graphics.moveTo(5, 15);
                    cout<<"\t\t\tModificar : "<<endl;
                    graphics.moveTo(8, 15);
                    cout<<"Codigo del destino : ";
                    getline(cin, myStr);
                    try{
                        graphics.setColor(graphics.FG_LIGHT_PURPLE);
                        window();
                        graphics.setColor(graphics.FG_WHITE);
                        destino.modify(listIndice,myStr,grafo,graphics,listZona,listaInvertida);
                    }catch(invalid_argument& ex){
                        graphics.moveTo(20, 29);
                        graphics.setColor(graphics.FG_DARK_RED);
                        cout<<"No se encontro ningun resultado"<<endl;
                        graphics.setColor(graphics.FG_WHITE);
                        getline(cin,myStr);
                    }
                }
                if(myStr=="2"){
                    graphics.setColor(graphics.FG_LIGHT_YELLOW);
                    window();
                    graphics.setColor(graphics.FG_WHITE);
                    graphics.moveTo(5, 15);
                    cout<<"\t\t\tModificar : "<<endl;
                    graphics.moveTo(8, 15);
                    cout<<"Codigo del destino : ";
                    getline(cin, myStr);
                    try{
                        myStr =  destino.getName(listIndice,myStr);
                        grafo.modifyAristas(myStr);
                    }catch(invalid_argument& ex){
                        graphics.moveTo(20, 29);
                        graphics.setColor(graphics.FG_DARK_RED);
                        cerr<<ex.what();
                        graphics.setColor(graphics.FG_WHITE);
                        getline(cin,myStr);
                    }
    
                }
            }
            else{
                graphics.moveTo(20, 29);
                graphics.setColor(graphics.FG_LIGHT_CYAN);
                cout<<"Permiso denegado"<<endl;
                graphics.setColor(graphics.FG_WHITE);
            }
        }
        else if(myStr=="6"){
            if(access.eliminar==1){
                graphics.setColor(graphics.FG_LIGHT_YELLOW);
                window();
                graphics.setColor(graphics.FG_WHITE);
                graphics.moveTo(5, 15);
                cout<<"\t\t\tEliminar Destino"<<endl;
                graphics.moveTo(7, 15);
                cout<<"Codigo del destino  : ";
                getline(cin,myStr);
                string aux;
                do{
                    graphics.setColor(graphics.FG_LIGHT_YELLOW);
                    window();
                    graphics.setColor(graphics.FG_WHITE);
                    graphics.moveTo(5, 15);
                    cout<<"\t\t\tEliminar Destino"<<endl;
                    band=false;
                    graphics.moveTo(7, 15);
                    cout<<"1)Eliminacion Logica"<<endl;
                    graphics.moveTo(8, 15);
                    cout<<"2)Eliminacion Fisica"<<endl;
                    graphics.moveTo(9, 15);
                    cout<<"3)Regresar"<<endl;
                    graphics.moveTo(10, 15);
                    cout<<"Elige una opcion : ";
                    getline(cin,aux);
                    if(aux=="1"){
                        try{
                            destino.logicRemove(listIndice,myStr,graphics);
                        }catch(invalid_argument& ex){
                            graphics.moveTo(20, 29);
                            graphics.setColor(graphics.FG_LIGHT_CYAN);
                            cout<<"destino no encontrado "<<ex.what()<<endl;
                            graphics.setColor(graphics.FG_WHITE);
                            cin.get();
                        }
                    }
                    else if(aux=="2"){
                        try{
                            aux=destino.getName(listIndice,myStr);
                            grafo.remove(aux);
                            destino.remove(listIndice,listZona,listaInvertida,myStr,graphics);
                        }catch(invalid_argument& ex){
                            graphics.moveTo(20, 15);
                            graphics.setColor(graphics.FG_DARK_RED);
                            cout<<"destino no encontrado "<<ex.what()<<endl;
                            graphics.setColor(graphics.FG_WHITE);
                            cin.get();
                        }
                    }
                    else if(aux=="3"){
                       
                    }
                    else{
                        band=true;
                    }
                }while(band==true);
            }
            else{
                graphics.moveTo(20, 29);
                graphics.setColor(graphics.FG_LIGHT_CYAN);
                cout<<"Permiso denegado"<<endl;
                graphics.setColor(graphics.FG_WHITE);
                cin.get();
            }
        }
        else if(myStr=="7"){
            if(access.activar==1){
                graphics.setColor(graphics.FG_LIGHT_GREEN);
                window();
                graphics.setColor(graphics.FG_WHITE);
                graphics.moveTo(5, 15);
                cout<<"\t\tActivar destino"<<endl;
                graphics.moveTo(7, 15);
                cout<<"Curp del destino : ";
                getline(cin,myStr);
                try{
                    destino.active(listIndice,myStr);
                }catch(invalid_argument& ex){
                    graphics.moveTo(20, 29);
                    graphics.setColor(graphics.FG_LIGHT_CYAN);
                    cout<<ex.what()<<endl;
                    graphics.setColor(graphics.FG_WHITE);
                }
            }
        }
        else if(myStr=="8"){
            try{
                grafo.printData(graphics);
            }catch(invalid_argument& ex){
                graphics.moveTo(20, 29);
                graphics.setColor(graphics.FG_DARK_RED);
                cout<<ex.what()<<endl;
                graphics.setColor(graphics.FG_WHITE);
            }
        }
        else if(myStr=="9"){
            if(!grafo.isEmpty()){
                graphics.moveTo(20, 29);
                graphics.setColor(graphics.FG_DARK_RED);
                cout<<"Grafo vacio";
                graphics.setColor(graphics.FG_WHITE);
            }
            else{
                graphics.setColor(graphics.FG_LIGHT_GREEN);
                window();
                graphics.setColor(graphics.FG_WHITE);
                grafo.travel(graphics);
            }
        }
        else if(myStr=="10"){
            if(!grafo.isEmpty()){
                graphics.moveTo(20, 29);
                graphics.setColor(graphics.FG_DARK_RED);
                cout<<"Grafo vacio";
                graphics.setColor(graphics.FG_WHITE);
            }else{
                graphics.setColor(graphics.FG_LIGHT_GREEN);
                window();
                graphics.setColor(graphics.FG_WHITE);
                grafo.busquedas(graphics);
            }
             
        }
        else if(myStr=="11"){
            //IF ALGO
                graphics.setColor(graphics.FG_DARK_BLUE);
                window();
                graphics.setColor(graphics.FG_WHITE);
                graphics.moveTo(5, 15);
                cout<<"\t\t\tBuscar Zona";
                graphics.moveTo(7, 15);
                cout<<"Zona : ";
                getline(cin,myStr);
                for(int i = 0;myStr[i];++i)
                    myStr[i] = toupper(myStr[i]);
                try{
                    graphics.setColor(graphics.FG_LIGHT_CYAN);
                    window();
                    graphics.setColor(graphics.FG_WHITE);
                    destino.searchZone(listZona,graphics,myStr);
                }catch(invalid_argument& ex){
                    graphics.moveTo(20, 29);
                    graphics.setColor(graphics.FG_DARK_RED);
                    cout<<ex.what()<<endl;
                    graphics.setColor(graphics.FG_WHITE);
                }
        }
        else if(myStr=="12"){
            graphics.setColor(graphics.FG_LIGHT_CYAN);
            window();
            graphics.setColor(graphics.FG_WHITE);
            listaInvertida.printListaInvertida(graphics);
        }
        else if(myStr=="13"){
            destino.save(listIndice,grafo,listZona,listaInvertida);
            cout<<"Adios vaquero"<<endl;
        }
        else{
            system("clear");
            graphics.moveTo(20, 29);
            cout<<"Opcion no valida"<<endl;
        }
    }while(myStr!="13");
}

void Menu::menuAdmin(){
    string myStr;
    int i=1,j=1;
    do{
        graphics.setColor(graphics.FG_DARK_RED);
        window();
        graphics.moveTo(4,15);
        cout<<"\t\t\tMenu de Administrador";
        graphics.moveTo(6,15);
        cout <<"\t\t\tIr  a :  ";
        graphics.moveTo(7,15);
        cout<<"1)Usuarios";
        graphics.moveTo(8,15);
        cout<<"2)Clientes";
        graphics.moveTo(9,15);
        cout<<"3)Administrar Perfiles";
        graphics.moveTo(10,15);
        cout<<"4)Destinos";
        graphics.moveTo(11, 15);
        cout<<"5)Ventas ";
        graphics.moveTo(12, 15);
        cout<<"6)Oficinas";
        graphics.moveTo(13,15);
        cout<<"7)Salir"<<endl;
        graphics.moveTo(14,15);
        cout<<"Elige una opcion : ";
        getline(cin,myStr);
        if(myStr=="1"){
            menuUsuarios(i,j);
        }
        else if(myStr=="2"){
            menuClientes(i,j);
        }
        else if(myStr=="3"){
            menuPerfiles(i,j);
        }
        else if(myStr=="4"){
            menuDestinos(i, j);
        }
        else if(myStr=="5"){
            if(!cliente.isEmpty()){
                graphics.moveTo(18, 40);
                cout<<"Accion no permitidda :,(";
                cin.get();
            }else{
                menuVentas(i, j);
                
            }
        }
        else if(myStr=="6"){
            menuOficinas(i, j);
        }
        else if(myStr=="7"){}
        else{
            graphics.moveTo(14,20);
            cout<<"Lo sentimos, opcion no valida"<<endl;
            graphics.moveTo(15,20);
            cin.get();

        }
    }while(myStr!="7");
}

void Menu::menuUsers(int &code,int &profile){
    string myStr;
    do{
        graphics.setColor(graphics.FG_DARK_CYAN);
        window();
        graphics.moveTo(4,15);
        cout<<"\t\tMenu de Usuario"<<endl;
        graphics.moveTo(6,15);
        cout<<"\t\tIr  a :  "<<endl;
        graphics.moveTo(7,15);
        cout<<"\t1)Usuarios"<<endl;
        graphics.moveTo(8,15);
        cout<<"\t2)Clientes"<<endl;
        graphics.moveTo(9,15);
        cout<<"\t3)Administrar Perfiles"<<endl;
        graphics.moveTo(10,15);
        cout<<"\t4)Destinos"<<endl;
        graphics.moveTo(11,15);
        cout<<"\t5)Ventas";
        graphics.moveTo(12,15);
        cout<<"\t6)Oficinas"<<endl;
        graphics.moveTo(13,15);
        cout<<"\t7)Salir";
        graphics.moveTo(14,15);
        cout<<"\tElige una opcion : ";
        getline(cin,myStr);
        if(myStr=="1"){
            menuUsuarios(code,profile);
        }
        else if(myStr=="2"){
            menuClientes(code, profile);
        }
        else if(myStr=="3"){
            menuPerfiles(code,profile);
        }
        else if(myStr=="4"){
            menuDestinos(code, profile);
        }
        else if(myStr=="5"){
            if(!cliente.isEmpty()){
                graphics.moveTo(18, 40);
                cout<<"Accion no permitidda :,(, no existen registros de clientes";
                cin.get();
            }else{
                menuVentas(code, profile);
            }
        }
        else if(myStr=="6"){
            menuOficinas(code, profile);
        }
        else if(myStr=="7"){
  
        }
        else{
            graphics.moveTo(14,20);
            cout<<"Lo sentimos, opcion no valida"<<endl;
            graphics.moveTo(15,20);
            cin.get();
        }
    }while(myStr!="7");
}

void Menu::window(){
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
}

void Menu::menuVentas(int &code, int &profile){
    string myStr;
    string online(usuario.getName(code));
    Perimisos access;
    userAccess(access, profile);
    do{
        graphics.setColor(graphics.FG_DARK_CYAN);
        window();
        graphics.moveTo(4, 10);
        cout<<"Filas: "<<venta.getRows()<<" Columnas : "<<venta.getColumns();
        graphics.moveTo(4, 43);
        cout<<"Sesion de :  "<<online<<endl;
        graphics.moveTo(5, 15);
        cout<<"\t\t\tMENU VENTAS";
        graphics.moveTo(6, 15);
        cout<<"1)Agregar Venta";
        graphics.moveTo(7, 15);
        cout<<"2)Mostrar Ventas";
        graphics.moveTo(8, 15);
        cout<<"3)Buscar";
        graphics.moveTo(9, 15);
        cout<<"4)Modificar Venta";
        graphics.moveTo(10, 15);
        cout<<"5)Eliminar Venta";
        graphics.moveTo(11, 15);
        cout<<"6)Control de Colisiones";
        graphics.moveTo(12, 15);
        cout<<"7)Salir";
        graphics.moveTo(13, 15);
        cout<<"Elige una opcion : ";
        getline(cin,myStr);
        if(myStr=="1"){
            if(access.agregar==1){
                List<Indices> list;
                Destinos destino(list);
                        if(!list.isEmpty()){
                            if(cliente.isEmpty()){
                                Indices b;
                                bool band;
                                venta.setIdUsuario(code);
                                graphics.setColor(graphics.FG_DARK_YELLOW);
                                window();
                                venta.setFecha(detalleDeVenta);
                                int i=-1;
                                bool seguirComprando=false;
                                do{
                                    band=false;
                                    try{
                                        i=cliente.setCliente(graphics);
                                    }catch(invalid_argument& ex){
                                        graphics.moveTo(20, 30);
                                        graphics.setColor(graphics.FG_DARK_RED);
                                        cerr<<"Codigo de Cliente No valido";
                                        band=true;
                                        cin.get();
                                        window();
                                    }
                                    myStr=to_string(i);
                                    if(cliente.isValidCliente(myStr)&&band==false){
                                        graphics.moveTo(20, 30);
                                        graphics.setColor(graphics.FG_DARK_RED);
                                        cerr<<"ID Cliente no valido";
                                        cin.get();
                                        window();
                                        band=true;
                                    }
                                }while(band);
                                venta.setIdCliente(myStr);
                                i=-1;
                                do{
                                    graphics.setColor(graphics.FG_DARK_YELLOW);
                                    window();
                                    do{
                                        band=false;
                                        try{
                                            i=destino.setDestino(graphics);
                                        }catch(invalid_argument& ex){
                                            graphics.moveTo(20, 28);
                                            graphics.setColor(graphics.FG_DARK_RED);
                                            cerr<<"Codigo de Destino No valido";
                                            band=true;
                                            cin.get();
                                            window();
                                        }
                                        b.setKey(i);
                                        myStr=to_string(i);
                                        if(!list.find(b)&&band==false){
                                            graphics.moveTo(20, 28);
                                            graphics.setColor(graphics.FG_DARK_RED);
                                            cerr<<"Codigo de Destino No valido";
                                            band=true;
                                            cin.get();
                                            window();
                                        }
                                    }while(band);
                                    detalleDeVenta.setCodigoDestino(myStr);
                                    detalleDeVenta.setCodeOffice(usuario.getOffice(code));
                                    graphics.setColor(graphics.FG_DARK_BLUE);
                                    do{
                                        graphics.moveTo(5, 15);
                                        cout<<"\t\tVENTA DE BOLETOS : ";
                                        band=false;
                                        window();
                                        graphics.moveTo(7, 15);
                                        cout<<"Costo :  ";
                                        getline(cin, myStr);
                                        try{
                                            detalleDeVenta.setCosto(myStr);
                                        }catch(invalid_argument& ex){
                                            graphics.moveTo(18, 28);
                                            graphics.setColor(graphics.FG_DARK_RED);
                                            cerr<<"Ingrese un costo valido";
                                            cin.get();
                                            window();
                                            band=true;
                                        }
                                    }while(band);
                                    detalleDeVenta.setCosto(myStr);
                                    do{
                                        band=false;
                                        graphics.moveTo(8, 15);
                                        cout<<"Cantidad de pasajes : ";
                                        getline(cin, myStr);
                                        try{
                                        detalleDeVenta.setCantida(myStr);
                                        }catch(invalid_argument& ex){
                                            graphics.moveTo(18, 28);
                                            cerr<<"Ingresa una cantidad valida";
                                            cin.get();
                                            window();
                                            band=true;
                                        }
                                    }while(band);
                                    if(!seguirComprando){
                                        do{
                                            band=false;
                                            graphics.moveTo(9, 15);
                                            cout<<"Folio de venta :  ";
                                            getline(cin,myStr);
                                            if(!venta.isValidFolio(myStr)){
                                                graphics.moveTo(18, 28);
                                                graphics.setColor(graphics.FG_DARK_RED);
                                                cerr<<"El folio "<<myStr<<" Ya fue registrado";
                                                graphics.moveTo(19, 28);
                                                cerr<<"Intenta de nuevo";
                                                cin.get();
                                                window();
                                                band=true;
                                            }
                                        }while(band);
                                        venta.setFolio(myStr);
                                    }
                                    do{
                                        band=false;
                                        graphics.moveTo(10, 15);
                                        cout<<"¿Desea realizar otra compra? : S/N ";
                                        graphics.moveTo(11, 17);
                                        getline(cin,myStr);
                                        if(myStr=="S"||myStr=="s"){
                                            seguirComprando=true;
                                        }else if(myStr=="N"||myStr=="n"){
                                            seguirComprando=false;
                                        }else{
                                            graphics.moveTo(18, 28);
                                            graphics.setColor(graphics.FG_DARK_RED);
                                            cerr<<"Caracter no valido";
                                            cin.get();
                                            window();
                                            band=true;
                                        }
                                    }while(band);
                                    detalleDeVenta.setFolioVenta(venta.getFolio());
                                    detalleDeVenta.insert();
                                }while(seguirComprando);
                                venta.insert(graphics);
                            }
                            else{
                                graphics.moveTo(18, 28);
                                graphics.setColor(graphics.FG_DARK_RED);
                                cout<<"No hay Clientes registrados en la base de datos";
                                graphics.setColor(graphics.FG_WHITE);
                            }
                        }else{
                            graphics.moveTo(18, 28);
                            graphics.setColor(graphics.FG_DARK_RED);
                            cout<<"No hay destinos registrados en la base de datos";
                            graphics.setColor(graphics.FG_WHITE);
                        }
            }
        }else if(myStr=="2"){
            if(access.mostrar==1){
                graphics.setColor(graphics.FG_DARK_CYAN);
                window();
                venta.print(graphics);
            }
        }else if(myStr=="3"){
            if(access.buscar){
                graphics.setColor(graphics.FG_DARK_YELLOW);
                window();
                graphics.moveTo(5, 15);
                cout<<"\t\t\tBuscar Venta : ";
                graphics.moveTo(7, 15);
                cout<<"Folio de venta : ";
                getline( cin, myStr);
                venta.search(myStr, graphics);
            }
        }else if(myStr=="4"){
            if(access.modificar){
                graphics.setColor(graphics.FG_LIGHT_BLUE);
                window();
                graphics.moveTo(5, 15);
                cout<<"\t\t\tModificar Venta : ";
                getline(cin, myStr);
                system("clear");
                try{
                    venta.modify(myStr, graphics);
                }catch(invalid_argument& ex){
                    graphics.moveTo(20, 15);
                    cerr<<ex.what();
                    cin.get();
                }
            }
            
        }else if(myStr=="5"){
            if(access.eliminar){
                graphics.setColor(graphics.FG_LIGHT_BLUE);
                window();
                graphics.moveTo(5, 15);
                cout<<"\t\t\tEliminar Venta : ";
                getline(cin,myStr);
                graphics.setColor(graphics.FG_LIGHT_BLUE);
                window();
                venta.remove(myStr, graphics);
            }
            
        }else if(myStr=="6"){
            graphics.setColor(graphics.FG_LIGHT_BLUE);
            window();
            graphics.moveTo(5, 15);
            cout<<"\t\tConstro de Colisiones : ";
            graphics.moveTo(6, 15);
            cout<<"\t1)Expandir Filas ";
            graphics.moveTo(7, 15);
            cout<<"\t2)Expandir Columnas ";
            graphics.moveTo(8, 15);
            cout<<"\t3)Regresar";
            graphics.moveTo(9, 15);
            cout<<"\tElige una opcion : ";
            getline(cin,myStr);
            if(myStr=="1"){
                graphics.setColor(graphics.FG_DARK_GREEN);
                window();
                graphics.moveTo(5, 15);
                cout<<"Expandir Filas  : ";
                graphics.moveTo(6, 15);
                cout<<"Filas actuales : "<<venta.getRows();
                venta.expandirFilas();
                graphics.moveTo(8, 15);
                cout<<"Se expandieron las filas a  :  "<<venta.getRows();
                cin.get();
            }else if(myStr=="2"){
                graphics.setColor(graphics.FG_LIGHT_PURPLE);
                window();
                graphics.moveTo(5, 15);
                cout<<"Expandir Columnas  : ";
                graphics.moveTo(6, 15);
                cout<<"Columnas actuales : "<<venta.getColumns();
                venta.expandirColumnas();
                graphics.moveTo(8, 15);
                cout<<"Se expandieron las columnas  a  :  "<<venta.getColumns();
                cin.get();
            }else if(myStr=="3"){
                
            }else{
                
            }
   
        }
        else if(myStr=="7"){
            
        }else{
            graphics.moveTo(14,20);
            cout<<"Opcion no valida";
            cin.get();
        }
    }while(myStr!="7");
}

void Menu::menuOficinas(int &code, int & profile){
    string myStr;
    string online(usuario.getName(code));
    const int userOffice(usuario.getOffice(code));
    Perimisos access;
    userAccess(access, profile);
    do{
        window();
        graphics.moveTo(4, 43);
        cout<<"Sesion de :  "<<online<<endl;
        graphics.moveTo(5, 15);
        cout<<"\t\t\tMENU OFICINAS :";
        graphics.moveTo(6, 15);
        cout<<"1)Crear Oficina";
        graphics.moveTo(7, 15);
        cout<<"2)Mostrar Oficina";
        graphics.moveTo(8, 15);
        cout<<"3)Buscar";
        graphics.moveTo(9, 15);
        cout<<"4)Modificar Oficina";
        graphics.moveTo(10, 15);
        cout<<"5)Eliminar Oficina";
        graphics.moveTo(11, 15);
        cout<<"6(Corte de caja por oficina";
        graphics.moveTo(12, 15);
        cout<<"7)Informe global rango de fechas ";
        graphics.moveTo(13, 15);
        cout<<"8)Salir";
        graphics.moveTo(14, 15);
        cout<<"Elige una opcion : ";
        getline(cin,myStr);
        if(myStr=="1"){
            window();
            graphics.moveTo(5, 15);
            bool band;
            cout<<"\t\tRegistrar Nueva Oficina : ";
            graphics.moveTo(7, 15);
            cout<<"Nombre : ";
            getline(cin,myStr);
            oficina.setName(myStr);
            int i=0;
            do{
                if(i>0){
                    graphics.setColor(graphics.FG_DARK_RED);
                    window();
                }
                graphics.moveTo(8, 15);
                cout<<"Codigo : ";
                getline(cin,myStr);
                i++;
                try{
                    band=oficina.setCode(myStr);
                }catch(invalid_argument& ex){
                    graphics.moveTo(15, 15);
                    graphics.setColor(graphics.FG_DARK_RED);
                    cout<<"El codigo debe ser numerico";
                    cin.get();
                    band = true;
                }
            }while (band);
            graphics.moveTo(9, 15);
            cout<<"Direccion : ";
            getline(cin,myStr);
            oficina.setAddress(myStr);
            oficina.insert();
        }
        else if(myStr=="2"){
            if(oficina.isEmpty()){
                graphics.setColor(graphics.FG_DARK_RED);
                graphics.moveTo(18, 25);
                cout<<"NO HAY OFICINAS REGISTRADAS";
                graphics.setColor(graphics.FG_WHITE);
            }else{
                window();
                oficina.printOffices(graphics);
                
            }
        }
        else if(myStr=="3"){
            if(oficina.isEmpty()){
                graphics.setColor(graphics.FG_DARK_RED);
                graphics.moveTo(18, 25);
                cout<<"NO HAY OFICINAS REGISTRADAS";
                graphics.setColor(graphics.FG_WHITE);
            }else{
                window();
                graphics.moveTo(5, 15);
                cout<<"\t\tBuscar Oficina : ";
                graphics.moveTo(7, 15);
                cout<<"Codigo : ";
                getline(cin,myStr);
                try{
                    oficina.search(graphics,myStr);
                }catch(invalid_argument& ex){
                    graphics.setColor(graphics.FG_DARK_RED);
                    graphics.moveTo(19, 15);
                    cout<<ex.what();
                    cin.get();
                }
            }
            
        }
        else if(myStr=="4"){
            if(oficina.isEmpty()){
                graphics.setColor(graphics.FG_DARK_RED);
                graphics.moveTo(18, 25);
                cout<<"NO HAY OFICINAS REGISTRADAS";
                graphics.setColor(graphics.FG_WHITE);
            }else{
                window();
                graphics.moveTo(5, 15);
                cout<<"\t\tModificar Oficina : ";
                graphics.moveTo(7, 15);
                cout<<"Codigo : ";
                getline(cin,myStr);
                try{
                    oficina.modify(graphics, myStr);
                }catch(invalid_argument& ex){
                    graphics.setColor(graphics.FG_DARK_RED);
                    graphics.moveTo(19, 15);
                    cout<<ex.what();
                    cin.get();
                }
            }
        }
        else if(myStr=="5"){
            if(oficina.isEmpty()){
                graphics.setColor(graphics.FG_DARK_RED);
                graphics.moveTo(18, 25);
                cout<<"NO HAY OFICINAS REGISTRADAS";
                graphics.setColor(graphics.FG_WHITE);
            }else{
                window();
                graphics.moveTo(5, 15);
                cout<<"\t\tEliminar Oficina : ";
                graphics.moveTo(7, 15);
                cout<<"Codigo : ";
                getline(cin,myStr);
                try{
                    oficina.deleteOffice(myStr,userOffice);
                }catch(invalid_argument& ex){
                    graphics.setColor(graphics.FG_DARK_RED);
                    graphics.moveTo(19, 15);
                    cout<<"Oficina no encontrada";
                    cin.get();
                }
            }
        }
        else if(myStr=="6"){
          //  oficina.cortePorDia(graphics,myStr);
            if(!cliente.isEmpty()){
                graphics.moveTo(18, 40);
                cout<<"Accion no permitidda :,(";
                cin.get();
            }else{
                oficina.printCorteOficina(graphics);
            }
        }
        else if(myStr=="7"){
            if(!cliente.isEmpty()){
                graphics.moveTo(18, 40);
                cout<<"Accion no permitidda :,(";
                cin.get();
            }else{
                oficina.cortePorRangoDeFechas(graphics);
            }
        }
        else if(myStr=="8"){
  
        }
        else{
            
        }
    }while(myStr!="8");
}
