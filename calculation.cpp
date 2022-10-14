//
// Created by Wang on 2/10/2022.
//
#include <string>
#include "arithmetic.h"
#include "calculation.h"

using namespace std;

//validity judgment has a lot of room for improvement
bool IsValidValue(string s) {
    int pointCnt = 0;
    int eCnt = 0;
    for (char i: s) {
        if (i > '9' && i != 'e' || i < '0' && i != '.' && i != '-') {
            return false;
        } else if (i == '.') {
            pointCnt++;
        } else if (i == 'e') {
            eCnt++;
        }
        if (pointCnt > 1 || eCnt > 1) {
            return false;
        }
    }
    return true;
}

bool IsValidVariableName(string s) {
    for (char i: s) {
        if (!(i >= 'a' && i <= 'z' || i >= 'A' && i <= 'Z' || i == '_')) {
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
    //Matching parentheses recursion
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
    //Deal with minus
    int m = s.rfind("--");
    while (m != string::npos) {
        if (m == 0) {
            s.erase(0, 2);
            m = s.rfind("--");
        } else {
            s.replace(m, 2, "+");
            m = s.rfind("--");
        }
    }
    //Addition recursion
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
    //Subtraction recursion
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
    //Multiplication recursion
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
    //Division recursion
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
    //return variable value
    for (int i = 0; i < n; ++i) {
        if (s == names[i]) {
            return values[i];
        }
    }
    //return function value (calculate one-parameter function here)
    for (int i = 0; i < kFunctions->length(); ++i) {
        int m = s.find(kFunctions[i]);
        if (m == 0) {
            if (kFunctions[i] == "sqrt") {
                return Sqrt(Calculate(s.substr(kFunctions[i].length()), names, values, n));
            }
        }
    }
    //validity judgment and return
    if (IsValidValue(s)) {
        return s;
    } else {
        return "E";
    }
}