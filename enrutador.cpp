#include "enrutador.h"

Enrutador::Enrutador(const string& id) : Id(id) {}

const string& Enrutador::getId() const {
    return Id;
}

const vector<EnlaceVecinos>& Enrutador::getVecinos() const {
    return Vecinos;
}

const vector<RutaDestino>& Enrutador::getTabla() const {
    return Tabla;
}

void Enrutador::setEnlaceVecinos(const string& vecino, int costo) {
    for (size_t i = 0; i < Vecinos.size(); i++) {
        if (Vecinos[i].vecino == vecino) {
            Vecinos[i].costo = costo;
            return;
        }
    }
    Vecinos.push_back({vecino, costo});
}

void Enrutador::quitarEnlace(const string& vecino) {
    for (size_t i = 0; i < Vecinos.size(); i++) {
        if (Vecinos[i].vecino == vecino) {
            Vecinos.erase(Vecinos.begin() + i);
            return;
        }
    }
}

void Enrutador::setTabla(const vector<RutaDestino>& NuevaTabla) {
    Tabla = NuevaTabla;
}


//obtenemos la tabla del destino
const RutaDestino* Enrutador::buscarRuta(const string& destino) const {
    for (size_t i = 0; i < Tabla.size(); i++) {
        if (Tabla[i].Destino == destino) {
            return &Tabla[i]; //{Destino, costo, camino}
        }
    }
    return nullptr;
}