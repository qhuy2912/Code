#include<bits/stdc++.h>

using namespace std;

bool KiemTra(const string& expression) {
    stack<char> parentheses;
    for (char ch : expression) {
        if (ch == '(') {
            parentheses.push(ch);
        } else if (ch == ')') {
            if (parentheses.empty()) return false;
            parentheses.pop();
        }
    }
    return parentheses.empty();
}

bool apdungToanTu(bool a, bool b, char op) {
    switch (op) {
        case '&': return a && b;  
        case '|': return a || b;  
        case '>': return !a || b; 
        case '=': return a == b;  
        default: return false;
    }
}


bool PhuDinh(bool value) {
    return !value;
}


bool TinhGiaTri(const string& expression, const map<char, bool>& values) {
    stack<bool> operands;    
    stack<char> operators;   

    for (size_t i = 0; i < expression.length(); ++i) {
        char ch = expression[i];

        if (isspace(ch)) continue;

        if (ch == '(') {
            operators.push(ch);
        } else if (isalpha(ch)) {
            if (values.find(ch) == values.end()) {
                throw invalid_argument("Bien " + string(1, ch) + " khong co gia tri.");
            }
            operands.push(values.at(ch));
        } else if (ch == ')') {
            while (!operators.empty() && operators.top() != '(') {
                char op = operators.top(); operators.pop();
                if (op == '!') {
                    bool a = operands.top(); operands.pop();
                    operands.push(PhuDinh(a));
                } else {
                    bool b = operands.top(); operands.pop();
                    bool a = operands.top(); operands.pop();
                    operands.push(apdungToanTu(a, b, op));
                }
            }
            if (!operators.empty() && operators.top() == '(') {
                operators.pop();
            }
        } else if (ch == '&' || ch == '|' || ch == '>' || ch == '=') {
            while (!operators.empty() && operators.top() != '(' && operators.top() != '!') {
                char op = operators.top(); operators.pop();
                bool b = operands.top(); operands.pop();
                bool a = operands.top(); operands.pop();
                operands.push(apdungToanTu(a, b, op));
            }
            operators.push(ch);
        } else if (ch == '!') {
            operators.push(ch);
        }
    }

    while (!operators.empty()) {
        char op = operators.top(); operators.pop();
        if (op == '!') {
            bool a = operands.top(); operands.pop();
            operands.push(PhuDinh(a));
        } else {
bool b = operands.top(); operands.pop();
            bool a = operands.top(); operands.pop();
            operands.push(apdungToanTu(a, b, op));
        }
    }

    return operands.top();
}

int main() {
    string expression;
    cout << "Nhap bieu thuc logic: ";
    getline(cin, expression);

    if (!KiemTra(expression)) {
        cout << "Bieu thuc khong hop le." << endl;
        return 1;
    }

    map<char, bool> values;
    int n;
    cout << "Nhap so luong bien: ";
    cin >> n;

    cout << "Nhap gia tri cho cac bien (dang A 1 hoac A 0):" << endl;
    for (int i = 0; i < n; ++i) {
        char var;
        bool val;
        cin >> var >> val;
        values[var] = val;
    }

    try {
        bool result = TinhGiaTri(expression, values);
        cout << "Ket qua bieu thuc: " << (result ? "True" : "False") << endl;
    } catch (const invalid_argument& e) {
        cerr << "Loi: " << e.what() << endl;
        return 1;
    }

    return 0;
}


