#include <bits/stdc++.h>
using namespace std;

// PREFIX TO POSTFIX

// funtion to check if character is operator or not
bool isOperator(char x)
{
    switch (x) {
    case '+':
    case '-':
    case '/':
    case '*':
        return true;
    }
    return false;
}
 
// Convert prefix to Postfix expression
string prefixToPostfix(string pre_exp)
{
 
    stack<string> s;
    // length of expression
    int length = pre_exp.size();
 
    // reading from right to left
    for (int i = length - 1; i >= 0; i--)
    {
        // check if symbol is operator
        if (isOperator(pre_exp[i]))
        {
            // pop two operands from stack
            string op1 = s.top();
            s.pop();
            string op2 = s.top();
            s.pop();
 
            // concat the operands and operator
            string temp = op1 + op2 + pre_exp[i];
 
            // Push string temp back to stack
            s.push(temp);
        }
 
        // if symbol is an operand
        else {
 
            // push the operand to the stack
            s.push(string(1, pre_exp[i]));
        }
    }
 
    // stack contains only the Postfix expression
    return s.top();
}

bool isInfix(string exp) // numbers are positive
{
    if (exp.size() && !isOperator(exp.front()) && !isOperator(exp.back()))
        return true;
    return false;
}

// INFIX TO POSTFIX 

bool isOperator22(char c)
{
    return (!isalpha(c) && !isdigit(c));
}

int getPriority(char C)
{
    if (C == '-' || C == '+')
        return 1;
    else if (C == '*' || C == '/')
        return 2;
    else if (C == '^')
        return 3;
    return 0;
}
 
string infixToPostfix(string infix)
{
    infix = '(' + infix + ')';
    int l = infix.size();
    stack<char> char_stack;
    string output;
 
    for (int i = 0; i < l; i++) {
 
        // If the scanned character is an
        // operand, add it to output.
        if (isalpha(infix[i]) || isdigit(infix[i]))
            output += infix[i];
 
        // If the scanned character is an
        // ‘(‘, push it to the stack.
        else if (infix[i] == '(')
            char_stack.push('(');
 
        // If the scanned character is an
        // ‘)’, pop and output from the stack
        // until an ‘(‘ is encountered.
        else if (infix[i] == ')') {
            while (char_stack.top() != '(') {
                output += char_stack.top();
                char_stack.pop();
            }
 
            // Remove '(' from the stack
            char_stack.pop();
        }
 
        // Operator found
        else
        {
            while(!char_stack.empty() && getPriority(infix[i]) < getPriority(char_stack.top()))
            {
                output += char_stack.top();
                char_stack.pop();
            }
            
            // Push current Operator on stack
            char_stack.push(infix[i]);
        }
    }
    while(!char_stack.empty())
        output += char_stack.top();
    return output;
}

// INFIX TO PREFIX
 
string infixToPrefix(string infix)
{
    /* Reverse String
     * Replace ( with ) and vice versa
     * Get Postfix
     * Reverse Postfix  *  */
 
    // Reverse infix
    reverse(infix.begin(), infix.end());
 
    // Replace ( with ) and vice versa
    for (int i = 0; i < infix.size(); i++) {
        if (infix[i] == '(') 
            infix[i] = ')';
        else if (infix[i] == ')') 
            infix[i] = '(';
    }
 
    string prefix = infixToPostfix(infix);
 
    // Reverse postfix
    reverse(prefix.begin(), prefix.end());
 
    return prefix;
}
 
int main()
{
    string s;
    cin >> s;
    if(isInfix(s))
        cout << infixToPrefix(s) << endl;
    else
        cout << prefixToPostfix(s) << endl;
    
    return 0;
}