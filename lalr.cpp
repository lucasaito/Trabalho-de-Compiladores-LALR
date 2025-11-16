#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <cctype>
#include <memory>
#include <algorithm>

using namespace std;

// ===========================================================
// TOKENIZAÇÃO
// ===========================================================

enum TokenType { ID, NUM, PLUS, TIMES, LP, RP, END };

struct Token {
    TokenType type;
    string lexeme;
};

vector<Token> tokenize(const string& input) {
    vector<Token> tokens;
    for (size_t i = 0; i < input.size(); i++) {
        char c = input[i];

        if (isspace(c)) continue;

        if (isalpha(c)) {
            tokens.push_back({ID, string(1, c)});
            continue;
        }

        if (isdigit(c)) {
            tokens.push_back({NUM, string(1, c)});
            continue;
        }

        if (c == '+') { tokens.push_back({PLUS, "+"}); continue; }
        if (c == '*') { tokens.push_back({TIMES, "*"}); continue; }
        if (c == '(') { tokens.push_back({LP, "("}); continue; }
        if (c == ')') { tokens.push_back({RP, ")"}); continue; }

        cerr << "Caractere invalido: " << c << endl;
        exit(1);
    }
    tokens.push_back({END, "$"});
    return tokens;
}

// ===========================================================
// ESTRUTURA DE AST
// ===========================================================

struct AST {
    string label;
    vector<shared_ptr<AST>> children;

    AST(string l) : label(l) {}
};

void printAST(const shared_ptr<AST>& node, int depth = 0) {
    if (!node) return;
    for (int i = 0; i < depth; i++)
        cout << "  ";
    cout << node->label << "\n";

    for (auto& c : node->children)
        printAST(c, depth + 1);
}

// ===========================================================
// TABELA LALR(1)
// ===========================================================

struct Action {
    char kind;  // 's' = shift, 'r' = reduce, 'a' = accept, 'e' = error
    int value;
};

Action ACTION[12][7];
int GOTO_TAB[12][3];

struct Prod { string lhs; int lhs_id; int rhs_size; };
vector<Prod> prods = {
    {"",0,0},
    {"E",0,3}, // 1: E → E + T
    {"E",0,1}, // 2: E → T
    {"T",1,3}, // 3: T → T * F
    {"T",1,1}, // 4: T → F
    {"F",2,3}, // 5: F → ( E )
    {"F",2,1}  // 6: F → id
};

void initTables() {
    for (int i=0;i<12;i++)
        for (int j=0;j<7;j++)
            ACTION[i][j] = {'e',0};

    ACTION[0][ID] = {'s',5};
    ACTION[0][LP] = {'s',4};

    ACTION[1][PLUS] = {'s',6};
    ACTION[1][END] = {'a',0};

    ACTION[2][PLUS] = {'r',2};
    ACTION[2][TIMES] = {'s',7};
    ACTION[2][RP] = {'r',2};
    ACTION[2][END] = {'r',2};

    ACTION[3][PLUS] = {'r',4};
    ACTION[3][TIMES] = {'r',4};
    ACTION[3][RP] = {'r',4};
    ACTION[3][END] = {'r',4};

    ACTION[4][ID] = {'s',5};
    ACTION[4][LP] = {'s',4};

    ACTION[5][PLUS] = {'r',6};
    ACTION[5][TIMES] = {'r',6};
    ACTION[5][RP] = {'r',6};
    ACTION[5][END] = {'r',6};

    ACTION[6][ID] = {'s',5};
    ACTION[6][LP] = {'s',4};

    ACTION[7][ID] = {'s',5};
    ACTION[7][LP] = {'s',4};

    ACTION[8][PLUS] = {'s',6};
    ACTION[8][RP] = {'s',11};

    ACTION[9][PLUS] = {'r',1};
    ACTION[9][TIMES] = {'s',7};
    ACTION[9][RP] = {'r',1};
    ACTION[9][END] = {'r',1};

    ACTION[10][PLUS] = {'r',3};
    ACTION[10][TIMES] = {'r',3};
    ACTION[10][RP] = {'r',3};
    ACTION[10][END] = {'r',3};

    ACTION[11][PLUS] = {'r',5};
    ACTION[11][TIMES] = {'r',5};
    ACTION[11][RP] = {'r',5};
    ACTION[11][END] = {'r',5};

    for (int i=0;i<12;i++)
        for (int j=0;j<3;j++)
            GOTO_TAB[i][j] = -1;

    GOTO_TAB[0][0] = 1; 
    GOTO_TAB[0][1] = 2;
    GOTO_TAB[0][2] = 3;

    GOTO_TAB[4][0] = 8;
    GOTO_TAB[4][1] = 2;
    GOTO_TAB[4][2] = 3;

    GOTO_TAB[6][0] = 9;
    GOTO_TAB[6][1] = 2;
    GOTO_TAB[6][2] = 3;

    GOTO_TAB[7][0] = 10;
    GOTO_TAB[7][1] = 2;
    GOTO_TAB[7][2] = 3;
}

// ===========================================================
// PARSER LALR(1) COM AST
// ===========================================================

void printStack(stack<int> st) {
    vector<int> v;
    while (!st.empty()) {
        v.push_back(st.top());
        st.pop();
    }
    cout << "Pilha: ";
    for (int i = v.size()-1; i >= 0; i--)
        cout << v[i] << " ";
    cout << "\n";
}

shared_ptr<AST> parse(const vector<Token>& tokens) {
    stack<int> st;
    stack<shared_ptr<AST>> ast_stack;

    st.push(0);
    int ip = 0;

    while (true) {
        int state = st.top();
        Token tok = tokens[ip];
        Action a = ACTION[state][tok.type];

        cout << "\nEstado atual: " << state
             << " | Token: " << tok.lexeme 
             << " | Acao: " << a.kind << a.value << "\n";
        printStack(st);

        if (a.kind == 'e') {
            cerr << "Erro sintatico no token: " << tok.lexeme << endl;
            return nullptr;
        }

        if (a.kind == 's') {
            cout << "SHIFT para o estado " << a.value << "\n";
            st.push(a.value);
            ast_stack.push(make_shared<AST>(tok.lexeme));
            ip++;
        }
        else if (a.kind == 'r') {
            Prod p = prods[a.value];
            cout << "REDUCE pela producao " << a.value 
                 << ": " << p.lhs << " -> ("
                 << p.rhs_size << " simbolos)\n";

            vector<shared_ptr<AST>> children;

            for (int i = 0; i < p.rhs_size; i++) {
                st.pop();
                children.push_back(ast_stack.top());
                ast_stack.pop();
            }

            reverse(children.begin(), children.end());

            shared_ptr<AST> node = make_shared<AST>(p.lhs);
            for (auto& c : children)
                node->children.push_back(c);

            int new_state = GOTO_TAB[st.top()][p.lhs_id];
            cout << "GOTO estado " << new_state << "\n";

            st.push(new_state);
            ast_stack.push(node);
        }
        else if (a.kind == 'a') {
            cout << "\nEntrada aceita!\n";
            return ast_stack.top();
        }
    }
}

// ===========================================================
// MAIN
// ===========================================================

int main() {
    initTables();

    cout << "Digite uma expressao: ";
    string input;
    getline(cin, input);

    auto tokens = tokenize(input);
    auto ast = parse(tokens);

    cout << "\n--- AST Final ---\n";
    printAST(ast);

    system("pause");
    return 0;
}
