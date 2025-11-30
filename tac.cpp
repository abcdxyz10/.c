#include <bits/stdc++.h>
using namespace std;

vector<string> tokenize(string s) {
    vector<string> tokens;
    string temp = "";
    for (int i = 0; i < s.size(); i++) {
        if (isalnum(s[i]) || s[i] == '_') {
            temp += s[i];
        } else {
            if (!temp.empty()) {
                tokens.push_back(temp);
                temp = "";
            }
            if (s[i] == ' ') continue;
            tokens.push_back(string(1, s[i]));
        }
    }
    if (!temp.empty()) tokens.push_back(temp);
    return tokens;
}

int prec(string op) {
    if (op == "+" || op == "-") return 1;
    else if (op == "*" || op == "/") return 2;
    return 0;
}

vector<string> infix2postfix(vector<string> tokens) {
    vector<string> output;
    stack<string> s;
    for (auto x : tokens) {
        if (isalnum(x[0]) || x[0] == '_') {
            output.push_back(x);
        }
        else if (x == "(") {
            s.push(x);
        }
        else if (x == ")") {
            while (!s.empty() && s.top() != "(") {
                output.push_back(s.top());
                s.pop();
            }
            s.pop();
        }
        else {
            while (!s.empty() && s.top() != "(" && prec(s.top()) >= prec(x)) {
                output.push_back(s.top());
                s.pop();
            }
            s.push(x);
        }
    }
    while (!s.empty()) {
        output.push_back(s.top());
        s.pop();
    }
    return output;
}

void gen_TAC(vector<string> postfix) {
    vector<tuple<string, string, string, string>> quadruples;
    vector<tuple<string, string, string>> triples;
    stack<string> st;
    int temp_count = 1;

    for (auto x : postfix) {
        if (isalnum(x[0]) || x[0] == '_') {
            st.push(x);
        } else {
            string b = st.top(); 
            st.pop();
            string a = st.top(); 
            st.pop();
            string tmp = "t" + to_string(temp_count++);
            quadruples.push_back({x, a, b, tmp});
            auto conv = [&](string s) {
                return (s[0] == 't') ? "(" + to_string(stoi(s.substr(1)) - 1) + ")" : s;
            };
            triples.push_back({x, conv(a), conv(b)});
            st.push(tmp);
        }
    }

    cout << "\nQuadruples:\nIdx\tOp\tArg1\tArg2\tResult\n";
    for (int i = 0; i < quadruples.size(); i++) {
        auto [op, a, b, r] = quadruples[i];
        cout << i << "\t" << op << "\t" << a << "\t" << b << "\t" << r << "\n";
    }

    cout << "\nTriples:\nIdx\tOp\tArg1\tArg2\n";
    for (int i = 0; i < triples.size(); i++) {
        auto [op, a, b] = triples[i];
        cout << i << "\t" << op << "\t" << a << "\t" << b << "\n";
    }

    cout << "\nIndirect Triples:\nIdx\tPointer\n";
    for (int i = 0; i < triples.size(); i++) {
        cout << i << "\t" << i << "\n";
    }
}

int main() {
    string expr;
    cout << "Enter expression: ";
    getline(cin, expr);
    auto tokens = tokenize(expr);
    auto postfix = infix2postfix(tokens);
    gen_TAC(postfix);
}
