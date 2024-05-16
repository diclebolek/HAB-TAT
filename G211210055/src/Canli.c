#include "Canli.h"
#include <stdlib.h>

Canli* canli_olustur(int x, int y, int deger) {
    // Bu fonksiyon soyut olduğu için burada bir işlem yapılmayacak,
    // yalnızca alt sınıflar bu fonksiyonu kendi ihtiyaçlarına göre uygulayacak.
    return NULL;
}


char* gorunum(Canli* canli) {
    // Görünümü belirleyen kodu buraya ekleyin
}
void canli_yok_et(Canli* canli) {
    // Burada genel bir temizleme işlemi yapılabilir,
    // örneğin, dinamik bellek tahsisi yapıldıysa, bunu serbest bırakabiliriz.
    free(canli);
}