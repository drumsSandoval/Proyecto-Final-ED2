//
//  ventas.cpp
//  proyect
//
//  Created by Oscar Sandoval on 3/23/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#include "ventas.hpp"
#include <fstream>
#include "clientes.hpp"
#include "destinos.hpp"
#include <cmath>
using namespace std;
DestalleDeVenta::DestalleDeVenta(){
    
}

void DestalleDeVenta::setFolioVenta(std::string folio) {
    for(int i=0;i<10;i++){
        this->detalle.folioDeVenta[i]='\0';
    }
    for(int i = 0; folio[i]; i++){
        this->detalle.folioDeVenta[i] = folio[i];
    }
}

void DestalleDeVenta::setCodigoDestino(std::string & code) {
    try{
        this->detalle.codigoDestino=stoi(code);
    }catch(invalid_argument & ex){
        throw invalid_argument("Codigo no valido\n");
    }
}

void DestalleDeVenta::setCosto(std::string & costo) {
    try{
        this->detalle.costo=stof(costo);
    }catch(invalid_argument & ex){
        throw invalid_argument("Codigo no valido\n");
    }
}

void DestalleDeVenta::setDay(int d){
    this->detalle.day = d;
}

void DestalleDeVenta::setMonth(int m){
    this->detalle.month = m;
}

void DestalleDeVenta::setYear(int y){
    this->detalle.year = y;
}

void DestalleDeVenta::setCodeOffice(int c){
    this->detalle.codeOffice = c;
}

void DestalleDeVenta::setCantida(std::string &cantidad) {
    try{
        this->detalle.cantidad=stoi(cantidad);
    }catch(invalid_argument & ex){
        throw invalid_argument("Codigo no valido\n");
    }
}

void DestalleDeVenta::setDestino(std::string & a){
    detalle.codigoDestino=stoi(a);
}

std::string DestalleDeVenta::getFolioVenta() { 
    return detalle.folioDeVenta;
}

int DestalleDeVenta::getCodigoDestino() { 
    return detalle.codigoDestino;
}

float DestalleDeVenta::getCosto() { 
    return detalle.costo;
}

int DestalleDeVenta::getCantidad() { 
    return detalle.cantidad;
}

void DestalleDeVenta::insert(){
    ofstream archive("/Users/oscarsandoval/Desktop/proyect/DetalleVenta.txt",ios::app);
    archive.write((char*)&detalle, sizeof(detalle));
    archive.close();
}

void DestalleDeVenta::remove(std::string &folio){
    ofstream archive("/Users/oscarsandoval/Desktop/proyect/Aux.txt",ios::out);
    ifstream archive2("/Users/oscarsandoval/Desktop/proyect/DetalleVenta.txt");
    while(!archive2.eof()){
        archive2.read((char*)&detalle, sizeof(detalle));
        if(archive2.eof())break;
        if(folio==detalle.folioDeVenta){}
        else{
            archive.write((char*)&detalle, sizeof(detalle));
        }
    }
    archive.close();
    archive2.close();
    std::remove("/Users/oscarsandoval/Desktop/proyect/DetalleVenta.txt");
    rename("/Users/oscarsandoval/Desktop/proyect/Aux.txt", "/Users/oscarsandoval/Desktop/proyect/DetalleVenta.txt");
}

void DestalleDeVenta::modificar(std::string &folio,std::string ne){
 
}

////////////////////////////////////////   V    E   N    T    A    S    ////////////////////////////////////////////

Venta::Venta():idUsuario(NULL),idCliente(NULL){
    for(int i=0;i<10;i++){
        this->folio[i]='\0';
    }
    for(int i=0;i<8;i++){
        this->fecha[i]='\0';
    }
}

Ventas::Ventas():venta(){
    fstream archive("/Users/oscarsandoval/Desktop/proyect/Ventas.txt",ios::in);
    if(archive.good()){
        archive.close();
        string myStr;
        archive.open("/Users/oscarsandoval/Desktop/proyect/proyect/Colisiones.txt");
        while(getline(archive,myStr)){
            stringstream stream(myStr);
            getline(stream,myStr,'|');
            rows=stoi(myStr);
            getline(stream,myStr,'|');
            columns=stoi(myStr);
        }
        archive.close();
        return;
    }
    archive.open("/Users/oscarsandoval/Desktop/proyect/Ventas.txt",ios::app);
    const long aux=0;
    for(int i=0;i<100;i++){
        archive.write((char*)&aux,sizeof(long));
        for(int j=0;j<4;j++){
            archive.write((char*)&venta,sizeof(Venta));
        }
    }
    archive.close();
    archive.open("/Users/oscarsandoval/Desktop/proyect/proyect/Colisiones.txt",ios::out);
    archive<<100<<"|"<<4<<endl;
    rows=100;
    columns=4;
}

void Ventas::setIdUsuario(int &id) {
    this->venta.idUsuario=id;
}

void Ventas::setFolio(std::string &folio) {
    for(int i=0;i<10;i++){
        this->venta.folio[i]='\0';
    }
    for(int i = 0; folio[i]; i++){
        this->venta.folio[i] = folio[i];
    }
}


void Ventas::setFecha(DestalleDeVenta& detalle) {
    time_t now(time(0));
    tm* time  = localtime(&now);
    string aux;
    if(time->tm_wday==0){
        aux = "Domingo";
    }
    else if(time->tm_wday==1){
        aux = "Lunes";
    }
    else if(time->tm_wday==2){
        aux = "Martes";
    }
    else if(time->tm_wday==3){
        aux = "Miercoles";
    }
    else if(time->tm_wday==4){
        aux = "Jueves";
    }
    else if(time->tm_wday==5){
        aux = "Viernes";
    }
    else if(time->tm_wday==6){
        aux = "Sabado";
    }
    aux+=" " + to_string(time->tm_mday);
    detalle.setDay(time->tm_mday);
    if(time->tm_mon==0){
        aux += "/Enero";
        detalle.setMonth(1);
    }
    else if(time->tm_mon==1){
        aux += "/Febrero";
        detalle.setMonth(2);
    }
    else if(time->tm_mon==2){
        aux += "/Marzo";
        detalle.setMonth(3);
    }
    else if(time->tm_mon==3){
        aux += "/Abril";
        detalle.setMonth(4);
    }
    else if(time->tm_mon==4){
        aux += "/Mayo";
        detalle.setMonth(5);
    }
    else if(time->tm_mon==5){
        aux += "/Junio";
        detalle.setMonth(6);
    }
    else if(time->tm_mon==6){
        aux += "/Julio";
        detalle.setMonth(7);
    }
    else if(time->tm_mon==7){
        aux += "/Agosto";
        detalle.setMonth(8);
    }
    else if(time->tm_mon==8){
        aux += "/Septiembre";
        detalle.setMonth(9);
    }
    else if(time->tm_mon==9){
        aux += "/Octubre";
        detalle.setMonth(10);
    }
    else if(time->tm_mon==10){
        aux += "/Noviembre";
        detalle.setMonth(11);
    }
    else if(time->tm_mon==11){
        aux += "/Diciembre";
        detalle.setMonth(12);
    }
    aux += "/" + to_string(1900 + time->tm_year);
    detalle.setYear(1900 + time->tm_year);
    for(int i=0;i<30;i++){
        this->venta.fecha[i]='\0';
    }
    for(int i = 0; aux[i]; i++){
        this->venta.fecha[i] = aux[i];
    }
}

void Ventas::setIdCliente(std::string &id) {
    try{
        this->venta.idCliente=stoi(id);
    }catch(invalid_argument& ex){
        throw invalid_argument("ID Cliente no valido\n");
    }
}

int Ventas::getIdUsuario() { 
    return venta.idUsuario;
}

std::string Ventas::getFolio() { 
    return venta.folio;
}

std::string Ventas::getFecha() { 
    return venta.fecha;
}

int Ventas::getIdCliente() { 
    return venta.idCliente;
}

int Ventas::getRows(){
    return rows;
}

int Ventas::getColumns(){
    return columns;
}

int Ventas::dispersion(std::string key){
    int i(0);
    int d_base(-1);
    while(i<key.size()){
        d_base=d_base+(100*key[i])+(key[i+1]%87645);
        i+=2;
    }
    return d_base%rows;
}

void Ventas::insert(Console&graphics){
    int hash(dispersion(getFolio()));
    long pos(hash*(columns*sizeof(Venta)+sizeof(long)));//sizeof(Venta))*4+sizeof(long));
    long cont;
    fstream archive("/Users/oscarsandoval/Desktop/proyect/Ventas.txt",ios::in|ios::out);
    archive.seekg(pos);
    archive.read((char*)&cont, sizeof(long));
    if(cont==columns){
        graphics.setColor(graphics.FG_DARK_RED);
        graphics.moveTo(3, 15);
        cout<<"\t┌───────────────────────────────────────────────────┐\n";
        graphics.moveTo(4, 15);
        cout<<"\t│                   NO HAY ESPACIO                  │\n";
        graphics.moveTo(5, 15);
        cout<<"\t└───────────────────────────────────────────────────┘\n";
        archive.close();
        cin.get();
        return;
    }
    long aux = pos + (cont*sizeof(Venta)+sizeof(long));
    archive.seekp(aux,ios::beg);
    archive.write((char*)&venta, sizeof(Venta));
    cont++;
    archive.seekp(pos,ios::beg);
    archive.write((char*)&cont, sizeof(long));
    archive.close();
}

void Ventas::print(Console & graphics){
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Ventas.txt");
    if(!archive.good()){
        cout<<"UPPSSSS ALGO SALIO MAL"<<endl;
        return;
    }
    int pos(0);
    long aux;
    graphics.setColor(graphics.FG_DARK_RED);
    graphics.moveTo(3, 15);
    cout<<"\t┌───────────────────────────────────────────────────┐\n";
    graphics.moveTo(4, 15);
    cout<<"\t│              VENTAS  REALIZADAS                   │\n";
    graphics.moveTo(5, 15);
    cout<<"\t└───────────────────────────────────────────────────┘\n";
    int auxf,auxe;
    auxf=7; auxe=10;
    graphics.setColor(graphics.FG_DARK_CYAN);
    graphics.moveTo(6, 5);
    Clientes cliente;
    Usuario user;
    cout<<"   Fila  FOLIO\t  CLIENTE\t USUARIO\t      FECHA";
    graphics.setColor(graphics.FG_WHITE);
    int a=0;
    while(!archive.eof()){
        archive.seekg(pos);
        archive.read((char*)&aux, sizeof(aux));
        if(archive.eof())break;
        if(aux>0){
            for(int i(0);i<aux;++i){
                graphics.moveTo(18, 40);
                archive.read((char*)&venta, sizeof(venta));
                graphics.moveTo(auxf,auxe-5);
                cout<<"   "<<a<<"      "<<getFolio();
                auxe=19;
                graphics.moveTo(auxf,auxe);
                cout<<"        "<<cliente.getName(to_string(getIdCliente()));;
                auxe=35;
                graphics.moveTo(auxf,auxe);
                cout<<"     "<<user.getUserName(getIdUsuario());
                auxe=54;
                graphics.moveTo(auxf,auxe);
                cout<<getFecha();
                auxf++;
                auxe=10;
            }
        }
        pos=pos+(sizeof(Venta)*columns+sizeof(long));
        a++;
    }
    cin.get();
}

bool Ventas::isValidFolio(std::string & folio){
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Ventas.txt");
    int pos(0);
    long aux;
    Venta persona;
    int i=0;
    while(!archive.eof()){
        archive.seekg(pos);
        archive.read((char*)&aux, sizeof(aux));
        if(archive.eof())break;
        if(aux>0){
            for(int i(0);i<aux;++i){
                archive.read((char*)&persona, sizeof(Venta));
                if(persona.folio==folio)
                    return false;
            }
        }
        pos=pos+(sizeof(Venta)*columns+sizeof(long));
        i++;
    }
    return true;
}

void Ventas::search(string& folio,Console& graphics){
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Ventas.txt",ios::in);
    int hash(dispersion(folio));
    long pos(hash*(columns*sizeof(Venta)+sizeof(long))),cont;
    List<Detalle> list;
    archive.seekg(pos);
    archive.read((char*)&cont, sizeof(long));
    Detalle detalle;
    if(cont==0||isValidFolio(folio)){
        graphics.setColor(graphics.FG_DARK_RED);
        graphics.moveTo(3, 15);
        cout<<"\t┌───────────────────────────────────────────────────┐\n";
        graphics.moveTo(4, 15);
        cout<<"\t│  NO SE ENCONTRO NINGUNA VENTA CON ESTE FOLIO      │\n";
        graphics.moveTo(5, 15);
        cout<<"\t└───────────────────────────────────────────────────┘\n";
        archive.close();
        cin.get();
        return;
    }
    if(cont==1){
        archive.read((char*)&venta, sizeof(venta));
        archive.close();
        archive.open("/Users/oscarsandoval/Desktop/proyect/DetalleVenta.txt");
        while(!archive.eof()){
            archive.read((char*)&detalle, sizeof(detalle));
            if(archive.eof())break;
            if(detalle.folioDeVenta==folio){
                list.insertData(list.getLastPos(),detalle);
            }
        }
        printTicket(list,graphics);
    }else{
        bool band=false;
        for(int i=0;i<cont;++i){
            archive.read((char*)&venta, sizeof(venta));
            if(venta.folio==folio){
                band=true;
                break;
            }
        }
        archive.close();
        if(band==true){
            archive.open("/Users/oscarsandoval/Desktop/proyect/DetalleVenta.txt");
            while(!archive.eof()){
                archive.read((char*)&detalle, sizeof(detalle));
                if(archive.eof())break;
                if(detalle.folioDeVenta==folio){
                list.insertData(list.getLastPos(),detalle);
                }
            }
            printTicket(list,graphics);
        }else{
            graphics.moveTo(4, 15);
            cout<<"\t┌───────────────────────────────────────────────────┐\n";
            graphics.moveTo(5, 15);
            cout<<"\t│            VENTA NO ENCONTRADA   :,(              │\n";
            graphics.moveTo(6, 15);
            cout<<"\t└───────────────────────────────────────────────────┘\n";
            cin.get();
        }
    }
}

void Ventas::printTicket(List<Detalle> &list,Console& graphic){
    system("clear");
    Clientes cliente;
    Usuario usuario;
    graphic.moveTo(3, 12);
    cout<<"▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅"<<endl;
    graphic.moveTo(4, 23);
    cout<<" ___ _ ____ _  _ ____ ___";
    graphic.moveTo(5, 23);
    cout<<"  |  | |___ |-:_ |===  | ";
    graphic.moveTo(6, 12);
    cout<<"▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅"<<endl;
    graphic.moveTo(21,57);
    cout<<"©Estructura de datos 2®";
    graphic.moveTo(22,61);
    cout<<"█║▌│█│║▌║││█║▌║▌║";
    graphic.moveTo(23,59);
    cout<<"_oscar_sandoval_";
    graphic.moveTo(21, 6);
    cout<<"Venta realizado por : "<<usuario.getName(getIdUsuario());
    graphic.moveTo(22, 6);
    cout<<"Cliente : "<<cliente.getName(to_string(getIdCliente()));
    graphic.moveTo(23, 6);
    cout<<"Folio de venta : "<<getFolio();
    graphic.moveTo(2, 15);
    cout<<"Fecha de compra : "<<getFecha();
    graphic.setColor(graphic.FG_GRAY);
    graphic.moveTo(7, 9);
    cout<<" Destino\t   Boletos\t   costo\t     Total ";
    int x,y,i=0;
    x=8;
    List<Indices> aux;
    Destinos des(aux);
    while(i<=list.size()){
        y=10;
        graphic.moveTo(x, y);
        try{
            cout<<des.getName(aux,to_string(list[i].codigoDestino));
        }catch(invalid_argument ex){}
        y=32;
        graphic.moveTo(x, y);
        cout<<list[i].cantidad;
        y=45;
        graphic.moveTo(x, y);
        cout<<list[i].costo;
        y=64;
        graphic.moveTo(x, y);
        cout<<list[i].costo*list[i].cantidad;
        i++;
        x++;
    }
    cin.get();
}

void Ventas::modify(string &modify,Console &graphics){
    long pos(getAddress(modify));
    if(pos==-1){
        throw invalid_argument("No se encontro ningun registro con este RFC");
    }
    string myStr;
    DestalleDeVenta detalle;
    fstream archive("/Users/oscarsandoval/Desktop/proyect/Ventas.txt",ios::in|ios::out);
    if(getFolio()==modify){
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
            cout<<"\t\t\tMOdificar Registro";
            graphics.moveTo(6, 15);
            cout<<"\t1)ID Cliente";
            graphics.moveTo(7, 15);
            cout<<"\t2)ID Usuario";
            graphics.moveTo(8, 15);
            cout<<"\t3)Folio";
            graphics.moveTo(9, 15);
            cout<<"\t4)Fecha";
            graphics.moveTo(10, 15);
            cout<<"\t5)Regresar";
            graphics.moveTo(11, 15);
            cout<<"\tElige una opcion : ";
            getline(cin,myStr);
            if(myStr=="1"){
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
                graphics.moveTo(6, 15);
                cout<<"Id cliente actual :  "<<getIdCliente()<<endl;
                graphics.moveTo(7, 15);
                cout<<"ID Cliente : ";
                getline(cin,myStr);
                try{
                    setIdCliente(myStr);
                }catch(invalid_argument & ex){
                    graphics.moveTo(12, 15);
                    cerr<<ex.what()<<endl;
                    cin.get();
                }
            }else if(myStr=="2"){
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
                system("clear");
                graphics.moveTo(6, 15);
                cout<<"Id Usuario actual :  "<<getIdUsuario()<<endl;
                graphics.moveTo(7, 15);
                cout<<"ID Usuario : ";
                getline(cin,myStr);
                int b;
                try{
                    b=stoi(myStr);
                }catch(invalid_argument & ex){
                    graphics.moveTo(12, 15);
                    cerr<<ex.what()<<endl;
                    cin.get();
                }
                setIdUsuario(b);
            }else if(myStr=="3"){
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
                    graphics.moveTo(8, 15);
                    cout<<"Folio actual : "<<getFolio();
                     graphics.moveTo(6, 15);
                    cout<<"Nuevo folio : ";
                    getline(cin,myStr);
                }while(!isValidFolio(myStr));
                string idC(to_string(getIdCliente())),fecha(getFecha());
                int idu=getIdUsuario();
                removeModify(modify, graphics);
                setIdUsuario(idu);
                setIdCliente(idC);
                modifyDetalle(modify, myStr);
                setFolio(myStr);
                insert(graphics);
                return ;
            }else if(myStr=="4"){
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
                fecha date;
                graphics.moveTo(6, 15);
                cout<<"Fecha actual :  "<<getFecha();
                 graphics.moveTo(7, 15);
                cout<<"Dia  : ";
                getline(cin,myStr);
                date.first.first = stoi(myStr);
                graphics.moveTo(8, 15);
                cout<<"Mes  : ";
                getline(cin,myStr);
                date.first.second = stoi(myStr);
                graphics.moveTo(9, 15);
                cout<<"Año : ";
                getline(cin,myStr);
                date.second = stoi(myStr);
                setFecha(date);
                modifyDate(date,getFolio());
            }else if(myStr=="5"){
                
            }else{
                 graphics.moveTo(15, 15);
                cout<<"\tOpcion no valida "<<endl;
                cin.get();
            }
        }while(myStr!="5");
        archive.seekg(pos);
        archive.write((char*)&venta, sizeof(venta));
    }
    archive.close();
}

void Ventas::remove(string& remove,Console& graphics){
    fstream archive("/Users/oscarsandoval/Desktop/proyect/Ventas.txt",ios::in|ios::out);
    long pos(dispersion(remove)*(columns*sizeof(Venta)+sizeof(long)));//(columns*sizeof(data))+sizeof(long));
    DestalleDeVenta detalle;
    long aux;
    archive.seekg(pos,ios::beg);
    archive.read((char*)&aux, sizeof(aux));
    if(aux>0){
        for(int i(0);i<aux;++i){
            aux=archive.tellg();
            archive.read((char*)&venta, sizeof(Venta));
            if(getFolio()==remove){
                if(aux==1){
                    archive.seekg(pos,ios::beg);
                    aux--;
                    archive.write((char*)&aux, sizeof(long));
                    detalle.remove(remove);
                }else{
                    archive.seekg(pos,ios::beg);
                    archive.read((char*)&aux, sizeof(aux));
                    Venta personas[columns];
                    for(long i(0);i<aux;++i){
                        archive.read((char*)&personas[i], sizeof(Venta));
                    }
                    aux--;
                    archive.seekg(pos,ios::beg);
                    archive.write((char*)&aux, sizeof(long));
                    for(long i(0);i<aux+1;++i){
                        if(remove!=personas[i].folio)
                            archive.write((char*)&personas[i],sizeof(Venta));
                    }
                    detalle.remove(remove);
                }
                archive.close();
                return;
            }
        }
    }
}

long Ventas::getAddress(std::string rc){
    fstream archive("/Users/oscarsandoval/Desktop/proyect/Ventas.txt",ios::in|ios::out);
    int pos(0);
    long aux;
    long a;
    while(!archive.eof()){
        archive.seekg(pos,ios::beg);
        if(archive.eof())break;
        archive.read((char*)&aux, sizeof(aux));
        if(aux>0){
            for(int i=0;i<aux;i++){
                a=archive.tellg();
                archive.read((char*)&venta, sizeof(Venta));
                if(getFolio()==rc)
                    return a;
            }
        }
        pos=pos+(sizeof(Venta)*columns+sizeof(long));
    }
    return -1;
}

void Ventas::insertCopyC(){
    fstream archive("/Users/oscarsandoval/Desktop/proyect/Aux.txt",ios::in|ios::out);
    int hash(dispersion(getFolio()));
    long pos(hash*((columns*2)*sizeof(Venta)+sizeof(long)));
    long cont;
    archive.seekg(pos);
    archive.read((char*)&cont, sizeof(long));
    if(cont==columns){
        cout<<"\t│                   NO HAY ESPACIO                  │\n";
        archive.close();
        cin.get();
        return;
    }
    long aux = pos + (cont*sizeof(Venta)+sizeof(long));
    archive.seekp(aux,ios::beg);
    archive.write((char*)&venta, sizeof(Venta));
    cont++;
    archive.seekp(pos,ios::beg);
    archive.write((char*)&cont, sizeof(long));
    archive.close();
}

void Ventas::insertCopyR(){
    fstream archive("/Users/oscarsandoval/Desktop/proyect/Aux.txt",ios::in|ios::out);
    int hash(dispersion(getFolio()));
    long pos(hash*(columns*sizeof(venta)+sizeof(long)));
    long cont;
    archive.seekg(pos);
    archive.read((char*)&cont, sizeof(long));
    if(cont==columns){
        cout<<"\t│                   NO HAY ESPACIO                  │\n";
        archive.close();
        cin.get();
        return;
    }
    long aux = pos + (cont*sizeof(Venta)+sizeof(long));
    archive.seekp(aux,ios::beg);
    archive.write((char*)&venta, sizeof(Venta));
    cont++;
    archive.seekp(pos,ios::beg);
    archive.write((char*)&cont, sizeof(long));
    archive.close();
}

void Ventas::copyFile(const int archivo){
    ifstream read("/Users/oscarsandoval/Desktop/proyect/Ventas.txt");
    int pos(0);
    long aux;
    while(!read.eof()){
        read.seekg(pos,ios::beg);
        read.read((char*)&aux, sizeof(aux));
        if(read.eof())break;
        if(aux>0){
            for(int i(0);i<aux;++i){
                read.read((char*)&venta, sizeof(Venta));
                if(archivo==1)
                    insertCopyR();
                else
                    insertCopyC();
            }
        }
        pos=pos+(sizeof(Venta)*columns+sizeof(long));
    }
}

void Ventas::expandirFilas(){
    for(int i=0;i<10;i++){
        this->venta.folio[i]='\0';
    }
    for(int i=0;i<8;i++){
        this->venta.fecha[i]='\0';
    }
    venta.idCliente=NULL;
    venta.idUsuario=NULL;
    ofstream archive("/Users/oscarsandoval/Desktop/proyect/Aux.txt",ios::out);
    const long aux=0;
    for(int i=0;i<rows*2;i++){
        archive.write((char*)&aux,sizeof(long));
        for(int j=0;j<columns;j++){
            archive.write((char*)&venta,sizeof(venta));
        }
    }
    archive.close();
    archive.open("/Users/oscarsandoval/Desktop/proyect/proyect/Colisiones.txt",ios::out);
    archive<<rows*2<<"|"<<columns;
    archive.close();
    rows=rows*2;
    copyFile(1);
    std::remove("/Users/oscarsandoval/Desktop/proyect/Ventas.txt");
    rename("/Users/oscarsandoval/Desktop/proyect/Aux.txt","/Users/oscarsandoval/Desktop/proyect/Ventas.txt");
}

void Ventas::expandirColumnas(){
    for(int i=0;i<10;i++){
        this->venta.folio[i]='\0';
    }
    for(int i=0;i<8;i++){
        this->venta.fecha[i]='\0';
    }
    venta.idCliente=NULL;
    venta.idUsuario=NULL;
    ofstream archive("/Users/oscarsandoval/Desktop/proyect/Aux.txt",ios::out);
    const long aux=0;
    for(int i=0;i<rows;i++){
        archive.write((char*)&aux,sizeof(long));
        for(int j=0;j<columns*2;j++){
            archive.write((char*)&venta,sizeof(Venta));
        }
    }
    archive.close();
    archive.open("/Users/oscarsandoval/Desktop/proyect/proyect/Colisiones.txt",ios::out);
    archive<<rows<<"|"<<columns*2;
    archive.close();
    copyFile(2);
    columns=columns*2;
    std::remove("/Users/oscarsandoval/Desktop/proyect/Ventas.txt");
    rename("/Users/oscarsandoval/Desktop/proyect/Aux.txt","/Users/oscarsandoval/Desktop/proyect/Ventas.txt");
}

void Ventas::setFecha(fecha& date){
    string aux;
    int a(date.first.first%6);
    if(a==0){
        aux = "Domingo";
    }
    else if(a==1){
        aux = "Lunes";
    }
    else if(a==2){
        aux = "Martes";
    }
    else if(a==3){
        aux = "Miercoles";
    }
    else if(a==4){
        aux = "Jueves";
    }
    else if(a==5){
        aux = "Viernes";
    }
    else if(a==6){
        aux = "Sabado";
    }
    aux+=" " + to_string(date.first.first);
    if(date.first.second==1){
        aux += "/Enero";
      
    }
    else if(date.first.second==2){
        aux += "/Febrero";
        
    }
    else if(date.first.second==3){
        aux += "/Marzo";

    }
    else if(date.first.second==4){
        aux += "/Abril";
        
    }
    else if(date.first.second==5){
        aux += "/Mayo";
        
    }
    else if(date.first.second==6){
        aux += "/Junio";

    }
    else if(date.first.second==7){
        aux += "/Julio";
 
    }
    else if(date.first.second==8){
        aux += "/Agosto";

    }
    else if(date.first.second==9){
        aux += "/Septiembre";

    }
    else if(date.first.second==10){
        aux += "/Octubre";

    }
    else if(date.first.second==11){
        aux += "/Noviembre";

    }
    else if(date.first.second==12){
        aux += "/Diciembre";
 
    }
    aux += "/" + to_string(date.second);

    for(int i=0;i<30;i++){
        this->venta.fecha[i]='\0';
    }
    for(int i = 0; aux[i]; i++){
        this->venta.fecha[i] = aux[i];
    }
}

void Ventas::modifyDate(fecha & date, std::string folio){
    fstream archive("/Users/oscarsandoval/Desktop/proyect/DetalleVenta.txt",ios::in|ios::out);
    Detalle detalle;
    long pos;
    if(!archive.good()){
        cout<<"No existe el archivo Detalle de venta.txt"<<endl;
        return;
    }
    while(!archive.eof()){
        pos = archive.tellg();
        archive.read((char*)&detalle, sizeof(Detalle));
        if(archive.eof())break;
        if(detalle.folioDeVenta==folio){
            detalle.day = date.first.first;
            detalle.month = date.first.second;
            detalle.year = date.second;
            archive.seekp(pos,ios::beg);
            archive.write((char*)&detalle, sizeof(Detalle));
        }
    }
    archive.close();
}

void Ventas::modifyDetalle(std::string folio, std::string ne){
    fstream archive("/Users/oscarsandoval/Desktop/proyect/DetalleVenta.txt",ios::in|ios::out);
    Detalle detalle;
    long pos;
    if(!archive.good()){
        cout<<"No existe el archivo Detalle de venta.txt"<<endl;
        return;
    }
    while(!archive.eof()){
     
        pos = archive.tellg();
        archive.read((char*)&detalle, sizeof(Detalle));
        if(archive.eof())break;
        if(detalle.folioDeVenta==folio){
            for(int i=0;i<10;i++){
                detalle.folioDeVenta[i]='\0';
            }
            for(int i = 0; ne[i]; i++){
                detalle.folioDeVenta[i] = ne[i];
            }
            archive.seekp(pos,ios::beg);
            archive.write((char*)&detalle, sizeof(Detalle));
        }
    }
    archive.close();
}

void Ventas::removeModify(string &remove, Console &g){
    fstream archive("/Users/oscarsandoval/Desktop/proyect/Ventas.txt",ios::in|ios::out);
    long pos(dispersion(remove)*(columns*sizeof(Venta)+sizeof(long)));//(columns*sizeof(data))+sizeof(long));
    DestalleDeVenta detalle;
    long aux;
    archive.seekg(pos,ios::beg);
    archive.read((char*)&aux, sizeof(aux));
    if(aux>0){
        for(int i(0);i<aux;++i){
            aux=archive.tellg();
            archive.read((char*)&venta, sizeof(Venta));
            if(getFolio()==remove){
                if(aux==1){
                    archive.seekg(pos,ios::beg);
                    aux--;
                    archive.write((char*)&aux, sizeof(long));
                    detalle.remove(remove);
                }else{
                    archive.seekg(pos,ios::beg);
                    archive.read((char*)&aux, sizeof(aux));
                    Venta personas[columns];
                    for(long i(0);i<aux;++i){
                        archive.read((char*)&personas[i], sizeof(Venta));
                    }
                    aux--;
                    archive.seekg(pos,ios::beg);
                    archive.write((char*)&aux, sizeof(long));
                    for(long i(0);i<aux+1;++i){
                        if(remove!=personas[i].folio)
                            archive.write((char*)&personas[i],sizeof(Venta));
                    }
                }
                archive.close();
                return;
            }
        }
    }
}
