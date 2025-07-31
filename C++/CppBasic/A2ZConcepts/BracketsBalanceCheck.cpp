#include <iostream>
#include <stack>
#include <unordered_map>
#include <string>
using namespace std;
//logic to check if brackets are balanced
// A string is considered balanced if every opening bracket has a corresponding closing bracket in the correct order.
bool isBalancedLogicOne(const string& s) {
    stack<char> st;
    for (char ch : s) {
        if (ch == '(' || ch == '{' || ch == '[') {
            st.push(ch);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (st.empty()) return false;
            char top = st.top();
            if ((ch == ')' && top != '(') ||
                (ch == '}' && top != '{') ||
                (ch == ']' && top != '[')) {
                return false;
            }
            st.pop();
        }
    }
    return st.empty();
}

// 2nd logic to check if brackets are balanced
// This logic uses a map to match closing brackets with their corresponding opening brackets.
bool isBalancedLogicTwo(const string& s) {
    stack<char> st;
    unordered_map<char, char> match = {{')', '('}, {'}', '{'}, {']', '['}};
    for (char ch : s) {
        if (ch == '(' || ch == '{' || ch == '[') {
            st.push(ch);
        } else if (match.count(ch)) {
            if (st.empty() || st.top() != match[ch]) return false;
            st.pop();
        }
    }
    return st.empty();
}
int main() {
    string expr;
    cout << "Enter an expression: ";
    cin >> expr;

    if (isBalancedLogicOne(expr))
        cout << "Balanced" << endl;
    else
        cout << "Not Balanced" << endl;

    if (isBalancedLogicTwo(expr))
        cout << "Balanced" << endl;
    else
        cout << "Not Balanced" << endl;

    return 0;
}