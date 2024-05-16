// Canli.h

#ifndef CANLI_H
#define CANLI_H

// Ön bildirim
struct Habitat;

typedef struct {
    int x;
    int y;
    int deger;
	char sembol; // Yeni özellik: sembol
    void (*hareket_et)(struct Habitat* habitat); // Hareket etme fonksiyonu
    char* (*gorunum)(); // Görünüm fonksiyon göstericisi
} Canli;

Canli* canli_olustur(int x, int y, int deger);
void canli_yok_et(Canli* canli);

#endif
