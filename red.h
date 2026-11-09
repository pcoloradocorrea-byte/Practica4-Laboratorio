#ifndef RED_H
#define RED_H

#include <string>
#include <vector>
#include "enrutador.h"
#include <fstream>

using namespace std;

class Red {
private:
    vector<Enrutador> enrutadores;
    int buscarIndice(string id) const;

public:
    bool existe(string id) const;
    bool agregarEnrutador(string id);
    bool quitarEnrutador(string id);
    int cantidad() const;


    bool agregarEnlace(string a, string b, int costo);
    bool quitarEnlace(string a, string b);
    void imprimirRed() const;
    void calcularTabla(string origen);
    void imprimirTabla(string origen) const;
    void calcularTodasLasTablas();
    int costoEnvio(string origen, string destino) const;
    void imprimirCamino(string origen, string destino) const;
    bool cargarDesdeArchivo(string nombreArchivo);
    bool guardarEnArchivo(string nombreArchivo) const;
    bool generarArchivoAleatorio(string nombreArchivo, int cantidad, int costoMax) const;
};

#endif // RED_H