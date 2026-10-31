
#include <cctype>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

//helper functions 

// a token is a number if it is an optional - followed by one or more digits
// a lone - is the subtraction operator
bool isNumber(const string& tok) {
    if (tok.empty()) return false;
    size_t i = 0;
    if (tok[0] == '-') {
        if (tok.size() == 1) return false;
        i = 1;
    }
    for (; i < tok.size(); ++i)
        if (!isdigit(static_cast<unsigned char>(tok[i]))) return false;
    return true;
}

int precedence(const string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    if (op == "^") return 3;
    return 0;
}

bool isRightAssociative(const string& op) { return op == "^"; }

// division rounded down toward negative infinity.
int floorDiv(int a, int b) {
    int q = a / b;                                   // cpp truncates toward 0
    if (a % b != 0 && ((a < 0) != (b < 0))) --q;     // fix when signs differ
    return q;
}

// integer power with a nonnegative exponent.
int power(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; ++i) result *= base;
    return result;
}

int applyOperation(int a, int b, const string& op) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") return floorDiv(a, b);
    if (op == "^") return power(a, b);
    throw invalid_argument("Unknown operator: " + op);
}

// tracing helpers 
template <typename T>
string stackToString(stack<T> s) {         
    vector<T> items;
    while (!s.empty()) { items.push_back(s.top()); s.pop(); }
    string out = "[";
    for (int i = static_cast<int>(items.size()) - 1; i >= 0; --i) {
        if constexpr (is_same_v<T, string>) out += items[i];
        else out += to_string(items[i]);
        if (i > 0) out += ", ";
    }
    return out + "]";
}

//pop two values and one operator push the result
void applyTop(stack<int>& values, stack<string>& ops, bool trace) {
    string op = ops.top(); ops.pop();
    int b = values.top(); values.pop();
    int a = values.top(); values.pop();
    int r = applyOperation(a, b, op);
    values.push(r);
    if (trace)
        cout << "    apply " << a << " " << op << " " << b << " = " << r << "\n";
}

// evaluate 

int evaluate(const vector<string>& tokens, bool trace = false) {
    stack<int> values;
    stack<string> ops;

    for (const string& tok : tokens) {
        if (trace) cout << "Token " << tok << ":\n";
        if (isNumber(tok)) {
            values.push(stoi(tok));
        } else {
            // pop while top has higher precedence or equal precedence and
            // the incoming operator is left associative
            while (!ops.empty() &&
                   (precedence(ops.top()) > precedence(tok) ||
                    (precedence(ops.top()) == precedence(tok) &&
                     !isRightAssociative(tok)))) {
                applyTop(values, ops, trace);
            }
            ops.push(tok);
        }
        if (trace)
            cout << "    values = " << stackToString(values)
                 << "   ops = " << stackToString(ops) << "\n";
    }

    if (trace && !ops.empty()) cout << "Remaining calculations:\n";
    while (!ops.empty()) {
        applyTop(values, ops, trace);
        if (trace)
            cout << "    values = " << stackToString(values)
                 << "   ops = " << stackToString(ops) << "\n";
    }
    return values.top();
}

string join(const vector<string>& t) {
    string s;
    for (size_t i = 0; i < t.size(); ++i) s += (i ? " " : "") + t[i];
    return s;
}

int main() {
    // (b) + (c) evaluate and trace
    vector<string> expr = {"8", "+", "3", "*", "2", "^", "2", "-", "20", "/", "4"};
    cout << "(b)/(c) Trace of: " << join(expr) << " \n";
    int result = evaluate(expr, true);
    cout << "Result = " << result << "\n\n";

    // (d) associativity and division tests
    vector<pair<vector<string>, int>> tests = {
        {{"2", "^", "3", "^", "2"}, 512},   // right-assoc 2^(3^2)
        {{"-7", "/", "2"}, -4},             // floor(-3.5) = -4
        {{"7", "/", "-2"}, -4},             // extra
        {{"7", "/", "2"}, 3},               // extra
        {{"10", "-", "3", "-", "2"}, 5},    // left assoc subtraction
        {{"8", "+", "3", "*", "2", "^", "2", "-", "20", "/", "4"}, 15},
    };
    cout << "Tests\n";
    for (auto& [toks, expected] : tests) {
        int got = evaluate(toks);
        cout << join(toks) << " = " << got << "   (expected " << expected << ") "
             << (got == expected ? "PASS" : "FAIL") << "\n";
    }
    return 0;
}