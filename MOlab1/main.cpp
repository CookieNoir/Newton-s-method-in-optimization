#include <iostream>

using namespace std;

double det(double x11, double x12, double x21, double x22)
{
	return x11 * x22 - x12 * x21;
}

void swap(double &a, double &b)
{
	double temp = a;
	a = b;
	b = temp;
}

double norm(double x1, double x2)
{
	return sqrt(x1*x1 + x2 * x2);
}

void matrMultiply(double x1, double x2,
	double m11, double m12, double m21, double m22,
	double &res1, double &res2)
{
	res1 = x1 * m11 + x2 * m21;
	res2 = x1 * m12 + x2 * m22;
}

void main(char* argv[])
{
	double eps,
		a, b, c, d, e, f,
		fa, fb, fc, fd, fe,
		x1 = 0, x2 = 0,
		grad1, grad2,
		h11, h12, h21, h22;
	//a*x1^2 + b*x2^2 + c*x1*x2 + d*x1 + e*x2 + f
	cout << "Input eps and x0 coordinates\n";
	cin >> eps >> x1 >> x2;
	cout << "Input a, b, c, d, e, f\n";
	cin >> a >> b >> c >> d >> e >> f;
	h11 = 2 * a;
	h12 = c;
	h21 = c;
	h22 = 2 * b;
	double deth = 1.0 / det(h11, h12, h21, h22);
	swap(h11, h22);
	h12 *= -1;
	h21 *= -1;

	h11 *= deth;
	h12 *= deth;
	h21 *= deth;
	h22 *= deth;

	fa = 2 * a;
	fb = 2 * b;
	fc = c;
	fd = d;
	fe = e;

	grad1 = fa * x1 + fc * x2 + d;
	grad2 = fb * x2 + fc * x1 + e;

	while (norm(grad1, grad2) >= eps)
	{
		double mul1 = 0, mul2 = 0;
		matrMultiply(grad1, grad2, h11, h12, h21, h22, mul1, mul2);
		x1 -= mul1;
		x2 -= mul2;

		grad1 = fa * x1 + fc * x2 + d;
		grad2 = fb * x2 + fc * x1 + e;
	}
	double result = a * x1*x1 + b * x2*x2 + c * x1*x2 + d * x1 + e * x2 + f;
	cout << "Found optimal solution x*=(" << x1 << ", " << x2 << ");\n";
	cout << "f*=" << result << ".";
	system("pause");
}