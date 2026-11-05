#include <bits/stdc++.h>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// f(x) = sin(x)/x, quy ước f(0) = 1
double f(double x) {
    if (fabs(x) < 1e-12) return 1.0;
    return sin(x) / x;
}

// Đạo hàm cấp 2 BẰNG GIẢI TÍCH (lim x->0 = -1/3)
double f2_exact(double x) {
    if (fabs(x) < 1e-6) return -1.0 / 3.0;
    double x2 = x * x;
    double x3 = x2 * x;
    return -sin(x) / x - (2.0 * cos(x)) / x2 + (2.0 * sin(x)) / x3;
}

// Đạo hàm cấp 4 BẰNG GIẢI TÍCH (lim x->0 = 1/5 = 0.2)
double f4_exact(double x) {
    if (fabs(x) < 1e-6) return 0.2;
    double x2 = x * x;
    double x3 = x2 * x;
    double x4 = x3 * x;
    double x5 = x4 * x;
    return sin(x) / x + (4.0 * cos(x)) / x2 - (12.0 * sin(x)) / x3 
           - (24.0 * cos(x)) / x4 + (24.0 * sin(x)) / x5;
}

// Công thức hình thang
double trapezoidal(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));
    for (int i = 1; i < n; i++) sum += f(a + i * h);
    return sum * h;
}

// Công thức Simpson
double simpson(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = f(a) + f(b);
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += (i % 2 == 0 ? 2.0 : 4.0) * f(x);
    }
    return sum * h / 3.0;
}

int main() {
    double a = 0.0, b = 1.0;
    double eps = 3e-4;
    const double exact = 0.9460830703671830;

    // HEADER
    cout << "==================================================================\n";
    cout << " BAI 3:  I = int_0^1 sin(x)/x dx\n";
    cout << "==================================================================\n";
    cout << "Du lieu: a = 0, b = 1, sai so cho phep eps = " 
         << scientific << setprecision(1) << eps << "\n";
    cout << "f(x) = sin(x)/x, quy uoc f(0) = 1 (vi lim x->0 sin(x)/x = 1)\n\n";

    // Y 1 - BUOC 1: Dùng giải tích tìm M2 và M4
    double M2 = 0, M4 = 0;
    double xM2 = 0, xM4 = 0;
    int gridN = 1000;
    for (int i = 0; i <= gridN; i++) {
        double x = a + (b - a) * i / gridN;
        double val2 = fabs(f2_exact(x));
        double val4 = fabs(f4_exact(x));
        if (val2 > M2) { M2 = val2; xM2 = x; }
        if (val4 > M4) { M4 = val4; xM4 = x; }
    }

    cout << "------------------------------------------------------------------\n";
    cout << " Y 1 - BUOC 1: Uoc luong M2 = max|f''(x)| tren [0,1]\n";
    cout << "------------------------------------------------------------------\n";
    // ĐÃ SỬA CÂU CHỮ CHO ĐÚNG BẢN CHẤT GIẢI TÍCH
    cout << "Ta co: f''(x) = -sin(x)/x - 2cos(x)/x^2 + 2sin(x)/x^3\n";
    cout << "Gia tri |f''(x)| tai mot so diem:\n";
    cout << setw(5) << "x" << setw(19) << "|f''(x)|" << "\n";
    cout << fixed << setprecision(6);
    for (int k = 0; k <= 4; k++) {
        double x = a + (b - a) * k / 4.0;
        cout << setw(8) << x << setw(16) << fabs(f2_exact(x)) << "\n";
    }
    cout << "Quet luoi " << gridN << " diem tren [0,1]:\n";
    cout << "  M2 = " << M2 << "  dat tai x = " << xM2
         << "   (giai tich: 1/3 = " << 1.0 / 3 << ")\n\n";

    // Y 1 - BUOC 2
    double c1 = pow(b - a, 3) * M2 / 12.0;
    cout << "------------------------------------------------------------------\n";
    cout << " Y 1 - BUOC 2: Tim n nho nhat de sai so hinh thang < eps\n";
    cout << "------------------------------------------------------------------\n";
    cout << "Cong thuc: |E_T| <= (b-a)^3 * M2 / (12 n^2)\n";
    cout << "         = " << M2 << " / (12 n^2) = " << c1 << " / n^2\n";
    cout << "Can: " << c1 << " / n^2 <= " << scientific << setprecision(1) << eps
         << "  =>  n >= sqrt(" << fixed << setprecision(6) << c1 << " / "
         << scientific << setprecision(1) << eps << ") = "
         << fixed << setprecision(4) << sqrt(c1 / eps) << "\n\n";

    cout << "Thu lan luot n = 1, 2, 3, ... :\n";
    cout << setw(4) << "n" << setw(10) << "h" << setw(18) << "Sai so toi da" << "   Ket luan\n";
    int n = 1;
    while (true) {
        double bound = c1 / ((double)n * n);
        cout << setw(4) << n << fixed << setprecision(4) << setw(10) << (b - a) / n
             << scientific << setprecision(4) << setw(18) << bound
             << (bound <= eps ? "   DAT  <= eps  --> DUNG" : "   chua dat (> eps)") << "\n";
        if (bound <= eps) break;
        n++;
    }
    cout << fixed << setprecision(6);
    cout << "\n==> KET LUAN Y 1: n = " << n << "  (h = " << (b - a) / n << ")\n";
    cout << "    Sai so hinh thang toi da tai n = " << n << ": "
         << scientific << setprecision(4) << c1 / ((double)n * n) << fixed << "\n\n";

    // Y 2
    cout << "------------------------------------------------------------------\n";
    cout << " Y 2: Sai so cong thuc Simpson voi n = " << n << "\n";
    cout << "------------------------------------------------------------------\n";
    if (n % 2 == 0) {
        cout << "Kiem tra: n = " << n << " la so chan --> dung duoc cong thuc Simpson.\n";
    } else {
        n++;
        cout << "n le --> Simpson can n chan, tang n len " << n << ".\n";
    }
    // ĐÃ SỬA CÂU CHỮ CHO ĐÚNG BẢN CHẤT GIẢI TÍCH
    cout << "Tinh M4 = max|f''''(x)| voi f'''' = sin(x)/x + 4cos(x)/x^2 - 12sin(x)/x^3 - 24cos(x)/x^4 + 24sin(x)/x^5 , quet luoi "
         << gridN << " diem:\n";
    cout << "  M4 = " << fixed << setprecision(4) << M4 
         << "  dat tai x = " << xM4 << "   (giai tich: 1/5 = 0.2000)\n";

    double simpsonError = (pow(b - a, 5) * M4) / (180.0 * pow(n, 4));
    cout << "Cong thuc: |E_S| <= (b-a)^5 * M4 / (180 n^4)\n";
    cout << "         = 1 * " << fixed << setprecision(4) << M4 << " / (180 * " << n << "^4)\n";
    cout << "         = " << scientific << setprecision(4) << simpsonError << fixed << "\n";
    cout << "\n==> KET LUAN Y 2: Sai so Simpson tai n = " << n << " la "
         << scientific << setprecision(4) << simpsonError << fixed << "\n\n";

    // Y 3
    double h = (b - a) / n;
    cout << "------------------------------------------------------------------\n";
    cout << " Y 3: Tinh I voi n = " << n << ", h = " << fixed << setprecision(4) << h << "\n";
    cout << "------------------------------------------------------------------\n";

    cout << "Bang cac nut chia:\n";
    cout << setw(4) << "i" << setw(8) << "x_i" << setw(16) << "f(x_i)"
         << setw(10) << "HeSo(T)" << setw(10) << "HeSo(S)" << "\n";
    double sumInner = 0, sumOdd = 0, sumEven = 0;
    for (int i = 0; i <= n; i++) {
        double x = a + i * h;
        double cT = (i == 0 || i == n) ? 0.5 : 1.0;
        int cS = (i == 0 || i == n) ? 1 : (i % 2 == 1 ? 4 : 2);
        cout << setw(4) << i << fixed << setprecision(2) << setw(8) << x
             << setprecision(8) << setw(16) << f(x)
             << setprecision(1) << setw(10) << cT << setw(10) << cS << "\n";
        if (i > 0 && i < n) {
            sumInner += f(x);
            if (i % 2 == 1) sumOdd += f(x); else sumEven += f(x);
        }
    }

    // TỪNG BƯỚC HÌNH THANG
    cout << "\n[HINH THANG]  T = h * [ (f0 + fn)/2 + (f1 + ... + f(n-1)) ]\n";
    cout << fixed << setprecision(8);
    cout << "  (f0 + fn)/2         = (" << f(a) << " + " << f(b) << ")/2 = "
         << 0.5 * (f(a) + f(b)) << "\n";
    cout << "  f1 + ... + f(n-1)   = " << sumInner << "\n";
    cout << "  Tong trong ngoac    = " << 0.5 * (f(a) + f(b)) + sumInner << "\n";
    cout << "  T = " << h << " * " << 0.5 * (f(a) + f(b)) + sumInner << " = "
         << h * (0.5 * (f(a) + f(b)) + sumInner) << "\n";

    // TỪNG BƯỚC SIMPSON
    cout << "\n[SIMPSON]  S = h/3 * [ f0 + fn + 4*(f1+f3+...) + 2*(f2+f4+...) ]\n";
    cout << "  f0 + fn             = " << f(a) + f(b) << "\n";
    cout << "  Tong chi so le      = " << sumOdd << "   --> 4 * " << sumOdd
         << " = " << 4 * sumOdd << "\n";
    cout << "  Tong chi so chan    = " << sumEven << "   --> 2 * " << sumEven
         << " = " << 2 * sumEven << "\n";
    double inside = f(a) + f(b) + 4 * sumOdd + 2 * sumEven;
    cout << "  Tong trong ngoac    = " << inside << "\n";
    cout << "  S = " << h << "/3 * " << inside << " = " << h / 3.0 * inside << "\n";

    // KẾT QUẢ CUỐI CÙNG
    double I_trap = trapezoidal(a, b, n);
    double I_simp = simpson(a, b, n);

    cout << "\n------------------------------------------------------------------\n";
    cout << " KET QUA CUOI CUNG (lam tron 6 chu so thap phan)\n";
    cout << "------------------------------------------------------------------\n";
    cout << fixed << setprecision(6);
    cout << "I (hinh thang) = " << I_trap << "\n";
    cout << "I (Simpson)    = " << I_simp << "\n\n";
    cout << "Doi chieu voi gia tri chinh xac Si(1) = " << setprecision(6) << exact << "\n";
    cout << scientific << setprecision(3);
    cout << "  Sai so thuc te hinh thang |I - T| = " << fabs(exact - I_trap)
         << "  (< eps = 3e-04 ? " << (fabs(exact - I_trap) < eps ? "DUNG" : "SAI") << ")\n";
    cout << "  Sai so thuc te Simpson    |I - S| = " << fabs(exact - I_simp)
         << "  (<= can tren " << setprecision(3) << simpsonError << " ? "
         << (fabs(exact - I_simp) <= simpsonError ? "DUNG" : "SAI") << ")\n";

    return 0;
}