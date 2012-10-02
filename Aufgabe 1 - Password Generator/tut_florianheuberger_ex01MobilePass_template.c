#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getRand(int max) {
  // Returns a random integer between 0 and max.
  // If max==0, then the result is between 0 and RAND_MAX (predefined constant)
  int u = rand();
  if (max > 0) {
    u %= max;
  }
  return u;
}

char getKeyChar(short key, char use_first);

void generate_pass(int len);



int main() {
    srand(time(NULL)); // Zufallsgenerator jetzt(!) neu starten
    const int pass_len = 10;
    generate_pass(pass_len);
    return 0;
}



char getKeyChar(short key, char use_first) {
  // TODO:
  // * Wenn use_first==1: gib "Hauptbuchstaben" der Taste key zurueck
  // * Wenn use_first==0: gib zufalls-gestuetzt eines der Zeichen von Taste key zurueck
}

void generate_pass(int len) {
  char password[10]; // Achtung!

    // TODO:
    // * Waehle len-mal eine Taste x zwischen 0 und 9

    // TODO:
    // * entweder:
    //   Rufe getKeyChar(x,1) auf und speichere Resultat als Anfangsbuchstabe von password[]
    // * oder:
    //   Rufe getKeyChar(x,0) fuer alle uebrigen Buchstaben von password[] auf

    // * Schreibe fertiges Passwort:
    /* z.B.: */ printf("%s\n", password);
}

