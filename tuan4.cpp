#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

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


void bai1()
{
    cout << "\n";
    cout << "BAI 1\n";

    vector<double> x = {0 , 1 , 3 , 5};
    vector<double> y = {1 , 2 , 1 , 4};

    vector<double> p = timHeSoLagrange(x , y);

    cout << "P(x) = ";
    inDaThuc(p);

    cout << "f(2) xap xi = " << tinhGiaTriDaThuc(p , 2) << endl;
}


void bai2()
{
    cout << "\n";
    cout << "BAI 2\n";

    vector<double> x = {-4 , -3 , -1 , 0};
    vector<double> y;

    for (double value : x)
    {
        y.push_back(value * value * value + value * value - 10);
    }

    vector<double> p = timHeSoLagrange(x , y);

    cout << "Da thuc noi suy: ";
    inDaThuc(p);

    double A = -10.0 / 12.0;
    double B = 5.0 / 3.0;
    double C = -14.0 / 3.0;
    double D = 29.0 / 6.0;

    cout << "A = " << A << endl;
    cout << "B = " << B << endl;
    cout << "C = " << C << endl;
    cout << "D = " << D << endl;
}


void bai3()
{
    cout << "\n";
    cout << "BAI 3\n";

    int n;

    cout << "Nhap n = ";
    cin >> n;

    double result = pow(n , 2) * pow(n + 1 , 2) / 4.0;

    cout << "S_n = n^2(n + 1)^2 / 4" << endl;
    cout << "S_" << n << " = " << result << endl;
}


void bai4()
{
    cout << "\n";
    cout << "BAI 4\n";

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

    cout << "Cac sai phan chia:" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << table[0][i] << " ";
    }

    cout << endl;

    cout << "Newton:" << endl;

    cout << "P(x) = "
         << "3"
         << " - 9(x + 1)"
         << " + 6(x + 1)x"
         << " + 5(x + 1)x(x - 3)"
         << " + (x + 1)x(x - 3)(x - 6)"
         << endl;

    double value = 0.25;

    double result =
        3
        - 9 * (value + 1)
        + 6 * (value + 1) * value
        + 5 * (value + 1) * value * (value - 3)
        + (value + 1) * value * (value - 3) * (value - 6);

    cout << "f(0.25) xap xi = " << result << endl;
}


void bai5()
{
    cout << "\n";
    cout << "BAI 5\n";

    vector<double> x = {0 , 1 , 2 , 3 , 4 , 5 , 6 , 7};
    vector<double> y = {1.4 , 1.3 , 1.4 , 1.1 , 1.3 , 1.8 , 1.6 , 2.3};

    vector<double> p1 = binhPhuongToiThieu(x , y , 1);
    vector<double> p2 = binhPhuongToiThieu(x , y , 2);

    cout << "\n(a) f(x) = a + bx" << endl;
    inDaThuc(p1);
    cout << "Sai so S = " << tinhTongBinhPhuongSaiSo(x , y , p1) << endl;

    cout << "\n(b) f(x) = a + bx + cx^2" << endl;
    inDaThuc(p2);
    cout << "Sai so S = " << tinhTongBinhPhuongSaiSo(x , y , p2) << endl;

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

    cout << "\n(c) f(x) = ae^(bx)" << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "Sai so S = " << errorExp << endl;

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

    cout << "\n(d) f(x) = ln(ax + b)" << endl;
    cout << "a = " << aLog << endl;
    cout << "b = " << bLog << endl;
    cout << "Sai so S = " << errorLog << endl;
}


void bai6()
{
    cout << "\n";
    cout << "BAI 6\n";

    vector<double> x = {0.78 , 1.56 , 2.34 , 3.12 , 3.81};
    vector<double> y = {2.50 , 1.20 , 1.12 , 4.28 , 7.50};

    vector<double> p = binhPhuongToiThieu(x , y , 2);

    cout << "y = ";
    inDaThuc(p);

    cout << "a = " << p[2] << endl;
    cout << "b = " << p[1] << endl;
    cout << "c = " << p[0] << endl;

    cout << "Sai so S = " << tinhTongBinhPhuongSaiSo(x , y , p) << endl;
}


void bai7()
{
    cout << "\n";
    cout << "BAI 7\n";

    vector<double> x;

    for (int i = 0; i <= 25; i += 5)
    {
        x.push_back(i * M_PI / 180.0);
    }

    vector<double> y;

    for (double value : x)
    {
        y.push_back(sin(value));
    }

    double target = 12.5 * M_PI / 180.0;

    double approximate = tinhNoiSuyLagrange(x , y , target);
    double exact = sin(target);

    double error = abs(exact - approximate);

    double bound = 1;

    for (double value : x)
    {
        bound *= abs(target - value);
    }

    bound /= 720.0;

    cout << fixed << setprecision(12);

    cout << "L5(12.5 do) = " << approximate << endl;
    cout << "sin(12.5 do) = " << exact << endl;

    cout << "Sai so thuc te = " << error << endl;
    cout << "Danh gia sai so <= " << bound << endl;
}


void bai8()
{
    cout << "\n";
    cout << "BAI 8\n";

    vector<double> x = {2 , 4 , 6 , 8 , 10 , 12};
    vector<double> y = {7.32 , 8.24 , 9.20 , 10.19 , 11.01 , 12.05};

    vector<double> p1 = binhPhuongToiThieu(x , y , 1);
    vector<double> p2 = binhPhuongToiThieu(x , y , 2);

    cout << "\n(a) y = a + bx" << endl;
    inDaThuc(p1);
    cout << "a = " << p1[0] << endl;
    cout << "b = " << p1[1] << endl;
    cout << "Sai so S = " << tinhTongBinhPhuongSaiSo(x , y , p1) << endl;

    cout << "\n(b) y = a + bx + cx^2" << endl;
    inDaThuc(p2);
    cout << "a = " << p2[0] << endl;
    cout << "b = " << p2[1] << endl;
    cout << "c = " << p2[2] << endl;
    cout << "Sai so S = " << tinhTongBinhPhuongSaiSo(x , y , p2) << endl;

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

    cout << "\n(c) y = ax^b" << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "Sai so S = " << errorPower << endl;

    cout << "\nKet luan:" << endl;
    cout << "Mo hinh co sai so nho nhat la mo hinh phu hop nhat." << endl;
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