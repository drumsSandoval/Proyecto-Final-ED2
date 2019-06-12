//
//  oficinas.cpp
//  proyect
//
//  Created by Oscar Sandoval on 4/26/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#include "oficinas.hpp"
#include <fstream>
#include "list.hpp"
#include "ventas.hpp"
#include "destinos.hpp"
using namespace std;

Oficinas::Oficinas(){
    string aux;
    fstream archive("/Users/oscarsandoval/Desktop/proyect/Oficinas.txt");
    if(!archive.good()){
        aux = "MATRIZ";
        setName(aux);
        aux = "1";
        setCode(aux);
        aux = "Corregidora #489";
        setAddress(aux);
        insert();
    }
    archive.close();
}

void Oficinas::setName(std::string & name){
    for(int i=0;i<30;++i){
        this->office.name[i]='\0';
    }
    for(int i=0;name[i];i++){
        this->office.name[i]=name[i];
    }
}

bool Oficinas::setCode(std::string &code){
    if(!isValidCode(code)){
        try{
            office.code = stoi(code);
        }catch(invalid_argument& ex){
            throw invalid_argument("Ingrese un valor Numerico");
        }
        return false;
    }
    return true;
}

void Oficinas::setAddress(std::string &address){
    for(int i=0;i<40;++i){
        this->office.address[i]='\0';
    }
    for(int i=0;address[i];++i){
        this->office.address[i] = address[i];
    }
}

string Oficinas::getName(){
    return office.name;
}

int Oficinas::getCode(){
    return office.code;
}

string Oficinas::getAddress(){
    return office.address;
}

string Oficinas::getName(int & code){
    fstream archive("/Users/oscarsandoval/Desktop/proyect/Oficinas.txt");

    while(!archive.eof()){
        archive.read((char*)&office, sizeof(Oficina));
        if(archive.eof())break;
        if(office.code == code)
            return office.name;
        
    }
    return " ";
}

bool Oficinas::isEmpty(){
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Oficinas.txt");
    bool aux(!archive.good());
    archive.close();
    return aux;
}

bool Oficinas::isValidCode(string& cod){
    int code;
    try{
        code = (stoi(cod));
    }catch(invalid_argument& ex ){
        throw invalid_argument("Codigo no valido\n");
    }
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Oficinas.txt");
    if(!archive.good()){
        return false;
    }
    Oficina aux;
    while(!archive.eof()){
        archive.read((char*)&aux, sizeof(Oficina));
        if(aux.code==code){
            archive.close();
            return true;
        }
    }
    archive.close();
    return false;
}

void Oficinas::insert(){
    office.active=true;
    ofstream archive("/Users/oscarsandoval/Desktop/proyect/Oficinas.txt",ios::app);
    archive.write((char*)&office, sizeof(Oficina));
    archive.close();
}

void Oficinas::printOffices(Console& graphics){
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Oficinas.txt");
    graphics.setColor(graphics.FG_LIGHT_PURPLE);
    graphics.moveTo(3, 15);
    cout<<"\t\t\t OFICINAS REGISTRADAS : ";
    graphics.setColor(graphics.FG_LIGHT_BLUE);
    graphics.moveTo(5, 5);
    cout<<"\tNombre\t\tCodigo\t\t\tDomicilio";
    graphics.setColor(graphics.FG_WHITE);
    int i(6), j;
    while(!archive.eof()){
        j=9;
        archive.read((char*)&office, sizeof(office));
        if(archive.eof())break;
        graphics.moveTo(i, j);
        cout<<office.name;
        j+=15;
        graphics.moveTo(i, j);
        cout<<office.code;
        j+=20;
        graphics.moveTo(i, j);
        cout<<office.address;
        i++;
    }
    archive.close();
    cin.get();
}

void Oficinas::modify(Console& graphics,string& cod){
    int code;
    try{
        code = (stoi(cod));
    }catch(invalid_argument& ex ){
         throw invalid_argument("Codigo no valido\n");
    }
    if(code == 1) {
        throw invalid_argument("No es posible editar la Matriz\n");
    }
    fstream archive("/Users/oscarsandoval/Desktop/proyect/Oficinas.txt");
    long pos;
    while(!archive.eof()){
        pos = archive.tellg();
        archive.read((char*)&office, sizeof(Oficina));
        if(archive.eof())break;
        if(office.code==code){
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
                graphics.moveTo(5, 15);
                cout<<"Modificar Oficina : ";
                graphics.moveTo(7, 15);
                cout<<"1)Nombre";
                graphics.moveTo(8, 15);
                cout<<"2)Codigo";
                 graphics.moveTo(9, 15);
                cout<<"3)Direccion ";
                graphics.moveTo(10, 15);
                cout<<"4)Regresar";
                graphics.moveTo(11, 15);
                cout<<"Elige una opcion : ";
                getline(cin,cod);
                if(cod=="1"){
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
                    graphics.moveTo(5, 15);
                    cout<<"Modificar Nombre : ";
                    graphics.moveTo(7, 15);
                    cout<<"Nombre actual : "<<getName();
                    graphics.moveTo(8, 15);
                    cout<<"Nuevo nombre : ";
                    getline(cin, cod);
                    setName(cod);
                }
                else if(cod=="2"){
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
                    graphics.moveTo(5, 15);
                    cout<<"Modificar Codigo : ";
                    graphics.moveTo(7, 15);
                    cout<<"Codigo actual : "<<getCode();
                    graphics.moveTo(8, 15);
                    cout<<"Nuevo Codigo : ";
                    getline(cin, cod);
                    setCode(cod);
                    modificarCodigoUsuarios(code, getCode());
                }
                else if(cod=="3"){
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
                    graphics.moveTo(5, 15);
                    cout<<"Modificar Direccion : ";
                    graphics.moveTo(7, 15);
                    cout<<"Direccion actual : "<<getAddress();
                    graphics.moveTo(8, 15);
                    cout<<"Nueva Direccion : ";
                    graphics.moveTo(9, 15);
                    getline(cin, cod);
                    setAddress(cod);
                }
                else if(cod=="4"){
                    
                }
                else{
               
                }
            }while (cod!="4");
            archive.seekg(pos,ios::beg);
            archive.write((char*)&office, sizeof(Oficina));
            return;
        }
    }
    throw invalid_argument("Oficina no encontrada :,(");
}

void Oficinas::modificarCodigoUsuarios(int &actual, int nuevo){
    
}

void Oficinas::deleteOffice(string& cod,int officeUser){
    int code;
    try{
        code = (stoi(cod));
    }catch(invalid_argument& ex ){
        throw invalid_argument("Codigo no valido\n");
    }
    if(!isValidDelete(code, officeUser)){
        throw invalid_argument("Existen usuarios en esta oficina, no es posible eliminar");
    }
    fstream archive("/Users/oscarsandoval/Desktop/proyect/Oficinas.txt");
    List<Oficina> list;
    bool band=false;
    while(!archive.eof()){
        archive.read((char*)&office, sizeof(Oficina));
        if(archive.eof())break;
        if(office.code==code){
            band=true;
            continue;
        }
        list.insertData(list.getLastPos(),office);
    }
    archive.close();
    if(!band){
        throw invalid_argument("El codigo no existe en la base de datos");
    }
    archive.open("/Users/oscarsandoval/Desktop/proyect/Oficinas.txt",ios::out);
    int i=0;
    while(i<=list.size()){
        archive.write((char*)&list[i], sizeof(Oficina));
        i++;
    }
    archive.close();
}

void Oficinas::search(Console& graphics,std::string &cod){
    int code;
    try{
        code = (stoi(cod));
    }catch(invalid_argument& ex ){
        throw invalid_argument("Codigo no valido\n");
    }
    cout<<code;cin.get();
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Oficinas.txt");
    while(!archive.eof()){
        archive.read((char*)&office, sizeof(Oficina));
        if(archive.eof())break;
        cout<<office.code;cin.get();
        if(office.code==code){
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
            graphics.moveTo(5, 15);
            cout<<"\t\tOficina encontrada : ";
            graphics.moveTo(7, 15);
            cout<<"Nombre : "<<office.name;
            graphics.moveTo(8, 15);
            cout<<"Codigo : "<<office.code;
            graphics.moveTo(9, 15);
            cout<<"Direccion : "<<office.address;
            cin.get();
            return;
        }
    }
    throw invalid_argument("No se encontro ninguna oficina con este codigo ");
}

void Oficinas::deleteOfficeLogic(std::string &cod){
    int code;
    try{
        code = (stoi(cod));
    }catch(invalid_argument& ex ){
        throw invalid_argument("Codigo no valido\n");
    }
    fstream archive("/Users/oscarsandoval/Desktop/proyect/Oficinas.txt");
    List<Oficina> list;
    bool band=false;
    while(!archive.eof()){
        archive.read((char*)&office, sizeof(Oficina));
        if(archive.eof())break;
        if(office.code==code){
            band=true;
            office.active=false;
        }
        list.insertData(list.getLastPos(),office);
    }
    archive.close();
    if(!band){
        throw invalid_argument("El codigo no existe en la base de datos");
    }
    archive.open("/Users/oscarsandoval/Desktop/proyect/Oficinas.txt",ios::out);
    int i=0;
    while(i<=list.size()){
        archive.write((char*)&list[i], sizeof(Oficina));
        i++;
    }
    archive.close();
}

void Oficinas::cortePorRangoDeFechas(Console& graphics){
    fecha first(firstDate(graphics));
    fecha second(secondDate(graphics));
    Detalle detalle;
    fecha fecha;
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/DetalleVenta.txt");
    if(!archive.good()){
        throw invalid_argument("No existen detalles de Venta registrados \n");
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
    graphics.moveTo(4, 10);
    cout<<"\t\tCorte de Caja Global";
    graphics.setColor(graphics.FG_DARK_RED);
    graphics.moveTo(5, 15);
    cout<<getDate(first.first.first, first.first.second, first.second)<<" a "<<getDate(second.first.first, second.first.second, second.second);
    graphics.moveTo(6, 5);
    graphics.setColor(graphics.FG_DARK_GREEN);
    cout<<"      Oficina\t   Destino\t\tCantidad\tCosto";
    int x=7;
    double contenedor=0;
    List<Indices> aux;
    Destinos des(aux);
    graphics.setColor(graphics.FG_WHITE);
    while(!archive.eof()){
        archive.read((char*)&detalle, sizeof(detalle));
        if(archive.eof())break;
        fecha.first.first = detalle.day; fecha.first.second = detalle.month; fecha.second = detalle.year;
        if(fecha.first.second>=first.first.second && fecha.first.second<=second.first.second){
            
            if(fecha.first.second==first.first.second){ //|| fecha.first.second == second.first.second){
                
                if(fecha.first.first>=first.first.first){// && fecha.first.first <=second.first.first){
                  
                    if(fecha.second>= first.second && fecha.second <= second.second){
                        //imprimir
                        graphics.moveTo(x, 11);
                        cout<<getName(detalle.codeOffice);
                        graphics.moveTo(x, 28);
                        cout<<des.getName(aux, to_string(detalle.codigoDestino));
                        graphics.moveTo(x, 53);
                        cout<<detalle.cantidad;
                        graphics.moveTo(x, 65);
                        cout<<"$ "<<detalle.costo;
                        contenedor+=detalle.cantidad*detalle.costo;
                        x++;
                    }
                }
            }else if(fecha.first.second == second.first.second){
                if(fecha.first.first >= second.first.first){
                    if(fecha.second>= first.second && fecha.second <= second.second){
                        graphics.moveTo(x, 11);
                        cout<<getName(detalle.codeOffice);
                        graphics.moveTo(x, 28);
                        cout<<des.getName(aux, to_string(detalle.codigoDestino));
                        graphics.moveTo(x, 53);
                        cout<<detalle.cantidad;
                        graphics.moveTo(x, 65);
                        cout<<"$ "<<detalle.costo;
                        contenedor+=detalle.cantidad*detalle.costo;
                        x++;
                    }
                }
            }
            else{
                if(fecha.second>= first.second && fecha.second <= second.second){
                    //imprimir
                    graphics.moveTo(x, 11);
                    cout<<getName(detalle.codeOffice);
                    graphics.moveTo(x, 28);
                    cout<<des.getName(aux, to_string(detalle.codigoDestino));
                    graphics.moveTo(x, 53);
                    cout<<detalle.cantidad;
                    graphics.moveTo(x, 65);
                    cout<<"$ "<<detalle.costo;
                    contenedor+=detalle.cantidad*detalle.costo;
                    x++;
                }
            }
        }
    }
    graphics.setColor(graphics.FG_DARK_YELLOW);
    graphics.moveTo(x+1, 15);
    cout<<"\tTotal vendido : "<<contenedor;
    archive.close();
    cin.get();
    
}

string Oficinas::getDate(int &day, int &month, int &year){
    string date(to_string (day) + " de ");
    switch (month){
        case 1:
            date+="Enero";
            break;
        case 2:
            date+="Febrero";
            break;
        case 3:
            date+="Marzo";
            break;
        case 4:
            date+="Abril";
            break;
        case 5:
            date+="Mayo";
            break;
        case 6:
            date+="Junio";
            break;
        case 7:
            date+="Julio";
            break;
        case 8:
            date+="Agosto";
            break;
        case 9:
            date+="Septiembre";
            break;
        case 10:
            date+="Octubre";
            break;
        case 11:
            date+="Noviembre";
            break;
        case 12:
            date+="Diciembre";
            break;
        default:
            date+="xxxxxx";
            break;
    }
    date+=" del " + to_string(year);
    return date;
}

void Oficinas::printCorteOficina(Console &graphics){
    int oficina(getOffice(graphics));
    if(oficina==-1){
        throw invalid_argument("Oficina no valida :( ");
    }
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/DetalleVenta.txt");
    Detalle detalle;
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
    graphics.moveTo(4, 15);
    graphics.setColor(graphics.FG_DARK_YELLOW);
    cout<<"Corte de caja Oficina : "<<getName(oficina);
    graphics.moveTo(6, 10);
    graphics.setColor(graphics.FG_DARK_GREEN);
    cout<<"      Fecha  \t   Destino\t\tCantidad\tCosto";
    int x=7;
    double contenedor=0;
    List<Indices> aux;
    Destinos des(aux);
    graphics.setColor(graphics.FG_WHITE);
    while(!archive.eof()){
        archive.read((char*)&detalle, sizeof(Detalle));
        if(archive.eof())break;
        if(oficina==detalle.codeOffice){
            graphics.moveTo(x, 11);
            cout<<detalle.day<<" / "<<detalle.month<<" / "<<detalle.year;
            graphics.moveTo(x, 28);
            cout<<des.getName(aux, to_string(detalle.codigoDestino));
            graphics.moveTo(x, 53);
            cout<<detalle.cantidad;
            graphics.moveTo(x, 65);
            cout<<"$ "<<detalle.costo;
            contenedor+=detalle.cantidad*detalle.costo;
            x++;
        }
    }
    graphics.moveTo(x+1, 15);
    cout<<"Total vendido : $"<<contenedor;
    archive.close();
    cin.get();
}

fecha Oficinas::firstDate(Console & graphics){
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/DetalleVenta.txt");
    if(!archive.good()){
        throw invalid_argument("No hay ventas Registradas");
    }
    archive.close();
    Detalle detalle;
    std::string myStr;
    fecha date;
    bool band;
    do{
        band=false;
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
        graphics.moveTo(5, 15);
        int i = 6;
        cout<<"\t\t\tFecha de inico  : ";
        List<string> fechas;
        
        List<fecha> list;
        diaMes aux;
        int year;
        archive.open("/Users/oscarsandoval/Desktop/proyect/DetalleVenta.txt");
        while(!archive.eof()){
            archive.read((char*)&detalle, sizeof(detalle));
            if(archive.eof())break;
            myStr = getDate(detalle.day, detalle.month, detalle.year);
            aux.first = detalle.day; aux.second = detalle.month; year = detalle.year;
            date.first = aux; date.second = year;
            if(!fechas.find(myStr)){
                fechas.insertData(fechas.getLastPos(), myStr);
                list.insertData(list.getLastPos(), date);
                graphics.moveTo(i, 13);
                cout<<i-5<<")"<<myStr;
                i++;
            }
        }
        archive.close();
        graphics.moveTo(i, 13);
        cout<<"Elige una opcion : ";
        getline(cin,myStr);
        int pos;
        try{
            pos = stoi(myStr);
        }catch(invalid_argument& ex){
            band=true;
            graphics.moveTo(19, 18);
            cout<<"Opcion no valida";
        }
        if(band==false){
            pos--;
            band=true;
            if(pos>=0 && pos<=fechas.size()){
                archive.close();
                return list[pos];
            }
        }
    }while(band);
    archive.close();
    return date;
}

fecha Oficinas::secondDate(Console & graphics){
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/DetalleVenta.txt");
    if(!archive.good()){
        throw invalid_argument("No hay ventas Registradas");
    }
    archive.close();
    Detalle detalle;
    std::string myStr;
    fecha date;
    bool band;
    do{
        band=false;
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
        graphics.moveTo(5, 15);
        int i = 6;
        cout<<"\t\t\tFecha de fin  : ";
        List<string> fechas;
        
        List<fecha> list;
        diaMes aux;
        int year;
        archive.open("/Users/oscarsandoval/Desktop/proyect/DetalleVenta.txt");
        while(!archive.eof()){
            archive.read((char*)&detalle, sizeof(detalle));
            if(archive.eof())break;
            myStr = getDate(detalle.day, detalle.month, detalle.year);
            aux.first = detalle.day; aux.second = detalle.month; year = detalle.year;
            date.first = aux; date.second = year;
            if(!fechas.find(myStr)){
                fechas.insertData(fechas.getLastPos(), myStr);
                list.insertData(list.getLastPos(), date);
                graphics.moveTo(i, 13);
                cout<<i-5<<")"<<myStr;
                i++;
            }
        }
        archive.close();
        graphics.moveTo(i, 13);
        cout<<"Elige una opcion : ";
        getline(cin,myStr);
        int pos;
        try{
            pos = stoi(myStr);
        }catch(invalid_argument& ex){
            band=true;
            graphics.moveTo(19, 18);
            cout<<"Opcion no valida";
        }
        if(band==false){
            pos--;
            band=true;
            if(pos>=0 && pos<=fechas.size()){
                archive.close();
                return list[pos];
            }
        }
    }while(band);
    archive.close();
    return date;
    
}

int Oficinas::getOffice(Console & graphics){
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
        graphics.setColor(graphics.FG_LIGHT_PURPLE);
        graphics.moveTo(3, 15);
        cout<<"\t\t SELECCIONE UNA OFICINA  : ";
        graphics.setColor(graphics.FG_LIGHT_BLUE);
        graphics.moveTo(5, 5);
        cout<<"\t\tNombre\t\tCodigo";
        graphics.setColor(graphics.FG_WHITE);
        int i(6), j;
        List<int> codes;
        archive.open("/Users/oscarsandoval/Desktop/proyect/Oficinas.txt");
        while(!archive.eof()){
            j=18;
            archive.read((char*)&office, sizeof(office));
            if(archive.eof())break;
            graphics.moveTo(i, 12);
            cout<<i-5<<")";
            graphics.moveTo(i, j);
            cout<<office.name;
            j+=17;
            graphics.moveTo(i, j);
            cout<<office.code;
            codes.insertData(codes.getLastPos(), office.code);
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

bool Oficinas::isValidDelete(int code, int officeUser){
    if(code == officeUser){
        return false;
    }
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
        archive.read((char*)&aux, sizeof(int));
        archive.read((char*)&profile, sizeof(int));
        archive.read((char*)&aux, sizeof(int));
        if(archive.eof())break;
        if(code==profile){
            if(active==1){
                archive.close();
                return false;
            }
        }
    }
    archive.close();
    return true;
   
}
