#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "constante.h"
#include "functii.h"
#include "structuri.h"


void Amesteca( bool baCartiDate[]);
int UrmatoareaCarte(bool baCartiDate[]);
int PunctajMana(int iaMana[], const int kiContorCarte);
void AfiseazaCarte(int iCarte);
void AfiseazaMana(int iaMana[], const int kiContorCarte);
void AfiseazaPsiM(int iaManaCasa[], const int kiContorCartiC, int iaManaJucator[], const int kiContorCartiJ); //Afiseaza mainile si punctajul


int main()
{
    time_t timp;
    time(&timp);
    srand(timp);

    joc();
    return EXIT_SUCCESS;
}


