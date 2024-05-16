// Pire.c
#include "Pire.h"
#include <stdlib.h>

Pire* pire_olustur(int x, int y, int deger) {
    Pire* pire = (Pire*)malloc(sizeof(Pire));
    if (pire == NULL) {
        return NULL;
    }
    // Canli sınıfının özelliklerini ayarlayın
    pire->canli.x = x;
    pire->canli.y = y;
    pire->canli.deger = deger;
    // Pire sınıfının görünüm fonksiyonunu atayın
    pire->canli.gorunum = pire_gorunum;
    return pire;
}

char* pire_gorunum() {
    return "P"; // Pireyi temsil eden harf
}
