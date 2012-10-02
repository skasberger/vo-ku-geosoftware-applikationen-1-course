/*
Program: Punktverwaltung
Programmer: Stefan Kasberger, Matr. Nr. 1011416
Datum: 20. Maerz 2012
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Clearscreen for Windows and Linux
#if WIN32
#define CLEARSCREEN system( "cls" );
#else if LINUX
#define CLEARSCREEN system( "clear" );
#endif

// Data Type Definitions
enum Punktart {
    GELAENDE, /* allg. Punkt */
    FEST, /* Festpunkt */
    FERN, /* Fernziel */
    POLY, /* Polygonpunkt */
    STAND /* Standpunkt*/ };

struct Punkt {
    char bezeichn[10]; /* Punktname oder -nummer */
    double koord[3]; /* y, x, H (in Meter) */
    enum Punktart art; };

// Function Declaration
int getRand(int max);
char menu();
void create_file();
void open_file(char *strFilename);
void show_list();
void edit_point_menue();
void edit_point();
void add_point();
int search_point(char *point_name);
int string2punktart (char *string);
char* punktart2string(int nummer);
void save_list();

// Global variables
int list_edited = 0;
char filename[80];
int file_open = 0;
int list_elements;
struct Punkt *list;


int main() {
    // main function will loop trough the menu selection until ESCAPE is pushed

    char selection, loc_filename[80] = "points.txt\0";
    int input;

    while(selection != '\e') {
        selection = menu();
        switch(selection) {
            case 'e':
                create_file();
                break;

            case 'o':
                CLEARSCREEN;

                printf("DATEI ÖFFNEN\n\n");
                printf("eigenen Dateinamen eingeben? (ja = 1, nein = 0): ");
                scanf("%i", &input);
                if(input == 1) {
                    printf("Dateiname: ");
                    scanf("%s", loc_filename);
                }
                printf("Filename: %s", loc_filename);
                open_file(loc_filename);

                break;

            case 'b':
                edit_point_menue();
                break;

            case 'a':
                show_list();
                break;

            case 's':
                save_list();

        }
    }
    free(list);
    return 0;
}

char menu() {
    // menu displays the main menu with the useable functions
    char selection;

    CLEARSCREEN;

    printf("MENUE\n");
    if (file_open) {
        printf(" aktueller Datensatz: %s", &filename);
        if(list_edited) printf(" (edited)");
        printf("\n\n");
    }
    else printf(" kein Datensatz geöffnet\n\n");

    printf("e....Datei erstellen\n");
    printf("o....Datei öffnen\n");
    if(file_open) {
        printf("b....Liste bearbeiten\n");
        printf("a....Liste ansehen\n");
    }
    printf("s....Liste sichern\n");
    printf("ESC....Beenden\n\nEingabe: ");
    scanf("%c", &selection);

    return(selection);
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


void create_file() {
    // create_file creates a random file with defined elements for testing
    int eleCount, i, j;
    FILE *fp;
    char loc_filename[80], punktart[9];

    // I/O
    CLEARSCREEN;
    printf("DATEI ERSTELLEN\n\n");
    printf("Dateiname:");
    scanf("%s", &loc_filename);
    printf("\nAnzahl Listenelemente:");
    scanf("%i", &eleCount);

    fp = fopen(loc_filename, "w");

    if (fp == NULL) {
        printf("\nFEHLER: Datei konnte nicht erstellt werden!\n");
    }
    else {
        for(i=0; i< eleCount; i++) {
            strcpy(punktart, punktart2string(getRand(5)));
            fprintf(fp, "test%i, %5.0f, %5.0f, %4.0f, %s\n", getRand(10000),(float) getRand(10000), (float) getRand(10000), (float) getRand(9000), punktart);
        }
        printf("\nDatei \"%s\" wurde erstellt.\n", loc_filename);
    }

    printf("  => erstellte Datei als Datensatz laden? (yes = 1, no = 0): "); // load the new file as actual dataset?
    scanf("%i", &i);
    if (i == 1) {
        fclose(fp);
        CLEARSCREEN;
        open_file(loc_filename);
    }
    else fclose(fp);
}


void open_file(char *strFilename) {
    // this function opens a file and transfers it's data to a struct Punkt array
    int i, n = 0, b = 0, a = 0, j = 0, x = 0, y = 0, h = 0, filerows = 0, position_in_row = 0, row = 0, y_Val = 0, x_Val = 0, h_Val = 0;
    char temp, x_koord[10], y_koord[10], hoehe[5], art[9];
    FILE *fp;

    fp = fopen(strFilename, "r");

    if (fp == NULL) {
        printf("\nFEHLER: Datei konnte nicht geöffnet werden!\n");
    }
    else {
        file_open = 1;
        strcpy(filename, strFilename);
        printf("\nDatei \"%s\" konnte geöffnet werden.\n", filename);

        while (!feof(fp)) { // get the row number
            temp = fgetc(fp);
            if(temp == '\n') filerows++;
        }

        list = malloc(filerows*sizeof(struct Punkt));
        rewind(fp);

        // read out of the file char-by-char until the end-of-the file is reached
        while (!feof(fp)) {
            temp = fgetc(fp);

            if(temp == ',') {
                position_in_row++;
                j = 0;
            }

            else if(temp == '\n') {
                // at the end of a row all variables of the row will be stored and re-initialized
                list[row].bezeichn[b] = '\0';
                y_koord[y] = '\0';
                x_koord[x] = '\0';
                hoehe[h] = '\0';
                art[a] = '\0';

                // transform Koordinaten String to Integer
                for (i=0; i < y; i++) {
                    y_Val = y_koord[i]-48;

                    for(n=0; n+i < y-1; n++) {
                        y_Val *= 10;
                    }
                    list[row].koord[0] += y_Val;
                }

                for (i=0; i < x; i++) {
                    x_Val = x_koord[i]-48;

                    for(n=0; n+i < x-1; n++) {
                        x_Val = x_Val * 10;
                    }
                    list[row].koord[1] += x_Val;
                }

                for (i=0; i < h; i++) {
                    h_Val = hoehe[i]-48;

                    for(n=0; n+i < h-1; n++) {
                        h_Val *= 10;
                    }
                    list[row].koord[2] += h_Val;
                }

                // store Festpunktart
                if(0 == strcmp(art, "GELAENDE")) list[row].art = GELAENDE;
                else if(0 == strcmp(art, "FEST")) list[row].art = FEST;
                else if(0 == strcmp(art, "FERN")) list[row].art = FERN;
                else if(0 == strcmp(art, "POLY")) list[row].art = POLY;
                else if(0 == strcmp(art, "STAND")) list[row].art = STAND;

                // reset all variables for next row
                position_in_row = 0;
                b = 0;
                y = 0;
                x = 0;
                h = 0;
                a = 0;
                y_Val = 0;
                x_Val = 0;
                h_Val = 0;
                *art = "";
                row++;
            }

            // read out the single variables between the commas
            if (temp != ' ' && temp != ',' && temp != '\n') {
                switch(position_in_row) {
                    case 0:
                        list[row].bezeichn[b] = temp;
                        b++;
                        break;

                    case 1:
                        y_koord[y] = temp;
                        y++;
                        break;

                    case 2:
                        x_koord[x] = temp;
                        x++;
                        break;

                    case 3:
                        hoehe[h] = temp;
                        h++;
                        break;

                    case 4:
                        art[a] = temp;
                        a++;
                        break;
                    j++;
                }
            }
        }
    }
    list_elements = filerows;
    fclose(fp);
}


void show_list() {
    // shows the actual dataset as a formatted list in columns and rows
    int i;
    char punktart[9];

    CLEARSCREEN

    printf("AUSGABE AKTUELLE LISTE (%s", filename);
    if(list_edited) printf(" - edited");
        printf(")\n\n");
    printf("BEZEICHNUNG      Y      X  HOEHE  PUNKTART\n");
    for(i=0; i < list_elements;i++) {
        strcpy(punktart, punktart2string((list+i)->art));
        printf("%11s  %5.0f  %5.0f  %5.0f  %8s\n", list[i].bezeichn, list[i].koord[0], list[i].koord[1], list[i].koord[2], punktart); // print list on screen
    }

    printf("\nMöchtest du einen Punkt bearbeiten? (ja = 1, nein = 0)"); // asking for editing the list
    scanf("%i", &i);
    if(i == 1) edit_point_menue();
}

void edit_point_menue() {
    // menu for different point editing functions (updating, adding, deleting)
    int element;
    char bez[10], test[20];
    int selection = 1;

    do {
        // I/O
        CLEARSCREEN;
        printf("PUNKTE BEARBEITEN (%s", filename);
        if(list_edited) printf(" - edited");
        printf(")\n\n");
        printf("1....Punkt ändern\n");
        printf("2....Punkt hinzufügen\n");
        printf("3....Punkt löschen\n");
        printf("0....Abbrechen\n");
        printf("\nEingabe: ");
        scanf("%i", &selection);

        switch(selection) {
            case 1: // edit point
                edit_point();
                break;

            case 2: // add point
                add_point();
                break;

            case 3: // delete point
                CLEARSCREEN;
                printf("PUNKT LÖSCHEN (%s", filename);
                if(list_edited) printf(" - edited");
                printf(")\n\n");
                printf("Punktname eingeben: ");
                scanf("%s", bez);
                element = search_point(bez);
                strcpy(list[element].bezeichn, "EMPTY\0");
                list_edited = 1;
                break;
        }
    }
    while(selection);
}

void edit_point() {
    // updates a point based on input
    int i, flag = 0, input, element;
    double x, y, h;
    char name[10], bez[10], art[20];

    char test[10];

    CLEARSCREEN;

    // I/O
    printf("PUNKT ÄNDERN (%s", filename);
    if(list_edited) printf(" - edited");
    printf(")\n\n");
    printf("0....Alles\n");
    printf("1....Name\n");
    printf("2....Y-Koordinate\n");
    printf("3....X-Koordinate\n");
    printf("4....Höhe\n");
    printf("5....Punktart\n");
    printf("\nEingabe: ");
    scanf("%i", &input);

    do {
        printf("\n\nPunktname eingeben: ");
        scanf("%s", name);
        element = search_point(name);

        if(element >= 0) { // if there has been found an row with the name of 'name', so the return value of search_point is >= 0 , then...
            if(input == 1 || input == 0) {
                printf("\n\"%s\":  Eingabe neuer Name: ", list[element].bezeichn);
                scanf("%s", bez);
                strcpy(list[element].bezeichn, bez);
                list_edited = 1;
            }
            if(input == 2 || input == 0) {
                printf("\n\"%.0f\":  Eingabe neue Y-Koordinate: ", list[element].koord[0]);
                scanf("%lf", &y);
                printf("Y:%f", y);
                list[element].koord[0] = y;
                list_edited = 1;
            }
            if(input == 3 || input == 0) {
                printf("\n\"%.0f\":  Eingabe neue X-Koordinate: ", list[element].koord[1]);
                scanf("%lf", &x);
                printf("X:%f", x);
                list[element].koord[1] = x;
                list_edited = 1;
            }
            if(input == 4 || input == 0) {
                printf("\n\"%.0f\":  Eingabe neue Hoehe: ", list[element].koord[2]);
                scanf("%lf", &h);
                list[element].koord[2] = h;
                list_edited = 1;
            }
            if(input == 5 || input == 0) {
                do {
                    printf("\n\"%s\":  Eingabe neue Punktart (POLY, GELAENDE, FERN, STAND, FEST): ", punktart2string(list[element].art), list[element].art);
                    scanf("%s", art);
                    if (string2punktart(art) > 0) {
                        flag = 1;
                        list[element].art = string2punktart(art);
                    }
                }while(!flag);
            }
        }

    else printf("\n\nFEHLER: Punkt ist nicht vorhanden!");
    } while(element < 0);
}

void add_point() {
    // add a new point at the end and increase punkt array by one
    double x, y, h;
    int punktart;
    char bez[10];

    CLEARSCREEN;

    // I/O
    printf("PUNKT HINZUFÜGEN (%s", filename);
    if(list_edited) printf(" - edited");
    printf(")\n\n");
    printf("\nName: ");
    scanf("%s", bez);
    printf("\nY-Koordinate: ");
    scanf("%lf", &y);
    printf("\nX-Koordinate: ");
    scanf("%lf", &x);
    printf("\nHöhe: ");
    scanf("%lf", &h);
    printf("\nPunktart");
    printf("\n  1. allg. Punkt (GELAENDE)");
    printf("\n  2. Festpunkt (FEST)");
    printf("\n  3. Fernziel (FERN)");
    printf("\n  4. Polygonpunkt (POLY)");
    printf("\n  5. Standpunkt (STAND)");
    printf("\n\nEingabe: ");
    scanf("%i", &punktart);

    if(search_point(bez) >= 0) { // looks for an point with the same name
        printf("\nPunkt ist schon vorhanden, bitte andere Bezeichnung wählen!");
    }
    else {
        list_elements++;
        list_edited = 1;

        struct Punkt *temp = realloc(list, list_elements*sizeof(struct Punkt)); // reallocates memory and sets pointer
        if (temp != NULL) {list = temp;}

        // write new row
        strcpy(list[list_elements-1].bezeichn, bez);
        list[list_elements-1].koord[0] = y;
        list[list_elements-1].koord[1] = x;
        list[list_elements-1].koord[2] = h;
        list[list_elements-1].art = punktart-1;
    }
}


int search_point(char *point_name) {
    // searches for string point_name in the Punkt array and returns the number of the element
    int i, element = -1;
    char bez[10], test[10];

    strcpy(bez, point_name);

    for(i=0; i < list_elements; i++) {

        if(0 == strcmp(list[i].bezeichn, bez)) element = i;
    }
    return element;
}

int string2punktart (char *string) {
    // transforms a Festpunkte string into an integer value and returns this
    int flag = 0, punktart;

    if(0 == strcmp(string, "GELAENDE")) punktart = 0;
    else if(0 == strcmp(string, "FEST")) punktart = 1;
    else if(0 == strcmp(string, "FERN")) punktart = 2;
    else if(0 == strcmp(string, "POLY")) punktart = 3;
    else if(0 == strcmp(string, "STAND")) punktart = 4;
    else {
        printf("\n\nFEHLER: Punktart wurde falsch eingegeben.");
        punktart = -1;
    }
    return punktart;
}

char* punktart2string(int nummer) {
    // transforms an Festpunkt integer into an string and returns the pointer to it
    char string[10];
    switch(nummer) {
        case 0:
            strcpy(string, "GELAENDE\0");
            break;
        case 1:
            strcpy(string, "FEST\0");
            break;
        case 2:
            strcpy(string, "FERN\0");
            break;
        case 3:
            strcpy(string, "POLY\0");
            break;
        case 4:
            strcpy(string, "STAND\0");
            break;
    }
    return string;
}


void save_list() {
    // saves the actual dataset in an new file or writes over the actually loaded file
    int i, input;
    char punktart[9];
    FILE *fp;

    // I/O
    CLEARSCREEN;
    printf("DATEI SPEICHERN\n\n");
    printf("1....in neuer Datei speichern\n");
    printf("2....in aktuller Datei \"%s\" speichern\n", filename);
    printf("\nEingabe: ");
    scanf("%i", &input);

    if(input == 1) {
        printf("\nDateinamen eingeben: ");
        scanf("%s", filename);
    }

    fp = fopen(filename, "w");

    if (fp == NULL) {
        printf("\nFEHLER: Datei konnte nicht gespeichert werden!\n");
    }
    else {
        for(i=0; i < list_elements; i++) {
            if(0 != strcmp(list[i].bezeichn, "EMPTY")) {
                strcpy(punktart, punktart2string(getRand(5)));
                fprintf(fp, "%s, %5.0f, %5.0f, %4.0f, %8s\n", list[i].bezeichn, list[i].koord[0], list[i].koord[1], list[i].koord[2], punktart); // writes row by row into the file
                list_edited = 0;
            }
        }
    }
    fclose(fp);
}
