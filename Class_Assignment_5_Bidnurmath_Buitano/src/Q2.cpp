
/*  1 the expression read from the table/figure is written as infix tokens
    2 infix -> postfix with an operator stack shuntingn yard
    3 postfix is evaluated with a value stack for all 16 input rows
    also verifies the minimum sop part d and the nand only circuit part e
    operators  !  not (unary, highest)   &  and   |  OR (lowest) */ 

#include <cstdio>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>
using namespace std;

bool isVariable(const string& t) { return t.size() == 1 && t[0] >= 'A' && t[0] <= 'Z'; }
bool isOperator(const string& t) { return t == "!" || t == "&" || t == "|"; }

int precedence(const string& op) {
    if (op == "!") return 3;
    if (op == "&") return 2;
    if (op == "|") return 1;
    return 0;                        // (
}

template <typename T>
string stackToString(stack<T> s) {    // bottom to top
    vector<T> v;
    while (!s.empty()) { v.push_back(s.top()); s.pop(); }
    string out = "[";
    for (int i = (int)v.size() - 1; i >= 0; --i) {
        if constexpr (is_same_v<T, string>) out += v[i]; else out += to_string(v[i]);
        if (i) out += " ";
    }
    return out + "]";
}

string join(const vector<string>& t) {
    string s;
    for (size_t i = 0; i < t.size(); ++i) s += (i ? " " : "") + t[i];
    return s;
}

// infix -> postfix using an operator stack
vector<string> toPostfix(const vector<string>& infix, bool trace = false) {
    vector<string> out;
    stack<string> ops;
    if (trace) printf("%-6s %-38s %s\n", "Token", "Output (postfix so far)", "Operator stack");
    for (const string& tok : infix) {
        if (isVariable(tok)) {
            out.push_back(tok);
        } else if (tok == "(") {
            ops.push(tok);
        } else if (tok == ")") {
            while (ops.top() != "(") { out.push_back(ops.top()); ops.pop(); }
            ops.pop();                                   // discard (
        } else if (tok == "!") {
            ops.push(tok);                               // unary prefix just push
        } else {                                         // binary & or |
            while (!ops.empty() && ops.top() != "(" &&
                   precedence(ops.top()) >= precedence(tok)) {
                out.push_back(ops.top()); ops.pop();
            }
            ops.push(tok);
        }
        if (trace) printf("%-6s %-38s %s\n", tok.c_str(), join(out).c_str(),
                          stackToString(ops).c_str());
    }
    while (!ops.empty()) { out.push_back(ops.top()); ops.pop(); }
    if (trace) printf("%-6s %-38s %s\n", "end", join(out).c_str(), "[]");
    return out;
}

// evaluate postfix with a value stack
int evalPostfix(const vector<string>& postfix, const map<char, int>& in, bool trace = false) {
    stack<int> vals;
    for (const string& tok : postfix) {
        if (isVariable(tok)) {
            vals.push(in.at(tok[0]));
        } else if (tok == "!") {
            int a = vals.top(); vals.pop();
            vals.push(!a);
        } else {
            int b = vals.top(); vals.pop();
            int a = vals.top(); vals.pop();
            vals.push(tok == "&" ? (a & b) : (a | b));
        }
        if (trace) printf("  %-3s %s\n", tok.c_str(), stackToString(vals).c_str());
    }
    return vals.top();
}

// direct gate bygate simulation of the table reference
int circuit(int A, int B, int C, int D) {
    int N1 = !C, N2 = !D, P = B | N1, Q = A & P, R = C | N2, S = B & R, T = A & D;
    return Q | S | T;
}

// NAND only circuit from part (e)
int nand2(int x, int y) { return !(x & y); }
int nand3(int x, int y, int z) { return !(x & y & z); }
int nandOnly(int A, int B, int C, int D) {
    int G1 = nand2(C, C), G2 = nand2(D, D);
    int G3 = nand2(B, G2), G4 = nand2(A, G1);
    int G5 = nand2(B, C), G6 = nand2(A, D);
    int G7 = nand2(G5, G6), G8 = nand2(G7, G7);
    return nand3(G3, G4, G8);
}

int main() {
    // Z = Q + S + T = A(B + C') + B(C + D') + AD
    vector<string> zInfix = {"(", "A", "&", "(", "B", "|", "!", "C", ")", ")", "|",
                             "(", "B", "&", "(", "C", "|", "!", "D", ")", ")", "|",
                             "(", "A", "&", "D", ")"};
    // minimum sop Z = BD' + BC + AC' + AD
    vector<string> sopInfix = {"B", "&", "!", "D", "|", "B", "&", "C", "|",
                               "A", "&", "!", "C", "|", "A", "&", "D"};

    cout << "Infix -> postfix for Z \nInfix: " << join(zInfix) << "\n";
    vector<string> zPost = toPostfix(zInfix, true);
    vector<string> sopPost = toPostfix(sopInfix);
    cout << "\nPostfix Z   : " << join(zPost) << "\n";
    cout << "Postfix SOP : " << join(sopPost) << "\n";

    cout << "\nvalue stack trace for A=1 B=0 C=1 D=0 (m10) \n";
    int z10 = evalPostfix(zPost, {{'A', 1}, {'B', 0}, {'C', 1}, {'D', 0}}, true);
    cout << "Z = " << z10 << "\n";

    cout << "\ntruth table (Z computed with the stack) \n";
    cout << " m | A B C D | Z(stack) | gates | minSOP | NAND\n";
    vector<int> minterms;
    bool ok = true;
    for (int m = 0; m < 16; ++m) {
        int A = (m >> 3) & 1, B = (m >> 2) & 1, C = (m >> 1) & 1, D = m & 1;
        map<char, int> in = {{'A', A}, {'B', B}, {'C', C}, {'D', D}};
        int z = evalPostfix(zPost, in);
        int g = circuit(A, B, C, D), s = evalPostfix(sopPost, in), n = nandOnly(A, B, C, D);
        if (z != g || z != s || z != n) ok = false;
        if (z) minterms.push_back(m);
        printf("%2d | %d %d %d %d |    %d     |   %d   |   %d    |  %d\n", m, A, B, C, D, z, g, s, n);
    }
    cout << "\nZ = sum m(";
    for (size_t i = 0; i < minterms.size(); ++i)
        cout << minterms[i] << (i + 1 < minterms.size() ? ", " : ")\n");
    cout << (ok ? "Stack result, gate circuit, min SOP and NAND circuit all MATCH.\n"
                : "MISMATCH found!\n");

    int gray[4] = {0, 1, 3, 2};
    cout << "\nK-map (rows AB, cols CD, Gray order):\n        00 01 11 10\n";
    for (int r = 0; r < 4; ++r) {
        printf("AB=%d%d  ", (gray[r] >> 1) & 1, gray[r] & 1);
        for (int c = 0; c < 4; ++c) {
            int m = (gray[r] << 2) | gray[c];
            printf("  %d", circuit((m >> 3) & 1, (m >> 2) & 1, (m >> 1) & 1, m & 1));
        }
        cout << "\n";
    }
    return 0;
}