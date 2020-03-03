// e g h get - _ \

#pragma once
#include <iostream>
#include <assert.h>
#include <math.h>

using namespace std;

class Numar_Complex {
	int real;
	double imag; // avem numar complex compus din partea reala <real> si parta imaginara double <imag>
public:
	// construcor default
	Numar_Complex() = default;
	// constructor cu parametri
	Numar_Complex(const int real, const double imag) : real{ real }, imag{ imag } {}
	// copy constructor
	Numar_Complex(const Numar_Complex &x) : real{ x.real }, imag{ x.imag } {}
	// destructor
	~Numar_Complex() = default;


	// overload on + operator
	// partea imaginara si reala se aduna separat
	Numar_Complex operator + (const Numar_Complex &nr) {
		Numar_Complex rez;
		rez.imag = imag + nr.imag;
		rez.real = real + nr.real;
		return rez;
	}

	// overload on - operator
	// partea imaginara si reala se scad separat
	Numar_Complex operator - (const Numar_Complex &nr) {
		Numar_Complex rez;
		rez.imag = imag - nr.imag;
		rez.real = real - nr.real;
		return rez;
	}

	// overload on * operator
	// (a+bi) * (c+di) = ac-bd + (ad+bc)i
	Numar_Complex operator* (const Numar_Complex &nr) {
		Numar_Complex rez;
		rez.imag = real * nr.imag + nr.real * imag;
		rez.real = real * nr.real - imag * nr.imag;
		return rez;
	}
	// overload on / operator
	// (a+bi) / (c+di) = (a1a2 + b1b2)/(a2^2 + b2^2) + (a2b1 - a1b2)/(a2^2 + b2^2)
	// se ignora cazul in care real si/sau imaginar = 0
	Numar_Complex operator/ (const Numar_Complex &nr) {
		Numar_Complex rez(0, 0);
		if (nr.real == 0 && nr.imag == 0) return rez;
		rez.real = (real * nr.real + imag * nr.imag) / (nr.real * nr.real + nr.imag * nr.imag);
		rez.imag = (nr.real * imag - nr.imag * real) / (nr.real * nr.real + nr.imag * nr.imag);
		return rez;
	}
	// overload on = operator
	// partea imaginara si reala 
	void operator=(const Numar_Complex &x) {
		real = x.real;
		imag = x.imag;
	}


	// printare prin overload pe operator <<
	friend 	ostream& operator<<(ostream& os, Numar_Complex& x);

	// citire prin overload pe operator >>
	friend  istream& operator>>(istream& is, Numar_Complex& x);

	// metoda de furnizare a partii reale
	int getReal() {
		return real;
	}
	// metoda de furnizare a partii imaginare
	double getImag() {
		return imag;
	}
	// metoda de setare a partii reale
	void setReal(int x) {
		real = x;
	}
	// metoda de setare a partii imaginare
	void setImag(double x) {
		imag = x;
	}
	// metoda de furnizare a moduluilui unui numar complex
	double modul() {
		return std::sqrt(real * real + imag * imag);
	}
};
ostream& operator<<(ostream& os, Numar_Complex& x) {
	if (x.getReal() == x.getImag() && x.getImag() == 0) os << 0;
	else if (x.getImag() == 0 && x.getReal() != 0) os << x.getReal();
	else if (x.getReal() == 0 && x.getImag() != 0) os << x.getImag() << "*i";
	else if (x.getImag() < 0) os << x.getReal() << x.getImag() << "*i";
	else os << x.getReal() << " + " << x.getImag() << "*i";
	return os;
}
istream& operator>>(istream& is, Numar_Complex& x) {
	cout << "Se citeste un numar complex.\nparte reala: ";
	int a;
	is >> a;
	x.setReal(a);
	cout << "parte imaginara: ";
	double b;
	is >> b;
	x.setImag(b);
	return is;
}
class Vector_Complex {
	Numar_Complex *v;			// pointer catre adresa (de inceput) a vectorului
	int len;		// numarul de elemente din vector
	int capMax;		// capacitate maxima
public:
	// friend class Numar_Complex;
	// constructor default, aloca un vector cu 5 spatii 
	Vector_Complex() {
		v = new Numar_Complex[5];
		len = 0;
		capMax = 5;
	}
	// constuctor cu parametri, de capacitate maxima dim si il umple cu acelasi element dat ca parametru
	Vector_Complex(Numar_Complex n[], int dim) {
		v = new Numar_Complex[dim+5];
		for (int i = 0; i < dim; i++)
			v[i] = n[i];
		len = dim;
		capMax = dim+5;
	}
	// copy constructor
	Vector_Complex(Vector_Complex &ot) {
		v = new Numar_Complex[ot.capMax];
		for (int i = 0; i < ot.len; i++)
			v[i] = ot.v[i];
		len = ot.len;
		capMax = ot.capMax;
	}
	~Vector_Complex() {
		delete[] v;
		len = 0;
		capMax = 0;
	}
	// metoda de furnizare a nr de elemente
	int getLen() {
		return len;
	}
	// metoda de furnizare a capacitatii maxime
	int getCapMax() {
		return capMax;
	}
	// metoda de printare directa a tot vectorului
	void printArray() {
		for (int i = 0; i < len; i++)
			cout << v[i] << ", ";
	}
	// metoda de inserare a unui element cat timp aceasta este posibila
	void insert(const Numar_Complex &a) {
		if (len < capMax) v[len++] = a;
	}
	double* makeModules() {
		double *vmod;
		vmod = new double[len];
		for (int i = 0; i < len; i++) {
			vmod[i] = v[i].modul();
		}
		return vmod;
	}
	void sortByModules() {
		for (int i = 0; i < len - 1; i++)
			for (int j = i + 1; j < len; j++)
				if (v[i].modul() > v[j].modul()) {
					Numar_Complex aux = v[i];
					v[i] = v[j];
					v[j] = aux;
				}
	}
	Numar_Complex sum() {
		Numar_Complex suma(0, 0);
		for (int i = 0; i < len; i++)
			suma = suma + v[i];
		return suma;
	}

	Numar_Complex dotProduct(const Vector_Complex& w) {
		Numar_Complex suma(0, 0);
		if (w.len != len) {
			cout << "Nu au aceeasi lunime";
			return Numar_Complex(-1, -1); //returneaza nr complex -1,-1
		}
		for (int i = 0; i < len; i++)
			suma = suma + (v[i] * w.v[i]);
		return suma;
	}
};

void testVector();