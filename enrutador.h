#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <string>
#include <vector>
#include <list>

using namespace std;

struct EnlaceVecinos {
    string vecino;
    int costo;
};

struct RutaDestino {
    string Destino;
    int costo;
    list<string> camino;
};

class Enrutador {
private:
    string Id;
    vector<EnlaceVecinos> Vecinos;
    vector<RutaDestino> Tabla;

public:
    Enrutador(const string& id = "");


    const string& getId() const;
    const vector<EnlaceVecinos>& getVecinos() const;
    const vector<RutaDestino>& getTabla() const;


    void setEnlaceVecinos(const string& vecino, int costo);
    void quitarEnlace(const string& vecino);
    void setTabla(const vector<RutaDestino>& NuevaTabla);

    const RutaDestino* buscarRuta(const string& destino) const;
};

#endif // ENRUTADOR_H