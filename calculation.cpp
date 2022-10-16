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
    int space = s.find(' ');
    while (space != string::npos) {
        s.erase(space, 1);
        space = s.find(' ');
    }
    if (s.empty()) {
        return s;
    }
    //Matching parentheses recursion
    int left;
    int bracket = s.find('(');
    while (bracket != string::npos) {
        int cnt = 1;
        left = bracket;
        for (int i = bracket + 1; i < s.length(); ++i) {
            if (s[i] == '(') {
                cnt++;
            } else if (s[i] == ')') {
                if (cnt == 1) {
                    cnt = 0;
                    s.replace(left, i - left + 1, Calculate(s.substr(left + 1, i - left - 1), names, values, n));
                    break;
                } else {
                    cnt--;
                }
            }
        }
        if (cnt != 0) {
            return "E";
        }
        bracket = s.find('(');
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
        bool neg_sign = false;
        if (s[i] == '-') {
            if (s[i - 1] != '*' && s[i - 1] != '/' && s[i - 1] != 'e') {
                for (int j = 0; j < kFunctionNum; ++j) {
                    int begin = i - kFunctions[j].length();
                    if (begin < 0) {
                        continue;
                    } else if (s.substr(begin, kFunctions[j].length()) == kFunctions[j]) {
                        neg_sign = true;
                    }
                }
                if (!neg_sign) {
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
    //return function value (calculate one-parameter function here)
    for (int i = 0; i < kFunctionNum; ++i) {
        int m = s.find(kFunctions[i]);
        if (m == 0) {
            string input = Calculate(s.substr(kFunctions[i].length()), names, values, n);
            if (input == "E") {
                return "E";
            }
            if (kFunctions[i] == "sqrt") {
                return Sqrt(input);
            }
        }
    }
    //return variable value
    for (int i = 0; i < n; ++i) {
        if (s == names[i]) {
            return values[i];
        }
    }
    //validity judgment and return
    if (IsValidValue(s)) {
        return s;
    } else {
        return "E";
    }
}
