#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "Habitat.h"
#include "Bitki.h"
#include "Bocek.h"
#include "Sinek.h"
#include "Pire.h"
void clear_screen() {
    printf("\033[2J\033[H"); // ANSI escape kodu ile ekranı temizle
}
void createHabitatFromFile(const char* dosya_yolu, Habitat* habitat) {
    FILE* dosya = fopen(dosya_yolu, "r");
    if (dosya == NULL) {
        printf("Dosya acilamadi: %s\n", dosya_yolu);
        exit(EXIT_FAILURE);
    }


    // Habitatın genişliğini hesaplama
    int genislik = 0;
    int maks_eleman_sayisi = 0;
    char satir[100]; // Örnek olarak bir satırın maksimum uzunluğunu 100 olarak alıyoruz

    while (fgets(satir, sizeof(satir), dosya) != NULL) {
        int eleman_sayisi = 0;
        int deger;
        char* token = strtok(satir, " \t\n");
        while (token != NULL) {
            sscanf(token, "%d", &deger);
            eleman_sayisi++;
            token = strtok(NULL, " \t\n");
        }

        if (eleman_sayisi > maks_eleman_sayisi) {
            maks_eleman_sayisi = eleman_sayisi;
        }

        genislik++;
    }

    // Dosya imleci başa alınıyor
    fseek(dosya, 0, SEEK_SET);

    // Yükseklik değerini ayarlama
    habitat->yukseklik = maks_eleman_sayisi;

    // Genişlik değerini ayarlama
    habitat->genislik = genislik;

    // Alanı oluşturma
	habitat->alan = (Canli***)malloc(habitat->genislik * sizeof(Canli**));
    for (int i = 0; i < habitat->genislik; i++) {
        habitat->alan[i] = (Canli**)malloc(habitat->yukseklik * sizeof(Canli*));
        for (int j = 0; j < habitat->yukseklik; j++) {
            habitat->alan[i][j] = (Canli*)malloc(sizeof(Canli));
        }
    }

	int x = 0, y = 0;
    int deger;
    while (fscanf(dosya, "%d", &deger) != EOF) {
        Canli* canli;
        if (deger >= 1 && deger <= 9) {
            Bitki* bitki = bitki_olustur(x, y, deger);
            canli = (Canli*)bitki; // Bitki işaretçisini Canli türüne dönüştür
        } else if (deger >= 10 && deger <= 20) {
            Bocek* bocek = bocek_olustur(x, y, deger);
            canli = (Canli*)bocek; // Böcek işaretçisini Canli türüne dönüştür
        } else if (deger >= 21 && deger <= 50) {
            Sinek* sinek = sinek_olustur(x, y, deger);
            canli = (Canli*)sinek; // Sinek işaretçisini Canli türüne dönüştür
        } else if (deger >= 51 && deger <= 99) {
            Pire* pire = pire_olustur(x, y, deger);
            canli = (Canli*)pire; // Pire işaretçisini Canli türüne dönüştür
        } else {
            printf("Hata: Geçersiz deger: %d\n", deger);
            exit(EXIT_FAILURE);
        }

        habitat->alan[x][y] = canli;




        // İlerlemeyi ayarla
        y++;
        if (y >= habitat->yukseklik) {
            y = 0;
            x++;
        }
	
    }
	
    fclose(dosya);
}

void printHabitatStatus(Habitat* habitat) {
    for (int i = 0; i < habitat->genislik; i++) {
        for (int j = 0; j < habitat->yukseklik; j++) {
            Canli* canli = habitat->alan[i][j];
            if (canli != NULL) {
                printf("%s ", canli->gorunum());
            } else {
                printf("X ");
            }
        }
        printf("\n");
    }
}
// İki nokta arasındaki öklid mesafesini hesaplayan fonksiyon
double distance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void naturalSelection(Habitat* habitat) {
    int genislik = habitat->yukseklik;
    int yukseklik = habitat->genislik;
	Canli* deger;
	deger = habitat->alan[0][0];
    int canli = deger->deger; // hayatta olanı temsil edecek
    for (int i=0; i < genislik; i++) {
		
        for (int j=0; j < yukseklik+1; j++) {
            
			
			if (!(i == 0 && j == 0)) {//ilk hücreyi saymasın diye ekledim
			//printf("Coordinate: (%d, %d)\n", i, j);
				if (habitat->alan[i][j] != NULL) {
					if (canli >= 10 && canli <= 20) { //canli eger bocekse
					
						if (habitat->alan[i][j]->deger >= 10 && habitat->alan[i][j]->deger <= 20) { //sıradaki hücre böcek mi karşılaştırması yapılır büyük olan yaşar
							if (canli > habitat->alan[i][j]->deger) { //eger canlinin degeri büyükse hayatta kalır 
								free(habitat->alan[i][j]);
								habitat->alan[i][j] = NULL;

								
							}else if (canli == habitat->alan[i][j]->deger) { // Eğer aynı değere sahip bir canlı varsa
								double mesafe1 = distance(deger->x, deger->y, genislik, yukseklik);
								double mesafe2 = distance(i, j, genislik, yukseklik);
								if (mesafe2>mesafe1) {							
									// Daha uzak olan ölecek
									free(habitat->alan[i][j]);
									habitat->alan[i][j] = NULL;

								}
								else {
									//  
									free(deger);
									deger = NULL;
									deger=habitat->alan[i][j];
									canli = deger->deger;
								}
							}else {//eger canlinin degeri kucukse
									free(deger);
									deger = NULL;
									deger=habitat->alan[i][j];
									canli = deger->deger;
							}
						}else if (habitat->alan[i][j]->deger >= 1 && habitat->alan[i][j]->deger <= 9 || habitat->alan[i][j]->deger >= 51 && habitat->alan[i][j]->deger <= 99) { // Bitki yada pireyse
								free(habitat->alan[i][j]);
								habitat->alan[i][j] = NULL;
								
						}else if (habitat->alan[i][j]->deger >= 21 && habitat->alan[i][j]->deger <= 50) { // Sıradaki hucre sinekse
							free(deger);
							deger = NULL;
							deger=habitat->alan[i][j];
							canli = deger->deger;
							
						}else {
							continue;
						}
						
										
					}else if (canli >= 1 && canli <= 9) { // Bitki ise hücredeki
						if (habitat->alan[i][j]->deger >= 1 && habitat->alan[i][j]->deger <= 9) { //siradaki hücre bitkiyse
							if (canli > habitat->alan[i][j]->deger) {
								free(habitat->alan[i][j]);
								habitat->alan[i][j] = NULL;
								
							}else if (canli == habitat->alan[i][j]->deger) { // Eğer aynı değere sahip bir canlı varsa
								double mesafe1 = distance(deger->x, deger->y, genislik, yukseklik);
								double mesafe2 = distance(i, j, genislik, yukseklik);
								if (mesafe2>mesafe1) {							
									// Mevcut hücredeki canlı ölecek
									free(habitat->alan[i][j]);
									habitat->alan[i][j] = NULL;
									
								}
								else {
									// Daha uzak olan hayatta kalacak
									free(deger);
									deger = NULL;
									deger=habitat->alan[i][j];
									canli = deger->deger;
								}						
								
							}else if (canli < habitat->alan[i][j]->deger){
								free(deger);
								deger = NULL;
								deger=habitat->alan[i][j];
								canli = deger->deger;
							}
						}else if ( habitat->alan[i][j]->deger >= 21 && habitat->alan[i][j]->deger <= 99) {//siradaki sinek veya pireyse
							free(habitat->alan[i][j]);
							habitat->alan[i][j] = NULL;
							
						}else if ( habitat->alan[i][j]->deger >= 10 && habitat->alan[i][j]->deger <= 20) {//siradaki hucre bocekse

							free(deger);
							deger = NULL;
							deger=habitat->alan[i][j];
							canli = deger->deger;
							
						}else {
							continue;
						}
						
						
					
					}else if (canli >= 21 && canli <= 50) { // sinek ise hücredeki
						if (habitat->alan[i][j]->deger >= 21 && habitat->alan[i][j]->deger <= 50) { //siradaki hücre sinekse
							if (canli > habitat->alan[i][j]->deger) {//canlinin degeri buyukse yasatıyoruz
								free(habitat->alan[i][j]);
								habitat->alan[i][j] = NULL;
								
							}else if (canli == habitat->alan[i][j]->deger) { // Eğer aynı değere sahip bir canlı varsa
								double mesafe1 = distance(deger->x, deger->y, genislik, yukseklik);
								double mesafe2 = distance(i, j, genislik, yukseklik);
								if (mesafe2>mesafe1) {							
									// Mevcut hücredeki canlı ölecek
									free(habitat->alan[i][j]);
									habitat->alan[i][j] = NULL;
									
								}
								else {
									// Daha uzak olan hayatta kalacak
									free(deger);
									deger = NULL;
									deger=habitat->alan[i][j];
									canli = deger->deger;
								}						
								
							}else if (canli < habitat->alan[i][j]->deger) { //canlinin degeri kucukse hucreyi nulla atıyoruz
								free(deger);
								deger = NULL;
								deger=habitat->alan[i][j];
								canli = deger->deger;
							}
						}else if ( habitat->alan[i][j]->deger >= 10 && habitat->alan[i][j]->deger <= 20 || habitat->alan[i][j]->deger >= 51 && habitat->alan[i][j]->deger <= 99) {//böcek yada pireyse sıradaki null yapıyoruz hücreleri
							free(habitat->alan[i][j]);
							habitat->alan[i][j] = NULL;
							
						}else if ( habitat->alan[i][j]->deger >= 1 && habitat->alan[i][j]->deger <= 9) {//siradaki bitkiyse sinegi yer

							free(deger);
							deger = NULL;
							deger=habitat->alan[i][j];
							canli = deger->deger;
							
						}else {
							continue;
						}
						
					}else if(canli >= 51 && canli <= 99){ // pire ise hücredeki
						if (habitat->alan[i][j]->deger >= 51 && habitat->alan[i][j]->deger <= 99) { 
							if (canli == habitat->alan[i][j]->deger) { // Eğer aynı değere sahip bir canlı varsa
								double mesafe1 = distance(deger->x, deger->y, genislik, yukseklik);
								double mesafe2 = distance(i, j, genislik, yukseklik);
								if (mesafe2>mesafe1) {							
									// Mevcut hücredeki canlı ölecek
									free(habitat->alan[i][j]);
									habitat->alan[i][j] = NULL;
									
								}
								else {
									// Daha uzak olan hayatta kalacak
									free(deger);
									deger = NULL;
									deger=habitat->alan[i][j];
									canli = deger->deger;
								}						
								
							}else { //canlinin degeri kucukse hucreyi nulla atıyoruz
								free(deger);
								deger = NULL;
								deger=habitat->alan[i][j];
								canli = deger->deger;
							}
						}else if ( habitat->alan[i][j]->deger >= 1 &&  habitat->alan[i][j]->deger <= 50) {//siradaki bitkiyse
							free(deger);
							deger = NULL;
							deger=habitat->alan[i][j];
							canli = deger->deger;
							
						}else {
							continue;
						}
	
					}else{
					continue;
				}
					
					
				}else{
					continue;
				}
				
			}													
			clear_screen(); //// ANSI escape kodu kullandım
			//printf("Current status of habitat:\n"); //çıktıları izledim
			//printHabitatStatus(habitat);
			printf("Kazanan: %s : (%d, %d)\n", deger->gorunum(), deger->x, deger->y);//canli değişkeni, deger işaretçisinin değerine eşit olduğu için deger işaretçisine erişerek onun kordinatlarını yazdırdım 1 den başlaması icin 1 ekledim
			printf("Value in the cell of the winning animal: %d\n", canli); //calisiyor		
        }

    }
			//printf("Hayatta kalan canli: (%d, %d)\n", hayatta_kalan->x, hayatta_kalan->y); // Koordinatları yazdır	

}



void habitatDestroy(Habitat* habitat) {
    if (habitat == NULL) {
        return;
    }

    for (int i = 0; i < habitat->genislik; i++) {
        for (int j = 0; j < habitat->yukseklik; j++) {
            Canli* canli = habitat->alan[i][j];
            if (canli != NULL) {
                free(canli);
            }
        }
        free(habitat->alan[i]);
    }

    free(habitat->alan);
    free(habitat);
}