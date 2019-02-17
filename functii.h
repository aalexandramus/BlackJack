#ifndef FUNCTII_H_INCLUDED
#define FUNCTII_H_INCLUDED
#include "structuri.h"

;
enum StartJoc
{
    UNU=1,
    DOI,
    TREI,
};


void Amesteca( bool baCartiDate[] )
{
    int iContor;
    for ( iContor=0; iContor<52; ++iContor)
    {
        baCartiDate[iContor]=false;
    }
}

//Aceasta functie returneaza valoarea unei carti noi si verifica daca a fost sau nu impartita deja
int UrmatoareaCarte(bool baCartiDate[])
{
    bool bCarteData	= true;
    int iCarteNoua	= -1;
    do
    {
        iCarteNoua = (rand() % 52);
        if (!baCartiDate[iCarteNoua])
        {
            bCarteData = false;
        }
    }
    while (bCarteData);
    return iCarteNoua;
}

int PunctajMana(int iaMana[], const int kiNumarCarte)
{
    int iContorCarti;
    int iContorAs	= 0;
    int iPunctaj	= 0;
    for ( iContorCarti = 0; iContorCarti < kiNumarCarte; ++iContorCarti)
    {
        const int kiUrmatoareaCarte = iaMana[iContorCarti];
        const int kiRang = (kiUrmatoareaCarte % 13);
        if (kiRang == 0)
        {
            ++iContorAs;
            ++iPunctaj;
        }
        else if (kiRang < 9)
        {
            iPunctaj = iPunctaj + (kiRang + 1);
        }
        else
        {
            iPunctaj = iPunctaj + 10;
        }
    }
    while (iContorAs > 0 && iPunctaj < 12)
    {
        --iContorAs;
        iPunctaj = iPunctaj + 10;
    }
    return iPunctaj;
}
void AfiseazaCarte(int iCarte)
{
    //Afiseaza Rang
    const int kiRang = (iCarte % 13);
    if (kiRang == 0)
    {
        printf("A");
    }
    else if (kiRang < 9)
    {
        printf("%d",(kiRang + 1));
    }
    else if (kiRang == 9)
    {
        printf("10");
    }
    else if (kiRang == 10)
    {
        printf("J");
    }
    else if (kiRang == 11)
    {
        printf("Q");
    }
    else
    {
        printf("K");
    }

}

void AfiseazaMana(int iaMana[], const int kiNumarCarte)
{
    int iContorCarti;
    for ( iContorCarti = 0; iContorCarti < kiNumarCarte; ++iContorCarti)
    {
        const int kiUrmatoareaCarte = iaMana[iContorCarti];
        AfiseazaCarte(kiUrmatoareaCarte);
        printf(" ");
    }
    printf("\n");
}


void AfiseazaPsiM(int iaManaCasa[], const int kiContorCartiC, int iaManaJucator[], const int kiContorCartiJ)
{
    printf("Mana Casei: Punctaj = %d \n",PunctajMana(iaManaCasa, kiContorCartiC));
    AfiseazaMana(iaManaCasa, kiContorCartiC);
    printf("Mana Jucatorului: Punctaj = %d \n",PunctajMana(iaManaJucator, kiContorCartiJ));
    AfiseazaMana(iaManaJucator, kiContorCartiJ);
    printf("\n");
}

void joc()
{
    //Alocare dinamica
    struct Jucator *  J = ( struct Jucator * ) malloc( sizeof( struct Jucator ));
    struct Jucator * C = ( struct Jucator * ) malloc( sizeof( struct Jucator ));
    if((J==NULL)||(C==NULL)) printf("Eroare la alocare");

    printf("Jocul incepe in \n %2d\n %2d\n %2d \n", TREI, DOI, UNU);
    FILE *f= fopen("castiguri.txt","w");
    if(f == NULL) printf("Nu s-a putut deschide fisierul");
    int n,i=0;
    printf("Introduceti numarul de runde dorite:");
    scanf("%d", &n);
    J->NrCastig=0;
    C->NrCastig=0;
    bool baCartiDate[NRCARTI];
    int iContorCartiC = 0;
    int iaManaCasa[MANA];
    int iContorCartiJ = 0;
    int iaManaJucator[MANA];  //Jucatorul poate sa aiba in mana maxim 11 carti (4 de 1, 4 de 2, 3 de 3)
    //La a 12-a carte pierde automat

    //Acest ciclu se executa o data pentru fiecare mana
    for(i=1; i<=n; i++)
    {
        //Amesteca cartile. Vezi functia corespunzatoare
        Amesteca(baCartiDate);
        //Impartirea cartilor. 2 carti pentru casa, 2 pentru jucator.
        iaManaJucator[0]	= UrmatoareaCarte(baCartiDate);
        iaManaCasa[0]		= UrmatoareaCarte(baCartiDate);
        iaManaJucator[1]	= UrmatoareaCarte(baCartiDate);
        iaManaCasa[1]		= UrmatoareaCarte(baCartiDate);
        iContorCartiC		= 2;
        iContorCartiJ		= 2;

        fprintf(f, "Runda %d : ",i);
        //Afiseaza mesaj pentru inceperea unei maini noi
        printf("\n================================================================================ \n");
        printf("+------------------------+ \n");
        printf("|----------Mana----------| \n");
        printf("|----------Noua----------| \n");
        printf("+------------------------+ \n");

        //In acest joc jucatorul are doua optiuni: Hit sau Stand.
        //Hit -> Mai primeste o carte; Stand -> Nu mai primeste
        char cOptiuneJucator;
        bool bHit	= true;
        int iPunctajJucator	= PunctajMana(iaManaJucator, iContorCartiJ);
        // Daca playerul mai doreste o carte, primeste dupa care se calculeaza scorul si se afiseaza mana.
        do
        {
            //Afiseaza mainile (se afiseaza doar o carte a casei si 2 ale jucatorului)
            printf("Mana Casei ");
            printf("[] ");
            AfiseazaCarte(iaManaCasa[1]);
            printf("\n");
            printf("Mana Jucatorului: Punctaj = %d \n", PunctajMana(iaManaJucator, iContorCartiJ));
            AfiseazaMana(iaManaJucator, iContorCartiJ);


            printf("D daca mai doriti o carte sau N daca va opriti:");
            scanf("%s",&cOptiuneJucator);
            if (cOptiuneJucator == 'D' || cOptiuneJucator == 'd')
            {
                iaManaJucator[iContorCartiJ] = UrmatoareaCarte(baCartiDate);
                ++iContorCartiJ;
            }
            else if (cOptiuneJucator == 'N' || cOptiuneJucator == 'n')
            {
                bHit = false;
            }
            else
            {
                printf("Eroare: Incearca din nou");
            }
            printf("\n");

            //Calculeaza Punctaj
            iPunctajJucator	= PunctajMana(iaManaJucator, iContorCartiJ);
        }
        while (bHit && iPunctajJucator < 22);

        // Daca jucatorul nu mai doreste carti se verifica cine a castigat
        if (iPunctajJucator > 21)
        {
            // Casa castiga
            printf("**** Casa a castigat!!! ****\n");
            fprintf(f,  "Casa a castigat\n");
            C->NrCastig++;
            AfiseazaPsiM(iaManaCasa, iContorCartiC, iaManaJucator, iContorCartiJ);
        }
        else
        {
            // Daca jucatorul nu a pierdut si casa este sub 17 pct, casa mai ia carti
            int iPunctajCasa = PunctajMana(iaManaCasa, iContorCartiC);
            while (iPunctajCasa < 17)
            {
                iaManaCasa[iContorCartiC] = UrmatoareaCarte(baCartiDate);
                ++iContorCartiC;
                iPunctajCasa = PunctajMana(iaManaCasa, iContorCartiC);
            }
            bool bCasaPierde = (iPunctajCasa > 21);
            if (bCasaPierde)
            {
                // Casa pierde, jucatorul castiga
                printf("**** Jucatorul a castigat!!! ****\n");
                fprintf(f, "Jucatorul a castigat\n");
                J->NrCastig++;
                AfiseazaPsiM(iaManaCasa, iContorCartiC, iaManaJucator, iContorCartiJ);
            }
            else
            {
                // Compara punctajele
                if (iPunctajJucator == iPunctajCasa)
                {
                    //Egalitate
                    printf("**** Egalitate!!! ****\n");
                    fprintf(f,"Egalitate\n");
                    AfiseazaPsiM(iaManaCasa, iContorCartiC, iaManaJucator, iContorCartiJ);
                }
                else if (iPunctajJucator > iPunctajCasa)
                {
                    // Jucatorul castiga
                    printf("**** Jucatorul a castigat!! ****\n");
                    fprintf(f, "Jucatorul a castigat\n");
                    J->NrCastig++;
                    AfiseazaPsiM(iaManaCasa, iContorCartiC, iaManaJucator, iContorCartiJ);
                }
                else
                {
                    // Casa castiga
                    printf("**** Casa a castigat!!! ****\n");
                    fprintf(f, "Casa a castigat\n");
                    C->NrCastig++;
                    AfiseazaPsiM(iaManaCasa, iContorCartiC, iaManaJucator, iContorCartiJ);
                }
            }
        }

    }

    fprintf(f,"Jucatorul a castigat de %d ori \nCasa a castigat de %d ori", J->NrCastig, C->NrCastig);
    fclose(f);
    free(J);
    free(C);
}

#endif // FUNCTII_H_INCLUDED
