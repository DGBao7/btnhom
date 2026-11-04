#include <iomanip>
#include <iostream>

using namespace std;

const int N = 10;

// Ham so cua Bai 1: f1(x) = 1/(1 + x^2).
double f1(double x) {
    return 1.0 / (1.0 + x * x);
}

// Ham so cua Bai 2: f2(x) = 1/(1 + x).
double f2(double x) {
    return 1.0 / (1.0 + x);
}

// Cong thuc hinh thang hop thanh:
// I_T = h/2 * [y_0 + y_n + 2*(y_1 + ... + y_(n-1))].
// Hai dau mut chi tinh mot lan; cac nut ben trong co he so 2.
double hinhThang(const double y[], double h) {
    double sum = 0.0;
    for (int i = 1; i < N; i++) {
        sum += y[i];
    }
    return h / 2.0 * (y[0] + y[N] + 2.0 * sum);
}

// Cong thuc Simpson hop thanh, yeu cau N la so chan:
// cac nut co chi so le nhan 4, chi so chan ben trong nhan 2.
double simpson(const double y[], double h) {
    double sumLe = 0.0;
    double sumChan = 0.0;
    for (int i = 1; i < N; i++) {
        if (i % 2 == 0) {
            sumChan += y[i];
        } else {
            sumLe += y[i];
        }
    }
    return h / 3.0 * (y[0] + y[N] + 4.0 * sumLe + 2.0 * sumChan);
}

// In cac gia tri y[first], y[first + step], ... de hien thi
// tong cac nut trong phep thay so cua cong thuc.
void inTong(const double y[], int first, int last, int step) {
    for (int i = first; i <= last; i += step) {
        if (i != first) {
            cout << " + ";
        }
        cout << y[i];
    }
}

// Liet ke nut chia x_i va gia tri ham y_i = f(x_i).
void inBangGiaTri(const double x[], const double y[]) {
    cout << "\nBang gia tri cac nut chia:\n";
    cout << "i\t\tx_i\t\tf(x_i)\n";
    for (int i = 0; i <= N; i++) {
        cout << i << "\t\t" << x[i] << "\t\t" << y[i] << "\n";
    }
}

// Giai mot bai tich phan theo ca hai cong thuc.
void giaiBai(const char* tenBai, const char* moTa, double (*f)(double)) {
    const double a = 0.0;
    const double b = 1.0;
    // Chia [a,b] thanh N doan bang nhau, do dai moi doan la h.
    const double h = (b - a) / N;
    double x[N + 1];
    double y[N + 1];

    // Nut thu i nam tai x_i = a + i*h; tinh y_i = f(x_i) tai moi nut.
    for (int i = 0; i <= N; i++) {
        x[i] = a + i * h;
        y[i] = f(x[i]);
    }

    cout << tenBai << "\n";
    cout << "* " << moTa << "\n";
    cout << "* Khoang lay tich phan: [" << a << ", " << b << "], n = " << N
         << ", h = (b - a)/n = " << h << "\n";
    inBangGiaTri(x, y);

    // Tinh va trinh bay tung thanh phan cua cong thuc hinh thang.
    const double ketQuaHinhThang = hinhThang(y, h);
    cout << "\n1. Cong thuc hinh thang:\n";
    cout << "   I_T = h/2 * [f(x_0) + f(x_n) + 2*(f(x_1) + ... + f(x_(n-1)))]\n";
    cout << "   I_T = " << h / 2.0 << " * [" << y[0] << " + " << y[N]
         << " + 2*(";
    inTong(y, 1, N - 1, 1);
    cout << ")]\n";
    cout << "   I_T = " << ketQuaHinhThang << "\n";

    // Tinh va trinh bay cac tong nut le, nut chan trong cong thuc Simpson.
    const double ketQuaSimpson = simpson(y, h);
    cout << "\n2. Cong thuc Simpson (n = " << N << " la so chan):\n";
    cout << "   I_S = h/3 * [f(x_0) + f(x_n) + 4*Tong cac chi so le"
         << " + 2*Tong cac chi so chan]\n";
    cout << "   I_S = " << h / 3.0 << " * [" << y[0] << " + " << y[N]
         << " + 4*(";
    inTong(y, 1, N - 1, 2);
    cout << ") + 2*(";
    inTong(y, 2, N - 2, 2);
    cout << ")]\n";
    cout << "   I_S = " << ketQuaSimpson << "\n";

}

// Danh gia sai so tien nghiem bang dao ham bac hai va bac bon tren [a,b].
void inDanhGiaSaiSo(const char* moTaDaoHamBac2, double M2,
                    const char* moTaDaoHamBac4, double M4) {
    const double a = 0.0;
    const double b = 1.0;
    const double h = (b - a) / N;
    const double saiSoHinhThang = (b - a) * h * h * M2 / 12.0;
    const double saiSoSimpson = (b - a) * h * h * h * h * M4 / 180.0;

    cout << "\n3. Danh gia sai so ly thuyet:\n";
    cout << "   " << moTaDaoHamBac2 << "\n";
    cout << "   |E_T| <= (b-a)*h^2*M2/12 = "
         << (b - a) << "*" << h << "^2*" << M2 << "/12 = "
         << saiSoHinhThang << "\n";
    cout << "   " << moTaDaoHamBac4 << "\n";
    cout << "   |E_S| <= (b-a)*h^4*M4/180 = "
         << (b - a) << "*" << h << "^4*" << M4 << "/180 = "
         << saiSoSimpson << "\n";
}

int main() {
    cout << fixed << setprecision(8);
    // Bai 1 chi tinh gan dung tich phan, khong in phan danh gia sai so.
    giaiBai("Bai 1",
            "Tinh I1 = tich phan tu 0 den 1 cua 1/(1 + x^2) dx.",
            f1);

    cout << "\n------------------------------------------------------------\n\n";

    // Với bài 2, max |f2''(x)| = 2 và max |f2''''(x)| = 24 trên [0,1].
    giaiBai("Bai 2",
            "Tinh I2 = tich phan tu 0 den 1 cua 1/(1 + x) dx.",
            f2);
    inDanhGiaSaiSo(
        "f''(x) = 2/(1 + x)^3; M2 = max|f''(x)| = 2 tai x = 0.",
        2.0,
        "f''''(x) = 24/(1 + x)^5; M4 = max|f''''(x)| = 24 tai x = 0.",
        24.0);
    return 0;
}