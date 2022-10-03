#include <string>
#include "arithmetic.h"


using namespace std;

void reverseStr(string &a) {
    char temp;
    for (int i = 0; i < a.length() / 2; ++i) {
        temp = a[i];
        a[i] = a[a.length() - 1 - i];
        a[a.length() - 1 - i] = temp;
    }
}

bool isZero(string a) {
    for (int i = 0; i < a.length(); ++i) {
        if (a[i] != '0') {
            return false;
        }
    }
    return true;
}

int dealWithE(string &a) {
    int n = 0;
    for (int i = 0; i < a.length(); ++i) {
        if (a[i] == 'e') {
            n = i;
            break;
        }
    }
    if (n > 0) {
        string result = a.substr(0, n);
        a = a.substr(n + 1);
        reverseStr(result);
        return stoi(result);
    } else {
        return 0;
    }
}

void addPoint(string &c, int cl, int cn) {
    if (cn > 0) {
        if (cl - cn > 0) {
            c = c.insert(cl - cn, ".");
        } else {
            char bw[40000] = {0};
            for (int i = 0; i < cn - cl + 2; ++i) {
                if (i == 1) {
                    bw[i] = '.';
                } else {
                    bw[i] = '0';
                }
            }
            c = bw + c;
        }
        for (int i = c.length() - 1; i >= 0; --i) {
            if (c[i] == '0') {
                c.erase(i, 1);
            } else if (c[i] == '.') {
                c = c.substr(0, i);
                break;
            } else {
                break;
            }
        }
    } else if (cn < 0) {
        char bw[40000] = {0};
        for (int i = 0; i < -cn; ++i) {
            bw[i] = '0';
        }
        c.append(bw);
    }
}

int toIntStr(string &a) {
    int n = 0;
    for (int i = 0; i < a.length(); ++i) {
        if (a[i] == '.') {
            n = i;
            a.erase(n, 1);
            break;
        }
    }
    return n;
}

string int_pls(string a, string b) {
    int al = a.length();
    int bl = b.length();
    char c[40000] = {0};
    for (int i = 0; i < al + bl; ++i) {
        c[i] += (i >= al ? 0 : (a[i] - '0')) + (i >= bl ? 0 : (b[i] - '0'));
        c[i + 1] += c[i] / 10;
        c[i] %= 10;
    }
    for (int i = 0; i < al + bl; ++i) {
        c[i] += '0';
    }
    return c;
}

string int_mul(string a, string b) {
    int al = a.length();
    int bl = b.length();
    char c[40000] = {0};

    for (int i = 0; i < al; ++i) {
        for (int j = 0; j < bl; ++j) {
            c[i + j] += (a[i] - '0') * (b[j] - '0');
            c[i + j + 1] += c[i + j] / 10;
            c[i + j] %= 10;
        }
    }
    for (int i = 0; i < al + bl; ++i) {
        c[i] += '0';
    }
    return c;
}

string pls(string a, string b) {
    reverseStr(a);
    reverseStr(b);
    int an = toIntStr(a);
    int bn = toIntStr(b);
    int n = max(an, bn);
    if (an > bn) {
        string bw = string(an - bn, '0');
        b = bw.append(b);
    } else if (bn > an) {
        string bw = string(bn - an, '0');
        a = bw.append(a);
    }
    string c = int_pls(a, b);
    int cl = 0;
    for (int i = a.length() + b.length() - 1; i >= 0; --i) {
        if (c[i] != '0') {
            cl = i + 1;
            break;
        }
    }
    c = c.substr(0, cl);
    reverseStr(c);
    addPoint(c, cl, n);
    return c;
}

string mul(string a, string b) {
    reverseStr(a);
    reverseStr(b);
    int ae = dealWithE(a);
    int be = dealWithE(b);
    int ce = ae + be;
    int an = toIntStr(a);
    int bn = toIntStr(b);

    if (isZero(a) || isZero(b)) {
        return "0";
    }

    int cn = an + bn;
    string c = int_mul(a, b);
    int cl = 0;
    for (int i = a.length() + b.length() - 1; i >= 0; --i) {
        if (c[i] != '0') {
            cl = i + 1;
            break;
        }
    }

    c = c.substr(0, cl);
    reverseStr(c);

    if (cn - cl - ce > 5 || cl - cn + ce > 5) {
        ce += cl - cn - 1;
        cn = cl - 1;
    } else {
        cn -= ce;
        ce = 0;
    }
    addPoint(c, cl, cn);
    if (ce != 0) {
        return c + "e" + to_string(ce);
    } else {
        return c;
    }
}




