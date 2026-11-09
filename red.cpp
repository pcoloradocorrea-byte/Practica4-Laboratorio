#include <iostream>
#include "red.h"
#include <array>
#include <cstdlib>


int Red::buscarIndice(string id) const {
    for (size_t i = 0; i < enrutadores.size(); i++) {
        if (enrutadores[i].getId() == id) {
            return i;
        }
    }
    return -1;
}


bool Red::existe(string id) const {
    return buscarIndice(id) != -1;
}

//agregamos la id
bool Red::agregarEnrutador(string id) {
    if (existe(id)) {
        return false;
    }
    Enrutador nuevo(id);
    enrutadores.push_back(nuevo);
    calcularTodasLasTablas();
    return true;
}


bool Red::quitarEnrutador(string id) {
    int pos = buscarIndice(id);
    if (pos == -1) {
        return false;
    }
    enrutadores.erase(enrutadores.begin() + pos);
    for (size_t i = 0; i < enrutadores.size(); i++) {
        enrutadores[i].quitarEnlace(id);
    }
    calcularTodasLasTablas();
    return true;
}



int Red::cantidad() const {
    return enrutadores.size();
}


//agrega una relacion de vecindad entre a y b con su respectivo costo
bool Red::agregarEnlace(string a, string b, int costo) {
    int posA = buscarIndice(a);
    int posB = buscarIndice(b);
    if (posA == -1 || posB == -1) {
        return false;
    }
    enrutadores[posA].setEnlaceVecinos(b, costo);
    enrutadores[posB].setEnlaceVecinos(a, costo);
    calcularTodasLasTablas();
    return true;
}



bool Red::quitarEnlace(string a, string b) {
    int posA = buscarIndice(a);
    int posB = buscarIndice(b);
    if (posA == -1 || posB == -1) {
        return false;
    }
    enrutadores[posA].quitarEnlace(b);
    enrutadores[posB].quitarEnlace(a);
    calcularTodasLasTablas();
    return true;
}


//imprimimos a todos con sus respectivos vecinos y costos
void Red::imprimirRed() const {
    for (size_t i = 0; i < enrutadores.size(); i++) {
        cout << enrutadores[i].getId() << ":";
        vector<EnlaceVecinos> vecinos = enrutadores[i].getVecinos();
        for (size_t j = 0; j < vecinos.size(); j++) {
            cout << " " << vecinos[j].vecino << "(" << vecinos[j].costo << ")";
        }
        cout << endl;
    }
}



//mas importante (Dijkstra) arma la tabla de origen con respecto a todos los demas
void Red::calcularTabla(string origen) {
    int posOrigen = buscarIndice(origen);//obtenemos el indice y vemos si origen existe
    if (posOrigen == -1) {
        return;
    }

    int n = enrutadores.size(); //cantidad de nodos A,B,C,D = 4
    const int INF = 1000000000; //

    vector<int> dist(n, INF);
    vector<int> previo(n, -1);
    vector<bool> visitado(n, false);

    dist[posOrigen] = 0;

    for (int paso = 0; paso < n; paso++) {
        int u = -1;
        for (int i = 0; i < n; i++) {
            if (!visitado[i] && dist[i] != INF) {
                if (u == -1 || dist[i] < dist[u]) {
                    u = i;
                }
            }
        }
        if (u == -1) {
            break;
        }
        visitado[u] = true;

        vector<EnlaceVecinos> vecinos = enrutadores[u].getVecinos();
        for (size_t j = 0; j < vecinos.size(); j++) {
            int v = buscarIndice(vecinos[j].vecino);
            if (v != -1 && dist[u] + vecinos[j].costo < dist[v]) {
                dist[v] = dist[u] + vecinos[j].costo;
                previo[v] = u;
            }
        }
    }

    vector<RutaDestino> nuevaTabla;
    for (int d = 0; d < n; d++) {
        if (d == posOrigen || dist[d] == INF) {
            continue;
        }
        RutaDestino r;
        r.Destino = enrutadores[d].getId();
        r.costo = dist[d];

        int actual = d;
        while (actual != -1) {
            r.camino.push_front(enrutadores[actual].getId());
            actual = previo[actual];
        }
        nuevaTabla.push_back(r);
    }

    enrutadores[posOrigen].setTabla(nuevaTabla);
}



void Red::imprimirTabla(string origen) const {
    int pos = buscarIndice(origen);
    if (pos == -1) {
        cout << "No existe el enrutador " << origen << endl;
        return;
    }
    vector<RutaDestino> tabla = enrutadores[pos].getTabla();
    cout << "Tabla de " << origen << ":" << endl;
    for (size_t i = 0; i < tabla.size(); i++) {
        cout << "  " << tabla[i].Destino << " costo " << tabla[i].costo << " camino: ";
        list<string>::const_iterator it;
        for (it = tabla[i].camino.begin(); it != tabla[i].camino.end(); it++) {
            cout << *it << " ";
        }
        cout << endl;
    }
}


//calcula la tabla de todos con todos
void Red::calcularTodasLasTablas() {
    for (size_t i = 0; i < enrutadores.size(); i++) {
        calcularTabla(enrutadores[i].getId());
    }
}


//mostramos el mejor camino desde origen y destino con su costo
int Red::costoEnvio(string origen, string destino) const {
    int pos = buscarIndice(origen);
    if (pos == -1 || buscarIndice(destino) == -1) { //verificacion
        return -1;
    }
    if (origen == destino) { //verificacion
        return 0;
    }
    const RutaDestino* r = enrutadores[pos].buscarRuta(destino); //obtenemos  la fila de destino
    if (r == nullptr) {
        return -1;
    }
    return r->costo; //obtenemos el costo para luego mostrarlo
}



void Red::imprimirCamino(string origen, string destino) const {
    int pos = buscarIndice(origen);
    if (pos == -1 || buscarIndice(destino) == -1) { //verificacion
        cout << "El origen o el destino no existen" << endl;
        return;
    }
    if (origen == destino) { //verificacion
        cout << "El origen y el destino son el mismo enrutador" << endl;
        return;
    }

    const RutaDestino* r = enrutadores[pos].buscarRuta(destino); //en el enrutador[pos] buscamos la fila de destino
    if (r == nullptr) {
        cout << "No hay camino de " << origen << " a " << destino << endl;
        return;
    }
    cout << "Camino de " << origen << " a " << destino << ": ";
    list<string>::const_iterator it;
    for (it = r->camino.begin(); it != r->camino.end(); it++) {
        cout << *it << " ";
    }
    cout << "(costo " << r->costo << ")" << endl;
}


//Lectura de archivo {Origen, Destino, Costo} Enlaces
bool Red::cargarDesdeArchivo(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        return false;
    }

    string a, b;
    int costo;
    while (archivo >> a >> b >> costo) {
        agregarEnrutador(a);   // si ya existe, no hace nada
        agregarEnrutador(b);
        agregarEnlace(a, b, costo);
    }

    archivo.close();
    return true;
}

//guardar el archivo
bool Red::guardarEnArchivo(string nombreArchivo) const {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        return false;
    }

    for (size_t i = 0; i < enrutadores.size(); i++) {
        string id = enrutadores[i].getId();
        vector<EnlaceVecinos> vecinos = enrutadores[i].getVecinos();
        for (size_t j = 0; j < vecinos.size(); j++) {
            if (id < vecinos[j].vecino) {
                archivo << id << " " << vecinos[j].vecino << " " << vecinos[j].costo << endl;
            }
        }
    }

    archivo.close();
    return true;
}



bool Red::generarArchivoAleatorio(string nombreArchivo, int cantidad, int costoMax) const {
    if (cantidad < 2 || cantidad > 26 || costoMax < 1) {
        return false;
    }

    array<string, 26> nombres = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
                                 "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        return false;
    }

    for (int i = 1; i < cantidad; i++) {
        int anterior = rand() % i;
        int costo = rand() % costoMax + 1;
        archivo << nombres[anterior] << " " << nombres[i] << " " << costo << endl;
    }

    archivo.close();
    return true;
}