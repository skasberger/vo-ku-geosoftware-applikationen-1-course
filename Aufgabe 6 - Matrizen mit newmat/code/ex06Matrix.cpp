/*
Program: Matrizenberechnung
Programmer: Stefan Kasberger, Matr. Nr. 1011416
Datum: 14. Juni 2012
*/

#include <iostream>
//#include <iomanip.h>
#include <newmat.h>
#include <newmatio.h>
#include <newmatap.h>
#include <fstream>
#include <string>
using namespace std;

// Clearscreen for Windows and Linux
/*#if WIN32
#define CLEARSCREEN system( "cls" );
#else if LINUX
#define CLEARSCREEN system( "clear" );
#endif*/

char menu();
void matrix(char *filename, int size);

int main()
{
    char selection[80];
    //int size = 0;

    //CLEARSCREEN;

    while(selection[0] != '\e') {
        cout << "MENUE" << endl;
        cout << "ESC....Beenden" << endl << endl;
        cout << "Dateiname der Matrix eingeben:";

        cin >> selection;


        /*if(selection[2] == '0') size = selection[3];
        else {
            size = selection[2] * 10 + selection[3];
        }*/

        if(selection[0] != '\e') matrix(selection, 5);
    }
}

void matrix(char *filename, int size) {
    //double row[25] = {1, 1, 1, 1, 1, 1, 2, 3, 4, 5, 1, 3, 6, 1, 1.5, 1, 4, 1, 2, 3.5, 1, 5, 1.5, 3.5, 7};
    double row[size * size];
    string cell;
    int i = 0;
    ifstream file;

    // Matrices
    Matrix matrix_input(size, size);
    SymmetricMatrix SymMatrix(size);
    UpperTriangularMatrix lowMatrix_transp(size);

    // open File
    //file.open(filename);
    file.open("X_05.txt");
    if ( file.fail () ) {
        cerr << "Oeffnen zum Lesen unmoeglich !" << endl;
        exit (1);
    }
    else {
        cout << "... Datei wurde eingelesen." << endl;
        while (file >> cell) {
            row[i] = cell;
            cout << "row:" << row[i] << "i: " << i << endl;
            i++;
        }
    }
    file.close();

    //matrix_input << 1 << 1 << 1 << 1 << 1 << 1 << 2 << 3 << 4 << 5 << 1 << 3 << 6 << 1 << 1.5 << 1 << 4 << 1 << 2 << 3.5 << 1 << 5 << 1.5 << 3.5 << 7;
    matrix_input << row;
    SymMatrix << matrix_input;

    cout << "MATRIX" << endl;
    //cout << setw(10) << setprecision(5) << matrix;
    cout << SymMatrix;

    // Cholesky
    LowerTriangularMatrix lowMatrix = NEWMAT::Cholesky(SymMatrix);

    cout << "CHOLESKY" << endl;
    cout << lowMatrix;

    lowMatrix_transp = lowMatrix.t();
    cout << "CHOLESKY TRANSPONIERT" << endl;
    cout << lowMatrix_transp;

    if(lowMatrix * lowMatrix_transp == SymMatrix) {
        cout << "EQUATION = TRUE" << endl;

    }
    else {
        cout << "EQUATION = FALSE" << endl;
    }
}

// Improvements
// eifnach nur anzahl der spalten bei eingabe angeben und die passende Datei wird daraus zusammengefügt =>  15 => X_15.txt wird geöffnet
