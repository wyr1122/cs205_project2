#include <iostream>
#include <cstring>

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
    string result = c.substr(0);

    if (cn - cl - ce > 5 || cl - cn + ce > 5) {
        ce += cl - cn - 1;
        cn = cl - 1;
    } else {
        cn -= ce;
        ce = 0;
    }

    if (cn > 0) {
        if (cl - cn > 0) {
            result = result.substr(0, cl - cn) + "." + c.substr(cl - cn);
        } else {
            char bw[40000] = {0};
            for (int i = 0; i < cn - cl + 2; ++i) {
                if (i == 1) {
                    bw[i] = '.';
                } else {
                    bw[i] = '0';
                }
            }
            result = bw + result;
        }
        for (int i = result.length() - 1; i >= 0; --i) {
            if (result[i] == '0') {
                result.erase(i, 1);
            } else if (result[i] == '.') {
                result = result.substr(0, i);
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
        result.append(bw);
    }
    if (ce != 0) {
        return result + "e" + to_string(ce);
    } else {
        return result;
    }
}

int main() {
    string a, b;
    cin >> a >> b;
    cout << mul(a, b);
}




