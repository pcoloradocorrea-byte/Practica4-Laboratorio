#include <iostream>
#include <cstdlib>
#include <ctime>
#include "red.h"

using namespace std;

// Muestra las opciones del menu
void mostrarMenu() {
    cout << "\n===== SIMULADOR DE RED DE ENRUTADORES =====" << endl;
    cout << "1. Agregar enrutador" << endl;
    cout << "2. Quitar enrutador" << endl;
    cout << "3. Agregar o actualizar enlace" << endl;
    cout << "4. Quitar enlace" << endl;
    cout << "5. Ver la red" << endl;
    cout << "6. Ver tabla de enrutamiento de un enrutador" << endl;
    cout << "7. Costo de envio entre dos enrutadores" << endl;
    cout << "8. Camino entre dos enrutadores" << endl;
    cout << "9. Cargar red desde archivo" << endl;
    cout << "10. Guardar red en archivo" << endl;
    cout << "11. Generar red aleatoria" << endl;
    cout << "0. Salir" << endl;
    cout << "Opcion: ";
}

int main() {
    srand(time(0));
    Red red;
    int opcion = -1;

    while (opcion != 0) {
        mostrarMenu();
        cin >> opcion;

        string a, b, archivo;
        int costo, cantidad, extra;

        if (opcion == 1) {
            cout << "Id del enrutador: ";
            cin >> a;
            if (red.agregarEnrutador(a) == true) {
                cout << "Enrutador agregado" << endl;
            }
            else {
                cout << "Ese enrutador ya existe" << endl;
            }
        }
        else if (opcion == 2) {
            cout << "Id del enrutador: ";
            cin >> a;
            if (red.quitarEnrutador(a) == true) {
                cout << "Enrutador quitado" << endl;
            }
            else {
                cout << "Ese enrutador no existe" << endl;
            }
        }
        else if (opcion == 3) {
            cout << "Enrutador 1: ";
            cin >> a;
            cout << "Enrutador 2: ";
            cin >> b;
            cout << "Costo: ";
            cin >> costo;
            if (red.agregarEnlace(a, b, costo) == true) {
                cout << "Enlace listo" << endl;
            }
            else {
                cout << "Alguno de los enrutadores no existe" << endl;
            }
        }
        else if (opcion == 4) {
            cout << "Enrutador 1: ";
            cin >> a;
            cout << "Enrutador 2: ";
            cin >> b;
            if (red.quitarEnlace(a, b) == true) {
                cout << "Enlace quitado" << endl;
            }
            else {
                cout << "Alguno de los enrutadores no existe" << endl;
            }
        }
        else if (opcion == 5) {
            red.imprimirRed();
        }
        else if (opcion == 6) {
            cout << "Enrutador: ";
            cin >> a;
            red.imprimirTabla(a);
        }
        else if (opcion == 7) {
            cout << "Origen: ";
            cin >> a;
            cout << "Destino: ";
            cin >> b;
            costo = red.costoEnvio(a, b);
            if (costo == -1) {
                cout << "No hay camino o alguno no existe" << endl;
            }
            else {
                cout << "Costo de envio: " << costo << endl;
            }
        }
        else if (opcion == 8) {
            cout << "Origen: ";
            cin >> a;
            cout << "Destino: ";
            cin >> b;
            red.imprimirCamino(a, b);
        }
        else if (opcion == 9) {
            cout << "Nombre del archivo: ";
            cin >> archivo;
            if (red.cargarDesdeArchivo(archivo) == true) {
                cout << "Red cargada" << endl;
            } else {
                cout << "No se pudo abrir el archivo" << endl;
            }
        }
        else if (opcion == 10) {
            cout << "Nombre del archivo: ";
            cin >> archivo;
            if (red.guardarEnArchivo(archivo) == true) {
                cout << "Red guardada" << endl;
            }
            else {
                cout << "No se pudo crear el archivo" << endl;
            }
        }

        else if (opcion == 11) {
            cout << "Cantidad de enrutadores (2 a 26): ";
            cin >> cantidad;
            cout << "Costo maximo: ";
            cin >> costo;
            if (red.generarArchivoAleatorio("aleatoria.txt", cantidad, costo) == true) {
                red = Red();
                red.cargarDesdeArchivo("aleatoria.txt");
                cout << "Red aleatoria generada y cargada" << endl;
            }

            else {
                cout << "Datos invalidos" << endl;
            }
        }

        else if (opcion != 0) {
            cout << "Opcion no valida" << endl;
        }
    }

    cout << "Hasta luego" << endl;
    return 0;
}