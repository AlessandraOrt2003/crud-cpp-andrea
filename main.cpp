#include <iostream>// Librería para entrada y salida estándar
#include <vector> // Librería para usar vectores dinámicos
#include <fstream> // Librería para trabajar con archivos
#include <sstream>// Librería para manipular cadenas de texto como flujos
#include <string>// Librería para usar cadenas de texto
using namespace std;// Permite usar elementos del espacio de nombres estándar sin anteponer "std::"

// Estructura para representar un producto
struct Producto {
    int id; // Identificador único del producto
    string nombre;  // Nombre del producto
    float precio;// Precio del producto
    int stock; // Cantidad disponible del producto
};

vector<Producto> productos;// Vector dinámico para almacenar la lista de productos
int siguienteId = 1;// Variable global que mantiene el siguiente ID disponible

void cargarDesdeArchivo() {
    productos.clear(); // Limpia el vector antes de cargar nuevos datos

    ifstream archivo("productos.txt"); // Abre el archivo en modo lectura
    if (!archivo.is_open()) return;    // Si el archivo no existe, se sale de la función

    Producto p;
    string linea;
    
    // Leer línea por línea del archivo
    while (getline(archivo, linea)) {
        istringstream iss(linea);   // Convierte la línea en un flujo para extraer datos
        iss >> p.id;                // Lee el ID
        iss.ignore();              // Ignora el siguiente carácter (espacio o separador)
        getline(iss, p.nombre, ';'); // Lee el nombre hasta el punto y coma
        iss >> p.precio >> p.stock; // Lee precio y stock

        productos.push_back(p);     // Agrega el producto al vector

        // Actualiza el siguiente ID si es necesario
        if (p.id >= siguienteId) {
            siguienteId = p.id + 1;
        }
    }

    archivo.close(); // Cierra el archivo
}


void guardarEnArchivo() {
    ofstream archivo("productos.txt"); // Abre el archivo en modo escritura

    // Recorre todos los productos para escribirlos en el archivo
    for (auto& p : productos) {
        archivo << p.id << " " << p.nombre << ";" << p.precio << " " << p.stock << "\n";
    }

    archivo.close(); // Cierra el archivo
}

void crearProducto() {
    Producto p;
    p.id = siguienteId++;          // Asigna un ID único al nuevo producto

    cout << "Nombre del producto: ";
    cin.ignore();                  // Limpia el buffer del teclado
    getline(cin, p.nombre);        // Permite ingresar el nombre completo con espacios

    cout << "Precio: ";
    cin >> p.precio;

    cout << "Stock: ";
    cin >> p.stock;

    productos.push_back(p);        // Agrega el nuevo producto al vector
    cout << "Producto agregado.\n";
}

void listarProductos() {
    cout << "\n--- Lista de Productos ---\n";
    //Muestra cada producto del vector
    for (auto& p : productos) {
        cout << "ID: " << p.id << " | Nombre: " << p.nombre << " | Precio: $" << p.precio << " | Stock: " << p.stock << "\n";
    }
}

void buscarPorPrecioMenorAlPromedio() {
    if (productos.empty()) {
        cout << "No hay productos registrados.\n";
        return;
    }
//Suma los precios de todos los productor
    float suma = 0;
    for (auto& p : productos) suma += p.precio;
    float promedio = suma / productos.size();

//Muestra los productor que tienen precio menor al promedio
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

//Busca el producto con el ID ingresado 
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
 // Busca y elimina el producto del vector
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
                // Muestra las opciones del menú

        cout << "\n===== MENU CRUD PRODUCTOS =====\n";
        cout << "1. Crear producto\n";
        cout << "2. Listar productos\n";
        cout << "3. Buscar por precio menor al promedio\n";
        cout << "4. Actualizar producto\n";
        cout << "5. Eliminar producto\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        // Ejecuta la opción seleccionada

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
    cargarDesdeArchivo();// Carga productos desde el archivo al iniciar
    menu();  // Llama al menú principal
    return 0;
}
