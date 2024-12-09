#ifndef LISTA_H
#define LISTA_H

#include "Nodo.h"
#include <iostream>
#include <fstream>
using namespace std;

class Lista {
private:
    Nodo* primeroPtr; 

    // Metodo auxiliar para verificar si la lista está vacía
    bool estaVacia() const {
        return primeroPtr == nullptr;
    }

public:
    Lista() : primeroPtr(nullptr) {}  

    ~Lista() {  
        while (!estaVacia()) {
            Nodo* temp = primeroPtr;
            primeroPtr = primeroPtr->siguientePtr;
            delete temp;
        }
    }
    
    // Metodo para verificar si un ID ya existe
	bool idExiste(int id) const {
	    Nodo* actualPtr = primeroPtr;
	    while (actualPtr != nullptr) {
	        if (actualPtr->id == id) {
	            return true; // ID ya existe
	        }
	        actualPtr = actualPtr->siguientePtr;
	    }
	    return false; // ID no existe
	}

    // Agregar un producto al inicio de la lista
    void agregarProducto(int id, const string& nombre, int stock, double precio) {
	    if (idExiste(id)) {
	        cout << "Error: El ID " << id << " ya existe. No se puede agregar el producto.\n";
	        return;
    }
	    Nodo* nuevoPtr = new Nodo(id, nombre, stock, precio);
	    nuevoPtr->siguientePtr = primeroPtr;
	    primeroPtr = nuevoPtr;
	    cout << "Producto agregado: " << nombre << " (ID: " << id << ")\n";
	}

    // Eliminar un producto por su ID
    void eliminarProducto(int id) {
        if (estaVacia()) {
            cout << "La lista está vacía. No se puede eliminar el producto.\n";
            return;
        }

        Nodo* actualPtr = primeroPtr;
        Nodo* previoPtr = nullptr;


        while (actualPtr != nullptr && actualPtr->id != id) {        // Buscar el producto por ID
            previoPtr = actualPtr;
            actualPtr = actualPtr->siguientePtr;
        }

        if (actualPtr != nullptr) {
            if (previoPtr == nullptr) {
                primeroPtr = actualPtr->siguientePtr;                // Si el producto está al principio de la lista
            } else {
                previoPtr->siguientePtr = actualPtr->siguientePtr;                // Eliminar el nodo intermedio
            }
            cout << "Producto eliminado: " << actualPtr->nombre << " (ID: " << id << ")\n";
            delete actualPtr;
        } else {
            cout << "Producto con ID " << id << " no encontrado.\n";
        }
    }

    // Modificar la cantidad de stock y el precio de un producto
    void modificarProducto(int id, int nuevoStock, double nuevoPrecio) {
	    Nodo* producto = buscarProducto(id);
	    if (producto == nullptr) {
	        cout << "Error: No se encontro un producto con ID " << id << ".\n";
	        return;
    }

	    
	    producto->stock = nuevoStock;       // Modificar el producto
	    producto->precio = nuevoPrecio;
	    cout << "Producto modificado: " << producto->nombre << " (ID: " << id << ")\n";
	}

    // Buscar un producto por su ID
    Nodo* buscarProducto(int id) const {
        Nodo* actualPtr = primeroPtr;
        while (actualPtr != nullptr) {
            if (actualPtr->id == id) {
                return actualPtr;
            }
            actualPtr = actualPtr->siguientePtr;
        }
        return nullptr; // Si no se encuentra el producto
    }

    // Mostrar productos ordenados por stock
    void mostrarOrdenadoPorStock() const {
        if (estaVacia()) {
            cout << "La lista está vacía.\n";
            return;
        }

        Nodo* actualPtr = primeroPtr;        // Crear un arreglo temporal para ordenar los productos
        while (actualPtr != nullptr) {
            Nodo* minPtr = actualPtr;
            Nodo* siguientePtr = actualPtr->siguientePtr;


            while (siguientePtr != nullptr) {            // Búsqueda del nodo con el stock más bajo
                if (siguientePtr->stock < minPtr->stock) {
                    minPtr = siguientePtr;
                }
                siguientePtr = siguientePtr->siguientePtr;
            }

            swap(actualPtr->id, minPtr->id);            // Intercambiar los datos
            swap(actualPtr->nombre, minPtr->nombre);
            swap(actualPtr->stock, minPtr->stock);
            swap(actualPtr->precio, minPtr->precio);

            actualPtr = actualPtr->siguientePtr;
        }


        cout << "Productos ordenados por cantidad en stock:\n";        // Mostrar lista ordenada
        mostrarInventario();
    }

    // Mostrar todos los productos
    void mostrarInventario() const {
        if (estaVacia()) {
            cout << "La lista está vacía.\n";
            return;
        }

        Nodo* actualPtr = primeroPtr;
        cout << "Inventario:\n";
        while (actualPtr != nullptr) {
            cout << "ID: " << actualPtr->id << ", Nombre: " << actualPtr->nombre
                 << ", Stock: " << actualPtr->stock << ", Precio: $" << actualPtr->precio << "\n";
            actualPtr = actualPtr->siguientePtr;
        }
    }
    
    // Método para exportar los datos a un archivo CSV
	void exportarACSV(const string& nombreArchivo) const {
    	ofstream archivo(nombreArchivo);
    	if (!archivo) {
        	cout << "Error al abrir el archivo para escribir.\n";
        	return;
    	}

   	 
    	archivo << "ID,Nombre,Stock,Precio\n";   // Escribe el encabezado del CSV

   	 
    Nodo* actualPtr = primeroPtr;  // Recorrer la lista y escribir los datos de cada nodo
    while (actualPtr != nullptr) {
        archivo << actualPtr->id << ","
                << actualPtr->nombre << ","
                << actualPtr->stock << ","
                << actualPtr->precio << "\n";
        actualPtr = actualPtr->siguientePtr;
    }

    archivo.close();
    cout << "Datos exportados a " << nombreArchivo << " exitosamente.\n";
}
};

#endif
