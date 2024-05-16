
// Bitki.h
#ifndef BITKI_H
#define BITKI_H
#include "Canli.h"

// Bitki sınıfının tanımı
typedef struct Bitki {
    Canli canli; // Canli sınıfından miras alınacak
} Bitki;

// Bitki yapısını oluşturacak fonksiyon
Bitki* bitki_olustur(int x, int y, int deger);
char* bitki_gorunum();
#endif
