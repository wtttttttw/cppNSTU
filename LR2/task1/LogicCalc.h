#pragma once
#include "stack.h"
#include <string>

using namespace std;

class LogicCalc {
private:
    static int prec(char op) {
        if (op == '!') return 3;
        if (op == '&') return 2;
        if (op == '|') return 1;
        if (op == '^') return 1;
        return 0;
    }

    static bool applyOp(char op, MyStack<int>& vals) {
        if (op == '!') {
            if (vals.empty()) return false;
            int a = vals.pop();
            vals.push(!a);
            return true;
        }
        if (vals.getSize() < 2) return false;
        int b = vals.pop();
        int a = vals.pop();
        int r = 0;
        if      (op == '&') r = a & b;
        else if (op == '|') r = a | b;
        else if (op == '^') r = a ^ b;
        vals.push(r);
        return true;
    }

public:
    static int evaluate(const string& expr) {
        MyStack<int>  vals;
        MyStack<char> ops;

        for (char c : expr) {
            if (c == ' ' || c == '\t') continue;

            if (c == '0' || c == '1') {
                vals.push(c - '0');
            }
            else if (c == '(') {
                ops.push(c);
            }
            else if (c == ')') {
                while (!ops.empty() && ops.peek() != '(') {
                    if (!applyOp(ops.pop(), vals)) return -1;
                }
                if (ops.empty()) return -1;
                ops.pop();
            }
            else if (c == '!' || c == '&' || c == '|' || c == '^') {
                while (!ops.empty() && ops.peek() != '(' &&
                       (c == '!' ? prec(ops.peek()) >  prec(c)
                                 : prec(ops.peek()) >= prec(c))) {
                    if (!applyOp(ops.pop(), vals)) return -1;
                }
                ops.push(c);
            }
            else {
                return -1;
            }
        }

        while (!ops.empty()) {
            if (ops.peek() == '(') return -1;
            if (!applyOp(ops.pop(), vals)) return -1;
        }
        if (vals.getSize() != 1) return -1;
        return vals.pop();
    }
};
