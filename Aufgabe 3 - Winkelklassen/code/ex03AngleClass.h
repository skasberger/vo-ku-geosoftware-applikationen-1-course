/*
Programmer: Stefan Kasberger, #10114616
Date: 02.05.2012
*/


class AngleClass {
public:
AngleClass(); // Konstruktor
~AngleClass(); // Destruktor

// Functions
void setGon(double gon);
double getGon();
void setDeg(double deg);
double getDeg();
void setRad(double rad);
double getRad();

private:
// Attributes
double gon_value; // Wert als GON gespeichert
};
