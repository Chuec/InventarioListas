#include <iostream>
#include <fstream>
#include "Lista.h"
using namespace std;

void mostrarMenu() {
    cout << "\n=== MENU DE OPCIONES ===\n"
     << "1. Agregar producto\n"
     << "2. Eliminar producto\n"
     << "3. Modificar producto\n"
     << "4. Mostrar inventario\n"
     << "5. Mostrar productos ordenados por stock\n"
     << "6. Buscar producto por ID\n"
     << "7. Exportar a CSV\n"
     << "8. Salir\n" 
     << "Seleccione una opcion: ";
}

int main() {
    Lista inventario;  
    int opcion, id, stock;
    double precio;
    string nombre;
    


    do {
        mostrarMenu();  
        cin >> opcion;
    	system("cls");
    	
        switch (opcion) {
            case 1: {
                cout << "Ingrese el ID del producto: ";
                cin >> id;
                cout << "Ingrese el nombre del producto: ";
                cin >> nombre;
                cout << "Ingrese el stock del producto: ";
                cin >> stock;
                cout << "Ingrese el precio del producto: ";
                cin >> precio;
                inventario.agregarProducto(id, nombre, stock, precio);
                break;
            }
            case 2: {
                cout << "Ingrese el ID del producto a eliminar: ";
                cin >> id;
                inventario.eliminarProducto(id);
                break;
            }
            case 3: {
                cout << "Ingrese el ID del producto a modificar: ";
                cin >> id;
                cout << "Ingrese el nuevo stock del producto: ";
                cin >> stock;
                cout << "Ingrese el nuevo precio del producto: ";
                cin >> precio;
                inventario.modificarProducto(id, stock, precio);
                break;
            }
            case 4: {
                inventario.mostrarInventario();
                break;
            }
            case 5: {
                inventario.mostrarOrdenadoPorStock();
                break;
            }
            case 6: {
                cout << "Ingrese el ID del producto a buscar: ";
                cin >> id;
                Nodo* producto = inventario.buscarProducto(id);
                if (producto) {
                    cout << "Producto encontrado: " << producto->nombre
                         << " (ID: " << producto->id << "), Stock: " << producto->stock
                         << ", Precio: $" << producto->precio << endl;
                } else {
                    cout << "Producto no encontrado con ID: " << id << endl;
                }
                break;
            }
			case 7: {
			    string nombreArchivo;
			    cout << "Ingrese el nombre del archivo CSV (ejemplo: inventario.csv): ";
			    cin >> nombreArchivo;
			    inventario.exportarACSV(nombreArchivo);
			    break;
			}
			case 8:
			    cout << "Saliendo del programa...\n";
			    break;
            default:
                cout << "Opcion no valida. Intente de nuevo.\n";
                break;
        }

        cout << "\nPresione Enter para continuar...";
        cin.ignore(); 
        cin.get();  
        system("cls");

    } while (opcion != 8); 

    return 0;
}
