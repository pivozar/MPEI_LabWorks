#include <iostream>
#include "matrix.h"

using namespace std;

SparseMatrix Read() {
	cout << "Enter 'rows', 'cols', 'count' of non-zero elements, then 'count' times: x, y, value\n";
	int rows, cols, cnt;
	cin >> rows >> cols >> cnt;
	SparseMatrix res(rows, cols);
	while (cnt) {
		cnt--;
		int x, y, val;
		cin >> x >> y >> val;
		res.UpdateElement(x, y, val);
	}
	return res;
}

int main() {
	SparseMatrix a, b;
	std::cout << "1.Enter matrix A\n2.Enter matrix B\n";
	std::cout << "3.Transpose matrix A\n4.Transpose matrix B\n";
	std::cout << "5.A + B\n6.A - B\n";
	std::cout << "7.A * B\n8.A == B\n";
	std::cout << "9.A * number\n10.B * number\n";
	std::cout << "11.Print A\n12.Print B\n";
	std::cout << "13.Exit\n";
	int cmd;
	while (true) {
		cout << "Command:__";
		cin >> cmd;
		if (cmd == 1) { a = Read(); }
		else if (cmd == 2) { b = Read(); }
		else if (cmd == 3) { a.Transpose().Print(); }
		else if (cmd == 4) { b.Transpose().Print(); }
		else if (cmd == 5) { (a + b).Print(); }
		else if (cmd == 6) { (a - b).Print(); }
		else if (cmd == 7) { (a * b).Print(); }
		else if (cmd == 8) { cout << (a == b) << endl; }
		else if (cmd == 9) {
			int num;
			cout << "Enter a number:\n";
			cin >> num;
			(num * a).Print();
		}
		else if (cmd == 10) {
			int num;
			cout << "Enter a number:\n";
			cin >> num;
			(num * b).Print();
		}
		else if (cmd == 11) { a.Print(); }
		else if (cmd == 12) { b.Print(); }
		else if (cmd == 13) { break; }
	}
    
    return 0;
}

