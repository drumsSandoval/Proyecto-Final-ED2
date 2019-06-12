//
//  indices.hpp
//  proyect
//
//  Created by Oscar Sandoval on 2/14/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#ifndef indices_hpp
#define indices_hpp
#include "list.hpp"
#include "node.hpp"
class Indices{
private:
    long address;
    int key;
public:
    Indices();
    //Setters
    void setAddress(long);
    void setKey(int);
    //Getters
    long getAddress();
    int getKey();
    //Sobre carga de operadores
    bool operator > (Indices&)const;
    bool operator < (const Indices&)const;
    bool operator >= (const Indices&)const;
    bool operator <= (const Indices&)const;
    bool operator == (const Indices&)const;
    Indices operator = (const Indices&);
    void save(List<Indices>&);
    friend std::ostream& operator << (std::ostream& os, Indices& c){
        os<<"Codigo : "<<c.getKey()<<endl;
        os<<"Direccion : "<<c.getAddress()<<endl<<endl;
        return os;
    }
};
class nodo{
public:
    int first;
    Node<nodo>* second;
    nodo():second(nullptr){}
    bool operator == (const nodo&a)const{
        return first==a.first;
    }
    
};
class IndiceSecundario{
private:
    std::string key;
    Node<nodo>* address;
public:
    IndiceSecundario(List<IndiceSecundario>&,List<nodo>&);
    IndiceSecundario();
    //Setters
    void setAddress(Node<nodo>*);
    void setKey(std::string);
    //Getters
    Node<nodo>* getAddress();
    std::string getKey();
    //Sobre carga de operadores
    bool operator > (IndiceSecundario&)const;
    bool operator < (const IndiceSecundario&)const;
    bool operator >= (const IndiceSecundario&)const;
    bool operator <= (const IndiceSecundario&)const;
    bool operator == (const IndiceSecundario&)const;
    IndiceSecundario operator = (const IndiceSecundario&);
    void save(List<IndiceSecundario>&,List<nodo>&);
    friend std::ostream& operator << (std::ostream& os, IndiceSecundario& c){
        os<<"zona : "<<c.getKey()<<endl;
        os<<" : "<<c.getAddress()<<endl;
        return os;
    }
};
#endif /* indices_hpp */
