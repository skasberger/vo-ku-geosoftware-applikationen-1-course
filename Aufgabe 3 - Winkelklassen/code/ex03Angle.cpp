/*
Programmer: Stefan Kasberger, #10114616
Date: 02.05.2012
*/

#include <iostream>
#include "ex03AngleClass.h"

using namespace std;

int main() {
  AngleClass alpha, beta, gamma;
  double gon, deg, rad;

  for(gon=-50; gon<=200; gon+=50) {
    alpha.setGon(gon);
    cout << gon<< "gon "
	 << alpha.getGon() << "gon "
	 << alpha.getDeg()  << "deg "
	 << alpha.getRad()  << "rad " << endl;
    deg = alpha.getDeg();
    beta.setDeg(deg);
    cout << deg<< "deg "
	 << beta.getGon() << "gon "
	 << beta.getDeg()  << "deg "
	 << beta.getRad()  << "rad " << endl;
    gamma.setRad(beta.getRad());
    rad = gamma.getRad();
    cout << rad << "rad" << endl;
  }
  return 0;
}
