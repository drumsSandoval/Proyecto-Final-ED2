//
//  destino.hpp
//  proyect
//
//  Created by Oscar Sandoval on 2/14/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#ifndef destino_hpp
#define destino_hpp
#include "indices.hpp"
#include "grafo.hpp"
class Destino{
public:
    int activate;
    int code;
    char zone[20];
    float location;
    char name[20];
    bool operator > (Destino& d)const{
       return this->code>d.code;
    }
    bool operator < (Destino& d)const{
        return this->code<d.code;
    }
    bool operator >= (Destino& d)const{
        return this->code>=d.code;
    }
    bool operator <= (Destino& d)const{
        return this->code<=d.code;
    }
    bool operator == (Destino& d)const{
        return this->code==d.code;
    }
    Destino operator = (const Destino& d){
        activate=d.activate;
        code=d.code;
        for(int i=0;i<20;i++)
            this->zone[i]='\0';
        for(int i=0;d.zone[i];i++)
            this->zone[i]=d.zone[i];
        location=d.location;
        for(int i=0;i<20;i++)
            this->name[i]='\0';
        for(int i=0;d.name[i];i++)
            this->name[i]=d.name[i];
        return *this;
    }
    friend std::ostream& operator << (std::ostream& os,Destino& c){
        os<<c.name<<endl;
        os<<"Code : "<<c.code<<endl;
        os<<"Zona : "<<c.zone<<endl;
        return os;
    }
};
class Destinos{
private:
    Destino destino;
    Indices indice;
    IndiceSecundario indiceZona;
    
public:
    Destinos(){}
    Destinos(List<Indices>&,List<IndiceSecundario>&,List<nodo>&);
    Destinos(List<Indices>&);
    void readGraph(Grafo&);
    //Setters
    void setCode();
    void setZone(std::string&);
    void setLocation(float&);
    void setName(std::string&);
    void setGrafo(std::string&);
    //Getters
    int getCode();
    std::string getZone();
    float getLocation();
    std::string getName();
    std::string getName(List<Indices>&,std::string);
 
    //Metodos chidos!
    void insert(List<Indices>&,List<IndiceSecundario>&,List<nodo>&);
    void print();
    void search(List<Indices>&,std::string&,Console&);
    void sort(List<Destino>&);
    void modify(List<Indices>&,std::string&,Grafo&,Console&,List<IndiceSecundario>&,List<nodo>&);
    void logicRemove(List<Indices>&,std::string&,Console&);
    void remove(List<Indices>&,List<IndiceSecundario>&,List<nodo>&,std::string&,Console&);
    void active(List<Indices>&,std::string&);
    void save(List<Indices>&,Grafo&,List<IndiceSecundario>&,List<nodo>&);
    void searchZone(List<Indices>&,List<IndiceSecundario>&,List<nodo>&,Console&,std::string&);
    void searchZone(List<IndiceSecundario>&,Console&,std::string&);
    Destinos operator = (const Destino&);
    int setDestino(Console&);
    bool isValidRemove(std::string&);
};
#endif /* destino_hpp */
