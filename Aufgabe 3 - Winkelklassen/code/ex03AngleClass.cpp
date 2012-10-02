/*
Programmer: Stefan Kasberger, #10114616
Date: 02.05.2012
*/

#include "ex03AngleClass.h"

AngleClass::AngleClass() {
    gon_value = 0;
}

AngleClass::~AngleClass() {
    gon_value = 0;
}

void AngleClass::setGon(double gon) {
    gon_value = gon;
}


double AngleClass::getGon() {
    return gon_value;
}


void AngleClass::setDeg(double deg) {
    gon_value = 10 * deg / 9;
}


double AngleClass::getDeg() {
    return (gon_value * 0.9);
}


void AngleClass::setRad(double rad) {
    gon_value = 400 * rad / (2 * 3.14159);
}


double AngleClass::getRad() {
    return (gon_value * (2 * 3.14159) / 400);
}
