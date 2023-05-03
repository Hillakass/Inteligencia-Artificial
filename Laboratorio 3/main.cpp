#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
#define INF 12345
int maxDepth;



int tablero[8][8] = {
        {0, -1, 0, -1, 0, -1, 0, -1},
        {-1, 0, -1, 0, -1, 0, -1, 0},
        {0, -1, 0, -1, 0, -1, 0, -1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
};

pair<int, int> computador_movimiento[2] = { {1, -1}, {1, 1} };
pair<int, int> jugador_movimiento[2] = { {-1, -1}, {-1, 1} };


bool MovimientosDisponibles(int jugador) {
    bool movimiento = false;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (tablero[i][j] == jugador) {
                for (int k = 0; k < 2; ++k) {
                    int fila = i + jugador_movimiento[k].first;
                    int columna = j + jugador_movimiento[k].second;
                    if (fila >= 0 && fila < 8 && columna >= 0 && columna < 8 && tablero[fila][columna] == 0) {
                        movimiento = true;
                        break;
                    }
                }
                if (tablero[i][j] == -jugador) {
                    for (int k = 0; k < 2; ++k) {
                        int fila = i + computador_movimiento[k].first;
                        int columna = j + computador_movimiento[k].second;
                        if (fila >= 0 && fila < 8 && columna >= 0 && columna < 8) {
                            if (tablero[fila][columna] == 0) {
                                movimiento = true;
                                break;
                            } else if (tablero[fila][columna] == -jugador) {
                                int fila_comida = fila + computador_movimiento[k].first;
                                int columna_comida = columna + computador_movimiento[k].second;
                                if (fila_comida >= 0 && fila_comida < 8 && columna_comida >= 0 && columna_comida < 8 && tablero[fila_comida][columna_comida] == 0) {
                                    movimiento = true;
                                    break;
                                }
                            }
                        }
                    }
                }
                if (movimiento) break;
            }
        }
        if (movimiento) break;
    }
    return movimiento;
}




void copiar(int t1[8][8], const int t2[8][8]) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            t1[i][j] = t2[i][j];
        }
    }
}

struct movimiento {
    movimiento() {}
    movimiento(const int t[8][8]) {
        copiar(tab, t);
    }
    int tab[8][8];
    void print() {
        int rr, cc, pp;

        for (rr = 0; rr < 8; ++rr) {
            printf("%d |", rr);
            for (cc = 0; cc < 8; ++cc) {
                if (tab[rr][cc] == 1) {
                    cout << " # |";
                }
                else if (tab[rr][cc] == -1) {
                    cout << " $ |";
                }
                else {
                    cout << "   |";
                }
            }
            printf("\n");

        }
    }
};

vector<movimiento> SaveTab;


int Utilidad(int table[8][8]) {
    int ans = 0;

    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            ans += -table[i][j];

    return ans;
}



void Resultados() {
    int result = Utilidad(tablero);

    if (result < 0)
        cout << "El jugador gana!!" << endl;
    else if (result == 0)
        cout << "Empate, nadie gana :c" << endl;
    else
        cout << "El computador gana!!" << endl;
}


struct Nodo {
    int mejor_tablero[8][8];
    int tablero_actual[8][8];
    int depth;

    bool minimize;
    Nodo(int c[8][8], int d) {
        depth = d;
        copiar(tablero_actual, c);
        minimize = depth & 1;
    }

    int MinMax(int alpha, int beta) {
        if (depth == maxDepth)
            return Utilidad(tablero_actual);

        int mejor = minimize ? INF : -INF;
        int jugador = minimize ? 1 : -1;
        pair< int, int>* options = minimize ? jugador_movimiento : computador_movimiento;

        //visitar nodos hijo
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (tablero_actual[i][j] == jugador) {
                    for (int k = 0; k < 2; k++) {
                        int fila = i + options[k].first;
                        int columna = j + options[k].second;
                        if (fila >= 0 && fila < 8 && columna >= 0 && columna < 8 && tablero_actual[fila][columna] == 0) {
                            //mover ficha
                            int temp = tablero_actual[fila][columna];
                            tablero_actual[fila][columna] = jugador;
                            tablero_actual[i][j] = 0;
                            //llamada recursiva
                            Nodo nodo = Nodo(tablero_actual, depth + 1);
                            int score = nodo.MinMax(alpha, beta);
                            //deshacer movimiento
                            tablero_actual[fila][columna] = temp;
                            tablero_actual[i][j] = jugador;
                            //actualizar mejor
                            if ((minimize && score < mejor) || (!minimize && score > mejor)) {
                                copiar(mejor_tablero, nodo.tablero_actual);
                                mejor = score;
                            }
                            //podar
                            if (minimize) {
                                beta = min(beta, mejor);
                                if (beta <= alpha)
                                    return mejor;
                            }
                            else {
                                alpha = max(alpha, mejor);
                                if (alpha >= beta)
                                    return mejor;
                            }
                        }
                    }
                }
            }
        }
        return mejor;
    }


};


void imprimirTablero() {
    ofstream archivo("C:\\Users\\Hillary Kassandra\\Downloads\\Correccion2\\datos2.tttt"); // Abrimos el archivo en modo de escritura
    if (archivo.is_open()) { // Verificamos si se abrió correctamente
        int rr, cc;

        for (rr = 0; rr < 8; ++rr) {

            for (cc = 0; cc < 8; ++cc) {
                if (tablero[rr][cc] == 1) {
                    archivo << "#";

                }
                else if (tablero[rr][cc] == -1) {
                    archivo << "$";

                }
                else {
                    archivo << "-";
                }
            }
            archivo << "\n";


        }

        archivo.close(); // Cerramos el archivo
    }
    else {
        cout << "No se pudo abrir el archivo para escribir." << endl;
    }
}




int main() {

    bool jugador;
    cout << "Elegir quien empieza el juego computadora=0 // jugador=1: ";
    cin >> jugador;
    cout << endl << "Indicar la profundidad(1 al 7): ";
    cin >> maxDepth;

    while (true) {

        if (jugador) {//movimiento jugador
            int x_i, y_i, x_f, y_f;

            if (!MovimientosDisponibles(1)) { break; }

            while (true) {

                imprimirTablero();

                cout << "Ingrese las coordenadas de la posicion inicial: " << endl;
                cout << "Fila y columna: ";
                cin >> x_i >> y_i;
                cout << "Ingrese las coordenadas de la posicion final: " << endl;
                cout << "Fila y columna: ";
                cin >> x_f >> y_f;

                if (tablero[x_i][y_i] != 1) {
                    cout << "Movimiento invalido, intente nuevamente :)";
                    continue;
                }
                if (x_f == x_i - 1 && y_f == y_i - 1) {//diagonal izquierda
                    if (tablero[x_f][y_f] == 0) {
                        tablero[x_i][y_i] = 0;
                        tablero[x_f][y_f] = 1;
                        movimiento tab(tablero);
                        SaveTab.push_back(tab);
                        break;
                    }
                }
                if (x_f == x_i - 1 && y_f == y_i + 1) {//diagonal derecha
                    if (tablero[x_f][y_f] == 0) {
                        tablero[x_i][y_i] = 0;
                        tablero[x_f][y_f] = 1;
                        movimiento tab(tablero);
                        SaveTab.push_back(tab);
                        break;
                    }

                }
                if (x_f == x_i - 2 && y_f == y_i - 2) {//comer una ficha izquierda
                    if (tablero[x_f][y_f] == 0 && tablero[x_i - 1][y_i - 1] == -1) {
                        tablero[x_i][y_i] = 0;
                        tablero[x_f][y_f] = 1;
                        tablero[x_i - 1][y_i - 1] = 0;
                        movimiento tab(tablero);
                        SaveTab.push_back(tab);
                        break;

                    }
                }
                if (x_f == x_i - 2 && y_f == y_i + 2) {//comer una ficha derecha
                    if (tablero[x_f][y_f] == 0 && tablero[x_i - 1][y_i + 1] == -1) {
                        tablero[x_i][y_i] = 0;
                        tablero[x_f][y_f] = 1;
                        tablero[x_i - 1][y_i + 1] = 0;
                        movimiento tab(tablero);
                        SaveTab.push_back(tab);
                        break;
                    }
                }

            }
        }
        else { //movimiento de computador

            Nodo root(tablero, 0);
            int result;

            result = root.MinMax(-INF, INF);

            if (result == -INF) {
                break;
            }

            copiar(tablero, root.mejor_tablero);
            imprimirTablero();
            movimiento tab(tablero);
            SaveTab.push_back(tab);
        }//acaba el else


        jugador = (!jugador);

    } //fin del while

    Resultados();

}