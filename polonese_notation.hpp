#include <iostream>
#include <cmath>
#include "pilhaEstatica.hpp"
#include "filaEstatica.hpp"

using namespace std;

int precedencia(char operador) {
    if (operador == '^') return 3;
    else if (operador == '/' || operador == '*') return 2;
    else return 1;
}

char correspondente(char fecha) {
    if (fecha == ')') return '(';
    else if (fecha == ']') return '[';
    else return '{';
}

bool operador(char c) {
    return c == '+' || c == '-' || c == '/'
        || c == '*' || c == '^';
}

bool fecha(char c) {
    return c == '}' || c == ']' || c == ')';
}

bool abre(char c) {
    return c == '{' || c == '[' || c == '(';
}

bool valido(char c) {
    return isdigit(c) || isalpha(c) ||
       operador(c) || abre(c) || fecha(c) || c == ' ';
}

bool converte(Fila<char> &saida, string expressao){
    Pilha <char> operadores;

    inicializar(operadores);
    inicializar(saida);

    for (int i = 0; i < expressao.length(); i++) {
        char atual = expressao[i];
        if (atual == ' ') continue;

        if (!valido(atual)) {
            cout << "caracter invalido! " << atual << " posicao: " << i <<endl;
            return false;
        }

        if (isdigit(atual) || isalpha(atual)) queue(saida, atual);
        
        if (abre(atual)) push(operadores, atual);
        
        if (operador(atual)) {
            char topo;
            while (top(operadores, topo) && operador(topo)) {
                if (precedencia(topo) >= precedencia(atual)) {
                    pop(operadores, topo);
                    queue(saida, topo);
                }
            }
            push(operadores, atual);
        }

        if (fecha(atual)) {
            char par = correspondente(atual);
            char topo;
            
            while (!vazia(operadores)) {
                top(operadores, topo);
                if (topo == par) {
                    pop(operadores, topo);
                    break;
                }
                if (abre(topo)) {
                    cout << "Fechado incorretamente: " << atual << endl;
                    return false;
                }
                pop(operadores, topo);
                queue(saida, topo);
            }
        }

    }
    
    char topo;
    while (!vazia(operadores)) {
        pop(operadores, topo);
        queue(saida, topo);
    }

    liberar(operadores);
    return true;
}

int valorVariavel(char variavel, int a, int b, int c) {
    if (variavel == 'a') return a;
    if (variavel == 'b') return b;
    if (variavel == 'c') return c;
    return 0;
}

int calcular(Fila<char> saida, int a, int b, int c) {

    Pilha<int> valores;

    inicializar(valores);

    for (int i = 0; i < saida.fim; i++) {

        char atual = saida.vetor[i];

        if (isdigit(atual)) {
            int numero = atual - '0';
            push(valores, numero);
        }
        else if (isalpha(atual)) {
            int numero = valorVariavel(atual, a, b, c);
            push(valores, numero);
        }

        else if (operador(atual)) {
            int v1, v2;

            pop(valores, v1);
            pop(valores, v2);

            int resultado = 0;

            switch (atual) {
                case '+': resultado = v2 + v1; break;
                case '-': resultado = v2 - v1; break;
                case '*': resultado = v2 * v1; break;
                case '/': resultado = v2 / v1; break;
                case '^': resultado = pow(v2, v1); break;
            }

            push(valores, resultado);
        }
    }

    int resultadoFinal;
    pop(valores, resultadoFinal);

    liberar(valores);

    return resultadoFinal;
}

int main()
{
    int opcao;
    string expressao;
 
    do {
        
        cout << " CALCULADORA POLONESA\n";
        cout << " 1 - Inserir expressao\n";
        cout << " 0 - Sair\n";
        cout << " Opcao: ";
        cin >> opcao;
        cin.ignore();
 
        if (opcao == 1) {
            cout << "\n Digite a expressao: ";
            getline(cin, expressao);
            
            Fila<char> saida;
            if (converte(saida, expressao)) {
                cout << " Expressão: ";
                mostrar(saida); cout << endl;
                
                int a, b, c;
                cout << " Digite valores para:\n";
                cout << " a: "; cin >> a;
                cout << " b: "; cin >> b;
                cout << " c: "; cin >> c;
                
                int resultado = calcular(saida, a, b, c);
                cout << "\nResultado: "
                     << resultado << endl;
            };
            
            
            liberar(saida);

        }
 
    } while (opcao != 0);

}
