#include <stdio.h>
#include "Habitat.h"
#include <stdlib.h>
int main() {

	Habitat* habitat = (Habitat*)malloc(sizeof(Habitat)); //habitat adında bir işaretçi oluşturdum ve bunu habitat türünde verileri içerecek kadar bellek tahsis ettirdim

    // Bellek ayrılma işleminin başarısız olup olmadığını kontrol ediyorum
    if (habitat == NULL) {
        fprintf(stderr, "Bellek ayrılma hatası\n");
        return 1; // Hata durumunu döndür
    }
	
    createHabitatFromFile("Veri.txt", habitat); //veri.txt dosyasından verileri okuyoruz
	printf("Initial state of habitat:\n");
    // Habitat durumunu ekrana yazdırma fonksiyonunu çağırdım
    printHabitatStatus(habitat);
	// Yeme ilişkilerini uygula
	int character;
    printf("Enter any random character: ");
    character = getchar(); //kullanıcı tarafından klavyeden bir karakteri okuyup character degiskenine atadım
	while(character){
		naturalSelection(habitat);
	}
    // Belleği serbest bıraktım
    habitatDestroy(habitat);

    return 0;
}
