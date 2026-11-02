#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// Ham f(x) = x^2 - 5, dung cho bai 4:
// tim nghiem cua phuong trinh x^2 - 5 = 0 trong khoang [2,3]
 double f(double x) { return x * x - 5; }

// Bai 4: Giai phuong trinh x^2 - 5 = 0 bang phuong phap chia doi
void bai4() {
    cout << "Bai 4\n";

    // Khoang ban dau [a, b], trong do ham f(x) doi dau:
    // f(2) < 0 va f(3) > 0 nen co it nhat mot nghiem trong [2,3]
    double a = 2, b = 3, x = 0;
    const int N = 4;  // So lan lap

    cout << fixed << setprecision(6);
    cout << "Xet f(x) = x^2 - 5. f(" << a << ") = " << f(a) << " < 0, f(" << b << ") = " << f(b) << " > 0.\n\n";

    // Voi moi lan lap:
    // - tim trung diem m = (a + b)/2
    // - xac dinh xem nghiem nam o nua khoang nao
    // - cap nhat [a,b] theo dau cua f(a)*f(x)
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
            // Nghiem o [a, x], nen cap nhat b = x
            b = x;
            cout << (f(x) > 0 ? " > 0" : " < 0") << " => Khoang [" << a << ", " << b << "]\n";
        } else {
            // Nghiem o [x, b], nen cap nhat a = x
            a = x;
            cout << (f(x) > 0 ? " > 0" : " < 0") << " => Khoang [" << a << ", " << b << "]\n";
        }
    }

    // Sai so danh gia sau N lan lap trong phuong phap chia doi:
    // |xN - alpha| <= (b - a)/2^N
    double err = (3.0 - 2.0) / pow(2.0, N);
    cout << "\nDanh gia sai so:\n";
    cout << "|x" << N << " - sqrt(5)| <= (3 - 2)/2^" << N << " = " << err << "\n";
}

// Bai 5: Giai phuong trinh x^3 - x - 1000 = 0
// Dua ve dang x = phi(x) voi phi(x) = (x + 1000)^(1/3)
// va su dung phuong phap lap (iteration fixed-point)

// Ham bien doi x = (x + 1000)^(1/3)
double phi(double x)  { return cbrt(x + 1000.0); }

// Dao ham cua phi(x): phi'(x) = 1 / (3*(x + 1000)^(2/3))
double dphi(double x) { return 1.0 / (3.0 * pow(x + 1000.0, 2.0 / 3.0)); }

void bai5() {
    const double eps = 1e-5;  // do chinh xac yeu cau

    cout << "Bai 5\n";

    // Chon khoang [9.9, 10.1] quanh gia tri 10 de dam bao phep lap hoi tu
    double lo = 9.9, hi = 10.1;
    double q = dphi(lo);   // q la mot chặn cho |phi'(x)| tren khoang duoc chon
    double x0 = 10.0;      // gia tri xuat phat

    cout << fixed << setprecision(8);
    cout << "* Phuong trinh x^3 - x - 1000 = 0 <=> x = (x + 1000)^(1/3) = phi(x)\n";
    cout << "* Khoang phan ly nghiem: phi(10) = " << phi(10.0) << ", chon D = [" << lo << ", " << hi << "]\n";
    cout << "* phi'(x) = 1 / (3 (x + 1000)^(2/3)). Voi x thuoc D: phi'(x) > 0 va\n";
    cout << "  phi'(x) <= phi'(" << lo << ") = " << q << " = q < 1\n";
    cout << "* Chon x0 = " << x0 << ". Cong thuc danh gia sai so :\n";
    cout << "  |xk - alpha| <= q/(1 - q) * |xk - x(k-1)| <= 1e-5\n";
    cout << "* Cac buoc lap:\n";
    cout << "   * x0 = " << x0 << "\n";

    // prev: x_{k-1}; cur: x_k
    double prev = x0, cur = x0, bound;
    int k = 0;
    do {
        k++;
        cur = phi(prev);  // cong thuc lap: x_k = phi(x_{k-1})
        bound = q / (1 - q) * fabs(cur - prev);
        cout << "   * x" << k << " = " << cur
             << "   |x" << k << " - x" << k - 1 << "| = " << scientific << setprecision(2) << fabs(cur - prev)
             << ", sai so <= " << bound << fixed << setprecision(8) << "\n";
        if (bound <= eps) break; // dung lai khi sai so da duoi muc yeu cau
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