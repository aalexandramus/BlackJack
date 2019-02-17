#ifndef STRUCTURI_H_INCLUDED
#define STRUCTURI_H_INCLUDED

 struct Carti
 {
     int valoare;
     char culoare;
 };

 struct Jucator
 {
     struct Carti c[NRCARTI];
     int NrCastig;
 }


#endif // STRUCTURI_H_INCLUDED
