#include <iostream>
#include <string>
using namespace std;

// Estructura del proceso
struct Proceso {
    string nombre;
    int usoCPU;      // En porcentaje
    int memoria;     // En MB
};

// Nodo de la lista enlazada
struct Nodo {
    Proceso proceso;
    Nodo* siguiente;
};

Nodo* cabeza = nullptr;
const int MEMORIA_TOTAL = 1024; // Memoria total en MB

// Funciones
void agregarProceso() {
    Proceso nuevoProceso;
    cout << "Ingrese nombre del proceso: ";
    cin >> nuevoProceso.nombre;
    cout << "Ingrese uso de memoria (MB): ";
    cin >> nuevoProceso.memoria;
    cout << "Ingrese uso de CPU (%): ";
    cin >> nuevoProceso.usoCPU;

    Nodo* nuevoNodo = new Nodo;
    nuevoNodo->proceso = nuevoProceso;
    nuevoNodo->siguiente = nullptr;

    if (cabeza == nullptr) {
        cabeza = nuevoNodo;
    } else {
        Nodo* actual = cabeza;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
    }

    cout << "Proceso agregado correctamente.\n";
}

void verProcesos() {
    if (cabeza == nullptr) {
        cout << "No hay procesos registrados.\n";
        return;
    }

    Nodo* actual = cabeza;
    cout << "\nLista de procesos:\n";
    while (actual != nullptr) {
        cout << "Nombre: " << actual->proceso.nombre << " | ";
        cout << "Memoria: " << actual->proceso.memoria << " MB | ";
        cout << "CPU: " << actual->proceso.usoCPU << "%\n";
        actual = actual->siguiente;
    }
}

void ordenarPorCPU() {
    if (!cabeza || !cabeza->siguiente) return;

    bool cambiado;
    do {
        cambiado = false;
        Nodo* actual = cabeza;
        while (actual->siguiente != nullptr) {
            if (actual->proceso.usoCPU < actual->siguiente->proceso.usoCPU) {
                swap(actual->proceso, actual->siguiente->proceso);
                cambiado = true;
            }
            actual = actual->siguiente;
        }
    } while (cambiado);

    cout << "Procesos ordenados por uso de CPU.\n";
}

void verUsoTotalCPU() {
    int totalCPU = 0;
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        totalCPU += actual->proceso.usoCPU;
        actual = actual->siguiente;
    }
    if (totalCPU > 100) totalCPU = 100;
    cout << "Uso total de CPU: " << totalCPU << "%\n";
}

void verMemoria() {
    int memoriaOcupada = 0;
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        memoriaOcupada += actual->proceso.memoria;
        actual = actual->siguiente;
    }
    int memoriaDisponible = MEMORIA_TOTAL - memoriaOcupada;
    cout << "Memoria ocupada: " << memoriaOcupada << " MB\n";
    cout << "Memoria disponible: " << memoriaDisponible << " MB\n";
}

// Menus
void gestorCPU() {
    int opcion;
    do {
        cout << "\n-- Gestor de CPU --\n";
        cout << "1. Ordenar procesos por uso de CPU\n";
        cout << "2. Ver uso total de CPU\n";
        cout << "3. Volver al menu principal\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: ordenarPorCPU(); break;
            case 2: verUsoTotalCPU(); break;
        }
    } while (opcion != 3);
}

void gestorMemoria() {
    cout << "\n-- Gestor de Memoria --\n";
    verMemoria();
}

int main() {
    int opcion;
    do {
        cout << "\n====== SISTEMA DE GESTION ======\n";
        cout << "1. Agregar procesos\n";
        cout << "2. Ver procesos\n";
        cout << "3. Gestor de CPU\n";
        cout << "4. Gestor de Memoria\n";
        cout << "5. Gestor de Almacenamiento\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: agregarProceso(); break;
            case 2: verProcesos(); break;
            case 3: gestorCPU(); break;
            case 4: gestorMemoria(); break;
            case 5: cout << "[Gestor de almacenamiento no implementado]\n"; break;
            case 6: cout << "Saliendo del sistema...\n"; break;
            default: cout << "Opcion no valida. Intente nuevamente.\n";
        }
    } while(opcion != 6);

    return 0;
}
