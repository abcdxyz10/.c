#include <bits/stdc++.h>
using namespace std;

void bnf_to_yacc_line(string line) {
    for (int i = 0; i < line.size(); i++) {

        if (i + 2 < line.size() &&
            line[i] == ':' && line[i+1] == ':' && line[i+2] == '=') {

            cout << ":";
            i += 2;    
        }
        else {
            cout << line[i];
        }
    }
    cout << "\n";
}
string expr;
int posn = 0;

char peekc() {
    while (posn < expr.size() && isspace(expr[posn])) posn++;
    if (posn < expr.size()) return expr[posn];
    return '\0';
}

char getc2() {
    char c = peekc();
    posn++;
    return c;
}

vector<string> val;
vector<int> L, R;

int makeNode(string v, int l = -1, int r = -1) {
    val.push_back(v);
    L.push_back(l);
    R.push_back(r);
    return val.size() - 1;
}

int number() {
    string num;
    while (isdigit(peekc())) num += getc2();
    return makeNode(num);
}

int term() {
    int node = number();
    while (peekc() == '*' || peekc() == '/') {
        char op = getc2();
        int right = number();
        node = makeNode(string(1, op), node, right);
    }
    return node;
}

int expression() {
    int node = term();
    while (peekc() == '+' || peekc() == '-') {
        char op = getc2();
        int right = term();
        node = makeNode(string(1, op), node, right);
    }
    return node;
}

void printAST(int idx, int level) {
    if (idx == -1) return;

    for (int i = 0; i < level; i++)
        cout << "  ";

    cout << val[idx] << "\n";
    printAST(L[idx], level + 1);
    printAST(R[idx], level + 1);
}
int main() {
    int n;
    cout << "Enter number of BNF rules: ";
    cin >> n;
    cin.ignore();

    cout << "Enter the BNF rules:\n";

    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);
        bnf_to_yacc_line(line);
    }
    cout << "\nEnter arithmetic expression: ";
    getline(cin, expr);

    posn = 0;
    val.clear();
    L.clear();
    R.clear();

    int root = expression();

    cout << "\nAST:\n";
    printAST(root, 0);

    return 0;
}
