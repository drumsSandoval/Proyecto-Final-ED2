//
//  destino.cpp
//  proyect
//
//  Created by Oscar Sandoval on 2/14/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#include "destinos.hpp"
#include <stdexcept>
#include <fstream>
#include "ventas.hpp"
Destinos::Destinos(List<Indices>& list,List<IndiceSecundario>& listZona,List<nodo>& listaInvertida):indiceZona(listZona,listaInvertida){
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Indices.txt");
    list.deleteAll();
    if(!archive.good()){
        destino.code=0;
        return;
    }
    while(!archive.eof()){
        archive.read((char*)&indice,sizeof(indice));
        if(archive.eof())break;
        list.insertData(list.getLastPos(), indice);
    }
    archive.close();
    destino.code = indice.getKey();
}

Destinos::Destinos(List<Indices>& list): indiceZona(){
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Indices.txt");
    list.deleteAll();
    if(!archive.good()){
        destino.code=0;
        return;
    }
    while(!archive.eof()){
        archive.read((char*)&indice,sizeof(indice));
        if(archive.eof())break;
        list.insertData(list.getLastPos(), indice);
    }
    archive.close();
}

void Destinos::readGraph(Grafo &grafo){
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Rutas.txt");
    if(!archive.good())
        return;
    archive.read((char*)&grafo,sizeof(Grafo));
}
//Setters
void Destinos::setCode(){
    destino.code++;
}
void Destinos::setName(std::string &name){
    for(int i=0;i<20;i++)
        this->destino.name[i]='\0';
    for(int i=0;name[i];i++)
        this->destino.name[i]=name[i];
}
void Destinos::setZone(std::string &zone){
    for(int i=0;i<20;i++)
        this->destino.zone[i]='\0';
    for(int i=0;zone[i];i++)
        this->destino.zone[i]=zone[i];
}
void Destinos::setLocation(float & location){
    destino.location=location;
}
//Getters
int Destinos::getCode(){
    return destino.code;
}
string Destinos::getZone(){
    return destino.zone;
}
float Destinos::getLocation(){
    return destino.location;
}
string Destinos::getName(){
    string myStr;
    for(int i=0;destino.name[i];i++)
        myStr+=destino.name[i];
    return myStr;
}
string Destinos::getName(List<Indices>& list,std::string user){
    try{
        indice.setKey(stoi(user));
    }catch(invalid_argument& ex){
        throw invalid_argument("Ingrese un valor valido");
    }
    try{
        indice=list.retrieve(list.findData(indice));
    }catch(ListException& ex){
        throw invalid_argument("Destino no encontrado :( get name\n");
    }
    string myStr;
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Destinos.txt");
    archive.seekg(indice.getAddress());
    archive.read((char*)&destino,sizeof(destino));
    for(int i=0;destino.name[i];i++){
        myStr+=destino.name[i];
    }
    return myStr;
}
//Metodos chidos
void Destinos::insert(List<Indices> & list,List<IndiceSecundario>& listZona,List<nodo>& listaInvertida){
    ofstream archive("/Users/oscarsandoval/Desktop/proyect/Destinos.txt",ios::app);
    system("clear");
    nodo node;
    indice.setAddress(archive.tellp());
    indice.setKey(getCode());
    indiceZona.setKey(getZone());
    indiceZona.setAddress(nullptr);
    list.insertData(list.getLastPos(), indice);
    node.first=destino.code;
    if(!listZona.find(indiceZona)){
        listaInvertida.insertData(listaInvertida.getLastPos(),node);
        indiceZona.setAddress(listaInvertida.getLastPos());
        listZona.insertData(listZona.getLastPos(),indiceZona);
    }else{
        int pos = listZona.findPos(indiceZona);
        Node<nodo> *aux=listZona[pos].getAddress();
        pos=listaInvertida[aux];
        if(listaInvertida[pos].second==nullptr){
            listaInvertida.insertData(listaInvertida.getLastPos(),node);
            listaInvertida[pos].second = listaInvertida.getLastPos();
          
        }else{
            while(listaInvertida[pos].second!=nullptr){
                aux=listaInvertida[pos].second;
                pos=listaInvertida[aux];
            }
            listaInvertida.insertData(listaInvertida.getLastPos(), node);
            listaInvertida[pos].second=listaInvertida.getLastPos();
        }
    }
    destino.activate=1;
    archive.write((char*)&destino, sizeof(destino));
    archive.close();
}
//Imprime
void Destinos::print(){
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Destinos.txt");
    if(!archive.good()){
        cout<<"No hay aspirantes resistrados"<<endl;
        return;
    }
    while(!archive.eof()){
        archive.read((char*)&destino,sizeof(destino));
        if(archive.eof())break;
        if(destino.activate==1){
            cout<<"\tDestino : "<<destino.name<<endl;
            cout<<"\tZona : "<<destino.zone<<endl;
            cout<<"\tUbicacion : "<<destino.location<<endl;
            cout<<"\tCodigo : "<<destino.code<<endl;
        }
    }
    archive.close();
}
//Consultas
void Destinos::search(List<Indices> &list, std::string &user,Console& graphics){
    try{
        indice.setKey(stoi(user));
    }catch(invalid_argument& ex){
        throw invalid_argument("Ingrese un valor valido");
    }
    try{
        indice=list.retrieve(list.findData(indice));
    }catch(ListException& ex){
        throw invalid_argument("Destino no encontrado :(\n");
    }
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Destinos.txt");
    archive.seekg(indice.getAddress());
    archive.read((char*)&destino,sizeof(destino));
    graphics.moveTo(5, 15);
    cout<<"\t\tDestino encontrado : "<<endl;
    graphics.moveTo(7, 15);
    cout<<"Destino : "<<destino.name<<endl;
    graphics.moveTo(8, 15);
    cout<<"Zona : "<<destino.zone<<endl;
    graphics.moveTo(9, 15);
    cout<<"Codigo : "<<destino.code<<endl;
    archive.close();
    cin.get();
}
//Modificar
void Destinos::modify(List<Indices> &list, std::string &user,Grafo& grafo,Console& graphics,List<IndiceSecundario>& listZona,List<nodo>&listaInvertida){
    try{
        indice.setKey(stoi(user));
    }catch(invalid_argument& ex){
        throw invalid_argument("Ingrese un valor valido");
    }
    try{
        indice=list.retrieve(list.findData(indice));
    }catch(ListException& ex){
        throw invalid_argument("Destino no encontrado :(\n");
    }
    fstream archive("/Users/oscarsandoval/Desktop/proyect/Destinos.txt",ios::in|ios::out);
    string myStr;
    archive.seekg(indice.getAddress());
    archive.read((char*)&destino,sizeof(destino));
    if(destino.activate==0){
        throw invalid_argument("Usuario no encontrado\n");
    }
    do{
        graphics.moveTo(5, 15);
        cout<<"\t\tModificar Destino"<<endl;
        graphics.moveTo(7, 15);
        cout<<"1)Nombre"<<endl;
        graphics.moveTo(8, 15);
        cout<<"2)Ubicacion"<<endl;
        graphics.moveTo(9, 15);
        cout<<"3)Zona"<<endl;
        graphics.moveTo(10, 15);
        cout<<"4)Regresar"<<endl;
        graphics.moveTo(11, 15);
        cout <<"Eline una opcion : ";
        getline(cin,myStr);
        if(myStr=="1"){
            system("clear");
            graphics.setColor(graphics.FG_DARK_GRAY);
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
            cout<<"\t\tModificar Nombre : "<<endl;
            graphics.moveTo(7, 15);
            cout<<"\tNombre actual : "<<getName()<<endl;
            graphics.moveTo(8, 15);
            cout<<"Nuevo nombre : ";
            getline(cin,myStr);
            for(int i = 0;myStr[i];++i)
                myStr[i] = toupper(myStr[i]);
            grafo.modifyData(getName(),myStr);
            setName(myStr);
        }
        else if(myStr=="2"){
            float aux;
            bool band;
            do{
                system("clear");
                graphics.setColor(graphics.FG_DARK_GRAY);
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
                graphics.moveTo(5, 15);
                cout<<"\t\tModificar Ubicacion : "<<endl;
                graphics.moveTo(7, 15);
                cout<<"\tUbicacion actual : "<<getLocation()<<endl;
                graphics.moveTo(8, 15);
                cout<<"Nueva ubicacion : ";
                try{
                    cin>>aux;
                }catch(invalid_argument& xe){
                    graphics.moveTo(20, 15);
                    cerr<<xe.what();
                    band=true;
                }
                cin.ignore();
            }while(band==true);
            setLocation(aux);
            
        }
        else if(myStr=="3"){
            bool band;
            do{
                system("clear");
                graphics.setColor(graphics.FG_DARK_GRAY);
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
                graphics.moveTo(5,15);
                cout<<"\t\tModificar Zona : "<<endl;
                graphics.moveTo(7,15);
                cout<<"\tZona actual : "<<getZone()<<endl;
                graphics.moveTo(8,15);
                cout<<"Nueva  Zona : ";
                getline(cin, myStr);
                try{
                    setZone(myStr);
                }catch(invalid_argument& ex){
                    graphics.moveTo(20,15);
                    cerr<<ex.what();
                    band=true;
                }
            }while(band==true);
            int aux(getCode());
            string aux2=getName();
            remove(list, listZona,listaInvertida, user,graphics);
            destino.code=aux;
            setZone(myStr);
            setName(aux2);
            insert(list,listZona, listaInvertida);
            return;
        }
        else if(myStr=="4"){
            system("clear");
        }
        else{
            cout<<"Opcion no valida\n";
        }
    }while(myStr!="4");
    archive.seekg(indice.getAddress());
    archive.write((char*)&destino, sizeof(destino));
    archive.close();
    destino.code = list.getLastPos()->getData().getKey();
    cout<<"Informacion Actualizada"<<endl;
}
//Eliminacion Logica
void Destinos::logicRemove(List<Indices> &list, std::string &user,Console& graphics){
    try{
        indice.setKey(stoi(user));
    }catch(invalid_argument& ex){
        throw invalid_argument("Ingrese un valor valido");
    }
    try{
        indice=list.retrieve(list.findData(indice));
    }catch(ListException& ex){
        throw invalid_argument("Destino no encontrado :(\n");
    }
    fstream archive("/Users/oscarsandoval/Desktop/proyect/Destinos.txt",ios::in|ios::out);
    string myStr;
    archive.seekg(indice.getAddress());
    archive.read((char*)&destino,sizeof(destino));
    if(destino.activate==1){
        destino.activate=0;
        archive.seekg(indice.getAddress());
        archive.write((char*)&destino,sizeof(destino));
        archive.close();
        graphics.moveTo(20, 29);
        cout<<"Destino eliminado"<<endl;
        cin.get();
        return;
    }
    archive.close();
    system("clear");
    cout<<"Destino no encontrado"<<endl;
}
//Activar Usuario
void Destinos::active(List<Indices> &list, std::string &user){
    try{
        indice.setKey(stoi(user));
    }catch(invalid_argument& ex){
        throw invalid_argument("Ingrese un valor valido");
    }
    try{
        indice=list.retrieve(list.findData(indice));
    }catch(ListException& ex){
        throw invalid_argument("Destino no encontrado :(\n");
    }
    fstream archive("/Users/oscarsandoval/Desktop/proyect/Destinos.txt",ios::in|ios::out);
    string myStr;
    archive.seekg(indice.getAddress());
    archive.read((char*)&destino,sizeof(destino));
    if(destino.activate==0){
        destino.activate=1;
        archive.seekg(indice.getAddress());
        archive.write((char*)&destino,sizeof(destino));
        archive.close();
        system("clear");
        cout<<"Destino activado"<<endl;
        return;
    }
    archive.close();
    system("clear");
    cout<<"Destino no encontrado"<<endl;
}

void Destinos::remove(List<Indices> &list,List<IndiceSecundario>& listZone,List<nodo>&listaInvertida, std::string &user,Console& graphics){
    if(!isValidRemove(user)){
        graphics.moveTo(20, 12);
        cout<<"No es posible eliminar este destino, tiene ventas registradas";
        cin.get();
        return;
    }
    try{
        indice.setKey(stoi(user));
    }catch(invalid_argument& ex){
        throw invalid_argument("Ingrese un valor valido");
    }
    try{
        indice=list.retrieve(list.findData(indice));
    }catch(ListException& ex){
        throw invalid_argument("Destino no encontrado :(\n");
    }
    int pos = list.findPos(indice);
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Destinos.txt");
    archive.seekg(list[pos].getAddress());
    archive.read((char*)&destino, sizeof(destino));
    archive.close();
    indiceZona.setKey(getZone());
    pos = listZone.findPos(indiceZona);
    Node<nodo>* aux(listZone[pos].getAddress());
    if(aux->getData().second == nullptr && aux->getData().first == getCode()){
        listZone.deleteData(listZone.findData(listZone[pos]));
        listaInvertida.deleteData(aux);
    }else{
        if(aux->getData().first==getCode()){
            listZone[pos].setAddress(aux->getData().second);
            listaInvertida.deleteData(aux);
        }else{
            Node<nodo>* aux2(aux->getData().second);
            while(aux2!=nullptr){
                if(aux2->getData().first==getCode()){
                    aux->getData().second = aux2->getData().second;
                    listaInvertida.deleteData(aux2);
                    break;
                }
                aux2 = aux2->getData().second;
                aux = aux->getData().second;
            }
        }
    }
    ifstream read("/Users/oscarsandoval/Desktop/proyect/Destinos.txt");
    ofstream writer("/Users/oscarsandoval/Desktop/proyect/Aux.txt",ios::out);
    list.deleteAll();
    while(!read.eof()){
        read.read((char*)&destino,sizeof(destino));
        if(read.eof())break;
        if(destino.code==stoi(user)){
            if(destino.activate==1){
                cout<<"Destino Eliminado"<<endl;
            }
            else{
                indice.setKey(getCode());
                indice.setAddress(writer.tellp());
                writer.write((char*)&destino,sizeof(destino));
                list.insertData(list.getLastPos(),indice);
            }
        }
        else{
            indice.setKey(getCode());
            indice.setAddress(writer.tellp());
            writer.write((char*)&destino,sizeof(destino));
            list.insertData(list.getLastPos(),indice);
        }
    }
    read.close();
    writer.close();
    std::remove("/Users/oscarsandoval/Desktop/proyect/Destinos.txt");
    rename("/Users/oscarsandoval/Desktop/proyect/Aux.txt","/Users/oscarsandoval/Desktop/proyect/Destinos.txt");
}

void Destinos::sort(List<Destino> &list){
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Destinos.txt");
    list.deleteAll();
    if(!archive.good()){
        throw invalid_argument("No hay Destinos Registrados\n");
    }
    while(!archive.eof()){
        archive.read((char*)&destino,sizeof(destino));
        if(archive.eof())break;
        if(destino.activate==1){
            list.insertData(list.getLastPos(), destino);
        }
    }
    archive.close();
    list.Sort();
}

void Destinos::save(List<Indices> &list,Grafo& grafo,List<IndiceSecundario>&listZona,List<nodo>&listaInvertida){
    indice.save(list);
    indiceZona.save(listZona,listaInvertida);
    if(grafo.isEmpty()){
        ofstream archive("/Users/oscarsandoval/Desktop/proyect/Rutas.txt",ios::out);
        archive.write((char*)&grafo,sizeof(grafo));
    }
    ofstream save;
    save.open("/Users/oscarsandoval/Desktop/proyect/ListaInvertida.txt",ios::out);
    int i=0;
    while(i<=listaInvertida.size()){
        save<<listaInvertida[i].first<<"|";
        i++;
    }
    save<<endl;
    i=0;
    while(i<=listaInvertida.size()){
        save<<listaInvertida[listaInvertida[i].second]<<"|";
        i++;
    }
    save<<endl;
    save.close();
}
void Destinos::searchZone(List<Indices> &listIndices, List<IndiceSecundario> &listZona, List<nodo> &listaInvertida, Console &graphics,string& zone){
    indiceZona.setKey(zone);
    if(!listZona.find(indiceZona)){
        throw invalid_argument("Zona no encontrada");
    }
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Destinos.txt");
    int pos = listZona.findPos(indiceZona);
    Node<nodo>* aux(listZona[pos].getAddress());
    int i=0,a,b;//auxf=7,auxe=8;
    a=7; b=9;
    graphics.setColor(graphics.FG_DARK_YELLOW);
    graphics.moveTo(6, 5);
    cout<<"   CODE\t\t\tDESTINO\t\t\tZONA";
    graphics.setColor(graphics.FG_WHITE);
    while(aux!=nullptr){
        int aux2;
        pos=listaInvertida[aux];
        indice.setKey(listaInvertida[pos].first);
        aux2 =listIndices.findPos(indice);
        archive.seekg(listIndices[aux2].getAddress());
        archive.read((char*)&destino,sizeof(destino));
        if(destino.activate==1){
                graphics.moveTo(a, b);
                cout<<destino.code;
                b=33;
                graphics.moveTo(a, b);
                cout<<destino.name;
                b=57;
                graphics.moveTo(a, b);
                cout<<destino.zone;
                a++;
                b=9;
        }
        //graphics.moveTo(auxf,auxe);
       // cout<<"Destino : "<<destino.name;
       // graphics.moveTo(auxf+1,auxe);
        //cout<<"Codigo : "<<destino.code;
        //graphics.moveTo(auxf+2,auxe);
        //cout<<"Zona : "<<destino.zone;
        i++;
       // auxe+=20;
       // if(i==3||i==6){
       //     auxf+=5;
         //   auxe=8;
      //  }
        aux=listaInvertida[pos].second;
    }
    archive.close();
    destino.code = listIndices.getLastPos()->getData().getKey();
    cin.get();
}

void Destinos::searchZone(List<IndiceSecundario> & list , Console & graphics, std::string &zone){
    indiceZona.setKey(zone);
    if(!list.find(indiceZona)){
        throw invalid_argument("Zona no encontrada");
    }
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Destinos.txt");
    int a,b;//auxf=7,auxe=8;
    a=7; b=9;
    graphics.setColor(graphics.FG_DARK_YELLOW);
    graphics.moveTo(6, 5);
    cout<<"   CODE\t\t\tDESTINO\t\t\tZONA";
    graphics.setColor(graphics.FG_WHITE);
    while(!archive.eof()){
        archive.read((char*)&destino, sizeof(Destino));
        if(archive.eof())break;
        if(destino.zone == zone){
            if(destino.activate==1){
                graphics.moveTo(a, b);
                cout<<destino.code;
                b=33;
                graphics.moveTo(a, b);
                cout<<destino.name;
                b=57;
                graphics.moveTo(a, b);
                cout<<destino.zone;
                a++;
                b=9;
            }
        }
    }
    cin.get();
}

int Destinos::setDestino(Console & graphics){
    string myStr;
    graphics.moveTo(4,25);
    graphics.setColor(graphics.FG_GRAY);
    cout<<"Seleccione el Destino del Cliente ";
    graphics.moveTo(5,8);
    graphics.setColor(graphics.FG_LIGHT_YELLOW);
    cout<<"Codigo\t\tDestino";
    graphics.moveTo(5,44);
    cout<<"Codigo\t\tDestino";
    graphics.setColor(graphics.FG_WHITE);
    for(int i=6;i<18;i++){
        graphics.moveTo(i, 40);
        cout<<"▎";
    }
    int x=6, y=10,i=0;
    bool band=false;
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/Destinos.txt");
    while(!archive.eof()){
        archive.read((char*)&destino, sizeof(destino));
        if(archive.eof())break;
        if(destino.activate==1){
            graphics.moveTo(x,y);
            cout<<destino.code;
            y+=8;
            graphics.moveTo(x, y);
            cout<<destino.name;
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
    archive.close();
    graphics.setColor(graphics.FG_LIGHT_BLUE);
    graphics.moveTo(19, 25);
    cout<<"Codigo de Destino : ";
    getline(cin, myStr);
    try{
        return stoi(myStr);
    }catch(invalid_argument& ex){
        throw invalid_argument("Ingresa un codigo valido");
    }
}

bool Destinos::isValidRemove(std::string &code){
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/DetalleVenta.txt");
    Detalle aux;
    if(!archive.good())
        return true;
    while(!archive.eof()){
        archive.read((char*)&aux, sizeof(Detalle));
        if(archive.eof())break;
        if(to_string(aux.codigoDestino) == code){
            return false;
        }
    }
    return true;
}
