#include <iostream>
#include <cmath>
using namespace std;

//phuong trinh bai 1
double f1(double x) {
    return 1 / (1 + x * x);
}
//phuong trinh bai 2
double f2(double x) {
    if (x == -1) {
        return 0;
    }
    return 1 / (1 + x);
}
// Sai so ham hinh thang: |E_T| <= (b-a) * h^2 * M2 / 12
// voi h = (b-a)/n va M2 = max |f''(x)| tren [a,b]
double saiSoHinhThang(double a, double b, int n = 10) {
    double h = (b - a) / (double) n;
    double M2 = 0.0;
    const int N = 100000;
    for (int i = 0; i <= N; i++) {
        double x = a + (b - a) * i / (double) N;
        double val = fabs(2.0 / pow(1.0 + x, 3.0));
        if (val > M2) M2 = val;
    }
    return (b - a) * h * h * M2 / 12.0;
}

// Sai so Simson: |E_S| <= (b-a) * h^4 * M4 / 180
// voi h = (b-a)/n va M4 = max |f''''(x)| tren [a,b]
double saiSoSimpSon(double a, double b, int n = 10) {
    double h = (b - a) / (double) n;
    double M4 = 0.0;
    const int N = 100000;
    for (int i = 0; i <= N; i++) {
        double x = a + (b - a) * i / (double) N;
        double val = fabs(24.0 / pow(1.0 + x, 5.0));
        if (val > M4) M4 = val;
    }
    return (b - a) * h * h * h * h * M4 / 180.0;
}

//cong thuc hinh thang
double hinhthang(double b, double a, double x[], double y[], int n) {
    double h = (b - a) / (double) n;
    double sum1 = 0;
    for (int i = 1; i < n; i++) {
        sum1 += y[i];
    }
    double IT = (h / 2) * ((y[0] + y[n]) + 2 * sum1);

    return IT;
}

//cong thuc simpson
double simpson(double b, double a, double x[], double y[], int n) {
    double h = (b - a) / (double) n;
    double sum1 = 0, sum2 = 0;
    for (int i = 1; i < n; i++) {
        if (i % 2 == 0) {
            sum2 += y[i];
        } else {
            sum1 += y[i];
        }
    }
    double IS = (h / 3) * ((y[0] + y[n]) + 4 * sum1 + 2 * sum2);

    return IS;
}


int main() {
    cout << "Bai 1" << endl;
    double b = 1.0;
    double a = 0.0;
    double x[] = {0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
    double *y = new double[11];
    for (int i = 0; i < 11; i++) {
        y[i] = f1(x[i]);
    }
    double hinhthang1 = hinhthang(b, a, x, y, 10);
    cout << "Ket qua cong thuc hinh thang: " << hinhthang1 << endl;
    double simpson1 = simpson(b, a, x, y, 10);
    cout << "Ket qua cong thuc simpson: " << simpson1 << endl;

    cout << "Bai 2" << endl;
    double *z = new double[11];
    for (int i = 0; i < 11; i++) {
        z[i] = f2(x[i]);
    }
    double hinhthang2 = hinhthang(b, a, x, z, 10);
    cout << "Ket qua cong thuc hinh thang: " << hinhthang2 << endl;
    double errorHinhThang = saiSoHinhThang(a, b, 10);
    cout << "Sai so cong thuc hinh thang: " << errorHinhThang << endl;

    double simpson2 = simpson(b, a, x, z, 10);
    cout << "Ket qua cong thuc simpson: " << simpson2 << endl;
    double errorSimpson = saiSoSimpSon(a, b, 10);
    cout << "Sai so cong thuc simpson: " << errorSimpson << endl;

    delete[] y;
    delete[] z;
    return 0;
}