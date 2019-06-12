//
//  clientes.cpp
//  proyect
//
//  Created by Oscar Sandoval on 2/4/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//


#include "ventas.hpp"
#include "clientes.hpp"
#include <iostream>
#include "ventas.hpp"
using namespace std;
Clientes::Clientes(){
    
}
Clientes::~Clientes(){
    
}
//Setters
//SetNombre
void Clientes::setName(const std::string& name){
    this->name=name;
}
//SetCodigo
void Clientes::setCode(const std::string& code){
    this->code=code;
}
//SetTelefono
void Clientes::setPhone(const std::string& phone){
    this->phone=phone;
}
//SetDomicilo
void Clientes::setAddress(const std::string& address){
    this->address=address;
}
//Set Activate
void Clientes::setActivate(const std::string activate){
    this->activate=activate;
}
//Getters
//GetNombre
string Clientes::getName(){
    return name;
}
//GetCodigo
string Clientes::getCode(){
    return code;
}//GetTelefono
string Clientes::getPhone(){
    return phone;
}
//GetDomicilio
string Clientes::getAddress(){
    return address;
}
//GetActivate
string Clientes::getActivate(){
    return activate;
}
//Metodos chidos
//Insert
void Clientes::insert(){
    ifstream aux("/Users/oscarsandoval/Desktop/proyect/Clientes.txt");
    bool band=false;
    size_t i;
    string myStr,line;
    setActivate("1");
    if(!aux.good()){
        myStr="1";
        setCode(myStr);
    }
    else{
        while(getline(aux,myStr)){
            stringstream stream(myStr);
            while(getline(stream,myStr,'|')){
                if(myStr=="1"){
                    getline(stream,myStr,'|');
                    getline(stream,myStr,'|');
                    getline(stream,myStr,'|');
                    getline(stream,myStr,'|');
                    band=true;
                    line = myStr;
                }
            }
        }
        aux.close();
        if(band==true){
            try{
                i=stoi(line);
                i+=1;
            }catch(invalid_argument ex){
                cerr<<ex.what()<<" Argumento invalido : "<<myStr<<endl;
                return;
            }
            setCode(to_string(i));
        }
        else{
            myStr="1";
            setCode(myStr);
        }
    }
    ofstream archive("/Users/oscarsandoval/Desktop/proyect/Clientes.txt",ios::app);
    if(!archive.is_open()){
        throw invalid_argument("No se pudo abrir el archivo");
    }
    archive<<activate<<"|"<<name<<"|"<<phone<<"|"<<address<<"|"<<code<<"|";
    archive.close();
}


//Print
void Clientes::toString(Console& graphics){//Console& graphics){
    string print,myStr;
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Clientes.txt");
    graphics.setColor(graphics.FG_DARK_YELLOW);
    graphics.moveTo(3, 15);
    cout<<"┌───────────────────────────────────────────────────┐";
    graphics.moveTo(4, 15);
    cout<<"│             Clientes registrados                  │\n";
    graphics.moveTo(5, 15);
    cout<<"└───────────────────────────────────────────────────┘\n";
    graphics.setColor(graphics.FG_LIGHT_GRAY);
    graphics.moveTo(6, 5);
    int a,b;
    cout<<"   CODE\t\t\tNOMBRE\t\t\tTELEFONO";
    a=7; b=9;
    graphics.setColor(graphics.FG_WHITE);
    while(getline(archive,myStr)){
        stringstream stream(myStr);
        while(getline(stream,myStr,'|')){
            if(myStr=="1"){
                getline(stream,myStr,'|');
                setName(myStr);
                getline(stream,myStr,'|');
                setPhone(myStr);
                getline(stream,myStr,'|');
                setAddress(myStr);
                getline(stream,myStr,'|');
                setCode(myStr);
                graphics.moveTo(a, b);
                cout<<getCode();
                b=33;
                graphics.moveTo(a, b);
                cout<<getName();
                b=55;
                graphics.moveTo(a, b);
                cout<<getPhone();
                a++;
                b=9;
            }
        }
    }
    cin.get();
}

//Buscar
void Clientes::search(const string& user,Console&graphics){//},Console& graphics){
    string myStr,aux;
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Clientes.txt");
    while(getline(archive,myStr)){
        stringstream stream(myStr);
        while(getline(stream,activate,'|')){
            getline(stream,name,'|');
            // cout<<"Nombre : " << myStr << "\n";
            getline(stream,phone,'|');
            // cout<<"Precio : " << myStr << "\n";
            getline(stream,address,'|');
            //  cout<<"Descripsion : " << myStr << "\n";
            getline(stream,code,'|');
            // cout<<"Codigo : " << myStr;
            if(code==user){
                if(activate=="1"){
                    system("clear");
                    graphics.setColor(graphics.FG_DARK_GREEN);
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
                    cout<<"\t\tCliente encontrado : "<<endl;
                    graphics.moveTo(6, 15);
                    cout<<"Nombre : "<<name<<endl;
                    graphics.moveTo(7, 15);
                    cout<<"Telefono : "<<phone<<endl;
                    graphics.moveTo(8, 15);
                    cout<<"Direccion : "<<address<<endl;
                    graphics.moveTo(9, 15);
                    cout<<"Codigo : "<<code<<endl;
                    archive.close();
                    cin.get();
                    return;
                }
            }
        }
    }
    archive.close();
    throw invalid_argument("No se encontro ningun cliente con ese codigo\n");
}


//Modifica
void Clientes::modify(const string& user,Console& graphics){//},Console& graphics){
    ofstream aux("/Users/oscarsandoval/Desktop/proyect/Auxiliar.txt",ios::out);
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Clientes.txt");
    string myStr;
    bool band=false;
    system("clear");
    graphics.setColor(graphics.FG_DARK_GREEN);
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
    while(getline(archive,myStr)){
        stringstream stream(myStr);
        while(getline(stream,activate,'|')){
            getline(stream,name,'|');
            // cout<<"Nombre : " << myStr << "\n";
            getline(stream,phone,'|');
            // cout<<"Precio : " << myStr << "\n";
            getline(stream,address,'|');
            //  cout<<"Descripsion : " << myStr << "\n";
            getline(stream,code,'|');
            // cout<<"Codigo : " << myStr;
            if(code==user){
                if(activate=="1"){
                    band=true;
                    graphics.moveTo(5, 15);
                    cout<<"Modificar Cliente : "<<endl;
                    graphics.moveTo(6, 15);
                    cout<<"Nombre : ";
                    getline(cin,myStr);
                    setName(myStr);
                    graphics.moveTo(7, 15);
                    cout<<"Telefono : ";
                    getline(cin,myStr);
                    setPhone(myStr);
                    graphics.moveTo(8, 15);
                    cout<<"Direccion : ";
                    getline(cin,myStr);
                    setAddress(myStr);
                    setCode(user);
                    setActivate("1");
                    aux<<activate<<"|"<<name<<"|"<<phone<<"|"<<address<<"|"<<code<<"|";
                    
                }
                else{
                    aux<<activate<<"|"<<name<<"|"<<phone<<"|"<<address<<"|"<<code<<"|";
                }
            }
            else{
                aux<<activate<<"|"<<name<<"|"<<phone<<"|"<<address<<"|"<<code<<"|";
            }
        }
    }
    archive.close();
    aux.close();
    std::remove("/Users/oscarsandoval/Desktop/proyect/Clientes.txt");
    rename("/Users/oscarsandoval/Desktop/proyect/Auxiliar.txt","/Users/oscarsandoval/Desktop/proyect/Clientes.txt");
}


//Eliminar
string Clientes::remove(string& user){
    if(!isValidRemoveCliente(user)){
        return "No es posible eliminar este cliente, tiene ventas registradas";
    }
    ofstream aux("/Users/oscarsandoval/Desktop/proyect/Auxiliar.txt",ios::out);
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Clientes.txt");
    string myStr;
    bool band=false;
    while(getline(archive,myStr)){
        stringstream stream(myStr);
        while(getline(stream,activate,'|')){
            getline(stream,name,'|');
            // cout<<"Nombre : " << myStr << "\n";
            getline(stream,phone,'|');
            // cout<<"Precio : " << myStr << "\n";
            getline(stream,address,'|');
            //  cout<<"Descripsion : " << myStr << "\n";
            getline(stream,code,'|');
            // cout<<"Codigo : " << myStr;
            if(code==user){
                if(activate=="1")
                    band=true;
                else{
                    aux<<activate<<"|"<<name<<"|"<<phone<<"|"<<address<<"|"<<code<<"|";
                }
            }
            else{
                aux<<activate<<"|"<<name<<"|"<<phone<<"|"<<address<<"|"<<code<<"|";
            }
        }
    }
    archive.close();
    aux.close();
    std::remove("/Users/oscarsandoval/Desktop/proyect/Clientes.txt");
    rename("/Users/oscarsandoval/Desktop/proyect/Auxiliar.txt","/Users/oscarsandoval/Desktop/proyect/Clientes.txt");
    if(band==true){
        myStr="Cliente eliminado con exito\n";
        return myStr;
    }
    myStr="No hay ningun cliente registrado con ese codigo";
    return myStr;
}

//Eliminar Logico
string Clientes::logicRemove(const std::string & user){
    ofstream aux("/Users/oscarsandoval/Desktop/proyect/Auxiliar.txt",ios::out);
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Clientes.txt");
    string myStr;
    bool band=false;
    while(getline(archive,myStr)){
        stringstream stream(myStr);
        while(getline(stream,activate,'|')){
            getline(stream,name,'|');
            // cout<<"Nombre : " << myStr << "\n";
            getline(stream,phone,'|');
            // cout<<"Precio : " << myStr << "\n";
            getline(stream,address,'|');
            //  cout<<"Descripsion : " << myStr << "\n";
            getline(stream,code,'|');
            // cout<<"Codigo : " << myStr;
            if(code==user){
                if(activate=="1"){
                    band=true;
                    activate="0";
                    aux<<activate<<"|"<<name<<"|"<<phone<<"|"<<address<<"|"<<code<<"|";
                }
                else{
                    aux<<activate<<"|"<<name<<"|"<<phone<<"|"<<address<<"|"<<code<<"|";
                }
            }
            else{
                aux<<activate<<"|"<<name<<"|"<<phone<<"|"<<address<<"|"<<code<<"|";
            }
        }
    }
    archive.close();
    aux.close();
    std::remove("/Users/oscarsandoval/Desktop/proyect/Clientes.txt");
    rename("/Users/oscarsandoval/Desktop/proyect/Auxiliar.txt","/Users/oscarsandoval/Desktop/proyect/Clientes.txt");
    if(band==true){
        myStr="Cliente eliminado con exito\n";
        return myStr;
    }
    myStr="No hay ningun cliente registrado con ese codigo";
    return myStr;
}

//Activar Logico
string Clientes::active(const std::string& user){
    ofstream aux("/Users/oscarsandoval/Desktop/proyect/Auxiliar.txt",ios::out);
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Clientes.txt");
    string myStr;
    bool band=false;
    while(getline(archive,myStr)){
        stringstream stream(myStr);
        while(getline(stream,activate,'|')){
            getline(stream,name,'|');
            // cout<<"Nombre : " << myStr << "\n";
            getline(stream,phone,'|');
            // cout<<"Precio : " << myStr << "\n";
            getline(stream,address,'|');
            //  cout<<"Descripsion : " << myStr << "\n";
            getline(stream,code,'|');
            // cout<<"Codigo : " << myStr;
            if(code==user){
                if(activate=="0"){
                    band=true;
                    activate="1";
                    aux<<activate<<"|"<<name<<"|"<<phone<<"|"<<address<<"|"<<code<<"|";
                }
                else{
                    aux<<activate<<"|"<<name<<"|"<<phone<<"|"<<address<<"|"<<code<<"|";
                }
            }
            else{
                aux<<activate<<"|"<<name<<"|"<<phone<<"|"<<address<<"|"<<code<<"|";
            }
        }
    }
    archive.close();
    aux.close();
    std::remove("/Users/oscarsandoval/Desktop/proyect/Clientes.txt");
    rename("/Users/oscarsandoval/Desktop/proyect/Auxiliar.txt","/Users/oscarsandoval/Desktop/proyect/Clientes.txt");
    if(band==true){
        myStr="Cliente eliminado con exito\n";
        return myStr;
    }
    myStr="No hay ningun cliente registrado con ese codigo";
    return myStr;
}

bool Clientes::isValidCliente(string& cod){
    string myStr,aux;
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Clientes.txt");
    if(!archive.good())
        return true;
    while(getline(archive,myStr)){
        stringstream stream(myStr);
        while(getline(stream,activate,'|')){
            getline(stream,name,'|');
            // cout<<"Nombre : " << myStr << "\n";
            getline(stream,phone,'|');
            // cout<<"Precio : " << myStr << "\n";
            getline(stream,address,'|');
            //  cout<<"Descripsion : " << myStr << "\n";
            getline(stream,code,'|');
            // cout<<"Codigo : " << myStr;
            if(code==cod){
                if(activate=="1"){
                    return false;
                }else{
                    return true;
                }
            }
        }
    }
    archive.close();
    return true;
}

bool Clientes::isEmpty(){
    fstream archive("/Users/oscarsandoval/Desktop/proyect/Clientes.txt",ios::in);
    if(!archive.good())
        return false;
    archive.close();
    return true;
}

bool Clientes::isValidRemoveCliente(const std::string & a){
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
                if(to_string(venta.idCliente)==a)
                    return false;
            }
        }
        pos=pos+(sizeof(Venta)*4+sizeof(long));
    }
    return true;
}

int Clientes::setCliente(Console& graphics){
    string myStr;
    graphics.moveTo(4,25);
    graphics.setColor(graphics.FG_GRAY);
    cout<<"Seleccione el Cliente de la venta ";
    graphics.moveTo(5,8);
    graphics.setColor(graphics.FG_LIGHT_YELLOW);
    cout<<"Codigo\t\tNombre";
    graphics.moveTo(5,44);
    cout<<"Codigo\t\tNombre";
    graphics.setColor(graphics.FG_WHITE);
    for(int i=6;i<18;i++){
        graphics.moveTo(i, 40);
        cout<<"▎";
    }
    int x=6, y=10,i=0;
    bool band=false;
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Clientes.txt");
    while(getline(archive,myStr)){
        stringstream stream(myStr);
        while(getline(stream,myStr,'|')){
            if(myStr=="1"){
                getline(stream,myStr,'|');
                setName(myStr);
                getline(stream,myStr,'|');
                setPhone(myStr);
                getline(stream,myStr,'|');
                setAddress(myStr);
                getline(stream,myStr,'|');
                setCode(myStr);
                graphics.moveTo(x,y);
                cout<<code;
                y+=8;
                graphics.moveTo(x, y);
                cout<<name;
                i++;
                if(i>5&& band==false){
                    x=6;
                    y = 50;
                    band=true;
                }else if(i>5 && band==true){
                    x++;
                    y = 50;
                }else{
                    x++;
                    y=10;
                }
            }
        }
    }
    archive.close();
    graphics.setColor(graphics.FG_LIGHT_BLUE);
    graphics.moveTo(19, 25);
    cout<<"Codigo de Cliente : ";
    getline(cin, myStr);
    return stoi(myStr);
    
}

string Clientes::getName(string user){
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Clientes.txt");
    string myStr;
    while(getline(archive,myStr)){
        stringstream stream(myStr);
        while(getline(stream,activate,'|')){
            getline(stream,name,'|');
            // cout<<"Nombre : " << myStr << "\n";
            getline(stream,phone,'|');
            // cout<<"Precio : " << myStr << "\n";
            getline(stream,address,'|');
            //  cout<<"Descripsion : " << myStr << "\n";
            getline(stream,code,'|');
            // cout<<"Codigo : " << myStr;
            if(code==user){
                if(activate=="1"){
                    string aux;
                    for(int i =0;name[i];i++){
                        if(name[i]==' '){
                            aux[i+1]=name[i+1];
                            archive.close();
                            return aux;
                        }
                        aux+=name[i];
                    }
                    archive.close();
                    return name;
                }
            }
        }
    }
    archive.close();
    return "  ";
}

void Clientes::comprimirArchivo(Huffman<data>& huffman,List<data>& list,List<int>& listFrecuency){
    if(huffman.size()!=-1) return;
    fstream archive("/Users/oscarsandoval/Desktop/proyect/Clientes.txt");
    
    if(!archive.good()){
        cout<<"\t\t\tEl archivo no existe"<<endl;
        return;
    }
    string myStr,contenedor;
    data data;
    
    while(getline(archive, myStr)){
        contenedor+=myStr;
    }
    aux(contenedor);
    archive.close();
    for(int i=0;contenedor[i];++i){
        if(!list.find(contenedor[i])){
            data.first = contenedor[i];
            data.second.first = 1;
            list.insertData(list.getLastPos(),data);
        }
    }
    for(int i=0;i<=list.size();i++){
        huffman.insertData(huffman.getPos(list[i]), list[i]);
    }
    
    huffman.getFrecuency(listFrecuency);
    for(int i = 0;i<=listFrecuency.size();i++){
        huffman.sort(huffman.lowerData(listFrecuency[i]), huffman.upperData(listFrecuency[i]));
    }
    system("clear");
    cout<<"Caracteres Ordenados segun su Frecuencia y codigo ASCII"<<endl;
    for(int i=0;i<=huffman.size();i++){
        cout<<huffman[i].first<<" : "<<huffman[i].second.first<<endl;
    }
    cout<<"Tamaño de Diccionario : "<<huffman.size()<<endl;
    while(huffman.size()!=0){
        huffman.generateTree();
    }
    int i = 0;
    archive.open("/Users/oscarsandoval/Desktop/proyect//Total de caracteres.txt",ios::out);
    archive<<huffman[i].second.first<<endl;
    archive.close();
    cout<<"RAIZ DE HUFFMAN : "<<huffman[i].second.first<<endl;
    cin.get();
    system("clear");
    huffman.generateDiccionary(list);
    list.printDiccionary();cin.get();
    system("clear");
    translateBinary(contenedor, list);
    cin.get();
}

void Clientes::translateBinary(std::string & text, List<data> & list){
    string newText;
    for(int i = 0; text[i];++i){
        newText += list.getHuffmanCode(text[i]);
    }
    system("clear");
    cout<<"Traduccion de texto : "<<endl;
    cout<<newText;cin.get();
    cout<<"StrLen = "<<newText.size()<<endl;
    while(newText.size()%8!=0){
        newText+="0";
    }
    cout<<"Size : "<<newText.size();cin.get();
    translateAsci(newText);
    list.saveDiccionary(newText);
}

void Clientes::translateAsci(std::string &text){
    int i=0;
    ofstream archive("/Users/oscarsandoval/Desktop/proyect/Huffman.txt",ios::out);
    string subString,encriptado;int aux;
    List<int> list;
    while(i<text.size()){
        subString = text.substr(i,8);
        cout<<subString<<endl;
        aux=stoi(subString,nullptr,2);
        encriptado+=char(aux);
        list.insertData(list.getLastPos(), aux);
        i=i+8;
    }
    cout<<encriptado<<endl;
    archive<<encriptado;
    archive.close();
    std::remove("/Users/oscarsandoval/Desktop/proyect/Clientes.txt");
}

void Clientes::descomprimirArchivo(){
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Diccionario de datos.txt");
    string myStr;
    if(!archive.good()){
        cout<<"No existe el archivo Diccionario de datos.txt"<<endl;
        return;
    }
    pair<string,string> data;
    List<pair<string, string>> list;
    unsigned char caracter;
    string binary;
    while(getline(archive,myStr)){
        stringstream stream(myStr);
        getline(stream,myStr,'@');
        data.first = myStr;
        getline(stream,myStr,'@');
        data.second = myStr;
        list.insertData(list.getLastPos(), data);
    }
    system("clear");
    for(int i = 0; i<=list.size();i++){
        cout<<list[i].first<<" : "<<list[i].second<<endl;
    }
    cout<<"Cargar el diccionario a memoria";
    cin.get();
    archive.close();
    archive.open("/Users/oscarsandoval/Desktop/proyect/Huffman.txt");
    string text;
    while(getline(archive,myStr)){
        text+=myStr;
    }
    archive.close();
    cout<<"Cargar el archivo comprimido a memoria : "<<endl<<text<<endl<<endl;
    cout<<"Pasar a decimal cada caracter : "<<endl<<endl;
    for(int i=0;text[i];++i){
        caracter = text[i];
        cout<<int(caracter)<<"  ";
    }
    cout<<endl;
    cin.get();
    system("clear");
    binary = list.getBinaryHuffman();
    cout<<"Pasar a binario los decimales"<<endl;
    cout<<binary<<endl;cin.get();
    string translate,a;
    for(int i=0;binary[i];i++){
        a+=binary[i];
        if(list.findHuffman(a)){
            translate += list.getHuffmanData(a);
            a = binary[++i];
        }
    }
    cout<<"Texto descomprimido  :  "<<endl<<endl;
    cout<<translate<<endl;cin.get();
    saveDescomprension(translate);
}

std::string Clientes::toBinary(int n){
    std::string r;
    while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
    if(r.size()==8){
        return r;
    }
    return r;
}

void Clientes::saveDescomprension(string& text){
    std::remove("/Users/oscarsandoval/Desktop/proyect//Huffman.txt");
    std::remove("/Users/oscarsandoval/Desktop/proyect/Diccionario de datos.txt");
    std::remove("/Users/oscarsandoval/Desktop/proyect/Total de caracteres.txt");
    ifstream a ("/Users/oscarsandoval/Desktop/proyect/proyect//AA.txt");
    ofstream archive("/Users/oscarsandoval/Desktop/proyect/Clientes.txt",ios::out);
    string myStr,b;
    while(getline(a, myStr)){
        b+=myStr;
    }
    a.close();
    archive<<b;
    archive.close();
    std::remove("/Users/oscarsandoval/Desktop/proyect/proyect//AA.txt");
}

bool Clientes::isValidInsert(){
    fstream archive ("/Users/oscarsandoval/Desktop/proyect//Huffman.txt");
    if(archive.good()){
        archive.close();
        return true;
    }
    return false;
}

void Clientes::aux(const std::string &s){
    ofstream archive ("/Users/oscarsandoval/Desktop/proyect/proyect//AA.txt",ios::out);
    archive<<s;
    archive.close();
}


