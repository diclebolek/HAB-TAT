// Sinek.c
#include "Sinek.h"
#include <stdlib.h>
Sinek* sinek_olustur(int x, int y, int deger) {
    Sinek* sinek = (Sinek*)malloc(sizeof(Sinek));
    if (sinek == NULL) {
        return NULL;
    }
    // Canli sınıfının özelliklerini ayarlayın
    sinek->canli.x = x;
    sinek->canli.y = y;
    sinek->canli.deger = deger;
    // Sinek sınıfının görünüm fonksiyonunu atayın
    sinek->canli.gorunum = sinek_gorunum;
    return sinek;
}

char* sinek_gorunum() {
    return "S"; // Sineği temsil eden harf
}
