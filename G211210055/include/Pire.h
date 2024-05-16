// Pire.h
#ifndef PIRE_H
#define PIRE_H

#include "Canli.h"

// Pire sınıfının tanımı
typedef struct Pire {
    Canli canli; // Canli sınıfından miras alınacak
} Pire;

// Pire yapısını oluşturacak fonksiyon
Pire* pire_olustur(int x, int y, int deger);
char* pire_gorunum();

#endif


