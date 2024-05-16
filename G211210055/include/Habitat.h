#ifndef HABITAT_H
#define HABITAT_H

#include "Canli.h"

typedef struct {
    int genislik;
    int yukseklik;
    Canli*** alan; // Habitat alanı
} Habitat;

// Diğer fonksiyonlar
void habitatDestroy(Habitat* habitat);
void createHabitatFromFile(const char* dosya_yolu, Habitat* habitat);
void printHabitatStatus(Habitat* habitat);
void naturalSelection(Habitat* habitat); //butun yeme ilişkilerim burada
double distance(int x1, int y1, int x2, int y2); //uzaklık hesaplamalarım
void clear_screen();


#endif



