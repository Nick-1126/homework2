#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <sstream>
#include <stdexcept>

using namespace std;

// 檢查括號是否對稱
bool areParenthesesBalanced(const string& expression) {
    stack<char> s;
    for (char ch : expression) {
        if (ch == '(') {
            s.push(ch);
        }
        else if (ch == ')') {
            if (s.empty()) {
                return false;
            }
            s.pop();
        }
    }
    return s.empty();
}

// 判斷運算子的優先順序
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// 中序轉後序 (Infix to Postfix)
string infixToPostfix(const string& expression) {
    stack<char> s;
    string postfix;
    for (char ch : expression) {
        if (isdigit(ch)) {
            postfix += ch;
        }
        else if (ch == '(') {
            s.push(ch);
        }
        else if (ch == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();
                s.pop();
            }
            s.pop();
        }
        else {
            while (!s.empty() && precedence(s.top()) >= precedence(ch)) {
                postfix += s.top();
                s.pop();
            }
            s.push(ch);
        }
    }
    while (!s.empty()) {
        postfix += s.top();
        s.pop();
    }
    return postfix;
}

// 計算後序運算式的結果
int evaluatePostfix(const string& postfix) {
    stack<int> s;
    for (char ch : postfix) {
        if (isdigit(ch)) {
            s.push(ch - '0');
        }
        else {
            int val2 = s.top(); s.pop();
            int val1 = s.top(); s.pop();
            switch (ch) {
            case '+': s.push(val1 + val2); break;
            case '-': s.push(val1 - val2); break;
            case '*': s.push(val1 * val2); break;
            case '/': s.push(val1 / val2); break;
            }
        }
    }
    return s.top();
}

int main() {
    char choice;  // 用於存放使用者的選擇
    do {
        string expression;  // 用於存放用戶輸入的運算式
        cout << "請輸入運算式: ";
        cin >> expression;  // 從標準輸入中讀取運算式

        // 檢查括號是否對稱
        if (!areParenthesesBalanced(expression)) {
            cout << expression << " 運算式的括號不對稱，無法繼續運算" << endl;
            return 1;  // 結束程式並返回錯誤碼 1
        }

        cout << expression << " 運算式的左右括號對稱" << endl;

        // 將中序運算式轉換為後序運算式
        string postfix = infixToPostfix(expression);
        cout << expression << " 運算式的後序表式法為： " << postfix << endl;

        // 計算後序運算式的結果
        int result = evaluatePostfix(postfix);
        cout << expression << " 運算式的運算結果為：" << result << endl;

        // 詢問使用者是否繼續測試
        cout << "是否繼續測試? (Y/y 繼續, 其他鍵退出): ";
        cin >> choice;  // 讀取使用者的選擇

    } while (choice == 'Y' || choice == 'y');  // 當輸入為 'Y' 或 'y' 時繼續測試

    cout << "測試結束，感謝使用！" << endl;

    return 0;
}
