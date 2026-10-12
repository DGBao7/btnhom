#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

double f(double x) { return x * x - 5; }

void bai4() {
    cout << "Bai 4\n";

    double a = 2, b = 3, x = 0;
    const int N = 4;

    cout << fixed << setprecision(6);
    cout << "Xet f(x) = x^2 - 5. f(" << a << ") = " << f(a) << " < 0, f(" << b << ") = " << f(b) << " > 0.\n\n";

    for (int k = 1; k <= N; k++) {
        double m = (a + b) / 2;
        x = m;
        cout << "* Lap " << k << ": x" << k << " = (" << a << " + " << b << ")/2 = " << x << ". ";
        cout << "f(" << x << ") = " << f(x);
        if (k == N) {
            cout << "\n  => x" << N << " = " << x << "\n";
            break;
        }
        if (f(a) * f(x) < 0) {
            b = x;
            cout << (f(x) > 0 ? " > 0" : " < 0") << " => Khoang [" << a << ", " << b << "]\n";
        } else {
            a = x;
            cout << (f(x) > 0 ? " > 0" : " < 0") << " => Khoang [" << a << ", " << b << "]\n";
        }
    }

    double err = (3.0 - 2.0) / pow(2.0, N);
    cout << "\nDanh gia sai so:\n";
    cout << "|x" << N << " - sqrt(5)| <= (3 - 2)/2^" << N << " = " << err << "\n";
}

double phi(double x)  { return cbrt(x + 1000.0); }                          
double dphi(double x) { return 1.0 / (3.0 * pow(x + 1000.0, 2.0 / 3.0)); }  

void bai5() {
    const double eps = 1e-5;

    cout << "Bai 5\n";

    double lo = 9.9, hi = 10.1;
    double q = dphi(lo);   
    double x0 = 10.0;

    cout << fixed << setprecision(8);
    cout << "* Phuong trinh x^3 - x - 1000 = 0 <=> x = (x + 1000)^(1/3) = phi(x)\n";
    cout << "* Khoang phan ly nghiem: phi(10) = " << phi(10.0) << ", chon D = [" << lo << ", " << hi << "]\n";
    cout << "* phi'(x) = 1 / (3 (x + 1000)^(2/3)). Voi x thuoc D: phi'(x) > 0 va\n";
    cout << "  phi'(x) <= phi'(" << lo << ") = " << q << " = q < 1\n";
    cout << "* Chon x0 = " << x0 << ". Cong thuc danh gia sai so :\n";
    cout << "  |xk - alpha| <= q/(1 - q) * |xk - x(k-1)| <= 1e-5\n";
    cout << "* Cac buoc lap:\n";
    cout << "   * x0 = " << x0 << "\n";

    double prev = x0, cur = x0, bound;
    int k = 0;
    do {
        k++;
        cur = phi(prev);
        bound = q / (1 - q) * fabs(cur - prev);
        cout << "   * x" << k << " = " << cur
             << "   |x" << k << " - x" << k - 1 << "| = " << scientific << setprecision(2) << fabs(cur - prev)
             << ", sai so <= " << bound << fixed << setprecision(8) << "\n";
        if (bound <= eps) break;
        prev = cur;
    } while (true);

    cout << "\nThu: |x" << k << " - x" << k - 1 << "| = " << scientific << setprecision(2) << fabs(cur - prev)
         << " => q/(1-q) * |x" << k << " - x" << k - 1 << "| = " << bound << " < 1e-5\n";
    cout << fixed << setprecision(5);
    cout << "Ket luan: x ~ " << cur << "\n";
}

int main() {
    bai4();
    cout << "------------------------------------------------------------\n\n";
    bai5();
    return 0;
}