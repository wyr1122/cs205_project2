//
// Created by Wang on 2/10/2022.
//
#include <string>
#include "arithmetic.h"
#include "calculation.h"

using namespace std;

bool IsValid(string &s) {
    for (char i: s) {
        if (i > '9' && i != 'e' || i < '0' && i != '.' && i != '-') {
            return false;
        }
    }
    return true;
}

string Calculate(string s, char name[kVariableNum][kVariableNameLimit], char value[kVariableNum][kLineLimit], int n) {
    s.erase(0, s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);

    int left;
    int cnt = 0;
    for (int i = 0; i < s.length(); ++i) {
        if (cnt == 0) {
            if (s[i] == '(') {
                cnt = 1;
                left = i;
            }
        } else if (cnt == 1) {
            if (s[i] == '(') {
                cnt++;
            }
            if (s[i] == ')') {
                cnt = 0;
                s.replace(left, i - left + 1, Calculate(s.substr(left + 1, i - left - 1), name, value, n));
            }
        } else {
            if (s[i] == ')') {
                cnt--;
            }
        }
    }
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '+') {
            string s1 = Calculate(s.substr(0, i), name, value, n);
            string s2 = Calculate(s.substr(i + 1), name, value, n);
            if (s1[0] == 'E' || s2[0] == 'E') {
                return "E";
            } else {
                return Pls(s1, s2);
            }
        }
    }
    for (int i = 1; i < s.length(); ++i) {
        if (s[i] == '-') {
            string s1 = Calculate(s.substr(0, i), name, value, n);
            string s2 = Calculate(s.substr(i + 1), name, value, n);
            if (s1[0] == 'E' || s2[0] == 'E') {
                return "E";
            } else {
                return Mns(s1, s2);
            }
        }
    }
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '*') {
            string s1 = Calculate(s.substr(0, i), name, value, n);
            string s2 = Calculate(s.substr(i + 1), name, value, n);
            if (s1[0] == 'E' || s2[0] == 'E') {
                return "";
            } else {
                return Mul(s1, s2);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (std::equal(s.begin(), s.end(), name[i])) {
            return value[i];
        }
    }
    if (IsValid(s)) {
        return s;
    } else {
        return "E";
    }
}