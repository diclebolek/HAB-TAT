// Bocek.h
#ifndef BOCEK_H
#define BOCEK_H

#include "Canli.h"

// Bocek sınıfının tanımı
typedef struct Bocek {
    Canli canli; // Canli sınıfından miras alınacak
} Bocek;

// Bocek yapısını oluşturacak fonksiyon
Bocek* bocek_olustur(int x, int y, int deger);
char* bocek_gorunum();
#endif

