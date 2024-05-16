// Sinek.h
#ifndef SINEK_H
#define SINEK_H

#include "Canli.h"

// Sinek sınıfının tanımı
typedef struct Sinek {
    Canli canli; // Canli sınıfından miras alınacak
} Sinek;

// Sinek yapısını oluşturacak fonksiyon
Sinek* sinek_olustur(int x, int y, int deger);
char* sinek_gorunum();
#endif


