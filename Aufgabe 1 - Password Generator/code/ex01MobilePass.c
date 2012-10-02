#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// #include int getRand(int max)
// #include char getKeyChar(short key, char use_first)
// #include void generate_pass(int len, int button)

/*
Programm:Mobile Phone Passwort Generator
Programmierer: Kasberger Stefan, 1011416
Datum: 08. Maerz 2012
*/

int getRand(int max) {
  // Returns a random integer between 0 and max.
  // If max==0, then the result is between 0 and RAND_MAX (predefined constant)

  int u = rand();
  if (max > 0) {
    u %= max;
  }
  return u;
}

char getKeyChar(short key, char use_first) {
  // TODO:
  // * Wenn use_first==1: gib "Hauptbuchstaben" der Taste key zurueck
  // * Wenn use_first==0: gib zufalls-gestuetzt eines der Zeichen von Taste key zurueck

  // Variablen
  const char taste0[2] = "+0";
  const char taste1[4] = ".,?1";
  const char taste2[4] = "abc2";
  const char taste3[4] = "def3";
  const char taste4[4] = "ghi4";
  const char taste5[4] = "jkl5";
  const char taste6[4] = "mno6";
  const char taste7[5] = "pqrs7";
  const char taste8[4] = "tuv8";
  const char taste9[5] = "wxzy9";

  char button;


  switch (key){
      case 0:
                if(use_first == 0){
                    button = taste0[getRand(strlen(taste0)-1)];
                }
                else if (use_first == 1){
                    button = taste0[0];
                }
      case 1:
                if(use_first == 0){
                    button = taste1[getRand(strlen(taste1)-1)];
                }
                else if (use_first == 1){
                    button = taste1[0];
                }
      case 2:
                if(use_first == 0){
                    button = taste2[getRand(strlen(taste2)-1)];
                }
                else if (use_first == 1){
                    button = taste2[0];
                }
      case 3:
                if(use_first == 0){
                    button = taste3[getRand(strlen(taste3)-1)];
                }
                else if (use_first == 1){
                    button = taste3[0];
                }
      case 4:
                if(use_first == 0){
                    button = taste4[getRand(strlen(taste4)-1)];
                }
                else if (use_first == 1){
                    button = taste4[0];
                }
      case 5:
                if(use_first == 0){
                    button = taste5[getRand(strlen(taste5)-1)];
                }
                else if (use_first == 1){
                    button = taste5[0];
                }
      case 6:
                if(use_first == 0){
                    button = taste6[getRand(strlen(taste6)-1)];
                }
                else if (use_first == 1){
                    button = taste6[0];
                }
      case 7:
                if(use_first == 0){
                    button = taste7[getRand(strlen(taste7)-1)];
                }
                else if (use_first == 1){
                    button = taste7[0];
                }
      case 8:
                if(use_first == 0){
                    button = taste8[getRand(strlen(taste8)-1)];
                }
                else if (use_first == 1){
                    button = taste8[0];
                }
      case 9:
                if(use_first == 0){
                    button = taste9[getRand(strlen(taste9)-1)];
                }
                else if (use_first == 1){
                    button = taste9[0];
                }
      default: break;
  }
  return button;
}

void generate_pass(int len, int button) {
    // Variablen
    char password[len];
    int i = 1;  // Off-Set von 1 wegen anderer Zufallsfunktion bei erstem Zeichen

    // Funktionen
    password[0] = getKeyChar(getRand(button), 0);
    while(i < len) {
        password[i] = getKeyChar(getRand(button), 1);
        i++;
    }
    printf("%s\n", password);
}


int main() {
    srand(time(NULL)); // Zufallsgenerator jetzt(!) neu starten
    const int pass_len = 10;
    const int buttons_count = 10;

    // Starte Passwort Generierung
    generate_pass(pass_len, buttons_count);

    // Rückgabewert bei korrekter Ausführung
    return 0;
}
