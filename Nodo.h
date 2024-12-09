#ifndef NODO_H
#define NODO_H

#include <string>
using namespace std;

class Nodo {
public:
    int id;                   
    string nombre;            
    int stock;                
    double precio;            
    Nodo* siguientePtr;       

    
    Nodo(int id, const string& nombre, int stock, double precio)
        : id(id), nombre(nombre), stock(stock), precio(precio), siguientePtr(nullptr) {}
};

#endif 
