#include <string>
#include <cstring>
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
            string bw = {};
            for (int i = 0; i < cn - cl + 2; ++i) {
                if (i == 1) {
                    bw.append(".");
                } else {
                    bw.append("0");
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
        for (int i = 0; i < -cn; ++i) {
            c.append("0");
        }
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

void align(string &a, string &b, int an, int bn) {

    if (an > bn) {
        string bw = string(an - bn, '0');
        b = bw.append(b);
    } else if (bn > an) {
        string bw = string(bn - an, '0');
        a = bw.append(a);
    }
    int al = a.length();
    int bl = b.length();
    if (al > bl) {
        b.append(string(al - bl, '0'));
    } else if (bl > al) {
        a.append(string(bl - al, '0'));
    }
}

string int_pls(string a, string b) {
    int al = a.length();
    int cl = al + 1;
    char c[cl + 1];
    memset(c, 0, cl);
    for (int i = 0; i < al; ++i) {
        c[i] += (a[i] - '0') + (b[i] - '0');
        c[i + 1] += c[i] / 10;
        c[i] %= 10;
    }
    for (int i = 0; i < cl; ++i) {
        c[i] += '0';
    }
    c[cl] = 0;
    return c;
}

string int_mns(string a, string b) {
    int al = a.length();
    int cl = al + 2;
    char c[cl + 1];
    memset(c, 0, cl);
    bool neg = false;
    for (int i = 0; i < al; ++i) {
        if (a[i] > b[i]) {
            break;
        } else if (a[i] < b[i]) {
            neg = true;
            break;
        }
    }
    if (neg) {
        swap(a, b);
    }
    for (int i = 0; i < al; ++i) {
        c[i] += 10 + (a[i] - '0') - (b[i] - '0');
        c[i + 1] += c[i] / 10 - 1;
        c[i] %= 10;
    }
    for (int i = 0; i < cl - 1; ++i) {
        c[i] += '0';
    }
    if (neg) {
        c[cl - 1] = '-';
    } else {
        c[cl - 1] = 0;
    }
    c[cl] = 0;
    return c;
}

string int_mul(string a, string b) {
    int al = a.length();
    int bl = b.length();
    char c[al + bl + 1];
    memset(c, 0, al + bl);
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
    c[al + bl] = 0;
    return c;
}

string pls(string a, string b) {
    reverseStr(a);
    reverseStr(b);
    int al = a.length();
    int bl = b.length();
    bool aNeg = a[al - 1] == '-';
    bool bNeg = b[bl - 1] == '-';
    if (aNeg)
        a.erase(al - 1, 1);
    if (bNeg)
        b.erase(bl - 1, 1);
    int an = toIntStr(a);
    int bn = toIntStr(b);
    int n = max(an, bn);
    align(a, b, an, bn);
    bool neg = false;
    string c;
    if (aNeg && bNeg) {
        c = int_pls(a, b);
        c.append("-");
    } else if (bNeg) {
        c = int_mns(a, b);
    } else if (aNeg) {
        c = int_mns(b, a);
    } else {
        c = int_pls(a, b);
    }
    if (isZero(c)) {
        return "0";
    }
    int cl = 0;
    for (int i = c.length() - 1; i >= 0; --i) {
        if (c[i] == '-') {
            neg = true;
        } else if (c[i] != '0') {
            cl = i + 1;
            break;
        }
    }
    c = c.substr(0, cl);
    reverseStr(c);
    addPoint(c, cl, n);
    if (neg) {
        c.insert(0, "-");
    }
    return c;
}

string mns(string a, string b) {
    if (b[0] == '-') {
        b.erase(0, 1);
    } else {
        b.insert(0, "-");
    }
    return pls(a, b);
}


string mul(string a, string b) {
    reverseStr(a);
    reverseStr(b);
    bool aNeg = a[a.length() - 1] == '-';
    bool bNeg = b[b.length() - 1] == '-';
    if (aNeg)
        a.erase(a.length() - 1, 1);
    if (bNeg)
        b.erase(b.length() - 1, 1);
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
    for (int i = c.length() - 1; i >= 0; --i) {
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
    if (aNeg && !bNeg || !aNeg && bNeg) {
        c.insert(0, "-");
    }
    if (ce != 0) {
        return c + "e" + to_string(ce);
    } else {
        return c;
    }
}




