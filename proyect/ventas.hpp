//
//  ventas.hpp
//  proyect
//
//  Created by Oscar Sandoval on 3/23/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#ifndef ventas_h
#define ventas_h
#include "usuarios.hpp"
#include <ctime>
#include "list.hpp"
#include "oficinas.hpp"
class Venta{
public:
    Venta();
    int idUsuario;
    char folio[10];
    char fecha[30];
    int idCliente;
};

class Detalle{
public:
    char folioDeVenta[10];
    int codigoDestino;
    float costo;
    int codeOffice;
    int cantidad;
    int day;
    int month;
    int year;
};

class DestalleDeVenta{
private:
    Detalle detalle;
public:
    DestalleDeVenta();
    void setFolioVenta(std::string);
    void setCodigoDestino(std::string&);
    void setCosto(std::string&);
    void setCantida(std::string&);
    void setDestino(std::string&);
    void setDay(int);
    void setMonth(int);
    void setYear(int);
    void setCodeOffice(int);
    std::string getFolioVenta();
    int getCodigoDestino();
    float getCosto();
    int getCantidad();
    void insert();
    void remove(std::string& folio);
    void modificar(std::string&folio,std::string ne);
};


class Ventas{
private:
    Venta venta;
    int rows;
    int columns;
    void copyFile(const int);
    void insertCopyR();
    void insertCopyC();
public:
    Ventas();
    void setIdUsuario(int&);
    void setFolio(std::string&);
    void setFecha(DestalleDeVenta&);
    void setIdCliente(std::string&);
    int getIdUsuario();
    long getAddress(std::string);
    int getRows();
    int getColumns();
    std::string getFolio();
    std::string getFecha();
    int getIdCliente();
    void modify(std::string&,Console& graphics);
    int dispersion(std::string);
    void insert(Console&);
    void print(Console&);
    bool isValidFolio(std::string&);
    void search(std::string&,Console&);
    void printTicket(List<Detalle>& list,Console&);
    void remove(string&,Console&);
    void removeModify(string&,Console&);
    void expandirFilas();
    void expandirColumnas();
    void setFecha(fecha&);
    void modifyDate(fecha&,std::string);
    void modifyDetalle(std::string,std::string);
};

#endif /* ventas_h */
