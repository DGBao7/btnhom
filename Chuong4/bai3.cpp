#include <bits/stdc++.h>
#include<iostream>
#include<cmath>
using namespace std;

// Định nghĩa f(x) = sin(x)/x, xử lý điểm kỳ dị x = 0 
// Vì lim(x->0) sin(x)/x = 1, ta phải "vá" giá trị tại x = 0,
// nếu không chương trình sẽ tính 0/0 (NaN).
// sử dụng hàm fabs() để lấy trị tuyệt đối của số thực, đồng thời dùng hàm sin() có sẵn trong thư viện cmath hoặc math.h để biểu diễn biểu thức
double f(double x) {
    if (fabs(x) < 1e-12) return 1.0;
    return sin(x) / x;
}

// Ước lượng M2 = max|f''(x)| và M4 = max|f''''(x)| trên [0,1]
// Dùng sai phân trung tâm để KIỂM CHỨNG kết quả tính tay (giải tích cho
// M2 = 1/3 và M4 = 1/5, đạt tại x = 0). Chọn bước h vừa phải (0.01) để
// tránh sai số làm tròn khi lấy đạo hàm cấp cao.
double f2(double x, double h = 1e-3) {
    return (f(x + h) - 2 * f(x) + f(x - h)) / (h * h);
}
double f4(double x, double h = 1e-2) {
    return (f(x + 2*h) - 4*f(x + h) + 6*f(x) - 4*f(x - h) + f(x - 2*h)) / (h*h*h*h);
}

// Công thức hình thang và Simpson
double trapezoidal(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));
    for (int i = 1; i < n; i++) sum += f(a + i * h);
    return sum * h;
}

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

    // Kiểm chứng M2, M4 bằng cách quét lưới mịn trên [0,1] 
    double M2 = 0, M4 = 0;
    int gridN = 1000;
    for (int i = 0; i <= gridN; i++) {
        double x = a + (b - a) * i / gridN;
        M2 = max(M2, fabs(f2(x)));
        M4 = max(M4, fabs(f4(x)));
    }
    cout << fixed << setprecision(6);
    cout << "== Buoc 1: uoc luong M2 = max|f''(x)| tren [0,1] ==\n";
    cout << "M2 (uoc luong so) = " << M2 << "   (giai tich: 1/3 = " << 1.0/3 << ")\n\n";

    // Tim n nho nhat de sai so hinh thang <= eps 
    // |E_T| <= (b-a)^3 * M2 / (12 n^2)  <=  eps
    int n = 1;
    while ((pow(b - a, 3) * M2) / (12.0 * n * n) > eps) n++;
    cout << "==> n nho nhat thoa man (hinh thang): n = " << n << "\n";
    cout << "    Sai so hinh thang tai n = " << n << ": "
         << (pow(b - a, 3) * M2) / (12.0 * n * n) << "\n\n";

    // sai so Simpson tai n vua chon 
    cout << "== Buoc 2: uoc luong M4 = max|f''''(x)| tren [0,1] ==\n";
    cout << "M4 (uoc luong so) = " << M4 << "   (giai tich: 1/5 = " << 0.2 << ")\n\n";

    double simpsonError = (pow(b - a, 5) * M4) / (180.0 * pow(n, 4));
    cout << "==> Sai so Simpson tai n = " << n << ": " << scientific << simpsonError << fixed << "\n\n";

    // tinh I bang ca hai cong thuc, lam tron 6 chu so 
    double I_trap = trapezoidal(a, b, n);
    double I_simp = simpson(a, b, n);

    cout << "== Buoc 3: gia tri tich phan voi n = " << n << " ==\n";
    cout << "I (hinh thang) = " << I_trap << "\n";
    cout << "I (Simpson)    = " << I_simp << "\n";

    return 0;
}