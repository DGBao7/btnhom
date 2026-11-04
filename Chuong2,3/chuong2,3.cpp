#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

const double PI = 3.14159265358979323846;

vector<double> giaiHePhuongTrinh(vector<vector<double>> a , vector<double> b)
// Khu Gauss - Jordan
{
    int n = b.size();

    for (int i = 0; i < n; i++)
    {
        int pivot = i;
        for (int j = i + 1; j < n; j++)
        {
            if (abs(a[j][i]) > abs(a[pivot][i]))
            {
                pivot = j;
            }
        }

        swap(a[i] , a[pivot]);
        swap(b[i] , b[pivot]);
        double div = a[i][i];

        for (int j = i; j < n; j++)
        {
            a[i][j] /= div;
        }

        b[i] /= div;

        for (int k = 0; k < n; k++)
        {
            if (k == i)
            {
                continue;
            }
            double factor = a[k][i];
            for (int j = i; j < n; j++)
            {
                a[k][j] -= factor * a[i][j];
            }
            b[k] -= factor * b[i];
        }
    }

    return b;
}

vector<double> timHeSoLagrange(vector<double> x , vector<double> y)
{
    int n = x.size();
    vector<double> p(n , 0);
    for (int i = 0; i < n; i++)
    {
        vector<double> basis(1 , 1.0);
        double denominator = 1;

        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                continue;
            }
            denominator *= x[i] - x[j];
            vector<double> next(basis.size() + 1 , 0);

            for (int k = 0; k < basis.size(); k++)
            {
                next[k] += -x[j] * basis[k];
                next[k + 1] += basis[k];
            }

            basis = next;
        }

        for (int k = 0; k < basis.size(); k++)
        {
            p[k] += y[i] * basis[k] / denominator;
        }

    }

    return p;
}

double tinhGiaTriDaThuc(vector<double> p , double x)
// Phuong Phap Horner
{
    double result = 0;

    for (int i = p.size() - 1; i >= 0; i--)
    {
        result = result * x + p[i];
    }

    return result;
}

vector<double> binhPhuongToiThieu(vector<double> x , vector<double> y , int degree)
{
    int n = x.size();
    int m = degree + 1;
    vector<vector<double>> A(m , vector<double>(m , 0));
    vector<double> B(m , 0);

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            for (int k = 0; k < n; k++)
            {
                A[i][j] += pow(x[k] , i + j);
            }
        }

        for (int k = 0; k < n; k++)
        {
            B[i] += y[k] * pow(x[k] , i);
        }
    }

    return giaiHePhuongTrinh(A , B);
}

double tinhTongBinhPhuongSaiSo(vector<double> x , vector<double> y , vector<double> p)
{
    double error = 0;

    for (int i = 0; i < x.size(); i++)
    {
        double d = y[i] - tinhGiaTriDaThuc(p , x[i]);
        error += d * d;
    }

    return error;
}

double tinhNoiSuyLagrange(vector<double> x , vector<double> y , double value)
{
    double result = 0;

    for (int i = 0; i < x.size(); i++)
    {
        double term = y[i];

        for (int j = 0; j < x.size(); j++)
        {
            if (i == j)
            {
                continue;
            }
            term *= (value - x[j]) / (x[i] - x[j]);
        }
        result += term;
    }

    return result;
}

void inDaThuc(vector<double> p)
{
    cout << fixed << setprecision(8);

    for (int i = p.size() - 1; i >= 0; i--)
    {
        if (abs(p[i]) < 1e-10)
        {
            continue;
        }

        if (i != p.size() - 1 && p[i] >= 0)
        {
            cout << " + ";
        }

        else if (i != p.size() - 1)
        {
            cout << " - ";
        }

        double value = abs(p[i]);

        if (i == 0)
        {
            cout << value;
        }
        else if (i == 1)
        {
            cout << value << "x";
        }
        else
        {
            cout << value << "x^" << i;
        }
    }
    cout << endl;
}

void inTieuDeBai(int so , string moTa)
{
    cout << "\n" << string(76 , '=') << endl;
    cout << "BAI " << so << endl;
    cout << moTa << endl;
    cout << string(76 , '=') << endl;
}


void inBangDuLieu(vector<double> x , vector<double> y)
{
    cout << "\nBang gia tri cac nut du lieu:" << endl;
    cout << left << setw(8) << "i"
         << setw(18) << "x_i"
         << setw(18) << "y_i" << endl;

    cout << string(44 , '-') << endl;

    for (int i = 0; i < x.size(); i++)
    {
        cout << left << setw(8) << i
             << setw(18) << x[i]
             << setw(18) << y[i] << endl;
    }

    cout << right;
}


void inBangBienDoi(vector<double> x , vector<double> y , vector<double> transformed , string tenCot)
{
    cout << left << setw(8) << "i"
         << setw(16) << "x_i"
         << setw(16) << "y_i"
         << setw(18) << tenCot << endl;

    cout << string(58 , '-') << endl;

    for (int i = 0; i < x.size(); i++)
    {
        cout << left << setw(8) << i
             << setw(16) << x[i]
             << setw(16) << y[i]
             << setw(18) << transformed[i] << endl;
    }

    cout << right;
}


void inCongThucLagrange(vector<double> x , vector<double> y)
{
    cout << "\nCong thuc noi suy Lagrange:" << endl;
    cout << "P(x) = ";

    for (int i = 0; i < y.size(); i++)
    {
        if (i > 0)
        {
            cout << (y[i] >= 0 ? " + " : " - ");
        }
        else if (y[i] < 0)
        {
            cout << "-";
        }

        cout << abs(y[i]) << " * L_" << i << "(x)";
    }

    cout << endl << "Trong do:" << endl;

    for (int i = 0; i < x.size(); i++)
    {
        cout << "L_" << i << "(x) = ";

        bool first = true;

        for (int j = 0; j < x.size(); j++)
        {
            if (i == j)
            {
                continue;
            }

            if (!first)
            {
                cout << " * ";
            }

            cout << "(x - (" << x[j] << ")) / (" << x[i] << " - (" << x[j] << "))";
            first = false;
        }

        cout << endl;
    }
}


void inCacHangLagrangeTaiDiem(vector<double> x , vector<double> y , double value)
{
    cout << "\nThay x = " << value << " vao cong thuc Lagrange:" << endl;

    for (int i = 0; i < x.size(); i++)
    {
        double term = y[i];

        cout << "Hang " << i << " = " << y[i];

        for (int j = 0; j < x.size(); j++)
        {
            if (i == j)
            {
                continue;
            }

            double factor = (value - x[j]) / (x[i] - x[j]);
            term *= factor;

            cout << " * (" << value << " - (" << x[j] << ")) / ("
                 << x[i] << " - (" << x[j] << "))";
        }

        cout << " = " << term << endl;
    }
}




void inThaySoDaThuc(vector<double> p , double value)
{
    cout << "P(" << value << ") = ";

    bool first = true;

    for (int i = p.size() - 1; i >= 0; i--)
    {
        if (abs(p[i]) < 1e-10)
        {
            continue;
        }

        if (!first)
        {
            cout << (p[i] >= 0 ? " + " : " - ");
        }
        else if (p[i] < 0)
        {
            cout << "-";
        }

        cout << abs(p[i]);

        if (i == 1)
        {
            cout << " * (" << value << ")";
        }
        else if (i > 1)
        {
            cout << " * (" << value << ")^" << i;
        }

        first = false;
    }

    cout << " = " << tinhGiaTriDaThuc(p , value) << endl;
}


void bai1()
{
    cout << fixed << setprecision(8);
    inTieuDeBai(1 , "Tim da thuc noi suy Lagrange va tinh gia tri tai x = 2.");

    vector<double> x = {0 , 1 , 3 , 5};
    vector<double> y = {1 , 2 , 1 , 4};

    inBangDuLieu(x , y);
    inCongThucLagrange(x , y);

    vector<double> p = timHeSoLagrange(x , y);

    cout << "\nDa thuc noi suy sau khi khai trien:" << endl;
    cout << "P(x) = ";
    inDaThuc(p);

    cout << "\nTinh gia tri tai x = 2:" << endl;
    inThaySoDaThuc(p , 2);
    cout << "Ket qua tinh bang phuong phap Horner: "
         << tinhGiaTriDaThuc(p , 2) << endl;
}


void bai2()
{
    cout << fixed << setprecision(8);
    inTieuDeBai(2 , "Lap da thuc noi suy tu ham y = x^3 + x^2 - 10.");

    vector<double> x = {-4 , -3 , -1 , 0};
    vector<double> y;

    for (double value : x)
    {
        y.push_back(value * value * value + value * value - 10);
    }

    cout << "Ham tao du lieu: y = x^3 + x^2 - 10" << endl;
    inBangDuLieu(x , y);
    inCongThucLagrange(x , y);

    vector<double> p = timHeSoLagrange(x , y);

    cout << "\nDa thuc noi suy sau khi khai trien:" << endl;
    cout << "P(x) = ";
    inDaThuc(p);

    double A = -10.0 / 12.0;
    double B = 5.0 / 3.0;
    double C = -14.0 / 3.0;
    double D = 29.0 / 6.0;

    cout << "\nCac he so theo bieu thuc cua bai:" << endl;
    cout << "A = -10 / 12 = " << A << endl;
    cout << "B = 5 / 3 = " << B << endl;
    cout << "C = -14 / 3 = " << C << endl;
    cout << "D = 29 / 6 = " << D << endl;
}


void bai3()
{
    cout << fixed << setprecision(8);
    inTieuDeBai(3 , "Tinh tong S_n theo cong thuc tong binh phuong.");

    int n;

    cout << "Nhap n = ";
    cin >> n;

    double result = pow(n , 2) * pow(n + 1 , 2) / 4.0;

    cout << "\nCong thuc:" << endl;
    cout << "S_n = 1^2 + 2^2 + ... + n^2" << endl;
    cout << "S_n = n^2(n + 1)^2 / 4" << endl;

    cout << "\nThay n = " << n << " vao cong thuc:" << endl;
    cout << "S_" << n << " = " << n << "^2 * (" << n << " + 1)^2 / 4" << endl;
    cout << "S_" << n << " = " << result << endl;
}


void bai4()
{
    cout << fixed << setprecision(8);
    inTieuDeBai(4 , "Lap da thuc noi suy Newton bang sai phan chia.");

    vector<double> x = {-1 , 0 , 3 , 6 , 7};
    vector<double> y = {3 , -6 , 39 , 822 , 1611};

    int n = x.size();

    vector<vector<double>> table(n , vector<double>(n));

    for (int i = 0; i < n; i++)
    {
        table[i][0] = y[i];
    }

    for (int j = 1; j < n; j++)
    {
        for (int i = 0; i < n - j; i++)
        {
            table[i][j] =
                (table[i + 1][j - 1] - table[i][j - 1])
                / (x[i + j] - x[i]);
        }
    }

    inBangDuLieu(x , y);

    cout << "\nBang sai phan chia Newton:" << endl;
    cout << left << setw(8) << "i"
         << setw(12) << "x_i"
         << setw(16) << "f[x_i]";

    for (int j = 1; j < n; j++)
    {
        cout << setw(16) << ("Bac " + to_string(j));
    }

    cout << endl << string(92 , '-') << endl;

    for (int i = 0; i < n; i++)
    {
        cout << left << setw(8) << i << setw(12) << x[i];

        for (int j = 0; j < n; j++)
        {
            if (j < n - i)
            {
                cout << setw(16) << table[i][j];
            }
            else
            {
                cout << setw(16) << "-";
            }
        }

        cout << endl;
    }

    cout << right;

    cout << "\nCac he so sai phan chia dau tien:" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << "f[x_0,...,x_" << i << "] = " << table[0][i] << endl;
    }

    cout << "\nDa thuc Newton:" << endl;
    cout << "P(x) = 3 - 9(x + 1) + 6(x + 1)x" << endl;
    cout << "       + 5(x + 1)x(x - 3)" << endl;
    cout << "       + (x + 1)x(x - 3)(x - 6)" << endl;

    double value = 0.25;

    double result =
        3
        - 9 * (value + 1)
        + 6 * (value + 1) * value
        + 5 * (value + 1) * value * (value - 3)
        + (value + 1) * value * (value - 3) * (value - 6);

    cout << "\nThay x = 0.25 vao da thuc Newton:" << endl;
    cout << "P(0.25) = 3 - 9(0.25 + 1) + 6(0.25 + 1)(0.25)" << endl;
    cout << "          + 5(0.25 + 1)(0.25)(0.25 - 3)" << endl;
    cout << "          + (0.25 + 1)(0.25)(0.25 - 3)(0.25 - 6)" << endl;
    cout << "P(0.25) = " << result << endl;
}


void bai5()
{
    cout << fixed << setprecision(8);
    inTieuDeBai(5 , "Tim cac mo hinh hoi quy bang phuong phap binh phuong toi thieu.");

    vector<double> x = {0 , 1 , 2 , 3 , 4 , 5 , 6 , 7};
    vector<double> y = {1.4 , 1.3 , 1.4 , 1.1 , 1.3 , 1.8 , 1.6 , 2.3};

    inBangDuLieu(x , y);
    cout << "\nHam muc tieu chung: S = Sum((y_i - f(x_i))^2)" << endl;

    vector<double> p1 = binhPhuongToiThieu(x , y , 1);
    vector<double> p2 = binhPhuongToiThieu(x , y , 2);

    cout << "\n(a) Mo hinh tuyen tinh: f(x) = a + bx" << endl;
    cout << "a = " << p1[0] << endl;
    cout << "b = " << p1[1] << endl;
    cout << "Ham hoi quy: f(x) = " << p1[0] << " + (" << p1[1] << ")x" << endl;
    cout << "Tong binh phuong sai so:" << endl;
    cout << "S = Sum((y_i - (a + bx_i))^2) = "
         << tinhTongBinhPhuongSaiSo(x , y , p1) << endl;

    cout << "\n(b) Mo hinh bac hai: f(x) = a + bx + cx^2" << endl;
    cout << "a = " << p2[0] << endl;
    cout << "b = " << p2[1] << endl;
    cout << "c = " << p2[2] << endl;
    cout << "Ham hoi quy: f(x) = " << p2[0] << " + (" << p2[1]
         << ")x + (" << p2[2] << ")x^2" << endl;
    cout << "Tong binh phuong sai so:" << endl;
    cout << "S = Sum((y_i - (a + bx_i + cx_i^2))^2) = "
         << tinhTongBinhPhuongSaiSo(x , y , p2) << endl;

    vector<double> logY;

    for (double value : y)
    {
        logY.push_back(log(value));
    }

    vector<double> expModel = binhPhuongToiThieu(x , logY , 1);

    double b = expModel[1];
    double a = exp(expModel[0]);

    double errorExp = 0;

    for (int i = 0; i < x.size(); i++)
    {
        double predicted = a * exp(b * x[i]);
        double d = y[i] - predicted;
        errorExp += d * d;
    }

    cout << "\n(c) Mo hinh ham mu: f(x) = ae^(bx)" << endl;
    cout << "Bang du lieu sau bien doi Y = ln(y):" << endl;
    inBangBienDoi(x , y , logY , "ln(y_i)");
    cout << "Sau bien doi: ln(y) = ln(a) + bx" << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "Ham hoi quy: f(x) = " << a << " * e^(" << b << " * x)" << endl;
    cout << "S = Sum((y_i - ae^(bx_i))^2) = " << errorExp << endl;

    vector<double> expY;

    for (double value : y)
    {
        expY.push_back(exp(value));
    }

    vector<double> logModel = binhPhuongToiThieu(x , expY , 1);

    double aLog = logModel[1];
    double bLog = logModel[0];

    double errorLog = 0;

    for (int i = 0; i < x.size(); i++)
    {
        double predicted = log(aLog * x[i] + bLog);
        double d = y[i] - predicted;
        errorLog += d * d;
    }

    cout << "\n(d) Mo hinh logarit: f(x) = ln(ax + b)" << endl;
    cout << "Bang du lieu sau bien doi Y = e^y:" << endl;
    inBangBienDoi(x , y , expY , "e^(y_i)");
    cout << "Sau bien doi: e^y = ax + b" << endl;
    cout << "a = " << aLog << endl;
    cout << "b = " << bLog << endl;
    cout << "Ham hoi quy: f(x) = ln((" << aLog << ")x + (" << bLog << "))" << endl;
    cout << "S = Sum((y_i - ln(ax_i + b))^2) = " << errorLog << endl;
}


void bai6()
{
    cout << fixed << setprecision(8);
    inTieuDeBai(6 , "Tim ham hoi quy bac hai y = ax^2 + bx + c.");

    vector<double> x = {0.78 , 1.56 , 2.34 , 3.12 , 3.81};
    vector<double> y = {2.50 , 1.20 , 1.12 , 4.28 , 7.50};

    inBangDuLieu(x , y);

    vector<double> p = binhPhuongToiThieu(x , y , 2);

    cout << "\nMo hinh can tim: y = ax^2 + bx + c" << endl;
    cout << "Cac he so cua mo hinh:" << endl;
    cout << "a = " << p[2] << endl;
    cout << "b = " << p[1] << endl;
    cout << "c = " << p[0] << endl;

    cout << "\nHam hoi quy thu duoc:" << endl;
    cout << "y = ";
    inDaThuc(p);

    cout << "Tong binh phuong sai so:" << endl;
    cout << "S = Sum((y_i - (ax_i^2 + bx_i + c))^2) = "
         << tinhTongBinhPhuongSaiSo(x , y , p) << endl;
}


void bai7()
{
    cout << fixed << setprecision(12);
    inTieuDeBai(7 , "Noi suy gia tri sin(12.5 do) va danh gia sai so.");

    vector<double> x;

    for (int i = 0; i <= 25; i += 5)
    {
        x.push_back(i * PI / 180.0);
    }

    vector<double> y;

    for (double value : x)
    {
        y.push_back(sin(value));
    }

    double target = 12.5 * PI / 180.0;

    double approximate = tinhNoiSuyLagrange(x , y , target);
    double exact = sin(target);

    double error = abs(exact - approximate);

    double bound = 1;

    for (double value : x)
    {
        bound *= abs(target - value);
    }

    bound /= 720.0;

    cout << "\nBang cac nut noi suy:" << endl;
    cout << left << setw(8) << "i"
         << setw(18) << "x_i (do)"
         << setw(22) << "x_i (radian)"
         << setw(18) << "sin(x_i)" << endl;
    cout << string(66 , '-') << endl;

    for (int i = 0; i < x.size(); i++)
    {
        cout << left << setw(8) << i
             << setw(18) << i * 5.0
             << setw(22) << x[i]
             << setw(18) << y[i] << endl;
    }

    cout << right;

    cout << "\nCong thuc noi suy Lagrange bac 5:" << endl;
    cout << "L_5(x) = Sum(y_i * Product((x - x_j) / (x_i - x_j))), j != i" << endl;
    cout << "Diem can tinh: x = 12.5 do = " << target << " radian" << endl;
    inCacHangLagrangeTaiDiem(x , y , target);

    cout << "\nGia tri noi suy:" << endl;
    cout << "L_5(12.5 do) = " << approximate << endl;
    cout << "Gia tri thuc sin(12.5 do) = " << exact << endl;
    cout << "Sai so thuc te |sin(12.5 do) - L_5(12.5 do)| = " << error << endl;

    cout << "\nDanh gia sai so ly thuyet:" << endl;
    cout << "|R_5(x)| <= M_6 / 6! * Product(|x - x_i|)" << endl;
    cout << "Voi ham sin(x): M_6 = max|sin^(6)(x)| <= 1 va 6! = 720." << endl;
    cout << "Product(|x - x_i|) = " << bound * 720.0 << endl;
    cout << "|R_5(12.5 do)| <= 1 / 720 * " << bound * 720.0 << endl;
    cout << "|R_5(12.5 do)| <= " << bound << endl;
}


void bai8()
{
    cout << fixed << setprecision(8);
    inTieuDeBai(8 , "So sanh cac mo hinh hoi quy tuyen tinh, bac hai va ham mu.");

    vector<double> x = {2 , 4 , 6 , 8 , 10 , 12};
    vector<double> y = {7.32 , 8.24 , 9.20 , 10.19 , 11.01 , 12.05};

    inBangDuLieu(x , y);
    cout << "\nHam muc tieu: S = Sum((y_i - f(x_i))^2)" << endl;

    vector<double> p1 = binhPhuongToiThieu(x , y , 1);
    vector<double> p2 = binhPhuongToiThieu(x , y , 2);

    cout << "\n(a) Mo hinh tuyen tinh: y = a + bx" << endl;
    cout << "a = " << p1[0] << endl;
    cout << "b = " << p1[1] << endl;
    cout << "Ham hoi quy: y = " << p1[0] << " + (" << p1[1] << ")x" << endl;
    cout << "S = Sum((y_i - (a + bx_i))^2) = "
         << tinhTongBinhPhuongSaiSo(x , y , p1) << endl;

    cout << "\n(b) Mo hinh bac hai: y = a + bx + cx^2" << endl;
    cout << "a = " << p2[0] << endl;
    cout << "b = " << p2[1] << endl;
    cout << "c = " << p2[2] << endl;
    cout << "Ham hoi quy: y = " << p2[0] << " + (" << p2[1]
         << ")x + (" << p2[2] << ")x^2" << endl;
    cout << "S = Sum((y_i - (a + bx_i + cx_i^2))^2) = "
         << tinhTongBinhPhuongSaiSo(x , y , p2) << endl;

    vector<double> logX;
    vector<double> logY;

    for (int i = 0; i < x.size(); i++)
    {
        logX.push_back(log(x[i]));
        logY.push_back(log(y[i]));
    }

    vector<double> p3 = binhPhuongToiThieu(logX , logY , 1);

    double b = p3[1];
    double a = exp(p3[0]);

    double errorPower = 0;

    for (int i = 0; i < x.size(); i++)
    {
        double predicted = a * pow(x[i] , b);
        double d = y[i] - predicted;
        errorPower += d * d;
    }

    cout << "\n(c) Mo hinh luy thua: y = ax^b" << endl;
    cout << "Bang du lieu sau bien doi X = ln(x), Y = ln(y):" << endl;
    cout << left << setw(8) << "i"
         << setw(16) << "x_i"
         << setw(16) << "y_i"
         << setw(18) << "ln(x_i)"
         << setw(18) << "ln(y_i)" << endl;
    cout << string(76 , '-') << endl;

    for (int i = 0; i < x.size(); i++)
    {
        cout << left << setw(8) << i
             << setw(16) << x[i]
             << setw(16) << y[i]
             << setw(18) << logX[i]
             << setw(18) << logY[i] << endl;
    }

    cout << right;
    cout << "Sau bien doi: ln(y) = ln(a) + b * ln(x)" << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "Ham hoi quy: y = " << a << " * x^(" << b << ")" << endl;
    cout << "S = Sum((y_i - ax_i^b)^2) = " << errorPower << endl;

    cout << "\nKet luan:" << endl;
    cout << "So sanh cac gia tri S o tren; mo hinh co S nho nhat phu hop nhat voi bo du lieu." << endl;
}

int main()
{
    cout << fixed << setprecision(8);
    bai1();
    bai2();
    bai3();
    bai4();
    bai5();
    bai6();
    bai7();
    bai8();

    return 0;
}