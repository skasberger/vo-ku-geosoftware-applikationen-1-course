/*
Programmer: Stefan Kasberger, #10114616
Date: 05.05.2012
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>
using namespace std;

int getRand(int max);
double skalaresProdukt(double x_vektor1, double y_vektor1, double x_vektor2, double y_vektor2, double betrag_vektor1, double betrag_vektor2);

class vektor {
public:
    double getNorm();
    int x;
    int y;
};

double vektor::getNorm() {
    double norm;

    norm = sqrt( y * y + x * x );

    return norm;
}


int main()
{
    int i, v1 = 2, v2 = 5;
    vector<vektor>::const_iterator it;
    vector<vektor> liste(20);

    cout << "PROGRAMM VEKTOR" << endl;
    cout << "Listenelemente: " << (int)liste.size() << endl;

    // Größe des Containers verändern
    liste.resize(23);
    cout << "Listenelemente (resize +3): " << (int)liste.size() << endl;

    // Befüllen der Vektoren mit Werten
    i = 0;
    for( it = liste.begin(); it != liste.end(); it++ ) {
        liste[i].x = (double)getRand(10);
        liste[i].y = (double)getRand(10);
        i++;
    }

    // Formatierte Ausgabe der Vektoren mit Normvektor
    i = 0;
    for( it = liste.begin(); it != liste.end(); it++ ) {
        cout << "Vektor " << i+1 << " (" << it->x << "," << it->y << ")" << " -> Norm = " << liste[i].getNorm() << endl;
        i++;
    }

    // Skalare Multiplikation
    cout << "Skalares Produkt von Vektor " << v1+1 << "(" << liste[v1].x << "," << liste[v1].y << ") und Vektor " << v2+1 << "(" << liste[v2].x << "," << liste[v2].y << ") = " << skalaresProdukt( liste[v1].x, liste[v1].y, liste[v2].x, liste[v2].y, liste[v1].getNorm(), liste[v2].getNorm() ) << endl;

    liste.clear();
    return 0;
}

double skalaresProdukt(double x_vektor1, double y_vektor1, double x_vektor2, double y_vektor2, double betrag_vektor1, double betrag_vektor2) {
    double skalar, winkel;

    // Winkel berechnen
    winkel = atan2l(y_vektor1, x_vektor1) - atan2l(y_vektor2, x_vektor2);

    skalar = betrag_vektor1 * betrag_vektor2 * cos(winkel);

    return skalar;
}


int getRand(int max) {
    // Returns a random integer between 0 and max.
    // If max==0, then the result is between 0 and RAND_MAX (predefined constant)

    int u = rand();

    if (max > 0) {
        u %= max;
    }
    return u;
}
