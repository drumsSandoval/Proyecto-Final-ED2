//
//  clientes.hpp
//  proyect
//
//  Created by Oscar Sandoval on 2/4/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#ifndef clientes_hpp
#define clientes_hpp
#include <string>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include "usuarios.hpp"
#include "huffman.hpp"

class Clientes{
private:
    std::string activate;
    std::string name;
    std::string code;
    std::string phone;
    std::string address;
    
    void translateBinary(std::string&, List<data>&);
    //Factor binario
    int getBinaryFactor(std::string&);
    //
    void translateAsci(std::string&);
    
    std::string toBinary(int);
    
    void saveDescomprension(std::string&);
public:
    //Constructor
    Clientes();
    //Destroyer
    ~Clientes();
    //Setters
    void setName(const std::string&);
    void setCode(const std::string&);
    void setPhone(const std::string&);
    void setAddress(const std::string&);
    void setActivate(const std::string);
    //Getters
    std::string getName();
    std::string getName(std::string);
    std::string getCode();
    std::string getPhone();
    std::string getAddress();
    std::string getActivate();
    //Agregar
    void insert();
    //Inprimir
    void toString(Console&);//Console&);
    //Buscar
    void search(const std::string&,Console&);//Console&);
    //Modificar
    void modify(const std::string&,Console&);//,Console&);
    //Eliminar
    std::string remove(std::string&);
    //Eliminar logico :
    std::string logicRemove(const std::string&);
    //Activar Logico
    std::string active(const std::string&);
    //Cliente valido
    bool isValidCliente(std::string&);

    bool isEmpty();
    int setCliente(Console&);
    
    bool isValidRemoveCliente(const std::string&);
    
    bool isValidInsert();
    
    void comprimirArchivo(Huffman<data>&,List<data>&,List<int>&);
    void descomprimirArchivo();
    
    void aux(const std::string&);

};

#endif /* clientes_hpp */
