#include <iomanip>
#include <cstring>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <locale.h>

using namespace std;

struct Ayakkabi {
    char ad[80];
    char marka[80];
    int numara;
    int stok;
};

void AyakkabiEkle();
void AyakkabiListeleme();
void AyakkabiArama();
void AyakkabiSil();
void AyakkabiDuzenle();

int main() {
setlocale(LC_ALL,"Turkish")	;
    char anamenu;
    do {
        system("cls");

        cout << "|------- Hosgeldiniz -------|" << endl;
        cout << "|      Secim Yapiniz        |" << endl;
        cout << "|   1- Ayakkabi Ekleme      |" << endl;
        cout << "|   2- Ayakkabi Listeleme   |" << endl;
        cout << "|   3- Ayakkabi Arama       |" << endl;
        cout << "|   4- Ayakkabi Sil         |" << endl;
        cout << "|   5- Ayakkabi Duzenle     |" << endl;
        cout << "|---------------------------|" << endl;

        char secim;
        cin >> secim;

        switch (secim) {
            case '1':
                AyakkabiEkle();
                break;
            case '2':
                AyakkabiListeleme();
                break;
            case '3':
                AyakkabiArama();
                break;
            case '4':
                AyakkabiSil();
                break;
            case '5':
                AyakkabiDuzenle();
                break;
        }

        cout << "Anamenuye Donmek icin: a basin cikmak icin: c" << endl;
        anamenu = getche();

    } while (anamenu == 'a');

    return 0;
}

Ayakkabi ayk;

void AyakkabiEkle() {
    ofstream yaz("ayakkabi.dat", ios::binary | ios::app);
    char secim;
    int adet = 0;

    do {
        cout << "Ayakkabi Adini Giriniz: " << endl;
        cin >> ayk.ad;
        cout << "Ayakkabi Markasini Giriniz: " << endl;
        cin >> ayk.marka;
        cout << "Ayakkabi Numara Giriniz: " << endl;
        cin >> ayk.numara;
        cout << "Ayakkabi Stok Miktarini Giriniz: " << endl;
        cin >> ayk.stok;

        yaz.write((char*)&ayk, sizeof(ayk));
        adet++;
        
        cout << "Baska Kayit Eklemek Istermisiniz (E/H): " << endl;
        secim = getche();
        cout << endl;
    } while (secim == 'e' || secim == 'E');

    cout << adet << " adet ayakkabi eklendi.." << endl;
    yaz.close();
}

void AyakkabiListeleme() {
    ifstream oku("ayakkabi.dat", ios::binary);
    oku.seekg(0, ios::end);
    int kayits = oku.tellg() / sizeof(ayk);
    cout << "Toplam Ayakkabi Kayit Sayisi: " << kayits << endl;

    if (kayits > 0) {
        for (int i = 0; i < kayits; i++) {
            oku.seekg(i * sizeof(ayk));
            oku.read((char*)&ayk, sizeof(ayk));

            cout << i + 1 << ". Ayakkabinin Bilgileri" << endl;
            cout << "Ad: " << ayk.ad << endl;
            cout << "Marka: " << ayk.marka << endl;
            cout << "Numara: " << ayk.numara << endl;
            cout << "Stok: " << ayk.stok << endl;
        }
    } else {
        cout << "Kayit bulunamadi..." << endl;
    }

    oku.close();
}

void AyakkabiArama() {
    ifstream oku("ayakkabi.dat", ios::binary);
    oku.seekg(0, ios::end);
    int kayits = oku.tellg() / sizeof(ayk);

    cout << "Aranan Ayakkabi Adini Giriniz: " << endl;
    char arananAd[80];
    cin >> arananAd;

    bool bulundu = false;

    if (kayits > 0) {
        for (int i = 0; i < kayits; i++) {
            oku.seekg(i * sizeof(ayk));
            oku.read((char*)&ayk, sizeof(ayk));

            if (strcmp(ayk.ad, arananAd) == 0) {
                bulundu = true;
                cout << "Bulunan Ayakkabinin Bilgileri" << endl;
                cout << "Ad: " << ayk.ad << endl;
                cout << "Marka: " << ayk.marka << endl;
                cout << "Numara: " << ayk.numara << endl;
                cout << "Stok: " << ayk.stok << endl;
                break;
            }
        }
    }

    if (!bulundu) {
        cout << "Kayit bulunamadi..." << endl;
    }

    oku.close();
}

void AyakkabiSil() {
    char silAd[80];
    cout << "Silmek Istediginiz Ayakkabi Adini Giriniz: " << endl;
    cin >> silAd;

    ifstream oku("ayakkabi.dat", ios::binary);
    ofstream yaz("yedek.dat", ios::binary);

    bool bulundu = false;
    while (oku.read((char*)&ayk, sizeof(ayk))) {
        if (strcmp(ayk.ad, silAd) != 0) {
            yaz.write((char*)&ayk, sizeof(ayk));
        } else {
            bulundu = true;
        }
    }

    oku.close();
    yaz.close();

    remove("ayakkabi.dat");
    rename("yedek.dat", "ayakkabi.dat");

    if (bulundu) {
        cout << "Kayit silindi." << endl;
    } else {
        cout << "Kayit bulunamadi." << endl;
    }
}

void AyakkabiDuzenle() {
    char duzenleAd[80];
    cout << "Duzenlemek Istediginiz Ayakkabi Adini Giriniz: " << endl;
    cin >> duzenleAd;

    ifstream oku("ayakkabi.dat", ios::binary);
    ofstream yaz("yedek.dat", ios::binary);

    bool bulundu = false;
    while (oku.read((char*)&ayk, sizeof(ayk))) {
        if (strcmp(ayk.ad, duzenleAd) == 0) {
            bulundu = true;
            cout << "Yeni Ayakkabi Adi: " << endl;
            cin >> ayk.ad;
            cout << "Yeni Ayakkabi Markasi: " << endl;
            cin >> ayk.marka;
            cout << "Yeni Ayakkabi Numarasi: " << endl;
            cin >> ayk.numara;
            cout << "Yeni Stok Miktari: " << endl;
            cin >> ayk.stok;
        }
        yaz.write((char*)&ayk, sizeof(ayk));
    }

    oku.close();
    yaz.close();

    remove("ayakkabi.dat");
    rename("yedek.dat", "ayakkabi.dat");

    if (bulundu) {
        cout << "Kayit duzenlendi." << endl;
    } else {
        cout << "Kayit bulunamadi." << endl;
    }
}

