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

bool opera(Fila<char> &saida){
    Pilha <char> operadores;

    string expressao = "(a + b) * c";

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
                    cout << "Fechado incorretamente!" << topo << endl;
                    return false;
                }
                pop(operadores, topo);
                queue(saida, topo);
            }
        }

    }
    
    char topo;
    pop(operadores, topo);
    queue(saida, topo);

    liberar(operadores);
    return true;
}

int main()
{
    
    int opcao;
    string expressao;
 
    do {
        
        cout << "   CALCULADORA POLONESA\n";
        cout << " 1. Inserir expressao\n";
        cout << " 0. Sair\n";
        cout << " Opcao: ";
        cin >> opcao;
        cin.ignore();
 
        if (opcao == 1) {
            cout << "\n Regras da expressao:\n";
            cout << " - Operadores  : + - / * ^\n";
            cout << " - Digitos     : apenas 1 digito por vez (0-9)\n";
            cout << " - Variaveis   : apenas 1 letra por vez (a-z)\n";
            cout << " - Agrupadores : ( ) [ ] { }\n";
            cout << " Exemplo: 3 + {[5 * a] - [b / (3 + c)]}\n";
            cout << "\n Digite a expressao: ";
            getline(cin, expressao);
            
            Fila<char> saida;
            if (opera(saida)) {
                mostrar(saida);
            };
    
            liberar(saida);

            // if (expressao.empty()) {
            //     cout << "  Erro: expressao vazia!\n";
            //     break;
            // }

            // if (!validarTokens(expressao)) break;

            // cout << "\n  Expressao recebida: " << expressao << "\n";
            // identificarComponentes(expressao);
            // cout << "\n  [Conversao e resolucao serao implementadas aqui]\n";
            // break;
 
            // case 0:
            //     cout << "\n  Encerrando...\n";
            //     break;
 
            // default:
            //     cout << "\n  Opcao invalida!\n";
        }
 
    } while (opcao != 0);

}
