//
//  menu.hpp
//  proyect
//
//  Created by Oscar Sandoval on 2/4/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#ifndef menu_hpp
#define menu_hpp
#include "clientes.hpp"
#include "usuarios.hpp"
#include "destinos.hpp"
#include "ventas.hpp"
#include "oficinas.hpp"
using namespace std;
class Menu{
private:
    Clientes cliente;
    Console graphics;
    Usuario usuario;
    Perfiles perfil;
    Ventas venta;
    DestalleDeVenta detalleDeVenta;
    Oficinas oficina;
    void window();
public:
    Menu();
    //METODOS GRAFICOS
    void inicio();
    bool login();
    int isValidUser(string&)const;
    int isValidPassword(string&, string&)const;
    //Metodos Clientes
    void menuClientes(int&,int&);
    //Menu Usuarios
    void menuUsuarios(int&,int&);
    void menuUsers(int&,int&);
    void userAccess(Perimisos&,int&);
    //Menu Perfiles
    void menuPerfiles(int&,int&);
    //Menu Administrador
    void menuAdmin();
    //Menu Destinos
    void menuDestinos(int&,int&);
    //Menu Ventas :
    void menuVentas(int &,int &);
    //Menu Oficionas
    void menuOficinas(int&,int&);
};
#endif /* menu_hpp */
