#include <bits/stdc++.h>
using namespace std;

set<string> keywords = {
    "auto","break","case","char","const","continue","default","do","double","else",
    "enum","extern","float","for","goto","if","int","long","register","return",
    "short","signed","sizeof","static","struct","switch","typedef","union",
    "unsigned","void","volatile","while","main","namespace","public","private",
    "protected","class","friend","virtual","template","this","new","delete",
    "try","catch","throw","inline","using","export","mutable"
};

set<char> op = {
    '+','-','*','/','%','<','>','=','!','&','|','^','~','.'
};

set<char> special = {
    '{','}','(',')',';',',','[',']'
};

void removeComments(string &s) {
    string res;
    bool block = false, line = false;

    for (int i = 0; i < s.size(); i++) {
        if (!block && !line && i + 1 < s.size() && s[i] == '/' && s[i + 1] == '*') {
            block = true;
            i++;
        }
        else if (block && i + 1 < s.size() && s[i] == '*' && s[i + 1] == '/') {
            block = false;
            i++;
        }
        else if (!block && !line && i + 1 < s.size() && s[i] == '/' && s[i + 1] == '/') {
            line = true;
            i++;
        }
        else if (line && s[i] == '\n') {
            line = false;
            res += '\n';
        }
        else if (!block && !line) {
            res += s[i];
        }
    }

    s = res;
}

bool isIdentifier(const string &s) {
    if (!isalpha(s[0]) && s[0] != '_') return false;

    for (char c : s) {
        if (!isalnum(c) && c != '_') return false;
    }
    return true;
}

void analyze(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "File not found.\n";
        return;
    }

    string code = "", line;
    while (getline(file, line)) {
        code += line + "\n";
    }

    removeComments(code);

    set<string> foundKeywords, identifiers;
    vector<char> foundOperators, foundSymbols;
    string token = "";

    for (char c : code) {
        if (isspace(c) || op.count(c) || special.count(c)) {
            if (!token.empty()) {
                if (keywords.count(token)) foundKeywords.insert(token);
                else if (isIdentifier(token)) identifiers.insert(token);
                token.clear();
            }

            if (op.count(c)) foundOperators.push_back(c);
            if (special.count(c)) foundSymbols.push_back(c);
        }
        else {
            token += c;
        }
    }

    cout << "Keywords (" << foundKeywords.size() << "): ";
    for (auto &k : foundKeywords) cout << k << " ";

    cout << "\nIdentifiers (" << identifiers.size() << "): ";
    for (auto &id : identifiers) cout << id << " ";

    cout << "\nOperators: ";
    for (auto &o : foundOperators) cout << o << " ";

    cout << "\nSpecial Symbols: ";
    for (auto &s : foundSymbols) cout << s << " ";

    cout << endl;
}

int main() {
    analyze("sample.c");
    return 0;
}
