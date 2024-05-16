// Bitki.c
#include "Bitki.h"
#include <stdlib.h>
Bitki* bitki_olustur(int x, int y, int deger) {
    Bitki* bitki = (Bitki*)malloc(sizeof(Bitki));
    if (bitki == NULL) {
        return NULL;
    }
    // Canli sınıfının özelliklerini ayarlayın
    bitki->canli.x = x;
    bitki->canli.y = y;
    bitki->canli.deger = deger;
    // Bitki sınıfının görünüm fonksiyonunu atayın
    bitki->canli.gorunum = bitki_gorunum;
    return bitki;
}

char* bitki_gorunum() {
    return "B"; // Bitkiyi temsil eden harf
}

