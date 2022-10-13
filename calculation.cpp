//
// Created by Wang on 2/10/2022.
//
#include <string>
#include "arithmetic.h"
#include "calculation.h"

using namespace std;

//validity judgment has a lot of room for improvement
bool IsValid(string &s) {
    for (char i: s) {
        if (i > '9' && i != 'e' || i < '0' && i != '.' && i != '-') {
            return false;
        }
    }
    return true;
}

string Calculate(string s, string names[], string values[], int n) {
    s.erase(0, s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
    if (s.empty()) {
        return s;
    }
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
                s.replace(left, i - left + 1, Calculate(s.substr(left + 1, i - left - 1), names, values, n));
            }
        } else {
            if (s[i] == ')') {
                cnt--;
            }
        }
    }

    int m = s.find("--");
    while (m != string::npos) {
        if (m == 0) {
            s.erase(0, 2);
            m = s.find("--");
        } else {
            s.replace(m, 2, "+");
            m = s.find("--");
        }
    }

    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '+') {
            string s1 = Calculate(s.substr(0, i), names, values, n);
            string s2 = Calculate(s.substr(i + 1), names, values, n);
            if (s1[0] == 'E' || s2[0] == 'E' || s1.empty() || s2.empty()) {
                return "E";
            } else {
                return Pls(s1, s2);
            }
        }
    }
    for (int i = s.length() - 1; i >= 0; --i) {
        if (s[i] == '-') {
            if (s[i - 1] != '*' && s[i - 1] != '/') {
                string s1 = Calculate(s.substr(0, i), names, values, n);
                string s2 = Calculate(s.substr(i + 1), names, values, n);
                if (s1[0] == 'E' || s2[0] == 'E' || s2.empty()) {
                    return "E";
                } else {
                    return Mns(s1, s2);
                }
            }
        }
    }
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '*') {
            string s1 = Calculate(s.substr(0, i), names, values, n);
            string s2 = Calculate(s.substr(i + 1), names, values, n);
            if (s1[0] == 'E' || s2[0] == 'E' || s1.empty() || s2.empty()) {
                return "E";
            } else {
                return Mul(s1, s2);
            }
        }
    }
    for (int i = s.length() - 1; i >= 0; --i) {
        if (s[i] == '/') {
            string s1 = Calculate(s.substr(0, i), names, values, n);
            string s2 = Calculate(s.substr(i + 1), names, values, n);
            if (s1[0] == 'E' || s2[0] == 'E' || s1.empty() || s2.empty()) {
                return "E";
            } else {
                return Div(s1, s2);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (s == names[i]) {
            return values[i];
        }
    }
    if (IsValid(s)) {
        return s;
    } else {
        return "E";
    }
}