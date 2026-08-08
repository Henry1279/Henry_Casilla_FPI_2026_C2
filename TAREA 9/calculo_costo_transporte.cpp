#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    // Declaración de variables
    double distancia;
    double tarifaBase;
    double costoPorKm;
    double recargo;
    double costoDistancia;
    double total;

    cout << "========================================" << endl;
    cout << "   CALCULADORA DE COSTO DE TRANSPORTE" << endl;
    cout << "========================================" << endl;

    // Solicitar la distancia
    do {
        cout << "\nIngrese la distancia en kilometros: ";
        cin >> distancia;

        if (distancia <= 0) {
            cout << "Error: la distancia debe ser mayor que 0." << endl;
        }

    } while (distancia <= 0);

    // Solicitar la tarifa base
    do {
        cout << "Ingrese la tarifa base: RD$ ";
        cin >> tarifaBase;

        if (tarifaBase < 0) {
            cout << "Error: la tarifa base no puede ser negativa." << endl;
        }

    } while (tarifaBase < 0);

    // Solicitar el costo por kilometro
    do {
        cout << "Ingrese el costo por kilometro: RD$ ";
        cin >> costoPorKm;

        if (costoPorKm < 0) {
            cout << "Error: el costo por kilometro no puede ser negativo." << endl;
        }

    } while (costoPorKm < 0);

    // Solicitar recargo adicional
    do {
        cout << "Ingrese el recargo adicional: RD$ ";
        cin >> recargo;

        if (recargo < 0) {
            cout << "Error: el recargo no puede ser negativo." << endl;
        }

    } while (recargo < 0);

    // Calcular el costo correspondiente a la distancia
    costoDistancia = distancia * costoPorKm;

    // Calcular el costo total
    total = tarifaBase + costoDistancia + recargo;

    // Mostrar los resultados
    cout << fixed << setprecision(2);

    cout << "\n========================================" << endl;
    cout << "        DESGLOSE DEL COSTO" << endl;
    cout << "========================================" << endl;
    cout << "Tarifa base: RD$ " << tarifaBase << endl;
    cout << "Costo por distancia (" << distancia << " km): RD$ " << costoDistancia << endl;
    cout << "Recargo adicional: RD$ " << recargo << endl;
    cout << "----------------------------------------" << endl;
    cout << "TOTAL A COBRAR: RD$ " << total << endl;
    cout << "========================================" << endl;

    return 0;
}
