//
//  grafo.cpp
//  proyect
//
//  Created by Oscar Sandoval on 2/21/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#include "grafo.hpp"
using namespace std;
Grafo::Grafo():counter(0){
    
}
bool Grafo::isEmpty(){
    return vertice[0].getActive()==1;
}
int Grafo::isValidData(string data){
    for(int i=0;i<counter;++i)
        if(vertice[i].getName()==data)
            return i;
    return -1;
}
void Grafo::printData(Console& graphics){
    if(!isEmpty()){
        throw std::invalid_argument("Grafo vacio");
    }
    string a;
    int aux=6;
    system("clear");
    graphics.moveTo(4,0);
    graphics.setColor(graphics.FG_WHITE);
    for(int i=0;i<counter;i++){
        
        cout<<"\t"<<vertice[i].getData();
    }
    graphics.moveTo(5,0);
    cout<<"______________________________________________________________________________";
    for(int i=0;i<counter;i++){
        graphics.moveTo(aux, 0);
        for(int j=0;j<counter;++j){
            /*arista[0][1].setActive(1);
            arista[0][2].setActive(1);*/
            if(arista[i][j].getActive()==1){
                graphics.setColor(graphics.FG_DARK_CYAN);
                cout<<"\t "<<arista[i][j].getPeso();
            }
            else{
                graphics.setColor(graphics.FG_LIGHT_RED);
                cout<<"\t * ";
            }
        }
        aux+=2;
    }
    aux=6;
    for(int i=0;i<counter;i++){
        graphics.moveTo(aux, 0);
        graphics.setColor(graphics.FG_WHITE);
        cout<<vertice[i].getData();
        aux+=2;
    }
    /////////
    graphics.moveTo(22, 25);
    graphics.setColor(graphics.FG_WHITE);
    cout<<"Presione enter para continuar";
    getline(cin,a);
    system("clear");

}
void Grafo::insertData(std::string  data,std::string d){
    if(counter==10)
        throw std::invalid_argument("memoria no disponible\n");
    std::string myStr;
    bool band;
    vertice[counter].setData(d);
    vertice[counter].setName(data);
    vertice[counter].setActive(1);
    for(int i=0;i<counter;i++){
        if(i==counter)
            continue;
        do{
            band=false;
            system("clear");
            std::cout<<"\t¿"<<vertice[counter].getName()<<" conecta con "<<vertice[i].getName()<<"? S/N"<<std::endl;
            getline(std::cin,myStr);
            if(myStr=="S"||myStr=="s"){
                arista[counter][i].setActive(1);
                arista[i][counter].setActive(1);
                do{
                    band=false;
                    try{
                        std::cout<<"\tDistancia de "<<vertice[counter].getName()<<" a "<<vertice[i].getName()<<" : ";
                        getline(std::cin,myStr);
                        arista[counter][i].setPeso(myStr);
                        arista[i][counter].setPeso(myStr);
                    }catch(std::invalid_argument& ex){
                        std::cerr<<ex.what()<<std::endl;
                        system("clear");
                        band=true;
                    }
                }while(band==true);
                std::cout<<"\tRuta conectada"<<std::endl;
            }
            else if(myStr=="N"||myStr=="n"){
                
            }
            else{
                system("clear");
                band=true;
                std::cout<<"Opcion no valida"<<std::endl;
            }
        }while(band==true);
    }
    counter++;
   /* if(counter==7){
        arista[0][2].setActive(1);
        arista[0][1].setActive(1);
    }*/
}
void Grafo::modifyData(std::string oldName, std::string newName){
    for(int i=0;i<counter;++i){
        if(vertice[i].getData()==oldName){
            vertice[i].setData(newName);
        }
    }
}
void Grafo::modifyAristas(std::string& data){
    int pos(isValidData(data));
    if(pos==-1)
        throw invalid_argument("No se encontro ninguna ruta\n");
    bool band;
    system("clear");
    cout<<"\tModificar Aristas de "<<vertice[pos].getData()<<endl<<endl;
    for(int i=0;i<counter;i++){
        do{
            band=false;
            cout<<"¿"<<vertice[pos].getData()<<" Conecta con "<<vertice[i].getData()<<"? "<<endl;
            getline(std::cin,data);
            if(data=="S"||data=="s"){
                arista[pos][i].setActive(1);
                arista[i][pos].setActive(1);
                do{
                    band=false;
                    try{
                        std::cout<<"Distancia de "<<vertice[pos].getData()<<" a "<<vertice[i].getData()<<" : ";
                        getline(std::cin,data);
                        arista[pos][i].setPeso(data);
                        arista[i][pos].setPeso(data);
                    }catch(std::invalid_argument& ex){
                        std::cerr<<ex.what()<<std::endl;
                        system("clear");
                        band=true;
                    }
                }while(band==true);
                std::cout<<"Ruta conectada"<<std::endl;
            }
            else if(data=="N"||data=="n"){
                arista[pos][i].setActive(0);
                arista[i][pos].setActive(0);
            }
            else{
                system("clear");
                band=true;
                std::cout<<"Opcion no valida"<<std::endl;
            }
        }while(band==true);
    }
}
void Grafo::remove(std::string data){
    int pos(isValidData(data));
    if(pos==-1)
        throw invalid_argument("No se encontro ningun destino remove \n");
    for(int i=pos;i<counter;++i){
        vertice[i]=vertice[i+1];
    }
    vertice[counter-1].setActive(0);
    for(int i=0;i<counter;i++)
        for(int j=pos;j<counter;++j)
            arista[i][j]=arista[i][j+1];
    for(int i=pos;i<counter;i++){
        for(int j=0;j<counter;j++){
            arista[i][j]=arista[i+1][j];
        }
    }
    for(int i=0;i<counter;i++){
        arista[i][counter].setActive(0);
        arista[counter][i].setActive(0);
    }
    counter--;
}
int Grafo::start(Console& graphics){
    string myStr;
    bool band;
    int i;
    system("clear");
    graphics.setColor(graphics.FG_LIGHT_BLUE);
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
    do{
        band=false;
        graphics.moveTo(5,15);
        std::cout<<"\t\t\tPunto de partida : "<<std::endl;
        for(i=0;i<counter;i++){
            graphics.moveTo(7+i,15);
            std::cout<<"\t"<<i+1<<")"<<vertice[i].getName()<<std::endl;
        }
        graphics.moveTo(7+i,15);
        cout<<"\tOrigen  : ";
        getline(cin,myStr);
        int pos;
        try{
            pos=stoi(myStr);
            if(pos<=counter&&pos>0){
                return --pos;
            }else{
                band=true;
            }
        }catch(invalid_argument& ex){
            band=true;
        }
    }while(band);
    return -1;
}
void Grafo::travel(Console& graphics){
    string myStr;
    bool band;
    system("clear");
    do{
        band=false;
        graphics.moveTo(5, 15);
        cout<<"\t\t\tRecorridos del Grafo : ";
        graphics.moveTo(7, 15);
        cout<<"\t1)Recorrido en Anchura"<<endl;
        graphics.moveTo(8, 15);
        cout<<"\t2)Recorrido en Profundidad"<<endl;
        graphics.moveTo(9, 15);
        cout <<"\t3)Regresar"<<endl;
        graphics.moveTo(10, 15);
        cout<<"\tElige una opcion : ";
        getline(cin,myStr);
        if(myStr=="1"){
            widthTravel(start(graphics),graphics);
        }else if(myStr=="2"){
            depthTravel(start(graphics),graphics);
        }else if(myStr=="3"){
            return;
        }else{
            graphics.moveTo(20, 18);
            cout<<"Opcion no valida"<<endl;
            band=true;
        }
    }while(band);
}
int Grafo::getPos(Vertice actual){
    for(int i=0;i<counter;i++)
        if(actual==vertice[i])
            return i;
    return -1;
}
void Grafo::widthTravel(int origen,Console& graphics){
    graphics.moveTo(15, 18);
    cout<<"Punto de partida "<<vertice[origen].getData()<<endl;
    ListaEstatica<Vertice> list;
    Queu<Vertice> queue;
    Vertice actual;
    //Anchura
    queue.enqueu(vertice[origen]);
    while(!queue.isEmpty()){
        actual=queue.dequeue();
        origen=getPos(actual);
        if(!list.find(actual)){
            list.insert(actual);
            int i=0;
            while(i<counter){
                if(arista[origen][i].getActive()==1){
                    if(!list.find(vertice[i])){
                        queue.enqueu(vertice[i]);
                    }
                }
                i++;
            }
        }
    }
    system("clear");
    graphics.setColor(graphics.FG_LIGHT_BLUE);
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
    cout<<"Recorrido en Anchura : ";
    graphics.setColor(graphics.FG_DARK_GREEN);
    for(int i =0;i<list.size();i++){
        graphics.moveTo(7+i, 15);
        cout<<list[i].getName();
    }
    graphics.setColor(graphics.FG_WHITE);
    cin.get();
}
void Grafo::depthTravel(int origen,Console& graphics){
    graphics.moveTo(15, 18);
    cout<<"Punto de partida "<<vertice[origen].getData()<<endl;
    //Profundidad
    ListaEstatica<Vertice> list;
    Stack<Vertice> stack;
    Vertice actual;
    //Anchura
    stack.push(vertice[origen]);
    while(!stack.isEmpty()){
        actual=stack.pop();
        origen=getPos(actual);
        if(!list.find(actual)){
            list.insert(actual);
            int i=0;
            while(i<counter){
                if(arista[origen][i].getActive()==1){
                    if(!list.find(vertice[i])){
                        stack.push(vertice[i]);
                    }
                }
                i++;
            }
        }
    }
    system("clear");
    graphics.setColor(graphics.FG_LIGHT_BLUE);
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
    cout<<"Recorrido en Profundidad : ";
    graphics.setColor(graphics.FG_DARK_GREEN);
    for(int i =0;i<list.size();i++){
        graphics.moveTo(7+i, 15);
        cout<<list[i].getName();
    }
    graphics.setColor(graphics.FG_WHITE);
    cin.get();
}
void Grafo::busquedas(Console& graphics){
    string myStr;
    bool band;
    int origen;
    int i;
    int destino;
    do{
        band=false;
        graphics.moveTo(5, 15);
        cout<<"\t\t\tBusqueda : ";
        for(i=0;i<counter;i++){
            graphics.moveTo(7+i,15);
            std::cout<<"\t"<<i+1<<")"<<vertice[i].getName()<<std::endl;
        }
        graphics.moveTo(7+i,15);
        cout<<"\tOrigen : ";
        getline(cin,myStr);
        try{
            origen=stoi(myStr);
            if(origen<=counter&&origen>0){
                origen--;
            }else{
                band=true;
            }
        }catch(invalid_argument& ex){
            band=true;
        }
    }while(band);
    system("clear");
    graphics.setColor(graphics.FG_LIGHT_BLUE);
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
    do{
        band=false;
        graphics.moveTo(5, 15);
        cout<<"\t\t\tBusqueda : ";
        for(i=0;i<counter;i++){
            graphics.moveTo(7+i, 15);
            std::cout<<"\t"<<i+1<<")"<<vertice[i].getName()<<std::endl;
        }
        graphics.moveTo(7+i, 15);
        cout<<"\tDestino : ";
        getline(cin,myStr);
        try{
            destino=stoi(myStr);
            if(destino<=counter&&destino>0){
                destino--;
            }else{
                band=true;
            }
        }catch(invalid_argument& ex){
            band=true;
        }
    }while(band);
    system("clear");
    graphics.setColor(graphics.FG_LIGHT_BLUE);
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
    cout<<"\t\t\tBusquedas"<<endl;
     graphics.moveTo(7, 15);
    cout<<"1)Busqueda en Anchura"<<endl;
     graphics.moveTo(8, 15);
    cout<<"2)Busqueda en Profundidad"<<endl;
     graphics.moveTo(9, 15);
    cout<<"3)Regresar"<<endl;
     graphics.moveTo(10, 15);
   cout <<"Elige una opcion : ";
    getline(cin,myStr);
    if(myStr=="1"){
        busquedaAnchura(origen, destino,graphics);
    }else if(myStr=="2"){
        busquedaProfundidad(origen,destino,graphics);
    }else if(myStr=="3"){
        return;
    }else{
        graphics.moveTo(22, 18);
        cout<<"Opcion no valida"<<endl;
    }
}
void Grafo::busquedaAnchura(int& origen,int& destino,Console& graphics){
    Queu<Vertice> queue;
    Stack<Vertice> stackOrigen;
    Stack<Vertice> stackDestino;
    ListaEstatica<Vertice> visitados;
    Vertice actual;
    queue.enqueu(vertice[origen]);
    while(!queue.isEmpty()){
        actual=queue.dequeue();
        if(!visitados.find(actual)){
            if(actual==vertice[destino]){
                desplegarRuta(stackOrigen,stackDestino, destino,graphics);
                return;
            }
            visitados.insert(actual);
            int i=0;
            while(i<counter){
                if(arista[getPos(actual)][i].getActive()==1){
                    if(!visitados.find(vertice[i])){
                        queue.enqueu(vertice[i]);
                        stackOrigen.push(actual);
                        stackDestino.push(vertice[i]);
                    }
                }
                i++;
            }
        }
    }
    graphics.moveTo(22, 18);
    cout<<"No existe Ruta entre estos 2 vertices"<<endl;
}
void Grafo::busquedaProfundidad(int& origen,int& destino,Console& graphics){
    Stack<Vertice> stack;
    Stack<Vertice> stackOrigen;
    Stack<Vertice> stackDestino;
    ListaEstatica<Vertice> visitados;
    Vertice actual;
    stack.push(vertice[origen]);
    while(!stack.isEmpty()){
        actual=stack.pop();
        if(!visitados.find(actual)){
            if(actual==vertice[destino]){
                desplegarRuta(stackOrigen,stackDestino, destino,graphics);
                return;
            }
            visitados.insert(actual);
            int i=0;
            while(i<counter){
                if(arista[getPos(actual)][i].getActive()==1){
                    if(!visitados.find(vertice[i])){
                        stack.push(vertice[i]);
                        stackOrigen.push(actual);
                        stackDestino.push(vertice[i]);
                    }
                }
                i++;
            }
        }
    }
    graphics.moveTo(22, 18);
    cout<<"No existe Ruta entre estos 2 vertices"<<endl;
}
void Grafo::desplegarRuta(Stack<Vertice> &stackOrigen, Stack<Vertice> &stackDestino, int &destino,Console& graphics){
    Vertice actual;
    actual=vertice[destino];
    string ab;
    graphics.moveTo(18, 16);
    cout<<"Ruta : ";
    while(!stackOrigen.isEmpty()&&!stackDestino.isEmpty()){
        ab+=actual.getName();
        while(!stackDestino.isEmpty()&&stackDestino.getTop()!=actual){
            stackDestino.pop();
            stackOrigen.pop();
        }
        if(!stackOrigen.isEmpty()){
            actual=stackOrigen.getTop();
            ab+="->";
        }
    }
    graphics.setColor(graphics.FG_DARK_GREEN);
    graphics.moveTo(20, 5);
    cout<<ab;
    cout<<endl;
    cin.get();
}
