#pragma once
#include <iostream>

using namespace std;

class FileOb {
protected:
	int number_openings;
public:
	FileOb() : number_openings{ 0 } {};
	virtual void display(const char* path) {
		FILE* out;
		char* tempStr = new char[126];
		// Open file
		if (!fopen_s(&out, path, "r")) {
			cout << "-----------\n";
			// While file didn't end
			while (!feof(out)) {
				// Read string from file
				fgets(tempStr, 126, out);
				cout << tempStr; // Print it in console
			}
			cout << "\n-----------\n";
			fclose(out);
			number_openings += 1;
		}
		else
			cout << "File wasn't opened";
	}
	// Return number of openings file
	int getNumber_openings() {
		return number_openings;
	}
};


// With ASCII code of symbols (same)
class FileObACIIChild : public FileOb {
public:
	FileObACIIChild() : FileOb() {};
	virtual void display(const char* path) {
		FILE* out;
		char* tempStr = new char[126];
		if (!fopen_s(&out, path, "r")) {
			cout << "-----------\n";
			while (!feof(out)) {
				fgets(tempStr, 126, out);
				cout << tempStr;
			}
			cout << "\n-----------\n";
			fclose(out);
			number_openings += 1;
		}
		else
			cout << "File wasn't opened";
	}
};


class FileObBitChild : public FileOb {
	// Translate int to binary code and print it
	void to_binary_code(int a) {
		// Binary number
		int* number = new int[125];
		int lenght = 0; // Lenght of it
		// Include in number 0 and 1
		while (a > 0) {
			number[lenght] = a&1; 
			lenght++;
			a >>= 1;
		}
		// Print binary number
		for (int i = lenght-1; i > -1; i--) {
			cout << number[i];
		}
	}
public:
	FileObBitChild() : FileOb() {};
	virtual void display(const char* path) {
		FILE* out;
		char tempSym;
		if (!fopen_s(&out, path, "r")) {
			while (!feof(out)) {
				tempSym = fgetc(out); // Take symbol from file
				// If it's symbol, but not a '\n' or '\0'
				if (tempSym != '\n' && tempSym != '\0') 
					to_binary_code((int)tempSym); // Translate this symbol to binary code and print it
				else
					cout << endl;
			}
			fclose(out);
			number_openings += 1;
		}
		else
			cout << "File wasn't opened";
	}
};