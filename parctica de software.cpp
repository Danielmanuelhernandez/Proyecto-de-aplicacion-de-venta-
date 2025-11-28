#include <iostream>
#include <cstdlib>
#include <limits> 
#include <iomanip> 
using namespace std;
// --- CONSTANTES ---
const double PRECIO_BOLILLO = 2.50;
const double PRECIO_DULCE = 11.00;
const double PRECIO_ESPANOL = 4.50;
enum {
    CODIGO_BOLILLO = 1,
    CODIGO_DULCE = 2,
    CODIGO_ESPANOL = 3,
    CODIGO_TERMINAR_VENTA = 0
};
// Función de utilidad para limpiar la pantalla
void limpiar_pantalla() {
    system("cls");
}
// Función para procesar la venta de un cliente 
double procesar_venta(int &cant_bolillo, int &cant_dulce, int &cant_espanol) {
    double total_compra = 0.0;
    int opcion_producto = 0;
    limpiar_pantalla();
    cout << "\n=============================" << endl;
    cout << "      LISTA DE PRECIOS" << endl;
    cout << "=============================" << endl;
    cout << "1. Bolillo ($" << fixed << setprecision(2) << PRECIO_BOLILLO << ")" << endl;
    cout << "2. Dulce y Reposteria ($" << fixed << setprecision(2) << PRECIO_DULCE << ")" << endl;
    cout << "3. Espanol ($" << fixed << setprecision(2) << PRECIO_ESPANOL << ")" << endl;
    cout << "0. TERMINAR CUENTA" << endl;
    cout << "=============================" << endl;
    cout << "Ingresa los codigos de los productos uno por uno:" << endl;
    do {
        cout << ">> ";
        // MANEJO DE ERRORES DE ENTRADA 
        if (!(cin >> opcion_producto)) { 
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "   [!] Error: Ingresa solo numeros." << endl;
            opcion_producto = -1; 
            continue;
        }
        switch(opcion_producto) {
            case CODIGO_BOLILLO:
                total_compra += PRECIO_BOLILLO;
                cant_bolillo++;
                cout << "   [+] Bolillo agregado." << endl;
                break;
            case CODIGO_DULCE:
                total_compra += PRECIO_DULCE;
                cant_dulce++;
                cout << "   [+] Reposteria agregada." << endl;
                break;
            case CODIGO_ESPANOL:
                total_compra += PRECIO_ESPANOL;
                cant_espanol++;
                cout << "   [+] Espanol agregado." << endl;
                break;
            case CODIGO_TERMINAR_VENTA:
                break;
            default:
                cout << "   [!] Codigo incorrecto." << endl;
        }
    } while (opcion_producto != CODIGO_TERMINAR_VENTA);
    return total_compra;
}
void mostrar_resumen(int cant_bolillo, int cant_dulce, int cant_espanol, double total) {
    limpiar_pantalla();
    cout << "\n***********************************" << endl;
    cout << "        RESUMEN DE LA COMPRA" << endl;
    cout << "***********************************" << endl;
    if (cant_bolillo > 0) cout << "- " << cant_bolillo << " pieza(s) de Bolillo" << endl;
    if (cant_dulce > 0)   cout << "- " << cant_dulce   << " pieza(s) de Reposteria" << endl;
    if (cant_espanol > 0) cout << "- " << cant_espanol << " pieza(s) de Pan Espanol" << endl;
    cout << "-----------------------------------" << endl;
    cout << " GRAN TOTAL A PAGAR: $" << fixed << setprecision(2) << total << endl;
    cout << "***********************************" << endl;
}
// Función para mostrar el historial de ventas
char mostrar_historial(int total_bolillo_vendido, int total_dulce_vendido, int total_espanol_vendido, double total_dinero_acumulado) {
    char opcion_historial;
    bool viendoHistorial = true;
    while(viendoHistorial) {
        limpiar_pantalla();
        cout << "\n###################################" << endl;
        cout << "       HISTORIAL DE VENTAS" << endl;
        cout << "###################################" << endl;
        cout << "Total Bolillos:   " << total_bolillo_vendido << endl;
        cout << "Total Reposteria: " << total_dulce_vendido << endl;
        cout << "Total Espanol:    " << total_espanol_vendido << endl;
        cout << "-----------------------------------" << endl;
        cout << " DINERO ACUMULADO: $" << fixed << setprecision(2) << total_dinero_acumulado << endl;
        cout << "###################################" << endl;
        cout << "\nOpciones del Historial:" << endl;
        cout << "[4] Regresar a cobrar (Nuevo Cliente)." << endl;
        cout << "[Otro] Salir del programa." << endl;
        cout << ">> ";
        cin >> opcion_historial;
        if (opcion_historial == '4') {
            return '4';
        } else {
            char confirmacion;
            limpiar_pantalla();
            cout << "\n[?] Estas seguro que deseas cerrar el programa? (S/N): ";
            cin >> confirmacion;
            if (confirmacion == 's' || confirmacion == 'S') {
                return '0';
            }
        }
    }
    return '0'; 
}
int main()
{
    int total_bolillo_vendido = 0;
    int total_dulce_vendido = 0;
    int total_espanol_vendido = 0;
    double total_dinero_acumulado = 0.0;
    char repetirPrograma;
    do {
        // Variables de VENTA
        double total_cliente = 0.0;
        int cantidad_bolillo = 0;
        int cantidad_dulce = 0;
        int cantidad_espanol = 0;
        // 1. PROCESAR VENTA 
        total_cliente = procesar_venta(cantidad_bolillo, cantidad_dulce, cantidad_espanol);
        // 2. ACTUALIZAR HISTORIAL
        total_bolillo_vendido += cantidad_bolillo;
        total_dulce_vendido += cantidad_dulce;
        total_espanol_vendido += cantidad_espanol;
        total_dinero_acumulado += total_cliente;
        // 3. MOSTRAR RESUMEN 
        mostrar_resumen(cantidad_bolillo, cantidad_dulce, cantidad_espanol, total_cliente);
        // 4. MENÚ POST-VENTA
        bool menuActivo = true;
        while(menuActivo) {
            cout << "\nQue deseas hacer?" << endl;
            cout << "[4] Cobrar a otro cliente." << endl;
            cout << "[5] Ver HISTORIAL de ventas." << endl;
            cout << "[Otro] Salir del programa." << endl;
            cout << ">> ";
            cin >> repetirPrograma;
            if (repetirPrograma == '4') {
                menuActivo = false; 
            }
            else if (repetirPrograma == '5') {
                repetirPrograma = mostrar_historial(
                    total_bolillo_vendido,
                    total_dulce_vendido,
                    total_espanol_vendido,
                    total_dinero_acumulado
                );
                menuActivo = false;
            }
            else {
                char confirmacion;
                limpiar_pantalla();
                cout << "\n[?] Estas seguro que deseas cerrar el programa? (S/N): ";
                cin >> confirmacion;
                if (confirmacion == 's' || confirmacion == 'S') {
                    menuActivo = false;
                    repetirPrograma = '0';
                } else {
                    limpiar_pantalla();
                }
            }
        }
    } while (repetirPrograma == '4');
    cout << "\nPrograma finalizado. Total acumulado: $" << fixed << setprecision(2) << total_dinero_acumulado << endl;
    return 0;
}
