#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// ============================================================================
// BÀI 1: PHƯƠNG PHÁP LẶP ĐƠN
// x - 0.5*sin(x) = 0.25  ==>  x = g(x) = 0.5*sin(x) + 0.25
// ============================================================================
double g1(double x) {
    return 0.5 * sin(x) + 0.25;
}

double dg1(double x) {
    return 0.5 * cos(x); // Đạo hàm g'(x)
}

void bai1() {
    cout << "==================================================================\n";
    cout << " BAI 1: PHUONG PHAP LAP DON\n";
    cout << " Phuong trinh: x - 0.5*sin(x) = 0.25  <=>  x = g(x) = 0.5*sin(x) + 0.25\n";
    cout << "==================================================================\n";

    // 1. Kiểm tra sự hội tụ trên đoạn [0, 1]
    double a = 0.0, b = 1.0;
    // max |g'(x)| trên [0, 1] đạt tại x = 0: q = 0.5*cos(0) = 0.5
    double q = 0;

    cout << "1. KIEM TRA SU HOI TU TREN [" << a << ", " << b << "]:\n";
    cout << "   g'(x) = 0.5 * cos(x)\n";
    // Quét lưới mịn để tìm giá trị lớn nhất của đạo hàm g'(x) => q
    for(int i=0; i<=100;i++){
        q = max(q, dg1(0+i/100));
    }
    cout << "   Mo-dul hoi tu q = max|g'(x)| = " << fixed << setprecision(4) << q << "\n";
    if (q < 1.0) {
        cout << "   ==> Vis q = " << q << " < 1, phep lap CHAC CHAN HOI TU.\n\n";
    } else {
        cout << "   ==> Phep lap KHONG dam bao hoi tu.\n\n";
        return;
    }

    // 2. Lặp 4 bước với x0 = 0.5
    double x0 = 0.5;
    cout << "2. THUC HIEN 4 BUOC LAP (Chon x0 = " << x0 << "):\n";
    cout << setw(8) << "k" << setw(15) << "x_k" << setw(25) << "|x_k - x_{k-1}|\n";
    cout << setw(8) << 0 << setw(18) << fixed << setprecision(6) << x0 << setw(18) << "-\n";

    double x_curr = x0;
    double x_1 = 0;
    for (int k = 1; k <= 4; k++) {
        double x_next = g1(x_curr);
        if (k == 1) x_1 = x_next;
        cout << setw(8) << k << setw(18) << fixed << setprecision(6) << x_next 
             << setw(18) << fabs(x_next - x_curr) << "\n";
        x_curr = x_next;
    }

    // 3. Đánh giá sai số
    double error_bound = (pow(q, 4) / (1.0 - q)) * fabs(x_1 - x0);
    cout << "\n3. DANH GIA SAI SO |x4 - alpha|:\n";
    cout << "   Cong thuc sai so tien quyet: |x4 - alpha| <= (q^4 / (1 - q)) * |x1 - x0|\n";
    cout << "   ==> |x4 - alpha| <= " << scientific << setprecision(6) << error_bound << "\n\n";
}

// ============================================================================
// BÀI 2: PHƯƠNG PHÁP CHIA ĐÔI
// f(x) = x^3 - x - 1 trên [1, 2]
// ============================================================================
double f2(double x) {
    return x * x * x - x - 1.0;
}

void bai2() {
    cout << "==================================================================\n";
    cout << " BAI 2: PHUONG PHAP CHIA DOI\n";
    cout << " Phuong trinh: x^3 - x - 1 = 0 tren [1, 2]\n";
    cout << "==================================================================\n";

    double a = 1.0, b = 2.0;

    // 1. Kiểm tra điều kiện
    cout << "1. KIEM TRA DIEU KIEN HOI TU:\n";
    cout << "   f(1) = " << f2(a) << ", f(2) = " << f2(b) << "\n";
    if (f2(a) * f2(b) < 0) {
        cout << "   ==> Vis f(1)*f(2) < 0 va f(x) lien tuc, phuong phap HOI TU LUON LUON.\n\n";
    }

    // 2. Lặp 4 bước
    cout << "2. THUC HIEN 4 BUOC LAP:\n";
    cout << setw(6) << "k" << setw(12) << "a_k" << setw(12) << "b_k" 
         << setw(12) << "x_k" << setw(14) << "f(x_k)" << "\n";

    double x4 = 0;
    for (int k = 1; k <= 4; k++) {
        double c = (a + b) / 2.0;
        x4 = c;
        cout << setw(6) << k << fixed << setprecision(6)
             << setw(12) << a << setw(12) << b 
             << setw(12) << c << setw(14) << f2(c) << "\n";

        if (f2(a) * f2(c) < 0) {
            b = c;
        } else {
            a = c;
        }
    }

    // 3. Đánh giá sai số
    double error_bound = (2.0 - 1.0) / pow(2, 4); // (b0 - a0) / 2^n
    cout << "\n3. DANH GIA SAI SO |x4 - alpha|:\n";
    cout << "   Cong thuc sai so chia doi: |x4 - alpha| <= (b - a) / 2^4\n";
    cout << "   ==> |x4 - alpha| <= " << fixed << setprecision(6) << error_bound << "\n\n";
}

// ============================================================================
// BÀI 3: PHƯƠNG PHÁP DÂY CUNG
// f(x) = x^3 - x - 1 trên [1, 2]
// ============================================================================
double f3_df(double x) {
    return 3.0 * x * x - 1.0; // f'(x)
}

double f3_ddf(double x) {
    return 6.0 * x; // f''(x)
}

void bai3() {
    cout << "==================================================================\n";
    cout << " BAI 3: PHUONG PHAP DAY CUNG\n";
    cout << " Phuong trinh: x^3 - x - 1 = 0 tren [1, 2]\n";
    cout << "==================================================================\n";

    double a = 1.0, b = 2.0;

    // 1. Kiểm tra sự hội tụ & chọn điểm cố định
    cout << "1. KIEM TRA SU HOI TU VA CHON DIEM CO DINH:\n";
    cout << "   f'(x) = 3x^2 - 1 > 0 tren [1, 2]\n";
    cout << "   f''(x) = 6x > 0 tren [1, 2]\n";
    cout << "   ==> f'(x) va f''(x) khong doi dau --> Phuong phap CHAC CHAN HOI TU.\n";

    // f(2) = 5 > 0 cùng dấu f''(x) > 0 nên d = 2 là điểm cố định
    double d = b; // d = 2
    double x_curr = a; // x0 = 1
    double m1 = f3_df(a); // min|f'(x)| trên [1,2] tại x=1 là 3(1)^2 - 1 = 2

    cout << "   Chon diem co dinh d = " << d << " (vi f(2)*f''(x) > 0)\n";
    cout << "   Gia tri m1 = min|f'(x)| tren [1,2] = " << m1 << "\n\n";

    // 2. Lặp 4 bước
    cout << "2. THUC HIEN 4 BUOC LAP (x0 = " << x_curr << "):\n";
    cout << setw(6) << "k" << setw(14) << "x_k" << setw(16) << "f(x_k)" << "\n";
    cout << setw(6) << 0 << fixed << setprecision(6) << setw(14) << x_curr << setw(16) << f2(x_curr) << "\n";

    for (int k = 1; k <= 4; k++) {
        // Công thức dây cung: x_{k+1} = x_k - [f(x_k) / (f(d) - f(x_k))] * (d - x_k)
        double x_next = x_curr - (f2(x_curr) / (f2(d) - f2(x_curr))) * (d - x_curr);
        cout << setw(6) << k << fixed << setprecision(6) << setw(14) << x_next << setw(16) << f2(x_next) << "\n";
        x_curr = x_next;
    }

    // 3. Đánh giá sai số
    double error_bound = fabs(f2(x_curr)) / m1;
    cout << "\n3. DANH GIA SAI SO |x4 - alpha|:\n";
    cout << "   Cong thuc sai so dây cung: |x4 - alpha| <= |f(x4)| / m1\n";
    cout << "   ==> |x4 - alpha| <= " << fixed << setprecision(6) << error_bound << "\n\n";
}

int main() {
    bai1();
    bai2();
    bai3();
    return 0;
}