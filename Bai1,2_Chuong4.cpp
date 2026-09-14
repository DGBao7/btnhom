#include <iostream>
using namespace std;
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
        y[i] = 1 / (1 + x[i] * x[i]);
    }
    double hinhthang1 = hinhthang(b, a, x, y, 10);
    cout << "Ket qua cong thuc hinh thang: " << hinhthang1 << endl;
    double simpson1 = simpson(b, a, x, y, 10);
    cout << "Ket qua cong thuc simpson: " << simpson1 << endl;

    cout << "Bai 2" << endl;
    double *z = new double[11];
    for (int i = 0; i < 11; i++) {
        z[i] = 1 / (1 + x[i]);
    }
    double hinhthang2 = hinhthang(b, a, x, z, 10);
    cout << "Ket qua cong thuc hinh thang: " << hinhthang2 << endl;
    double simpson2 = simpson(b, a, x, z, 10);
    cout << "Ket qua cong thuc simpson: " << simpson2 << endl;

    delete[] y;
    delete[] z;
    return 0;
}