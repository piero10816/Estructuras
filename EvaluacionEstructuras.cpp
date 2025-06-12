#include <iostream>
#include <string>
using namespace std;

struct Proceso {
    int id;
    string nombre;
    int prioridad;
    int usoCPU;
    Proceso* sig;
};

struct NodoMemoria {
    int idProceso;
    int memoriaAsignada;
    NodoMemoria* siguiente;
};

// Lista enlazada de procesos
Proceso* cabeza = NULL;

// Cola manual para planificacion
struct NodoCola {
    Proceso* proceso;
    NodoCola* sig;
};

NodoCola* frente = NULL;
NodoCola* fin = NULL;

// Pila manual para gestion de memoria
NodoMemoria* cima = NULL;

// ---------------- Menus ----------------

void mostrarMenuPrincipal() {
    cout << "\n===== SISTEMA DE GESTION DE PROCESOS =====" << endl;
    cout << "1. Gestion de Procesos" << endl;
    cout << "2. Planificacion de CPU" << endl;
    cout << "3. Gestion de Memoria" << endl;
    cout << "4. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

void mostrarMenuProcesos() {
    cout << "\n----- GESTION DE PROCESOS -----" << endl;
    cout << "1. Agregar nuevo proceso" << endl;
    cout << "2. Eliminar proceso" << endl;
    cout << "3. Buscar proceso por ID" << endl;
    cout << "4. Buscar proceso por nombre" << endl;
    cout << "5. Modificar prioridad" << endl;
    cout << "6. Mostrar todos los procesos" << endl;
    cout << "7. Volver al menu principal" << endl;
    cout << "Seleccione una opcion: ";
}

void mostrarMenuPlanificador() {
    cout << "\n----- PLANIFICADOR DE CPU -----" << endl;
    cout << "1. Encolar proceso" << endl;
    cout << "2. Ejecutar proceso (desencolar)" << endl;
    cout << "3. Mostrar cola de planificacion" << endl;
    cout << "4. Volver al menu principal" << endl;
    cout << "Seleccione una opcion: ";
}

void mostrarMenuMemoria() {
    cout << "\n----- GESTION DE MEMORIA -----" << endl;
    cout << "1. Asignar memoria a proceso" << endl;
    cout << "2. Liberar memoria" << endl;
    cout << "3. Mostrar estado de memoria" << endl;
    cout << "4. Volver al menu principal" << endl;
    cout << "Seleccione una opcion: ";
}

// ---------------- Funciones procesos ----------------

void agregarProceso() {
    Proceso* nuevo = new Proceso;
    cout << "ID: "; cin >> nuevo->id;
    cout << "Nombre: "; cin >> nuevo->nombre;
    cout << "Prioridad: "; cin >> nuevo->prioridad;
    cout << "Uso de CPU (%): "; cin >> nuevo->usoCPU;
    nuevo->sig = cabeza;
    cabeza = nuevo;
    cout << "Proceso agregado." << endl;
}

void mostrarProcesos() {
    Proceso* aux = cabeza;
    while (aux) {
        cout << "ID: " << aux->id << " Nombre: " << aux->nombre
             << " Prioridad: " << aux->prioridad << " CPU: " << aux->usoCPU << "%" << endl;
        aux = aux->sig;
    }
}

// ---------------- Cola planificacion ----------------

void encolar(Proceso* p) {
    NodoCola* nuevo = new NodoCola;
    nuevo->proceso = p;
    nuevo->sig = NULL;
    if (!frente) frente = fin = nuevo;
    else {
        fin->sig = nuevo;
        fin = nuevo;
    }
    cout << "Proceso encolado." << endl;
}

void desencolar() {
    if (!frente) {
        cout << "Cola vacia." << endl;
        return;
    }
    NodoCola* temp = frente;
    cout << "Ejecutando proceso ID: " << temp->proceso->id << endl;
    frente = frente->sig;
    delete temp;
    if (!frente) fin = NULL;
}

void mostrarCola() {
    NodoCola* aux = frente;
    while (aux) {
        cout << "ID: " << aux->proceso->id << " Nombre: " << aux->proceso->nombre << endl;
        aux = aux->sig;
    }
}

// ---------------- Pila memoria ----------------

void asignarMemoria() {
    NodoMemoria* nuevo = new NodoMemoria;
    cout << "ID del proceso: "; cin >> nuevo->idProceso;
    cout << "Memoria a asignar (MB): "; cin >> nuevo->memoriaAsignada;
    nuevo->siguiente = cima;
    cima = nuevo;
    cout << "Memoria asignada." << endl;
}

void liberarMemoria() {
    if (!cima) {
        cout << "Pila de memoria vacia." << endl;
        return;
    }
    NodoMemoria* temp = cima;
    cima = cima->siguiente;
    cout << "Memoria liberada del proceso ID: " << temp->idProceso << endl;
    delete temp;
}

void mostrarMemoria() {
    NodoMemoria* aux = cima;
    while (aux) {
        cout << "ID Proceso: " << aux->idProceso << " Memoria: " << aux->memoriaAsignada << "MB" << endl;
        aux = aux->siguiente;
    }
}

// ---------------- Main ----------------

int main() {
    int op1, op2;
    do {
        mostrarMenuPrincipal();
        cin >> op1;
        switch (op1) {
            case 1:
                do {
                    mostrarMenuProcesos();
                    cin >> op2;
                    switch (op2) {
                        case 1: agregarProceso(); break;
                        case 6: mostrarProcesos(); break;
                    }
                } while (op2 != 7);
                break;
            case 2:
                do {
                    mostrarMenuPlanificador();
                    cin >> op2;
                    switch (op2) {
                        case 1:
                            int id;
                            cout << "ID del proceso a encolar: ";
                            cin >> id;
                            {
                                Proceso* aux = cabeza;
                                while (aux && aux->id != id) aux = aux->sig;
                                if (aux) encolar(aux);
                                else cout << "No encontrado.\n";
                            }
                            break;
                        case 2: desencolar(); break;
                        case 3: mostrarCola(); break;
                    }
                } while (op2 != 4);
                break;
            case 3:
                do {
                    mostrarMenuMemoria();
                    cin >> op2;
                    switch (op2) {
                        case 1: asignarMemoria(); break;
                        case 2: liberarMemoria(); break;
                        case 3: mostrarMemoria(); break;
                    }
                } while (op2 != 4);
                break;
        }
    } while (op1 != 4);
    
    return 0;
}
