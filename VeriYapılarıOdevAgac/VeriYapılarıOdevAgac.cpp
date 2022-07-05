#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <queue>
#include <stack>
#include <ctime>

using namespace std;

//fonksiyonlar
bool listelemeMenuSecim();
void listelemeMenu();
bool menuSecim();
bool menu();
void agacOlustur(string);
void agaclariOlustur();
int txtSecim();


struct dugum {//ağaca dugum eklemek için kullanılır
    char ogrNo[15];
    char isim[30];
    char soyisim[30];
    dugum* sol;
    dugum* sag;
};
struct agac {//agaç oluşturak için kullanılır
    dugum* kok;
    int elemansayisi;
    void agacolustur();
    void ekle(dugum*);
    void yazdir(dugum*);
    void preorder(dugum*);
    void inorder(dugum*);
    void postorder(dugum*);
    void sil(char *);
    void sil(dugum **);
    bool ilkderinlik(char* ogrno);
    bool ilkgenislik(char*);
};

typedef agac veriyapisi;
veriyapisi agacKonum[3];
int sayac = 0;
string dosyaIcerik;

int txtSecim() {
    int secim;
    cout << "Hangi dosya icin arama yapmak istiyorsunuz ?" << endl;
    cout << "data1.txt icin : 1" << endl;
    cout << "data2.txt icin : 2" << endl;
    cout << "data3.txt icin : 3" << endl;
    while (true) {
        cin >> secim;
        if (secim == 1) {
            return 0;
        }
        else if (secim == 2) {
            return 1;
        }
        else if (secim == 3) {
            return 2;
        }
        else {
            cout << "Hatali sayi girdiniz." << endl;
        }
    }
}

void agac::yazdir(dugum* p) {
        if (p) {
            dosyaIcerik += p->ogrNo;
            dosyaIcerik += " ";
            dosyaIcerik += p->isim;
            dosyaIcerik += " ";
            dosyaIcerik += p->soyisim;
            dosyaIcerik += "\n";
            yazdir(p->sol);
            yazdir(p->sag);
        }
}

bool agac::ilkgenislik(char* ogrno){
    dugum* p;
    queue <dugum*>kuyruk;
    kuyruk.push(kok);
    bool ogrencivar = false;
    while (!kuyruk.empty()){
        p = kuyruk.front();
        kuyruk.pop();
        if (strcmp(ogrno, p->ogrNo) == 0){
            cout << "Bulunan ogrenci: " << p->isim << " " << p->soyisim << endl;
            ogrencivar = true;
        }
        if (p->sag){
            kuyruk.push(p->sag);
        }
        if (p->sol){
            kuyruk.push(p->sol);
        }
    }
    return ogrencivar;
}

bool agac::ilkderinlik(char* ogrno){
    dugum* p;
    bool ogrencivar = false;
    stack <dugum*> yigin;
    yigin.push(kok);
    while (!yigin.empty()){
        p = yigin.top();
        yigin.pop();
        if (strcmp(ogrno, p->ogrNo) == 0){
            cout << "Bulunan ogrenci: " << p->isim << " " << p->soyisim << endl;
            ogrencivar = true;
        }
        if (p->sag){
            yigin.push(p->sag);
        }
        if (p->sol){
            yigin.push(p->sol);
        }
    }
    return ogrencivar;
}
void agac::sil(dugum** sil){
    dugum* r, * q;
    r = *sil;
    if (r == NULL){
        return;
    }
    else if (r->sag == NULL){
        *sil = r->sol;
        delete r;
    }
    else if (r->sol == NULL){
        *sil = r->sag;
        delete r;
    }
    else{
        for (q = r->sag;q->sol;q = q->sol);
        q->sol = r->sol;
        *sil = r->sag;
        delete r;
    }
}
void agac::sil(char *ogrNo) {
    dugum* tara;
    dugum* ust = nullptr;
    tara = kok;
    bool bulundu = false;
    char yon = 'k';
    while (tara && !bulundu){
        int karsilas = strcmp(ogrNo, tara->ogrNo);
        if (karsilas < 0){
            ust = tara;
            yon = 'l';
            tara = tara->sol;
        }
        else if (karsilas > 0){
            ust = tara;
            yon = 'r';
            tara = tara->sag;
        }
        else { bulundu = true; }
    }
    if (bulundu){
        if (yon == 'l'){
            sil(&ust->sol);
        }
        else if (yon == 'r'){
            sil(&ust->sag);
        }
        else{
            sil(&kok);
        }
    }
    else{
        cout << "bulamadim" << endl;
    }
}

bool listelemeMenuSecim() {
    string Secim;
    int hangiTxt;
    while (true) {
        cin >> Secim;
        if (Secim == "R") {
            hangiTxt = txtSecim();
            clock_t baslangic = clock(), bitis;
            agacKonum[hangiTxt].preorder(agacKonum[hangiTxt].kok);
            bitis = clock();
            cout << "\n Islem Suresi: " << float(bitis - baslangic) / CLOCKS_PER_SEC << endl;
            return true;
        }
        else if (Secim == "I") {
            hangiTxt = txtSecim();
            clock_t baslangic = clock(), bitis;
            agacKonum[hangiTxt].inorder(agacKonum[hangiTxt].kok);
            bitis = clock();
            cout << "\n Islem Suresi: " << float(bitis - baslangic) / CLOCKS_PER_SEC << endl;
            return true;
        }
        else if (Secim == "O") {
            hangiTxt = txtSecim();
            clock_t baslangic = clock(), bitis;
            agacKonum[hangiTxt].postorder(agacKonum[hangiTxt].kok);
            bitis = clock();
            cout << "\n Islem Suresi: " << float(bitis - baslangic) / CLOCKS_PER_SEC << endl;
            return true;
        }
        else if (Secim == "D") {
            char ogrNo[15];
            hangiTxt = txtSecim();
            cout << "Hangi ogrenciyi aramak istiyorsaniz numarasini giriniz" << endl;
            cin >> ogrNo;
            clock_t baslangic = clock(), bitis;
            agacKonum[hangiTxt].ilkderinlik(ogrNo);
            bitis = clock();
            cout << "\n Islem Suresi: " << float(bitis - baslangic) / CLOCKS_PER_SEC << endl;
            return true;
        }
        else if (Secim == "G") {
            char ogrNo[15];
            hangiTxt = txtSecim();
            cout << "Hangi ogrenciyi aramak istiyorsaniz numarasini giriniz" << endl;
            cin >> ogrNo;
            clock_t baslangic = clock(), bitis;
            agacKonum[hangiTxt].ilkgenislik(ogrNo);
            bitis = clock();
            cout << "\n Islem Suresi: " << float(bitis - baslangic) / CLOCKS_PER_SEC << endl;
            return true;
        }
        else if (Secim == "M") {
            return true;
        }
        else {
            cout << "Hatali harf girdiniz." << endl;
        }
    }
}

void listelemeMenu() {
    cout << "Asagidaki islemlerden birini seciniz \n\n";
    cout << "Preorder listeleme yapmak icin : R" << endl;
    cout << "Inorder listeleme yapmak icin : I" << endl;
    cout << "Postorder listeleme yapmak icin : O" << endl;
    cout << "Ilk derinlik aramasi yapmak icin : D" << endl;
    cout << "Ilk genislik aramasi yapmak icin : G" << endl;
    cout << "Menuye donmek icin : M" << endl;
}
bool menuSecim() {
    string Secim;
    while (true) {
        cin >> Secim;
        if (Secim == "L") {
            listelemeMenu();
            return listelemeMenuSecim();
        }
        else if (Secim == "S") {
            string txtNo;
            char ogrno[15];
            cout << "Silmek istediginiz ogrencinin nosunu giriniz" << endl;
            cin >> ogrno;
            while (true) {
                cout << "Silmek istediginiz ogrencinin hangi txtde oldugunu giriniz" << endl;
                cout << "data1.txt icin : 1" << endl;
                cout << "data2.txt icin : 2" << endl;
                cout << "data3.txt icin : 3" << endl;
                cin >> txtNo;
                if (txtNo == "1") {
                    agacKonum[0].sil(ogrno);
                    return true;
                }
                else if (txtNo == "2") {
                    agacKonum[1].sil(ogrno);
                    return true;
                }
                else if (txtNo == "3") {
                    agacKonum[2].sil(ogrno);
                    return true;
                }
                else {
                    cout << "Hatali harf girdiniz " << endl;
                }
            }
        }
        else if (Secim == "Y") {
            int hangiTxt;
            string txtAd;
            hangiTxt = txtSecim();
            if (hangiTxt == 0) {
                txtAd = "data1.txt";
            }
            else if (hangiTxt == 1) {
                txtAd = "data2.txt";
            }
            else if (hangiTxt == 2) {
                txtAd = "data3.txt";
            }
            dosyaIcerik = "";
            agacKonum[hangiTxt].yazdir(agacKonum[hangiTxt].kok);
            ofstream dosyaYaz(txtAd);
            dosyaYaz << dosyaIcerik;
            dosyaYaz.close();
            cout << "Txt dosyaniz basariyla guncellenmistir." << endl;
            return true;
        }
        else if (Secim == "C") {
            string cikisKontrol;
            while (true)
            {
                cout << "Cikis yapmak istediginizden emin misiniz ?(E/H)" << endl;
                cin >> cikisKontrol;
                if (cikisKontrol == "E") {
                    return false;
                }
                else if (cikisKontrol == "H") {
                    return true;
                }
                else {
                    cout << "Hatali harf girdiniz." << endl;
                }
            }
        }
        else {
            cout << "Hatali harf girdiniz." << endl;
        }
    }
}

bool menu() {
    cout << "Asagidaki islemlerden birini seciniz \n\n";
    cout << "Listeyi ekrana yazdirmak icin : L" << endl;
    cout << "Ogrenci silmek icin : S" << endl;
    cout << "Dosyaya yazmak icin : Y" << endl;
    cout << "Cikis icin : C" << endl;
    return menuSecim();
}
void agac::preorder(dugum* p) {
    if (p) {
        cout << p->ogrNo << " " << p->isim << " " << p->soyisim << endl;
        preorder(p->sol);
        preorder(p->sag);
    }
}
void agac::inorder(dugum* p) {
    if (p) {
        inorder(p->sol);
        cout << p->ogrNo << " " << p->isim << " " << p->soyisim << endl;
        inorder(p->sag);
    }
}
void agac::postorder(dugum* p) {
    if (p) {
        postorder(p->sol);
        postorder(p->sag);
        cout << p->ogrNo << " " << p->isim << " " << p->soyisim << endl;
    }
}

void agac::ekle(dugum* eklenecek) {
    bool eklendi = false;
    dugum* tara; dugum* yeni = new dugum;
    tara = kok;
    *yeni = *eklenecek; yeni->sol = NULL; yeni->sag = NULL;

    if (kok == NULL) {
        kok = yeni;
        elemansayisi++;
        return;
    }
    while ((tara != NULL) && (!eklendi))
    {
        if (atoi(yeni->ogrNo) < atoi(tara->ogrNo))
        {
            if (tara->sol != NULL) { tara = tara->sol; }
            else
            {
                tara->sol = yeni;
                eklendi = true;
            }
        }
        else if (atoi(yeni->ogrNo) > atoi(tara->ogrNo))
        {
            if (tara->sag != NULL) tara = tara->sag;
            else
            {
                tara->sag = yeni;
                eklendi = true;
            }
        }
        else { cout << "Kopya" << endl;  return; }
    }
    if (eklendi == true) { elemansayisi++; }

}

void agac::agacolustur() {
    kok = NULL;
    elemansayisi = 0;
}

void agacOlustur(string txt) {
    typedef agac veriyapisi;
    veriyapisi kayit;
    dugum yenikayit;
    kayit.agacolustur();
    char ogrno[15], ad[30], soyad[30], satirAl[75];
    char* ptr;
    ifstream dosya1(txt);			//ifstream ile "data1.txt" dosyasını okumak için dosyayı açma
    dosya1.getline(satirAl, 75);
    for (int i = 0;i < 75;i++) {				//satır sonundaki '\r' karakterini, '\0' karakteri ile değiştirme
        if (satirAl[i] == '\r')
            satirAl[i] = '\0';
    }
    while (dosya1) {					//while döngüsü içinde dosyayı sonuna kadar satır satır okuma ve okunan satırları boşluklara göre parçalayıp,
        ptr = strtok(satirAl, "\t");		//	j sayacının değerine göre değişkenlere atama
        int j = 0;
        while (ptr != NULL) {
            if (j == 0) {
                strcpy(ogrno, ptr);
            }
            if (j == 1)
                strcpy(ad, ptr);
            if (j == 2)
                strcpy(soyad, ptr);
            if (j == 3) {			//bir ad ve bir soyad okunmasına rağmen satır sonu gelmedi ise öğrencinin iki adı var demektir,
                strcat(ad, " ");		//	bu iki ad arada bir boşluk bırakılarak öğrenci değişkenine atanır ve soyadı tekrar okunur
                strcat(ad, soyad);
                strcpy(soyad, ptr);
            }
            ptr = strtok(NULL, " ");
            j++;
        }
        strcpy(yenikayit.ogrNo, ogrno);
        strcpy(yenikayit.isim, ad);
        strcpy(yenikayit.soyisim, soyad);
        kayit.ekle(&yenikayit);
        //ekle(&kok1,ogrno,ad,soyad);
        dosya1.getline(satirAl, 75);
        for (int i = 0;i < 75;i++) {
            if (satirAl[i] == '\r')
                satirAl[i] = '\0';
        }
    }
    agacKonum[sayac] = kayit;
    sayac++;
    dosya1.close();
}
void agaclariOlustur() {
    string dizi[3] = { "data1.txt","data2.txt","data3.txt" };
    for (int i = 0;i < 3;i++) {
        agacOlustur(dizi[i]);
    }
}
int main(){
    agaclariOlustur();
    while (menu()) {

    };
}
