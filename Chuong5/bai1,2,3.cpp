#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;

// ---------- Bai 1: x - 0.5 sin x = 0.25  <=>  x = phi(x) = 0.25 + 0.5 sin x ----------
double phi(double x) { return 0.25 + 0.5 * sin(x); }

// ---------- Bai 2, 3: f(x) = x^3 - x - 1 ----------
double f(double x)   { return x * x * x - x - 1.0; }
double df(double x)  { return 3.0 * x * x - 1.0; }

// Nghiem chinh xac (Newton nhieu buoc) de danh gia sai so thuc te
double nghiemChinhXac(double x0) {
    for (int i = 0; i < 100; i++) x0 -= f(x0) / df(x0);
    return x0;
}

void bai1() {
    cout << "===== BAI 1: phuong phap lap don =====\n";
    double x = 0.25, q = 0.5;           // x0 = 0.25, |phi'(x)| = |0.5 cos x| <= 0.5 = q
    double x0 = x, x1 = phi(x0);
    cout << "x0 = " << x0 << "\n";
    x = x0;
    for (int k = 1; k <= 4; k++) {
        x = phi(x);
        cout << "x" << k << " = " << x << "\n";
    }
    double sai_so = pow(q, 4) / (1 - q) * fabs(x1 - x0);   // |x4-a| <= q^4/(1-q) |x1-x0|
    double a = x;                                           // nghiem "chinh xac" bang lap them
    for (int i = 0; i < 200; i++) a = phi(a);
    cout << "q = " << q << ", |x1-x0| = " << fabs(x1 - x0) << "\n";
    cout << "Danh gia tien nghiem: |x4 - alpha| <= " << sai_so << "\n";
    cout << "Nghiem (lap them)    : alpha = " << a << ", |x4 - alpha| thuc te = " << fabs(x - a) << "\n\n";
}

void bai2() {
    cout << "===== BAI 2: phuong phap chia doi tren [1,2] =====\n";
    double a = 1, b = 2, x = 0;
    double alpha = nghiemChinhXac(1.5);
    for (int k = 1; k <= 4; k++) {
        x = (a + b) / 2;
        cout << "k=" << k << ": [a,b] = [" << a << ", " << b << "], x" << k << " = " << x
             << ", f(x" << k << ") = " << f(x) << "\n";
        if (f(a) * f(x) < 0) b = x; else a = x;
    }
    double sai_so = (2.0 - 1.0) / pow(2, 4);
    cout << "Danh gia: |x4 - alpha| <= (b-a)/2^4 = " << sai_so << "\n";
    cout << "alpha = " << alpha << ", |x4 - alpha| thuc te = " << fabs(x - alpha) << "\n\n";
}

void bai3() {
    cout << "===== BAI 3: phuong phap day cung tren [1,2] =====\n";
    // f' > 0, f'' = 6x > 0 tren [1,2]; f(2)*f''>0 nen co dinh d = 2, x0 = 1
    double d = 2, x = 1, xPrev = 1;
    double m1 = df(1), M1 = df(2);       // f' tang: min = f'(1), max = f'(2)
    double alpha = nghiemChinhXac(1.5);
    cout << "d = " << d << ", x0 = " << x << ", m1 = " << m1 << ", M1 = " << M1 << "\n";
    for (int k = 1; k <= 4; k++) {
        xPrev = x;
        x = x - f(x) * (d - x) / (f(d) - f(x));
        cout << "x" << k << " = " << x << ", f(x" << k << ") = " << f(x) << "\n";
    }
    double s1 = (M1 - m1) / m1 * fabs(x - xPrev);   // cong thuc hau nghiem
    double s2 = fabs(f(x)) / m1;                     // |x - alpha| <= |f(x)|/m1
    cout << "Danh gia hau nghiem: |x4 - alpha| <= (M1-m1)/m1 * |x4-x3| = " << s1 << "\n";
    cout << "Danh gia |f(x4)|/m1 = " << s2 << "\n";
    cout << "alpha = " << alpha << ", |x4 - alpha| thuc te = " << fabs(x - alpha) << "\n";
}

int main() {
    cout << fixed << setprecision(8);
    bai1(); bai2(); bai3();
    return 0;
}
