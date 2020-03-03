// e g h get - _ \

#include "Header.h"
//using namespace std;






void testVector() {
	// testam numar complex
	Numar_Complex a(3, 4);
	Numar_Complex b(2, 1);
	Numar_Complex c(-3, 2);
	Numar_Complex d(5, -2);
	Numar_Complex e(0, 4);
	Numar_Complex x[5] = { a,b,c,d,e };
	cout << a << '\n';
	assert(a.getImag() == 4);
	assert(a.getReal() == 3);
	assert(a.modul() == 5);
	
	Vector_Complex v(x, 5);
	v.printArray();
	double* plm = v.makeModules();
	for (int i = 0; i < v.getLen(); i++) {
		cout << plm[i] << " ";
	}
	cout << endl;
	v.sortByModules();
	plm = v.makeModules();
	v.printArray();
	for (int i = 0; i < v.getLen(); i++) {
		cout << plm[i] << " ";
	}
	cout << endl;
	a = v.sum();
	cout << a;

}

int main() {
	testVector();

	return 0;
}