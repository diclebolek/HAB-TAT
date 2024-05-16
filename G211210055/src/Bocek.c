// Bocek.c
#include "Bocek.h"
#include <stdlib.h>
Bocek* bocek_olustur(int x, int y, int deger) {
    Bocek* bocek = (Bocek*)malloc(sizeof(Bocek));
    if (bocek == NULL) {
        return NULL;
    }
    // Canli sınıfının özelliklerini ayarlayın
    bocek->canli.x = x;
    bocek->canli.y = y;
    bocek->canli.deger = deger;
    // Bocek sınıfının görünüm fonksiyonunu atayın
    bocek->canli.gorunum = bocek_gorunum;
    return bocek;
}

char* bocek_gorunum() {
    return "C"; // Böceği temsil eden harf
}
