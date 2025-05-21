#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct Producto {
    int id;
    string nombre;
    float precio;
    int stock;
};

vector<Producto> productos;
int siguienteId = 1;

void cargarDesdeArchivo() {
    productos.clear();
    ifstream archivo("productos.txt");
    if (!archivo.is_open()) return;

    Producto p;
    string linea;
    while (getline(archivo, linea)) {
        istringstream iss(linea);
        iss >> p.id;
        iss.ignore(); 
        
        getline(iss, p.nombre, ';');
        iss >> p.precio >> p.stock;
        productos.push_back(p);
        if (p.id >= siguienteId) {
            siguienteId = p.id + 1;
        }
    }
    archivo.close();
}

void guardarEnArchivo() {
    ofstream archivo("productos.txt");
    for (auto& p : productos) {
        archivo << p.id << " " << p.nombre << ";" << p.precio << " " << p.stock << "\n";
    }
    archivo.close();
}

void crearProducto() {
    Producto p;
    p.id = siguienteId++;
    cout << "Nombre del producto: ";
    cin.ignore();
    getline(cin, p.nombre);
    cout << "Precio: ";
    cin >> p.precio;
    cout << "Stock: ";
    cin >> p.stock;
    productos.push_back(p);
    cout << "Producto agregado.\n";
}

void listarProductos() {
    cout << "\n--- Lista de Productos ---\n";
    for (auto& p : productos) {
        cout << "ID: " << p.id << " | Nombre: " << p.nombre << " | Precio: $" << p.precio << " | Stock: " << p.stock << "\n";
    }
}

void buscarPorPrecioMenorAlPromedio() {
    if (productos.empty()) {
        cout << "No hay productos registrados.\n";
        return;
    }

    float suma = 0;
    for (auto& p : productos) suma += p.precio;
    float promedio = suma / productos.size();

    cout << "\n--- Productos con precio menor al promedio ($" << promedio << ") ---\n";
    for (auto& p : productos) {
        if (p.precio < promedio) {
            cout << "ID: " << p.id << " | " << p.nombre << " | $" << p.precio << "\n";
        }
    }
}

void actualizarProducto() {
    int id;
    cout << "ID del producto a actualizar: ";
    cin >> id;

    for (auto& p : productos) {
        if (p.id == id) {
            cout << "Nuevo nombre: ";
            cin.ignore();
            getline(cin, p.nombre);
            cout << "Nuevo precio: ";
            cin >> p.precio;
            cout << "Nuevo stock: ";
            cin >> p.stock;
            cout << "Producto actualizado.\n";
            return;
        }
    }
    cout << "Producto no encontrado.\n";
}

void eliminarProducto() {
    int id;
    cout << "ID del producto a eliminar: ";
    cin >> id;

    for (auto it = productos.begin(); it != productos.end(); ++it) {
        if (it->id == id) {
            productos.erase(it);
            cout << "Producto eliminado.\n";
            return;
        }
    }
    cout << "Producto no encontrado.\n";
}

void menu() {
    int opcion;
    do {
        cout << "\n===== MENU CRUD PRODUCTOS =====\n";
        cout << "1. Crear producto\n";
        cout << "2. Listar productos\n";
        cout << "3. Buscar por precio menor al promedio\n";
        cout << "4. Actualizar producto\n";
        cout << "5. Eliminar producto\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1: crearProducto(); break;
            case 2: listarProductos(); break;
            case 3: buscarPorPrecioMenorAlPromedio(); break;
            case 4: actualizarProducto(); break;
            case 5: eliminarProducto(); break;
            case 6: guardarEnArchivo(); cout << "Guardado y salida del programa.\n"; break;
            default: cout << "Opción no válida.\n";
        }
    } while (opcion != 6);
}

int main() {
    cargarDesdeArchivo();
    menu();
    return 0;
}
