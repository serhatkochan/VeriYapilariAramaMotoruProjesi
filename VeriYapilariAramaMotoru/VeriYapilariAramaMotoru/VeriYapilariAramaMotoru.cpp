#include <iostream> // cpp
#include <string.h>
#include <string> // string
#include <iomanip>
#include <fstream> // file
#include <time.h> 
#include <ctime>
#include <conio.h> // time
#include <algorithm>
#include <locale>
#include <locale.h>
#include <sstream>
// ASCII tablosundaki kutuphane
using namespace std;

//struct lineer list
struct node {
	int data;
	node* next;

};
node* ekle(node* r, int sayi) {
	if (r == NULL) {
		r = new node;
		r->data = sayi;
		r->next = NULL;
	}
	else {
		node* yrd;
		yrd = r;
		while (yrd->next != NULL) { // yardimcinin next'i NULL oldugunda programdan cikacak ve yrd'nin next'ine yeni degeri atayacaz
			yrd = yrd->next;
		}
		yrd->next = new node;
		yrd->next->data = sayi;
		yrd->next->next = NULL;
		yrd = NULL;
		delete yrd;
	}
	return r;
}
void listele(node* r) {
	while (r != NULL) {
		cout << r->data << ". ";
		r = r->next;
	}
} // kelimelerin kacinci indiste oldugunu tutacagiz


//levenshtein distance
int dist(string X, int m, string Y, int n) { // levenshtein algoritmasi

	// base case: empty strings (case 1)
	if (m == 0)
		return n;

	if (n == 0)
		return m;

	int cost;

	// if last characters of the strings match (case 2)
	if (X[m - 1] == Y[n - 1])
		cost = 0;
	else
		cost = 1;


	return min(min(dist(X, m - 1, Y, n) + 1,	// deletion	(ekleme)
		dist(X, m, Y, n - 1) + 1),		 // insertion (silme)
		dist(X, m - 1, Y, n - 1) + cost);	// substitution (yer deðiþtirme)
}

// dosyalama islemleri
void dosyalamaIslemleri(string aranacakKelime) {
	fstream dosya1;
	dosya1.open("deneme.txt", ios::in | ios::out | ios::app);
	string dosya1denAlacagimizKelime;

	node* root0txt; // dist 0 ise bu root'un icine degerleri aktaracaz.
	root0txt = NULL;
	// dist 1 icin bu rootlarin icine degerleri aktaracaz.
	node* root1_1txt;
	node* root1_2txt;
	node* root1_3txt;
	root1_1txt = NULL;
	root1_2txt = NULL;
	root1_3txt = NULL;
	// dist 2 icin bu rootlarin icine degerleri aktaracaz.
	node* root2_1txt;
	node* root2_2txt;
	node* root2_3txt;
	root2_1txt = NULL;
	root2_2txt = NULL;
	root2_3txt = NULL;


	string kelimelerDist1txt[3] = { "0","0","0" }; // dist 1 icin baslangic olarak 3 kelimeye 0 degerini atadik
	string kelimelerDist2txt[3] = { "0","0","0" }; // dist 2 icin baslangic olarak 3 kleimeye 0 degerini atadik
	int adet0txt = 0; // kelime bulunduysa bu degisken ile islem yapacaz
	int adet1txt[3] = { 0,0,0 }; // baslangic olarak kelime adetlerine 0 degerini atadik
	int adet2txt[3] = { 0,0,0 }; // dist 2 icin 3 adetlik dizi
	int distHesaplama = 0; // dist'in degerini tutacagimiz degisken
	int kacinciKelime = 0; // ekrana kacinci kelime oldugunu bulmak icin
	int bulunduMu = 0;// 

	clock_t baslangictxt, baslangicdat, baslangicrft, baslangichtml, bitistxt, bitisdat, bitisrtf, bitishtml;
	baslangictxt = clock();
	while (dosya1.eof() != true) {// dosya end of file olmadýðý sürece devam edecek
		dosya1 >> dosya1denAlacagimizKelime;
		kacinciKelime += 1;
		int uzunluk1 = dosya1denAlacagimizKelime.length();
		int uzunluk2 = aranacakKelime.length();
		if ((uzunluk1 - uzunluk2) > 2 || (uzunluk2 - uzunluk1) > 2) {
			continue;
		}


		if (dosya1denAlacagimizKelime == aranacakKelime) { //dist 0 ise
			adet0txt++;
			root0txt = ekle(root0txt, kacinciKelime);
			continue;
		}
		bulunduMu = 0;
		for (int i = 0; i < 3; i++) {
			if (adet1txt[i] > 0) {//adetle islem yapmayacak
				if (kelimelerDist1txt[i] == dosya1denAlacagimizKelime) {
					adet1txt[i]++;
					bulunduMu = 1;
					if (i == 0) {
						root1_1txt = ekle(root1_1txt, kacinciKelime);
					}
					else if (i == 1) {
						root1_2txt = ekle(root1_2txt, kacinciKelime);
					}
					else {
						root1_3txt = ekle(root1_3txt, kacinciKelime);
					}
					break;
				}
			}
			if (adet2txt[i] > 0) {
				if (kelimelerDist2txt[i] == dosya1denAlacagimizKelime) {
					adet2txt[i]++;
					bulunduMu = 1;
					if (i == 0) {
						root2_1txt = ekle(root2_1txt, kacinciKelime);
					}
					else if (i == 1) {
						root2_2txt = ekle(root2_2txt, kacinciKelime);
					}
					else {
						root2_3txt = ekle(root2_3txt, kacinciKelime);
					}
					break;
				}
			}
		}
		if (bulunduMu == 1) {
			continue;
		}//eger dosyadan aldigimz kelimeden daha once kontrole ettiysek gereken islemleri yap ve continue





		distHesaplama = dist(aranacakKelime, aranacakKelime.length(), dosya1denAlacagimizKelime, dosya1denAlacagimizKelime.length());
		// --------- DÝST 1 ÝCÝN
		// gerek kalmadi(break komudu if'in icine yazildiginda da for dongusundan cikiyor galiba..) int kelimeEklendiMi=0; // kelime eklendiyse break komutu ile donguden cikacaz
		if (distHesaplama == 1) { //dist 1 ise yani uzaklik 1 ise 
			for (int i = 0; i < 3; i++) { // 3 kelimelik kelimelerDist1txt[3] dizisi olusturdugumuz icin for 3 olacak
				if (kelimelerDist1txt[i] == "0") { // eger kelime bos ise sorgusunu yapiyoruz
					kelimelerDist1txt[i] = dosya1denAlacagimizKelime; // yeni bir kelime ekleyecegimiz icin olusturdugumuz string tipindeki diziye yeni kelimemizi atiyoruz
					if (i == 0) { // 1. kelime icin 1. root calisacak
						root1_1txt = ekle(root1_1txt, kacinciKelime);
						adet1txt[i]++; // adet dizisine kelimeyi uygun adet[i] ye yerlestiriyoruz ade[1]

					}
					else if (i == 1) {
						root1_2txt = ekle(root1_2txt, kacinciKelime);
						adet1txt[i]++;
					}
					else {
						root1_3txt = ekle(root1_3txt, kacinciKelime);
						adet1txt[i]++;
					}
					break; // kelime eklendiyse donguden cik
				}
				else if (kelimelerDist1txt[i] == dosya1denAlacagimizKelime) { // eger kelime bos degil ise, dolu olan kelimenin bizim kelimemize denk olup olmadigini kontrol ediyoruz
					if (i == 0) { // 1. kelime icin 1. root calisacak
						root1_1txt = ekle(root1_1txt, kacinciKelime);
						adet1txt[i]++;
					}
					else if (i == 1) {
						root1_2txt = ekle(root1_2txt, kacinciKelime);
						adet1txt[i]++;
					}
					else {
						root1_3txt = ekle(root1_3txt, kacinciKelime);
						adet1txt[i]++;
					}
					break; // kelime eklendiyse donguden cik
				}
			}
		}
		if (distHesaplama == 2) {
			for (int i = 0; i < 3; i++) {
				if (kelimelerDist2txt[i] == "0") {
					kelimelerDist2txt[i] = dosya1denAlacagimizKelime;
					if (i == 0) {
						root2_1txt = ekle(root2_1txt, kacinciKelime);
						adet2txt[i]++;
					}
					else if (i == 1) {
						root2_2txt = ekle(root2_2txt, kacinciKelime);
						adet2txt[i]++;
					}
					else {
						root2_3txt = ekle(root2_3txt, kacinciKelime);
						adet2txt[i] += 1;
					}
					break;
				}
				else if (kelimelerDist2txt[i] == dosya1denAlacagimizKelime) {
					if (i == 0) {
						root2_1txt = ekle(root2_1txt, kacinciKelime);
						adet2txt[i]++;
					}
					else if (i == 1) {
						root2_2txt = ekle(root2_2txt, kacinciKelime);
						adet2txt[i]++;
					}
					else {
						root2_3txt = ekle(root2_3txt, kacinciKelime);
						adet2txt[i]++;
					}
					break; // kelime eklendiyse donguden cik
				}
			}
		}
	} // while dongusu bitisi
	bitistxt = clock();
	float olculenZamantxt = ((float)bitistxt - (float)baslangictxt) / CLOCKS_PER_SEC;

	dosya1.close();



	// dosya2 degiskenlerini olusturacagimiz yer
	fstream dosya2;
	dosya2.open("deneme2.dat", ios::in | ios::out | ios::app);
	string dosya2denAlacagimizKelime;

	node* root0dat; // dist 0 ise bu root'un icine degerleri aktaracaz.
	root0dat = NULL;
	// dist 1 icin bu rootlarin icine degerleri aktaracaz.
	node* root1_1dat;
	node* root1_2dat;
	node* root1_3dat;
	root1_1dat = NULL;
	root1_2dat = NULL;
	root1_3dat = NULL;
	// dist 2 icin bu rootlarin icine degerleri aktaracaz.
	node* root2_1dat;
	node* root2_2dat;
	node* root2_3dat;
	root2_1dat = NULL;
	root2_2dat = NULL;
	root2_3dat = NULL;




	string kelimelerDist1dat[3] = { "0","0","0" }; // dist 1 icin baslangic olarak 3 kelimeye 0 degerini atadik
	string kelimelerDist2dat[3] = { "0","0","0" }; // dist 2 icin baslangic olarak 3 kleimeye 0 degerini atadik
	int adet0dat = 0; // kelime bulunduysa bu degisken ile islem yapacaz
	int adet1dat[3] = { 0,0,0 }; // baslangic olarak kelime adetlerine 0 degerini atadik
	int adet2dat[3] = { 0,0,0 }; // dist 2 icin 3 adetlik dizi
	distHesaplama = 0; // dist degerini tutacagimiz degisken
	kacinciKelime = 0; // ekrana kacinci kelime oldugunu bulmak icin
	baslangicdat = clock();
	while (dosya2.eof() != true) {
		bulunduMu = 0;
		dosya2 >> dosya2denAlacagimizKelime;
		kacinciKelime += 1;
		int uzunluk1 = dosya2denAlacagimizKelime.length();
		int uzunluk2 = aranacakKelime.length();
		if ((uzunluk1 - uzunluk2) > 2 || (uzunluk2 - uzunluk1) > 2) {
			continue;
		}


		if (dosya2denAlacagimizKelime == aranacakKelime) { //dist 0 ise
			adet0dat++;
			root0dat = ekle(root0dat, kacinciKelime);
			continue;
		}
		for (int i = 0; i < 3; i++) {
			if (adet1dat[i] > 0) {//adetle islem yapmayacak
				if (kelimelerDist1dat[i] == dosya2denAlacagimizKelime) {
					adet1dat[i]++;
					bulunduMu = 1;
					if (i == 0) {
						root1_1dat = ekle(root1_1dat, kacinciKelime);
					}
					else if (i == 1) {
						root1_2dat = ekle(root1_2dat, kacinciKelime);
					}
					else {
						root1_3dat = ekle(root1_3dat, kacinciKelime);
					}
					break;
				}
			}
			if (adet2dat[i] > 0) {
				if (kelimelerDist2dat[i] == dosya2denAlacagimizKelime) {
					adet2dat[i]++;
					bulunduMu = 1;
					if (i == 0) {
						root2_1dat = ekle(root2_1dat, kacinciKelime);
					}
					else if (i == 1) {
						root2_2dat = ekle(root2_2dat, kacinciKelime);
					}
					else {
						root2_3txt = ekle(root2_3txt, kacinciKelime);
					}
					break;
				}
			}
		}
		if (bulunduMu == 1) {
			continue;
		}//eger dosyadan aldigimz kelimeden daha once kontrole ettiysek gereken islemleri yap ve continue














		distHesaplama = dist(aranacakKelime, aranacakKelime.length(), dosya2denAlacagimizKelime, dosya2denAlacagimizKelime.length());

		// --------- DÝST 1 ÝCÝN
		// gerek kalmadi(break komudu if'in icine yazildiginda da for dongusundan cikiyor galiba..) int kelimeEklendiMi=0; // kelime eklendiyse break komutu ile donguden cikacaz
		if (distHesaplama == 1) { //dist 1 ise yani uzaklik 1 ise 
			for (int i = 0; i < 3; i++) { // 3 kelimelik kelimelerDist1txt[3] dizisi olusturdugumuz icin for 3 olacak
				if (kelimelerDist1dat[i] == "0") { // eger kelime bos ise sorgusunu yapiyoruz
					kelimelerDist1dat[i] = dosya2denAlacagimizKelime; // yeni bir kelime ekleyecegimiz icin olusturdugumuz string tipindeki diziye yeni kelimemizi atiyoruz
					if (i == 0) { // 1. kelime icin 1. root calisacak
						root1_1dat = ekle(root1_1dat, kacinciKelime);
						adet1dat[i]++; // adet dizisine kelimeyi uygun adet[i] ye yerlestiriyoruz ade[1]
					}
					else if (i == 1) {
						root1_2dat = ekle(root1_2dat, kacinciKelime);
						adet1dat[i]++;
					}
					else {
						root1_3dat = ekle(root1_3dat, kacinciKelime);
						adet1dat[i]++;
					}
					break; // kelime eklendiyse donguden cik
				}
				else if (kelimelerDist1dat[i] == dosya2denAlacagimizKelime) { // eger kelime bos degil ise, dolu olan kelimenin bizim kelimemize denk olup olmadigini kontrol ediyoruz
					if (i == 0) { // 1. kelime icin 1. root calisacak
						root1_1dat = ekle(root1_1dat, kacinciKelime);
						adet1dat[i]++;
					}
					else if (i == 1) {
						root1_2dat = ekle(root1_2dat, kacinciKelime);
						adet1dat[i]++;
					}
					else {
						root1_3dat = ekle(root1_3dat, kacinciKelime);
						adet1dat[i]++;
					}
					break; // kelime eklendiyse donguden cik
				}
			}
		}
		if (distHesaplama == 2) {
			for (int i = 0; i < 3; i++) {
				if (kelimelerDist2dat[i] == "0") {
					kelimelerDist2dat[i] = dosya2denAlacagimizKelime;
					if (i == 0) {
						root2_1dat = ekle(root2_1dat, kacinciKelime);
						adet2dat[i]++;
					}
					else if (i == 1) {
						root2_2dat = ekle(root2_2dat, kacinciKelime);
						adet2dat[i]++;
					}
					else {
						root2_3dat = ekle(root2_3dat, kacinciKelime);
						adet2dat[i] += 1;
					}
					break;
				}
				else if (kelimelerDist2dat[i] == dosya2denAlacagimizKelime) {
					if (i == 0) {
						root2_1dat = ekle(root2_1dat, kacinciKelime);
						adet2dat[i]++;
					}
					else if (i == 1) {
						root2_2dat = ekle(root2_2dat, kacinciKelime);
						adet2dat[i]++;
					}
					else {
						root2_3dat = ekle(root2_3dat, kacinciKelime);
						adet2dat[i]++;
					}
					break; // kelime eklendiyse donguden cik
				}
			}
		}
	}//while dongusu bitisi
	bitisdat = clock();
	float olculenZamandat = ((float)bitisdat - (float)baslangicdat) / CLOCKS_PER_SEC;

	dosya2.close();





	// dosya3 degiskenlerini olusturacagimiz yer
	fstream dosya3;
	dosya3.open("deneme3.rtf", ios::in | ios::out | ios::app);
	string dosya3denAlacagimizKelime;

	node* root0rtf; // dist 0 ise bu root'un icine degerleri aktaracaz.
	root0rtf = NULL;
	// dist 1 icin bu rootlarin icine degerleri aktaracaz.
	node* root1_1rtf;
	node* root1_2rtf;
	node* root1_3rtf;
	root1_1rtf = NULL;
	root1_2rtf = NULL;
	root1_3rtf = NULL;
	// dist 2 icin bu rootlarin icine degerleri aktaracaz.
	node* root2_1rtf;
	node* root2_2rtf;
	node* root2_3rtf;
	root2_1rtf = NULL;
	root2_2rtf = NULL;
	root2_3rtf = NULL;




	string kelimelerDist1rtf[3] = { "0","0","0" }; // dist 1 icin baslangic olarak 3 kelimeye 0 degerini atadik
	string kelimelerDist2rtf[3] = { "0","0","0" }; // dist 2 icin baslangic olarak 3 kleimeye 0 degerini atadik
	int adet0rtf = 0; // kelime bulunduysa bu degisken ile islem yapacaz
	int adet1rtf[3] = { 0,0,0 }; // baslangic olarak kelime adetlerine 0 degerini atadik
	int adet2rtf[3] = { 0,0,0 }; // dist 2 icin 3 adetlik dizi
	distHesaplama = 0; // dist degerini tutacagimiz degisken
	kacinciKelime = 0; // ekrana kacinci kelime oldugunu bulmak icin
	baslangicrft = clock();
	while (dosya3.eof() != true) {
		dosya3 >> dosya3denAlacagimizKelime;
		kacinciKelime += 1;

		int uzunluk1 = dosya3denAlacagimizKelime.length();
		int uzunluk2 = aranacakKelime.length();
		if ((uzunluk1 - uzunluk2) > 2 || (uzunluk2 - uzunluk1) > 2) {
			continue;
		}


		if (dosya3denAlacagimizKelime == aranacakKelime) { //dist 0 ise
			adet0rtf++;
			root0rtf = ekle(root0rtf, kacinciKelime);
			continue;
		}
		bulunduMu = 0;
		for (int i = 0; i < 3; i++) {
			if (adet1rtf[i] > 0) {//adetle islem yapmayacak
				if (kelimelerDist1rtf[i] == dosya3denAlacagimizKelime) {
					adet1rtf[i]++;
					bulunduMu = 1;
					if (i == 0) {
						root1_1rtf = ekle(root1_1rtf, kacinciKelime);
					}
					else if (i == 1) {
						root1_2rtf = ekle(root1_2rtf, kacinciKelime);
					}
					else {
						root1_3rtf = ekle(root1_3rtf, kacinciKelime);
					}
					break;
				}
			}
			if (adet2rtf[i] > 0) {
				if (kelimelerDist2rtf[i] == dosya3denAlacagimizKelime) {
					adet2rtf[i]++;
					bulunduMu = 1;
					if (i == 0) {
						root2_1rtf = ekle(root2_1rtf, kacinciKelime);
					}
					else if (i == 1) {
						root2_2rtf = ekle(root2_2rtf, kacinciKelime);
					}
					else {
						root2_3rtf = ekle(root2_3rtf, kacinciKelime);
					}
					break;
				}
			}
		}
		if (bulunduMu == 1) {
			continue;
		}//eger dosyadan aldigimz kelimeden daha once kontrole ettiysek gereken islemleri yap ve continue












		distHesaplama = dist(aranacakKelime, aranacakKelime.length(), dosya3denAlacagimizKelime, dosya3denAlacagimizKelime.length());
		// --------- DÝST 1 ÝCÝN
		// gerek kalmadi(break komudu if'in icine yazildiginda da for dongusundan cikiyor galiba..) int kelimeEklendiMi=0; // kelime eklendiyse break komutu ile donguden cikacaz
		if (distHesaplama == 1) { //dist 1 ise yani uzaklik 1 ise 
			for (int i = 0; i < 3; i++) { // 3 kelimelik kelimelerDist1txt[3] dizisi olusturdugumuz icin for 3 olacak
				if (kelimelerDist1rtf[i] == "0") { // eger kelime bos ise sorgusunu yapiyoruz
					kelimelerDist1rtf[i] = dosya3denAlacagimizKelime; // yeni bir kelime ekleyecegimiz icin olusturdugumuz string tipindeki diziye yeni kelimemizi atiyoruz
					if (i == 0) { // 1. kelime icin 1. root calisacak
						root1_1rtf = ekle(root1_1rtf, kacinciKelime);
						adet1rtf[i]++; // adet dizisine kelimeyi uygun adet[i] ye yerlestiriyoruz ade[1]
					}
					else if (i == 1) {
						root1_2rtf = ekle(root1_2rtf, kacinciKelime);
						adet1rtf[i]++;
					}
					else {
						root1_3rtf = ekle(root1_3rtf, kacinciKelime);
						adet1rtf[i]++;
					}
					break; // kelime eklendiyse donguden cik
				}
				else if (kelimelerDist1rtf[i] == dosya3denAlacagimizKelime) { // eger kelime bos degil ise, dolu olan kelimenin bizim kelimemize denk olup olmadigini kontrol ediyoruz
					if (i == 0) { // 1. kelime icin 1. root calisacak
						root1_1rtf = ekle(root1_1rtf, kacinciKelime);
						adet1rtf[i]++;
					}
					else if (i == 1) {
						root1_2rtf = ekle(root1_2rtf, kacinciKelime);
						adet1rtf[i]++;
					}
					else {
						root1_3rtf = ekle(root1_3rtf, kacinciKelime);
						adet1rtf[i]++;
					}
					break; // kelime eklendiyse donguden cik
				}
			}
		}
		if (distHesaplama == 2) {
			for (int i = 0; i < 3; i++) {
				if (kelimelerDist2rtf[i] == "0") {
					kelimelerDist2rtf[i] = dosya3denAlacagimizKelime;
					if (i == 0) {
						root2_1rtf = ekle(root2_1rtf, kacinciKelime);
						adet2rtf[i]++;
					}
					else if (i == 1) {
						root2_2rtf = ekle(root2_2rtf, kacinciKelime);
						adet2rtf[i]++;
					}
					else {
						root2_3rtf = ekle(root2_3rtf, kacinciKelime);
						adet2rtf[i]++;
					}
					break;
				}
				else if (kelimelerDist2rtf[i] == dosya3denAlacagimizKelime) {
					if (i == 0) {
						root2_1rtf = ekle(root2_1rtf, kacinciKelime);
						adet2rtf[i]++;
					}
					else if (i == 1) {
						root2_2rtf = ekle(root2_2rtf, kacinciKelime);
						adet2rtf[i]++;
					}
					else {
						root2_3rtf = ekle(root2_3rtf, kacinciKelime);
						adet2rtf[i]++;
					}
					break; // kelime eklendiyse donguden cik
				}
			}
		}
	} //dosya3 while dongusunun bitisi
	bitisrtf = clock();
	float olculenZamanrtf = ((float)bitisrtf - (float)baslangicrft) / CLOCKS_PER_SEC;

	dosya3.close();






	// dosya4 degiskenlerini olusturacagimiz yer
	fstream dosya4;
	dosya4.open("deneme4.html", ios::in | ios::out | ios::app);
	string dosya4denAlacagimizKelime;

	node* root0html; // dist 0 ise bu root'un icine degerleri aktaracaz.
	root0html = NULL;
	// dist 1 icin bu rootlarin icine degerleri aktaracaz.
	node* root1_1html;
	node* root1_2html;
	node* root1_3html;
	root1_1html = NULL;
	root1_2html = NULL;
	root1_3html = NULL;
	// dist 2 icin bu rootlarin icine degerleri aktaracaz.
	node* root2_1html;
	node* root2_2html;
	node* root2_3html;
	root2_1html = NULL;
	root2_2html = NULL;
	root2_3html = NULL;




	string kelimelerDist1html[3] = { "0","0","0" }; // dist 1 icin baslangic olarak 3 kelimeye 0 degerini atadik
	string kelimelerDist2html[3] = { "0","0","0" }; // dist 2 icin baslangic olarak 3 kleimeye 0 degerini atadik
	int adet0html = 0; // kelime bulunduysa bu degisken ile islem yapacaz
	int adet1html[3] = { 0,0,0 }; // baslangic olarak kelime adetlerine 0 degerini atadik
	int adet2html[3] = { 0,0,0 }; // dist 2 icin 3 adetlik dizi
	distHesaplama = 0; // dist degerini tutacagimiz degisken
	kacinciKelime = 0; // ekrana kacinci kelime oldugunu bulmak icin
	baslangichtml = clock();
	while (dosya4.eof() != true) {
		dosya4 >> dosya4denAlacagimizKelime;
		kacinciKelime += 1;

		int uzunluk1 = dosya4denAlacagimizKelime.length();
		int uzunluk2 = aranacakKelime.length();
		if ((uzunluk1 - uzunluk2) > 2 || (uzunluk2 - uzunluk1) > 2) {
			continue;
		}


		if (dosya4denAlacagimizKelime == aranacakKelime) { //dist 0 ise
			adet0html++;
			root0html = ekle(root0html, kacinciKelime);
			continue;
		}
		bulunduMu = 0;
		for (int i = 0; i < 3; i++) {
			if (adet1html[i] > 0) {//adetle islem yapmayacak
				if (kelimelerDist1html[i] == dosya4denAlacagimizKelime) {
					adet1html[i]++;
					bulunduMu = 1;
					if (i == 0) {
						root1_1html = ekle(root1_1html, kacinciKelime);
					}
					else if (i == 1) {
						root1_2html = ekle(root1_2html, kacinciKelime);
					}
					else {
						root1_3html = ekle(root1_3html, kacinciKelime);
					}
					break;
				}
			}
			if (adet2html[i] > 0) {
				if (kelimelerDist2html[i] == dosya4denAlacagimizKelime) {
					adet2html[i]++;
					bulunduMu = 1;
					if (i == 0) {
						root2_1html = ekle(root2_1html, kacinciKelime);
					}
					else if (i == 1) {
						root2_2html = ekle(root2_2html, kacinciKelime);
					}
					else {
						root2_3html = ekle(root2_3html, kacinciKelime);
					}
					break;
				}
			}
		}
		if (bulunduMu == 1) {
			continue;
		}//eger dosyadan aldigimz kelimeden daha once kontrole ettiysek gereken islemleri yap ve continue






		distHesaplama = dist(aranacakKelime, aranacakKelime.length(), dosya4denAlacagimizKelime, dosya4denAlacagimizKelime.length());
		// --------- DÝST 1 ÝCÝN
		// gerek kalmadi(break komudu if'in icine yazildiginda da for dongusundan cikiyor galiba..) int kelimeEklendiMi=0; // kelime eklendiyse break komutu ile donguden cikacaz
		if (distHesaplama == 1) { //dist 1 ise yani uzaklik 1 ise 
			for (int i = 0; i < 3; i++) { // 3 kelimelik kelimelerDist1txt[3] dizisi olusturdugumuz icin for 3 olacak
				if (kelimelerDist1html[i] == "0") { // eger kelime bos ise sorgusunu yapiyoruz
					kelimelerDist1html[i] = dosya4denAlacagimizKelime; // yeni bir kelime ekleyecegimiz icin olusturdugumuz string tipindeki diziye yeni kelimemizi atiyoruz
					if (i == 0) { // 1. kelime icin 1. root calisacak
						root1_1html = ekle(root1_1html, kacinciKelime);
						adet1html[i]++; // adet dizisine kelimeyi uygun adet[i] ye yerlestiriyoruz ade[1]
					}
					else if (i == 1) {
						root1_2html = ekle(root1_2html, kacinciKelime);
						adet1html[i]++;
					}
					else {
						root1_3html = ekle(root1_3html, kacinciKelime);
						adet1html[i]++;
					}
					break; // kelime eklendiyse donguden cik
				}
				else if (kelimelerDist1html[i] == dosya4denAlacagimizKelime) { // eger kelime bos degil ise, dolu olan kelimenin bizim kelimemize denk olup olmadigini kontrol ediyoruz
					if (i == 0) { // 1. kelime icin 1. root calisacak
						root1_1html = ekle(root1_1html, kacinciKelime);
						adet1html[i]++;
					}
					else if (i == 1) {
						root1_2html = ekle(root1_2html, kacinciKelime);
						adet1html[i]++;
					}
					else {
						root1_3html = ekle(root1_3html, kacinciKelime);
						adet1html[i]++;
					}
					break; // kelime eklendiyse donguden cik
				}
			}
		}
		if (distHesaplama == 2) {
			for (int i = 0; i < 3; i++) {
				if (kelimelerDist2html[i] == "0") {
					kelimelerDist2html[i] = dosya4denAlacagimizKelime;
					if (i == 0) {
						root2_1html = ekle(root2_1html, kacinciKelime);
						adet2html[i]++;
					}
					else if (i == 1) {
						root2_2html = ekle(root2_2html, kacinciKelime);
						adet2html[i]++;
					}
					else {
						root2_3html = ekle(root2_3html, kacinciKelime);
						adet2html[i]++;
					}
					break;
				}
				else if (kelimelerDist2html[i] == dosya4denAlacagimizKelime) {
					if (i == 0) {
						root2_1html = ekle(root2_1html, kacinciKelime);
						adet2html[i]++;
					}
					else if (i == 1) {
						root2_2html = ekle(root2_2html, kacinciKelime);
						adet2html[i]++;
					}
					else {
						root2_3html = ekle(root2_3html, kacinciKelime);
						adet2html[i]++;
					}
					break; // kelime eklendiyse donguden cik
				}
			}
		}
	}// dosya4 while dongusunun sonu
	bitishtml = clock();
	float olculenZamanhtml = ((float)bitishtml - (float)baslangichtml) / CLOCKS_PER_SEC;
	//////////////////////////
	dosya4.close();



	int secenekSirasi = 1;
	int cevapKontrol = 0;
	int varMi = 0;
	ofstream dosyayaYaz;
	dosyayaYaz.open("sonuc.txt", ios::out);// sonuclari yazdiracagimiz dosyayi olusturduk

	if (adet0txt > 0 || adet0dat > 0 || adet0rtf > 0 || adet0html > 0) {
		if (adet0txt > 0) {
			cout << "Aradiginiz kelime dosya1.txt dosyasinda " << adet0txt << " adet bulundu ve ";
			listele(root0txt);
			cout << "kelimelerinde bulunmustur." << endl << endl;
			cout << "dosya1.txt dosyasinda arama islemi " << olculenZamantxt << " saniye surmustur." << endl << endl;

			dosyayaYaz << "Aradiginiz kelime dosya1.txt dosyasinda " << adet0txt << " adet bulundu ve ";
			while (root0txt != NULL) {
				dosyayaYaz << root0txt->data << ". ";
				root0txt = root0txt->next;
			}
			dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
			dosyayaYaz << "dosya1.txt dosyasinda arama islemi " << olculenZamantxt << " saniye surmustur." << endl << endl;
		}//if(adet0txt>0) bitisi
		if (adet0dat > 0) {
			cout << "Aradiginiz kelime dosya2.dat dosyasinda " << adet0dat << " adet bulundu ve ";
			listele(root0dat);
			cout << "kelimelerinde bulunmustur." << endl << endl;
			cout << "dosya2.dat dosyasinda arama islemi " << olculenZamandat << " saniye surmutur." << endl << endl;

			dosyayaYaz << "Aradiginiz kelime dosya2.dat dosyasinda " << adet0dat << " adet bulundu ve ";
			while (root0dat != NULL) {
				dosyayaYaz << root0dat->data << ". ";
				root0dat = root0dat->next;
			}
			dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
			dosyayaYaz << "dosya2.dat dosyasinda arama islemi " << olculenZamandat << " saniye surmustur." << endl << endl;
		}//if(adet0dat>0) bitisi
		if (adet0rtf > 0) {
			cout << "Aradiginiz kelime dosya3.rtf dosyasinda " << adet0rtf << " adet bulundu ve ";
			listele(root0rtf);
			cout << "kelimelerinde bulunmustur." << endl << endl;
			cout << "dosya3.rtf dosyasinda arama islemi " << olculenZamanrtf << " saniye surmustur." << endl << endl;

			dosyayaYaz << "Aradiginiz kelime dosya3.rtf dosyasinda " << adet0rtf << " adet bulundu ve ";
			while (root0rtf != NULL) {
				dosyayaYaz << root0rtf->data << ". ";
				root0rtf = root0rtf->next;
			}
			dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
			dosyayaYaz << "dosya3.rtf dosyasinda arama islemi " << olculenZamanrtf << " saniye surmustur." << endl << endl;
		}//if(adet0rtf>0) bitisi
		if (adet0html > 0) {
			cout << "Aradiginiz kelime dosya4.html dosyasinda " << adet0html << " adet bulundu ve ";
			listele(root0html);
			cout << "kelimelerinde bulunmustur." << endl << endl;
			cout << "dosya4.html dosyasinda arama islemi " << olculenZamanhtml << " saniye surmustur." << endl << endl;

			dosyayaYaz << "Aradiginiz keliem dosya4.html dosyasinda " << adet0html << " adet bulundu ve ";
			while (root0html != NULL) {
				dosyayaYaz << root0html->data << ". ";
				root0html = root0html->next;
			}
			dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
			dosyayaYaz << "dosya4.html dosyasinda arama islemi " << olculenZamanhtml << " saniye surmustur." << endl << endl;
		}//if(adet0html>0) bitisi
		cout << "Arama islemi toplam  " << olculenZamantxt + olculenZamandat + olculenZamanrtf + olculenZamanhtml << " saniye surmustur.";
		dosyayaYaz << "Arama islemi toplam " << olculenZamantxt + olculenZamandat + olculenZamanrtf + olculenZamanhtml << " saniye surmustur.";
	}//if(adet0txt>0 || adet0dat>0 || adet0rtf>0 || adet0html>0) bitisi


	else if (adet1txt[0] > 0 || adet1dat[0] > 0 || adet1rtf[0] > 0 || adet1html[0] > 0) {
		cout << "Aradiginiz kelime bulunamadi. Bunu mu demek istediniz? : ";
		if (adet1txt[0] > 0) {
			cout << kelimelerDist1txt[0] << endl << "1- Evet" << endl << "2- Hayir" << endl << "Cevap: ";
			cin >> cevapKontrol;
			if (cevapKontrol == 1) {
				cout << kelimelerDist1txt[0] << " kelimesinden dosya1.txt dosyasinda " << adet1txt[0] << " adet vardir ve ";
				listele(root1_1txt);
				cout << "kelimelerinde bulunmustur." << endl << endl;
				cout << "dosya1.txt dosyasinda arama islemi " << olculenZamantxt << " sanyie surmustur." << endl << endl;

				dosyayaYaz << kelimelerDist1txt[0] << " kelimesinden dosya1.txt dosyasinda " << adet1txt[0] << " adet vardir ve ";
				while (root1_1txt != NULL) {
					dosyayaYaz << root1_1txt->data << ". ";
					root1_1txt = root1_1txt->next;
				}
				dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
				dosyayaYaz << "dosya1.txt dosyasinda arama islemi " << olculenZamantxt << " saniye surmustur." << endl << endl;
				//txt dosyasi icin yazdirma islemi tamamlandi
				for (int i = 0; i < 3; i++) {
					if (kelimelerDist1dat[i] == kelimelerDist1txt[0]) {
						cout << kelimelerDist1txt[0] << " kelimesinden dosya2.dat dosyasinda " << adet1dat[i] << " adet vardir ve ";
						if (i == 0) {
							listele(root1_1dat);
						}
						else if (i == 1) {
							listele(root1_2dat);
						}
						else {
							listele(root1_3dat);
						}
						cout << "kelimelerinde bulunmustur." << endl << endl;
						cout << "dosya2.dat dosyasinda arama islemi " << olculenZamandat << " saniye surmustur." << endl << endl;

						dosyayaYaz << kelimelerDist1txt[0] << " kelimesinden dosya2.dat dosyasinda " << adet1dat[i] << " adet vardir ve ";
						if (i == 0) {
							while (root1_1dat != NULL) {
								dosyayaYaz << root1_1dat->data << ". ";
								root1_1dat = root1_1dat->next;
							}
						}
						else if (i == 1) {
							while (root1_2dat != NULL) {
								dosyayaYaz << root1_2dat->data << ". ";
								root1_2dat = root1_2dat->next;
							}
						}
						else {
							while (root1_3dat != NULL) {
								dosyayaYaz << root1_3dat->data << ". ";
								root1_3dat = root1_3dat->next;
							}
						}
						dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						dosyayaYaz << "dosya2.dat dosyasinda arama islemi " << olculenZamandat << " saniye surmustur." << endl << endl;
					}//if(kelimelerDist1dat[i]==kelimelerDist1txt[0]) bitisi
					//dat dosyasi icin yazdirma islemi tamamlandi
					if (kelimelerDist1rtf[i] == kelimelerDist1txt[0]) {
						cout << kelimelerDist1txt[0] << " kelimesinden dosya3.rtf dosyasinda " << adet1rtf[i] << " adet vardir ve ";
						if (i == 0) {
							listele(root1_1rtf);
						}
						else if (i == 1) {
							listele(root1_2rtf);
						}
						else {
							listele(root1_3rtf);
						}
						cout << "kelimelerinde bulunmustur." << endl << endl;
						cout << "dosya3.rtf dosyasinda arama islemi " << olculenZamanrtf << " saniye surmustur." << endl << endl;

						dosyayaYaz << kelimelerDist1txt[0] << " kelimesinden dosya3.rtf dosyasinda " << adet1rtf[i] << " adet vardir ve ";
						if (i == 0) {
							while (root1_1rtf != NULL) {
								dosyayaYaz << root1_1rtf->data << ". ";
								root1_1rtf = root1_1rtf->next;
							}
						}
						else if (i == 1) {
							while (root1_2rtf != NULL) {
								dosyayaYaz << root1_2rtf->data << ". ";
								root1_2rtf = root1_2rtf->next;
							}
						}
						else {
							while (root1_3rtf != NULL) {
								dosyayaYaz << root1_3rtf->data << ". ";
								root1_3rtf = root1_3rtf->next;
							}
						}
						dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						dosyayaYaz << "dosya3.rtf dosyasinda arama islemi " << olculenZamanrtf << " saniye surmustur." << endl << endl;
					}//if(kelimelerDist1rtf[i]==kelimelerDist1txt[0]) bitisi
					//rtf dosyasi icin yazdirma islemi tamamlandi
					if (kelimelerDist1html[i] == kelimelerDist1txt[0]) {
						cout << kelimelerDist1txt[0] << " kelimesinden dosya4.html dosyasinda " << adet1html[i] << " adet vardir ve ";
						if (i == 0) {
							listele(root1_1html);
						}
						else if (i == 1) {
							listele(root1_2html);
						}
						else {
							listele(root1_3html);
						}
						cout << "kelimelerinde bulunmustur." << endl << endl;
						cout << "dosya4.html dosyasinda arama islemi " << olculenZamanhtml << " saniye surmustur." << endl << endl;

						dosyayaYaz << kelimelerDist1txt[0] << " kelimesinden dosya4.html dosyasinda " << adet1html[i] << " adet vardir ve ";
						if (i == 0) {
							while (root1_1html != NULL) {
								dosyayaYaz << root1_1html->data << ". ";
								root1_1html = root1_1html->next;
							}
						}
						else if (i == 1) {
							while (root1_2html != NULL) {
								dosyayaYaz << root1_2html->data << ". ";
								root1_2html = root1_2html->next;
							}
						}
						else {
							while (root1_3html != NULL) {
								dosyayaYaz << root1_3html->data << ". ";
								root1_3html = root1_3html->next;
							}
						}
						dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						dosyayaYaz << "dosya4.html dosyasinda arama islemi " << olculenZamanhtml << " saniye surmustur." << endl << endl;
					}//if(kelimelerDist1html[i]==kelimelerDist1txt[0]) bitisi
					//html dosyasi icin yazdirma islemi tamamlandi
				}//for dongusu bitisi
			}//if(cevapKontrol==1) bitisi
			else {
				if (adet1txt[1] > 0 || adet2txt[0] > 0) {
					for (int i = 1; i < 3; i++) {
						if (adet1txt[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist1txt[i] << " kelimesinden dosya1.txt dosyasinda " << adet1txt[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist1txt[i] << " kelimesinden dosya1.txt dosyasinda " << adet1txt[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 1) {
								listele(root1_2txt);
								while (root1_2txt != NULL) {
									dosyayaYaz << root1_2txt->data << ". ";
									root1_2txt = root1_2txt->next;
								}
							}
							else {
								listele(root1_3txt);
								while (root1_3txt != NULL) {
									dosyayaYaz << root1_3txt->data << ". ";
									root1_3txt = root1_3txt->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet1txt[i]>0) bitisi
					}//for (int i=1; i<3; i++) bitisi
					for (int i = 0; i < 3; i++) {
						if (adet2txt[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist2txt[i] << " kelimesinden dosya1.txt dosyasinda " << adet2txt[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist2txt[i] << " kelimesinden dosya1.txt dosyasinda " << adet2txt[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 0) {
								listele(root2_1txt);
								while (root2_1txt != NULL) {
									dosyayaYaz << root2_1txt->data << ". ";
									root2_1txt = root2_1txt->next;
								}
							}
							else if (i == 1) {
								listele(root2_2txt);
								while (root2_2txt != NULL) {
									dosyayaYaz << root2_2txt->data << ". ";
									root2_2txt = root2_2txt->next;
								}
							}
							else {
								listele(root2_3txt);
								while (root2_3txt != NULL) {
									dosyayaYaz << root2_3txt->data << ". ";
									root2_3txt = root2_3txt->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet2txt[i]>0) bitisi
					}//for(int i=0; i<3; i++) bitisi
					cout << "dosya1.txt dosyasinda arama islemi " << olculenZamantxt << " saniye surmustur." << endl << endl;
					dosyayaYaz << "dosya1.txt dosyasinda arama islemi " << olculenZamantxt << " saniye surmustur." << endl << endl;
				}//if(adet1txt[1]>0 || adet2txt[0]>0) bitisi
				if (adet1dat[0] > 0 || adet2dat[0] > 0) {
					for (int i = 0; i < 3; i++) {
						if (adet1dat[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist1dat[i] << " kelimesinden dosya2.dat dosyasinda " << adet1dat[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist1dat[i] << " kelimesinden dosya2.dat dosyasinda " << adet1dat[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 0) {
								listele(root1_1dat);
								while (root1_1dat != NULL) {
									dosyayaYaz << root1_1dat->data << ". ";
									root1_1dat = root1_1dat->next;
								}
							}
							if (i == 1) {
								listele(root1_2dat);
								while (root1_2dat != NULL) {
									dosyayaYaz << root1_2dat->data << ". ";
									root1_2dat = root1_2dat->next;
								}
							}
							else {
								listele(root1_3dat);
								while (root1_3dat != NULL) {
									dosyayaYaz << root1_3dat->data << ". ";
									root1_3dat = root1_3dat->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet1dat[i]>0) bitisi
					}//for (int i=1; i<3; i++) bitisi
					for (int i = 0; i < 3; i++) {
						if (adet2dat[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist2dat[i] << " kelimesinden dosya2.dat dosyasinda " << adet2dat[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist2dat[i] << " kelimesinden dosya2.dat dosyasinda " << adet2dat[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 0) {
								listele(root2_1dat);
								while (root2_1dat != NULL) {
									dosyayaYaz << root2_1dat->data << ". ";
									root2_1dat = root2_1dat->next;
								}
							}
							else if (i == 1) {
								listele(root2_2dat);
								while (root2_2dat != NULL) {
									dosyayaYaz << root2_2dat->data << ". ";
									root2_2dat = root2_2dat->next;
								}
							}
							else {
								listele(root2_3dat);
								while (root2_3dat != NULL) {
									dosyayaYaz << root2_3dat->data << ". ";
									root2_3dat = root2_3dat->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet2dat[i]>0) bitisi
					}//for(int i=0; i<3; i++) bitisi
					cout << "dosya2.dat dosyasinda arama islemi " << olculenZamandat << " saniye surmustur." << endl << endl;
					dosyayaYaz << "dosya2.dat dosyasinda arama islemi " << olculenZamandat << " saniye surmustur." << endl << endl;
				}//if(adet1dat[0]>0 || adet2dat[0]>0) bitisi
				if (adet1rtf[0] > 0 || adet2rtf[0] > 0) {
					for (int i = 0; i < 3; i++) {
						if (adet1rtf[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist1rtf[i] << " kelimesinden dosya3.rtf dosyasinda " << adet1rtf[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist1rtf[i] << " kelimesinden dosya3.rtf dosyasinda " << adet1rtf[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 0) {
								listele(root1_1rtf);
								while (root1_1rtf != NULL) {
									dosyayaYaz << root1_1rtf->data << ". ";
									root1_1rtf = root1_1rtf->next;
								}
							}
							if (i == 1) {
								listele(root1_2rtf);
								while (root1_2rtf != NULL) {
									dosyayaYaz << root1_2rtf->data << ". ";
									root1_2rtf = root1_2rtf->next;
								}
							}
							else {
								listele(root1_3rtf);
								while (root1_3rtf != NULL) {
									dosyayaYaz << root1_3rtf->data << ". ";
									root1_3rtf = root1_3rtf->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet1rtf[i]>0) bitisi
					}//for (int i=1; i<3; i++) bitisi
					for (int i = 0; i < 3; i++) {
						if (adet2rtf[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist2rtf[i] << " kelimesinden dosya3.rtf dosyasinda " << adet2rtf[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist2rtf[i] << " kelimesinden dosya3.rtf dosyasinda " << adet2rtf[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 0) {
								listele(root2_1rtf);
								while (root2_1rtf != NULL) {
									dosyayaYaz << root2_1rtf->data << ". ";
									root2_1rtf = root2_1rtf->next;
								}
							}
							else if (i == 1) {
								listele(root2_2rtf);
								while (root2_2rtf != NULL) {
									dosyayaYaz << root2_2rtf->data << ". ";
									root2_2rtf = root2_2rtf->next;
								}
							}
							else {
								listele(root2_3rtf);
								while (root2_3rtf != NULL) {
									dosyayaYaz << root2_3rtf->data << ". ";
									root2_3rtf = root2_3rtf->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet2rtf[i]>0) bitisi
					}//for(int i=0; i<3; i++) bitisi
					cout << "dosya3.rtf dosyasinda arama islemi " << olculenZamanrtf << " saniye surmustur." << endl << endl;
					dosyayaYaz << "dosya3.rtf dosyasinda arama islemi " << olculenZamanrtf << " saniye surmustur." << endl << endl;
				}//if(adet1rtf[0]>0 || adet2rtf[0]>0) bitisi
				if (adet1html[0] > 0 || adet2html[0] > 0) {
					for (int i = 0; i < 3; i++) {
						if (adet1html[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist1html[i] << " kelimesinden dosya4.html dosyasinda " << adet1html[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist1html[i] << " kelimesinden dosya4.html dosyasinda " << adet1html[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 0) {
								listele(root1_1html);
								while (root1_1html != NULL) {
									dosyayaYaz << root1_1html->data << ". ";
									root1_1html = root1_1html->next;
								}
							}
							if (i == 1) {
								listele(root1_2html);
								while (root1_2html != NULL) {
									dosyayaYaz << root1_2html->data << ". ";
									root1_2html = root1_2html->next;
								}
							}
							else {
								listele(root1_3html);
								while (root1_3html != NULL) {
									dosyayaYaz << root1_3html->data << ". ";
									root1_3html = root1_3html->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet1html[i]>0) bitisi
					}//for (int i=1; i<3; i++) bitisi
					for (int i = 0; i < 3; i++) {
						if (adet2html[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist2html[i] << " kelimesinden dosya4.html dosyasinda " << adet2html[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist2html[i] << " kelimesinden dosya4.html dosyasinda " << adet2html[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 0) {
								listele(root2_1html);
								while (root2_1html != NULL) {
									dosyayaYaz << root2_1html->data << ". ";
									root2_1html = root2_1html->next;
								}
							}
							else if (i == 1) {
								listele(root2_2html);
								while (root2_2html != NULL) {
									dosyayaYaz << root2_2html->data << ". ";
									root2_2html = root2_2html->next;
								}
							}
							else {
								listele(root2_3html);
								while (root2_3html != NULL) {
									dosyayaYaz << root2_3html->data << ". ";
									root2_3html = root2_3html->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet2html[i]>0) bitisi
					}//for(int i=0; i<3; i++) bitisi
					cout << "dosya4.html dosyasinda arama islemi " << olculenZamanhtml << " saniye surmustur." << endl << endl;
					dosyayaYaz << "dosya4.html dosyasinda arama islemi " << olculenZamanhtml << " saniye surmustur." << endl << endl;
				}//if(adet1html[0]>0 || adet2html[0]>0) bitisi
				if (adet1txt[1] == 0 && adet1dat[0] == 0 && adet1rtf[0] == 0 && adet1html[0] == 0 && adet2txt[0] == 0 && adet2dat[0] == 0 && adet2rtf[0] == 0 && adet2html[0] == 0) {
					cout << "Aradiginiz kelimeye ait baþka bir veriye ulaþýlamadi.";
					dosyayaYaz << "Aradiginiz kelimeye ait baþka bir veriye ulaþýlamadi.";
				}
			}//else (cevapKontrol==2) ise bitisi
		}//if(adet1txt[0]>0) bitisi
		////////////
		else if (adet1dat[0] > 0) {
			cout << kelimelerDist1dat[0] << endl << "1- Evet" << endl << "2- Hayir" << endl << "Cevap: ";
			cin >> cevapKontrol;
			if (cevapKontrol == 1) {
				cout << kelimelerDist1dat[0] << " kelimesinden dosya2.dat dosyasinda " << adet1dat[0] << " adet vardir ve ";
				listele(root1_1dat);
				cout << "kelimelerinde bulunmustur." << endl << endl;
				cout << "dosya2.dat dosyasinda arama islemi " << olculenZamandat << " sanyie surmustur." << endl << endl;

				dosyayaYaz << kelimelerDist1dat[0] << " kelimesinden dosya2.dat dosyasinda " << adet1dat[0] << " adet vardir ve ";
				while (root1_1dat != NULL) {
					dosyayaYaz << root1_1dat->data << ". ";
					root1_1dat = root1_1dat->next;
				}
				dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
				dosyayaYaz << "dosya2.dat dosyasinda arama islemi " << olculenZamandat << " saniye surmustur." << endl << endl;
				//dat dosyasi icin yazdirma islemi tamamlandi
				for (int i = 0; i < 3; i++) {
					if (kelimelerDist1rtf[i] == kelimelerDist1dat[0]) {
						cout << kelimelerDist1dat[0] << " kelimesinden dosya3.rtf dosyasinda " << adet1rtf[i] << " adet vardir ve ";
						if (i == 0) {
							listele(root1_1rtf);
						}
						else if (i == 1) {
							listele(root1_2rtf);
						}
						else {
							listele(root1_3rtf);
						}
						cout << "kelimelerinde bulunmustur." << endl << endl;
						cout << "dosya3.rtf dosyasinda arama islemi " << olculenZamanrtf << " saniye surmustur." << endl << endl;

						dosyayaYaz << kelimelerDist1dat[0] << " kelimesinden dosya3.rtf dosyasinda " << adet1rtf[i] << " adet vardir ve ";
						if (i == 0) {
							while (root1_1rtf != NULL) {
								dosyayaYaz << root1_1rtf->data << ". ";
								root1_1rtf = root1_1rtf->next;
							}
						}
						else if (i == 1) {
							while (root1_2rtf != NULL) {
								dosyayaYaz << root1_2rtf->data << ". ";
								root1_2rtf = root1_2rtf->next;
							}
						}
						else {
							while (root1_3rtf != NULL) {
								dosyayaYaz << root1_3rtf->data << ". ";
								root1_3rtf = root1_3rtf->next;
							}
						}
						dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						dosyayaYaz << "dosya3.rtf dosyasinda arama islemi " << olculenZamanrtf << " saniye surmustur." << endl << endl;
					}//if(kelimelerDist1rtf[i]==kelimelerDist1dat[0]) bitisi
					//rtf dosyasi icin yazdirma islemi tamamlandi
					if (kelimelerDist1html[i] == kelimelerDist1dat[0]) {
						cout << kelimelerDist1dat[0] << " kelimesinden dosya4.html dosyasinda " << adet1html[i] << " adet vardir ve ";
						if (i == 0) {
							listele(root1_1html);
						}
						else if (i == 1) {
							listele(root1_2html);
						}
						else {
							listele(root1_3html);
						}
						cout << "kelimelerinde bulunmustur." << endl << endl;
						cout << "dosya4.html dosyasinda arama islemi " << olculenZamanhtml << " saniye surmustur." << endl << endl;

						dosyayaYaz << kelimelerDist1dat[0] << " kelimesinden dosya4.html dosyasinda " << adet1html[i] << " adet vardir ve ";
						if (i == 0) {
							while (root1_1html != NULL) {
								dosyayaYaz << root1_1html->data << ". ";
								root1_1html = root1_1html->next;
							}
						}
						else if (i == 1) {
							while (root1_2html != NULL) {
								dosyayaYaz << root1_2html->data << ". ";
								root1_2html = root1_2html->next;
							}
						}
						else {
							while (root1_3html != NULL) {
								dosyayaYaz << root1_3html->data << ". ";
								root1_3html = root1_3html->next;
							}
						}
						dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						dosyayaYaz << "dosya4.html dosyasinda arama islemi " << olculenZamanhtml << " saniye surmustur." << endl << endl;
					}//if(kelimelerDist1html[i]==kelimelerDist1dat[0]) bitisi
					//html dosyasi icin yazdirma islemi tamamlandi
				}//for dongusu bitisi
			}//if(cevapKontrol==1) bitisi
			else {
				if (adet2txt[0] > 0) {
					for (int i = 0; i < 3; i++) {
						if (adet2txt[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist2txt[i] << " kelimesinden dosya1.txt dosyasinda " << adet2txt[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist2txt[i] << " kelimesinden dosya1.txt dosyasinda " << adet2txt[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 0) {
								listele(root2_1txt);
								while (root2_1txt != NULL) {
									dosyayaYaz << root2_1txt->data << ". ";
									root2_1txt = root2_1txt->next;
								}
							}
							else if (i == 1) {
								listele(root2_2txt);
								while (root2_2txt != NULL) {
									dosyayaYaz << root2_2txt->data << ". ";
									root2_2txt = root2_2txt->next;
								}
							}
							else {
								listele(root2_3txt);
								while (root2_3txt != NULL) {
									dosyayaYaz << root2_3txt->data << ". ";
									root2_3txt = root2_3txt->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet2txt[i]>0) bitisi
					}//for(int i=0; i<3; i++) bitisi
					cout << "dosya1.txt dosyasinda arama islemi " << olculenZamantxt << " saniye surmustur." << endl << endl;
					dosyayaYaz << "dosya1.txt dosyasinda arama islemi " << olculenZamantxt << " saniye surmustur." << endl << endl;
				}//if(adet2txt[0]>0) bitisi
				if (adet1dat[1] > 0 || adet2dat[0] > 0) {
					for (int i = 1; i < 3; i++) {
						if (adet1dat[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist1dat[i] << " kelimesinden dosya2.dat dosyasinda " << adet1dat[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist1dat[i] << " kelimesinden dosya2.dat dosyasinda " << adet1dat[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 1) {
								listele(root1_2dat);
								while (root1_2dat != NULL) {
									dosyayaYaz << root1_2dat->data << ". ";
									root1_2dat = root1_2dat->next;
								}
							}
							else {
								listele(root1_3dat);
								while (root1_3dat != NULL) {
									dosyayaYaz << root1_3dat->data << ". ";
									root1_3dat = root1_3dat->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet1dat[i]>0) bitisi
					}//for (int i=1; i<3; i++) bitisi
					for (int i = 0; i < 3; i++) {
						if (adet2dat[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist2dat[i] << " kelimesinden dosya2.dat dosyasinda " << adet2dat[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist2dat[i] << " kelimesinden dosya2.dat dosyasinda " << adet2dat[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 0) {
								listele(root2_1dat);
								while (root2_1dat != NULL) {
									dosyayaYaz << root2_1dat->data << ". ";
									root2_1dat = root2_1dat->next;
								}
							}
							else if (i == 1) {
								listele(root2_2dat);
								while (root2_2dat != NULL) {
									dosyayaYaz << root2_2dat->data << ". ";
									root2_2dat = root2_2dat->next;
								}
							}
							else {
								listele(root2_3dat);
								while (root2_3dat != NULL) {
									dosyayaYaz << root2_3dat->data << ". ";
									root2_3dat = root2_3dat->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet2dat[i]>0) bitisi
					}//for(int i=0; i<3; i++) bitisi
					cout << "dosya2.dat dosyasinda arama islemi " << olculenZamandat << " saniye surmustur." << endl << endl;
					dosyayaYaz << "dosya2.dat dosyasinda arama islemi " << olculenZamandat << " saniye surmustur." << endl << endl;
				}//if(adet1dat[0]>0 || adet2dat[0]>0) bitisi
				if (adet1rtf[0] > 0 || adet2rtf[0] > 0) {
					for (int i = 0; i < 3; i++) {
						if (adet1rtf[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist1rtf[i] << " kelimesinden dosya3.rtf dosyasinda " << adet1rtf[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist1rtf[i] << " kelimesinden dosya3.rtf dosyasinda " << adet1rtf[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 0) {
								listele(root1_1rtf);
								while (root1_1rtf != NULL) {
									dosyayaYaz << root1_1rtf->data << ". ";
									root1_1rtf = root1_1rtf->next;
								}
							}
							if (i == 1) {
								listele(root1_2rtf);
								while (root1_2rtf != NULL) {
									dosyayaYaz << root1_2rtf->data << ". ";
									root1_2rtf = root1_2rtf->next;
								}
							}
							else {
								listele(root1_3rtf);
								while (root1_3rtf != NULL) {
									dosyayaYaz << root1_3rtf->data << ". ";
									root1_3rtf = root1_3rtf->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet1rtf[i]>0) bitisi
					}//for (int i=1; i<3; i++) bitisi
					for (int i = 0; i < 3; i++) {
						if (adet2rtf[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist2rtf[i] << " kelimesinden dosya3.rtf dosyasinda " << adet2rtf[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist2rtf[i] << " kelimesinden dosya3.rtf dosyasinda " << adet2rtf[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 0) {
								listele(root2_1rtf);
								while (root2_1rtf != NULL) {
									dosyayaYaz << root2_1rtf->data << ". ";
									root2_1rtf = root2_1rtf->next;
								}
							}
							else if (i == 1) {
								listele(root2_2rtf);
								while (root2_2rtf != NULL) {
									dosyayaYaz << root2_2rtf->data << ". ";
									root2_2rtf = root2_2rtf->next;
								}
							}
							else {
								listele(root2_3rtf);
								while (root2_3rtf != NULL) {
									dosyayaYaz << root2_3rtf->data << ". ";
									root2_3rtf = root2_3rtf->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet2rtf[i]>0) bitisi
					}//for(int i=0; i<3; i++) bitisi
					cout << "dosya3.rtf dosyasinda arama islemi " << olculenZamanrtf << " saniye surmustur." << endl << endl;
					dosyayaYaz << "dosya3.rtf dosyasinda arama islemi " << olculenZamanrtf << " saniye surmustur." << endl << endl;
				}//if(adet1rtf[0]>0 || adet2rtf[0]>0) bitisi
				if (adet1html[0] > 0 || adet2html[0] > 0) {
					for (int i = 0; i < 3; i++) {
						if (adet1html[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist1html[i] << " kelimesinden dosya4.html dosyasinda " << adet1html[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist1html[i] << " kelimesinden dosya4.html dosyasinda " << adet1html[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 0) {
								listele(root1_1html);
								while (root1_1html != NULL) {
									dosyayaYaz << root1_1html->data << ". ";
									root1_1html = root1_1html->next;
								}
							}
							if (i == 1) {
								listele(root1_2html);
								while (root1_2html != NULL) {
									dosyayaYaz << root1_2html->data << ". ";
									root1_2html = root1_2html->next;
								}
							}
							else {
								listele(root1_3html);
								while (root1_3html != NULL) {
									dosyayaYaz << root1_3html->data << ". ";
									root1_3html = root1_3html->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet1html[i]>0) bitisi
					}//for (int i=1; i<3; i++) bitisi
					for (int i = 0; i < 3; i++) {
						if (adet2html[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist2html[i] << " kelimesinden dosya4.html dosyasinda " << adet2html[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist2html[i] << " kelimesinden dosya4.html dosyasinda " << adet2html[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 0) {
								listele(root2_1html);
								while (root2_1html != NULL) {
									dosyayaYaz << root2_1html->data << ". ";
									root2_1html = root2_1html->next;
								}
							}
							else if (i == 1) {
								listele(root2_2html);
								while (root2_2html != NULL) {
									dosyayaYaz << root2_2html->data << ". ";
									root2_2html = root2_2html->next;
								}
							}
							else {
								listele(root2_3html);
								while (root2_3html != NULL) {
									dosyayaYaz << root2_3html->data << ". ";
									root2_3html = root2_3html->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet2html[i]>0) bitisi
					}//for(int i=0; i<3; i++) bitisi
					cout << "dosya4.html dosyasinda arama islemi " << olculenZamanhtml << " saniye surmustur." << endl << endl;
					dosyayaYaz << "dosya4.html dosyasinda arama islemi " << olculenZamanhtml << " saniye surmustur." << endl << endl;
				}//if(adet1html[0]>0 || adet2html[0]>0) bitisi
				if (adet1dat[1] == 0 && adet1rtf[0] == 0 && adet1html[0] == 0 && adet2txt[0] == 0 && adet2dat[0] == 0 && adet2rtf[0] == 0 && adet2html[0] == 0) {
					cout << "Aradiginiz kelimeye ait baþka bir veriye ulaþýlamadi.";
					dosyayaYaz << "Aradiginiz kelimeye ait baþka bir veriye ulaþýlamadi.";
				}
			}//else (cevapKontrol==2) ise bitisi
		}//else if(adet1dat[0]>0) bitisi
		/////////////
		else if (adet1rtf[0] > 0) {
			cout << kelimelerDist1rtf[0] << endl << "1- Evet" << endl << "2- Hayir" << endl << "Cevap: ";
			cin >> cevapKontrol;
			if (cevapKontrol == 1) {
				cout << kelimelerDist1rtf[0] << " kelimesinden dosya3.rtf dosyasinda " << adet1rtf[0] << " adet vardir ve ";
				listele(root1_1rtf);
				cout << "kelimelerinde bulunmustur." << endl << endl;
				cout << "dosya3.rtf dosyasinda arama islemi " << olculenZamanrtf << " sanyie surmustur." << endl << endl;

				dosyayaYaz << kelimelerDist1rtf[0] << " kelimesinden dosya3.rtf dosyasinda " << adet1rtf[0] << " adet vardir ve ";
				while (root1_1rtf != NULL) {
					dosyayaYaz << root1_1rtf->data << ". ";
					root1_1rtf = root1_1rtf->next;
				}
				dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
				dosyayaYaz << "dosya3.rtf dosyasinda arama islemi " << olculenZamanrtf << " saniye surmustur." << endl << endl;
				//dat dosyasi icin yazdirma islemi tamamlandi
				for (int i = 0; i < 3; i++) {
					if (kelimelerDist1html[i] == kelimelerDist1rtf[0]) {
						cout << kelimelerDist1rtf[0] << " kelimesinden dosya4.html dosyasinda " << adet1html[i] << " adet vardir ve ";
						if (i == 0) {
							listele(root1_1html);
						}
						else if (i == 1) {
							listele(root1_2html);
						}
						else {
							listele(root1_3html);
						}
						cout << "kelimelerinde bulunmustur." << endl << endl;
						cout << "dosya4.html dosyasinda arama islemi " << olculenZamanhtml << " saniye surmustur." << endl << endl;

						dosyayaYaz << kelimelerDist1rtf[0] << " kelimesinden dosya4.html dosyasinda " << adet1html[i] << " adet vardir ve ";
						if (i == 0) {
							while (root1_1html != NULL) {
								dosyayaYaz << root1_1html->data << ". ";
								root1_1html = root1_1html->next;
							}
						}
						else if (i == 1) {
							while (root1_2html != NULL) {
								dosyayaYaz << root1_2html->data << ". ";
								root1_2html = root1_2html->next;
							}
						}
						else {
							while (root1_3html != NULL) {
								dosyayaYaz << root1_3html->data << ". ";
								root1_3html = root1_3html->next;
							}
						}
						dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						dosyayaYaz << "dosya4.html dosyasinda arama islemi " << olculenZamanhtml << " saniye surmustur." << endl << endl;
					}//if(kelimelerDist1html[i]==kelimelerDist1rtf[0]) bitisi
					//html dosyasi icin yazdirma islemi tamamlandi
				}//for dongusu bitisi
			}//if(cevapKontrol==1) bitisi
			else {
				if (adet2txt[0] > 0) {
					for (int i = 0; i < 3; i++) {
						if (adet2txt[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist2txt[i] << " kelimesinden dosya1.txt dosyasinda " << adet2txt[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist2txt[i] << " kelimesinden dosya1.txt dosyasinda " << adet2txt[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 0) {
								listele(root2_1txt);
								while (root2_1txt != NULL) {
									dosyayaYaz << root2_1txt->data << ". ";
									root2_1txt = root2_1txt->next;
								}
							}
							else if (i == 1) {
								listele(root2_2txt);
								while (root2_2txt != NULL) {
									dosyayaYaz << root2_2txt->data << ". ";
									root2_2txt = root2_2txt->next;
								}
							}
							else {
								listele(root2_3txt);
								while (root2_3txt != NULL) {
									dosyayaYaz << root2_3txt->data << ". ";
									root2_3txt = root2_3txt->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet2txt[i]>0) bitisi
					}//for(int i=0; i<3; i++) bitisi
					cout << "dosya1.txt dosyasinda arama islemi " << olculenZamantxt << " saniye surmustur." << endl << endl;
					dosyayaYaz << "dosya1.txt dosyasinda arama islemi " << olculenZamantxt << " saniye surmustur." << endl << endl;
				}//if(adet2txt[0]>0) bitisi
				if (adet2dat[0] > 0) {
					for (int i = 0; i < 3; i++) {
						if (adet2dat[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist2dat[i] << " kelimesinden dosya2.dat dosyasinda " << adet2dat[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist2dat[i] << " kelimesinden dosya2.dat dosyasinda " << adet2dat[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 0) {
								listele(root2_1dat);
								while (root2_1dat != NULL) {
									dosyayaYaz << root2_1dat->data << ". ";
									root2_1dat = root2_1dat->next;
								}
							}
							else if (i == 1) {
								listele(root2_2dat);
								while (root2_2dat != NULL) {
									dosyayaYaz << root2_2dat->data << ". ";
									root2_2dat = root2_2dat->next;
								}
							}
							else {
								listele(root2_3dat);
								while (root2_3dat != NULL) {
									dosyayaYaz << root2_3dat->data << ". ";
									root2_3dat = root2_3dat->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet2dat[i]>0) bitisi
					}//for(int i=0; i<3; i++) bitisi
					cout << "dosya2.dat dosyasinda arama islemi " << olculenZamandat << " saniye surmustur." << endl << endl;
					dosyayaYaz << "dosya2.dat dosyasinda arama islemi " << olculenZamandat << " saniye surmustur." << endl << endl;
				}//if(adet2dat[0]>0) bitisi
				if (adet1rtf[1] > 0 || adet2rtf[0] > 0) {
					for (int i = 1; i < 3; i++) {
						if (adet1rtf[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist1rtf[i] << " kelimesinden dosya3.rtf dosyasinda " << adet1rtf[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist1rtf[i] << " kelimesinden dosya3.rtf dosyasinda " << adet1rtf[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 1) {
								listele(root1_2rtf);
								while (root1_2rtf != NULL) {
									dosyayaYaz << root1_2rtf->data << ". ";
									root1_2rtf = root1_2rtf->next;
								}
							}
							else {
								listele(root1_3rtf);
								while (root1_3rtf != NULL) {
									dosyayaYaz << root1_3rtf->data << ". ";
									root1_3rtf = root1_3rtf->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet1rtf[i]>0) bitisi
					}//for (int i=1; i<3; i++) bitisi
					for (int i = 0; i < 3; i++) {
						if (adet2rtf[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist2rtf[i] << " kelimesinden dosya3.rtf dosyasinda " << adet2rtf[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist2rtf[i] << " kelimesinden dosya3.rtf dosyasinda " << adet2rtf[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 0) {
								listele(root2_1rtf);
								while (root2_1rtf != NULL) {
									dosyayaYaz << root2_1rtf->data << ". ";
									root2_1rtf = root2_1rtf->next;
								}
							}
							else if (i == 1) {
								listele(root2_2rtf);
								while (root2_2rtf != NULL) {
									dosyayaYaz << root2_2rtf->data << ". ";
									root2_2rtf = root2_2rtf->next;
								}
							}
							else {
								listele(root2_3rtf);
								while (root2_3rtf != NULL) {
									dosyayaYaz << root2_3rtf->data << ". ";
									root2_3rtf = root2_3rtf->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet2rtf[i]>0) bitisi
					}//for(int i=0; i<3; i++) bitisi
					cout << "dosya3.rtf dosyasinda arama islemi " << olculenZamanrtf << " saniye surmustur." << endl << endl;
					dosyayaYaz << "dosya3.rtf dosyasinda arama islemi " << olculenZamanrtf << " saniye surmustur." << endl << endl;
				}//if(adet1rtf[0]>0 || adet2rtf[0]>0) bitisi
				if (adet1html[0] > 0 || adet2html[0] > 0) {
					for (int i = 0; i < 3; i++) {
						if (adet1html[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist1html[i] << " kelimesinden dosya4.html dosyasinda " << adet1html[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist1html[i] << " kelimesinden dosya4.html dosyasinda " << adet1html[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 0) {
								listele(root1_1html);
								while (root1_1html != NULL) {
									dosyayaYaz << root1_1html->data << ". ";
									root1_1html = root1_1html->next;
								}
							}
							if (i == 1) {
								listele(root1_2html);
								while (root1_2html != NULL) {
									dosyayaYaz << root1_2html->data << ". ";
									root1_2html = root1_2html->next;
								}
							}
							else {
								listele(root1_3html);
								while (root1_3html != NULL) {
									dosyayaYaz << root1_3html->data << ". ";
									root1_3html = root1_3html->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet1html[i]>0) bitisi
					}//for (int i=1; i<3; i++) bitisi
					for (int i = 0; i < 3; i++) {
						if (adet2html[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist2html[i] << " kelimesinden dosya4.html dosyasinda " << adet2html[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist2html[i] << " kelimesinden dosya4.html dosyasinda " << adet2html[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 0) {
								listele(root2_1html);
								while (root2_1html != NULL) {
									dosyayaYaz << root2_1html->data << ". ";
									root2_1html = root2_1html->next;
								}
							}
							else if (i == 1) {
								listele(root2_2html);
								while (root2_2html != NULL) {
									dosyayaYaz << root2_2html->data << ". ";
									root2_2html = root2_2html->next;
								}
							}
							else {
								listele(root2_3html);
								while (root2_3html != NULL) {
									dosyayaYaz << root2_3html->data << ". ";
									root2_3html = root2_3html->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet2html[i]>0) bitisi
					}//for(int i=0; i<3; i++) bitisi
					cout << "dosya4.html dosyasinda arama islemi " << olculenZamanhtml << " saniye surmustur." << endl << endl;
					dosyayaYaz << "dosya4.html dosyasinda arama islemi " << olculenZamanhtml << " saniye surmustur." << endl << endl;
				}//if(adet1html[0]>0 || adet2html[0]>0) bitisi
				if (adet1rtf[1] == 0 && adet1html[0] == 0 && adet2txt[0] == 0 && adet2dat[0] == 0 && adet2rtf[0] == 0 && adet2html[0] == 0) {
					cout << "Aradiginiz kelimeye ait baþka bir veriye ulaþýlamadi.";
					dosyayaYaz << "Aradiginiz kelimeye ait baþka bir veriye ulaþýlamadi.";
				}
			}//else (cevapKontrol==2) ise bitisi
		}//else if(adet1rtf[0]>0) bitisi
		/////////////
		else if (adet1html[0] > 0) {
			cout << kelimelerDist1html[0] << endl << "1- Evet" << endl << "2- Hayir" << endl << "Cevap: ";
			cin >> cevapKontrol;
			if (cevapKontrol == 1) {
				cout << kelimelerDist1html[0] << " kelimesinden dosya3.rtf dosyasinda " << adet1html[0] << " adet vardir ve ";
				listele(root1_1html);
				cout << "kelimelerinde bulunmustur." << endl << endl;
				cout << "dosya4.html dosyasinda arama islemi " << olculenZamanhtml << " sanyie surmustur." << endl << endl;

				dosyayaYaz << kelimelerDist1html[0] << " kelimesinden dosya4.html dosyasinda " << adet1html[0] << " adet vardir ve ";
				while (root1_1html != NULL) {
					dosyayaYaz << root1_1html->data << ". ";
					root1_1html = root1_1html->next;
				}
				dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
				dosyayaYaz << "dosya4.html dosyasinda arama islemi " << olculenZamanhtml << " saniye surmustur." << endl << endl;
				//html dosyasi icin yazdirma islemi tamamlandi
			}//if(cevapKontrol==1) bitisi
			else {
				if (adet2txt[0] > 0) {
					for (int i = 0; i < 3; i++) {
						if (adet2txt[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist2txt[i] << " kelimesinden dosya1.txt dosyasinda " << adet2txt[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist2txt[i] << " kelimesinden dosya1.txt dosyasinda " << adet2txt[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 0) {
								listele(root2_1txt);
								while (root2_1txt != NULL) {
									dosyayaYaz << root2_1txt->data << ". ";
									root2_1txt = root2_1txt->next;
								}
							}
							else if (i == 1) {
								listele(root2_2txt);
								while (root2_2txt != NULL) {
									dosyayaYaz << root2_2txt->data << ". ";
									root2_2txt = root2_2txt->next;
								}
							}
							else {
								listele(root2_3txt);
								while (root2_3txt != NULL) {
									dosyayaYaz << root2_3txt->data << ". ";
									root2_3txt = root2_3txt->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet2txt[i]>0) bitisi
					}//for(int i=0; i<3; i++) bitisi
					cout << "dosya1.txt dosyasinda arama islemi " << olculenZamantxt << " saniye surmustur." << endl << endl;
					dosyayaYaz << "dosya1.txt dosyasinda arama islemi " << olculenZamantxt << " saniye surmustur." << endl << endl;
				}//if(adet2txt[0]>0) bitisi
				if (adet2dat[0] > 0) {
					for (int i = 0; i < 3; i++) {
						if (adet2dat[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist2dat[i] << " kelimesinden dosya2.dat dosyasinda " << adet2dat[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist2dat[i] << " kelimesinden dosya2.dat dosyasinda " << adet2dat[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 0) {
								listele(root2_1dat);
								while (root2_1dat != NULL) {
									dosyayaYaz << root2_1dat->data << ". ";
									root2_1dat = root2_1dat->next;
								}
							}
							else if (i == 1) {
								listele(root2_2dat);
								while (root2_2dat != NULL) {
									dosyayaYaz << root2_2dat->data << ". ";
									root2_2dat = root2_2dat->next;
								}
							}
							else {
								listele(root2_3dat);
								while (root2_3dat != NULL) {
									dosyayaYaz << root2_3dat->data << ". ";
									root2_3dat = root2_3dat->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet2dat[i]>0) bitisi
					}//for(int i=0; i<3; i++) bitisi
					cout << "dosya2.dat dosyasinda arama islemi " << olculenZamandat << " saniye surmustur." << endl << endl;
					dosyayaYaz << "dosya2.dat dosyasinda arama islemi " << olculenZamandat << " saniye surmustur." << endl << endl;
				}//if(adet2dat[0]>0) bitisi
				if (adet2rtf[0] > 0) {
					for (int i = 0; i < 3; i++) {
						if (adet2rtf[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist2rtf[i] << " kelimesinden dosya3.rtf dosyasinda " << adet2rtf[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist2rtf[i] << " kelimesinden dosya3.rtf dosyasinda " << adet2rtf[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 0) {
								listele(root2_1rtf);
								while (root2_1rtf != NULL) {
									dosyayaYaz << root2_1rtf->data << ". ";
									root2_1rtf = root2_1rtf->next;
								}
							}
							else if (i == 1) {
								listele(root2_2rtf);
								while (root2_2rtf != NULL) {
									dosyayaYaz << root2_2rtf->data << ". ";
									root2_2rtf = root2_2rtf->next;
								}
							}
							else {
								listele(root2_3rtf);
								while (root2_3rtf != NULL) {
									dosyayaYaz << root2_3rtf->data << ". ";
									root2_3rtf = root2_3rtf->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet2rtf[i]>0) bitisi
					}//for(int i=0; i<3; i++) bitisi
					cout << "dosya3.rtf dosyasinda arama islemi " << olculenZamanrtf << " saniye surmustur." << endl << endl;
					dosyayaYaz << "dosya3.rtf dosyasinda arama islemi " << olculenZamanrtf << " saniye surmustur." << endl << endl;
				}//if(adet2rtf[0]>0) bitisi
				if (adet1html[1] > 0 || adet2html[0] > 0) {
					for (int i = 1; i < 3; i++) {
						if (adet1html[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist1html[i] << " kelimesinden dosya4.html dosyasinda " << adet1html[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist1html[i] << " kelimesinden dosya4.html dosyasinda " << adet1html[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 1) {
								listele(root1_2html);
								while (root1_2html != NULL) {
									dosyayaYaz << root1_2html->data << ". ";
									root1_2html = root1_2html->next;
								}
							}
							else {
								listele(root1_3html);
								while (root1_3html != NULL) {
									dosyayaYaz << root1_3html->data << ". ";
									root1_3html = root1_3html->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet1html[i]>0) bitisi
					}//for (int i=1; i<3; i++) bitisi
					for (int i = 0; i < 3; i++) {
						if (adet2html[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist2html[i] << " kelimesinden dosya4.html dosyasinda " << adet2html[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist2html[i] << " kelimesinden dosya4.html dosyasinda " << adet2html[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 0) {
								listele(root2_1html);
								while (root2_1html != NULL) {
									dosyayaYaz << root2_1html->data << ". ";
									root2_1html = root2_1html->next;
								}
							}
							else if (i == 1) {
								listele(root2_2html);
								while (root2_2html != NULL) {
									dosyayaYaz << root2_2html->data << ". ";
									root2_2html = root2_2html->next;
								}
							}
							else {
								listele(root2_3html);
								while (root2_3html != NULL) {
									dosyayaYaz << root2_3html->data << ". ";
									root2_3html = root2_3html->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet2html[i]>0) bitisi
					}//for(int i=0; i<3; i++) bitisi
					cout << "dosya4.html dosyasinda arama islemi " << olculenZamanhtml << " saniye surmustur." << endl << endl;
					dosyayaYaz << "dosya4.html dosyasinda arama islemi " << olculenZamanhtml << " saniye surmustur." << endl << endl;
				}//if(adet1html[0]>0 || adet2html[0]>0) bitisi
				if (adet1html[1] == 0 && adet2txt[0] == 0 && adet2dat[0] == 0 && adet2rtf[0] == 0 && adet2html[0] == 0) {
					cout << "Aradiginiz kelimeye ait baþka bir veriye ulaþýlamadi.";
					dosyayaYaz << "Aradiginiz kelimeye ait baþka bir veriye ulaþýlamadi.";
				}
			}//else (cevapKontrol==2) ise bitisi
		}//else if(adet1html[0]>0) bitisi
		////////////////
	}//else if(adet1txt[0]>0 || adet1dat[0]>0 || adet1rtf[0]>0 || adet1html[0]>0) bitisi 


	else if (adet2txt[0] > 0 || adet2dat[0] > 0 || adet2rtf[0] > 0 || adet2html[0] > 0) {
		cout << "Aradiginiz kelime bulunamadi. Bunu mu demek istediniz? : ";
		if (adet2txt[0] > 0) {
			cout << kelimelerDist2txt[0] << endl << "1- Evet" << endl << "2- Hayir" << endl << "Cevap: ";
			cin >> cevapKontrol;
			if (cevapKontrol == 1) {
				cout << kelimelerDist2txt[0] << " kelimesinden dosya1.txt dosyasinda " << adet2txt[0] << " adet vardir ve ";
				listele(root2_1txt);
				cout << "kelimelerinde bulunmustur." << endl << endl;
				cout << "dosya1.txt dosyasinda arama islemi " << olculenZamantxt << " sanyie surmustur." << endl << endl;

				dosyayaYaz << kelimelerDist2txt[0] << " kelimesinden dosya1.txt dosyasinda " << adet2txt[0] << " adet vardir ve ";
				while (root2_1txt != NULL) {
					dosyayaYaz << root2_1txt->data << ". ";
					root2_1txt = root2_1txt->next;
				}
				dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
				dosyayaYaz << "dosya1.txt dosyasinda arama islemi " << olculenZamantxt << " saniye surmustur." << endl << endl;
				//txt dosyasi icin yazdirma islemi tamamlandi
				for (int i = 0; i < 3; i++) {
					if (kelimelerDist2dat[i] == kelimelerDist2txt[0]) {
						cout << kelimelerDist2txt[0] << " kelimesinden dosya2.dat dosyasinda " << adet2dat[i] << " adet vardir ve ";
						if (i == 0) {
							listele(root2_1dat);
						}
						else if (i == 1) {
							listele(root2_2dat);
						}
						else {
							listele(root2_3dat);
						}
						cout << "kelimelerinde bulunmustur." << endl << endl;
						cout << "dosya2.dat dosyasinda arama islemi " << olculenZamandat << " saniye surmustur." << endl << endl;

						dosyayaYaz << kelimelerDist2txt[0] << " kelimesinden dosya2.dat dosyasinda " << adet2dat[i] << " adet vardir ve ";
						if (i == 0) {
							while (root2_1dat != NULL) {
								dosyayaYaz << root2_1dat->data << ". ";
								root2_1dat = root2_1dat->next;
							}
						}
						else if (i == 1) {
							while (root2_2dat != NULL) {
								dosyayaYaz << root2_2dat->data << ". ";
								root2_2dat = root2_2dat->next;
							}
						}
						else {
							while (root2_3dat != NULL) {
								dosyayaYaz << root2_3dat->data << ". ";
								root2_3dat = root2_3dat->next;
							}
						}
						dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						dosyayaYaz << "dosya2.dat dosyasinda arama islemi " << olculenZamandat << " saniye surmustur." << endl << endl;
					}//if(kelimelerDist1dat[i]==kelimelerDist1txt[0]) bitisi
					//dat dosyasi icin yazdirma islemi tamamlandi
					if (kelimelerDist2rtf[i] == kelimelerDist2txt[0]) {
						cout << kelimelerDist2txt[0] << " kelimesinden dosya3.rtf dosyasinda " << adet2rtf[i] << " adet vardir ve ";
						if (i == 0) {
							listele(root2_1rtf);
						}
						else if (i == 1) {
							listele(root2_2rtf);
						}
						else {
							listele(root2_3rtf);
						}
						cout << "kelimelerinde bulunmustur." << endl << endl;
						cout << "dosya3.rtf dosyasinda arama islemi " << olculenZamanrtf << " saniye surmustur." << endl << endl;

						dosyayaYaz << kelimelerDist2txt[0] << " kelimesinden dosya3.rtf dosyasinda " << adet2rtf[i] << " adet vardir ve ";
						if (i == 0) {
							while (root2_1rtf != NULL) {
								dosyayaYaz << root2_1rtf->data << ". ";
								root2_1rtf = root2_1rtf->next;
							}
						}
						else if (i == 1) {
							while (root2_2rtf != NULL) {
								dosyayaYaz << root2_2rtf->data << ". ";
								root2_2rtf = root2_2rtf->next;
							}
						}
						else {
							while (root2_3rtf != NULL) {
								dosyayaYaz << root2_3rtf->data << ". ";
								root2_3rtf = root2_3rtf->next;
							}
						}
						dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						dosyayaYaz << "dosya3.rtf dosyasinda arama islemi " << olculenZamanrtf << " saniye surmustur." << endl << endl;
					}//if(kelimelerDist1rtf[i]==kelimelerDist1txt[0]) bitisi
					//rtf dosyasi icin yazdirma islemi tamamlandi
					if (kelimelerDist2html[i] == kelimelerDist2txt[0]) {
						cout << kelimelerDist2txt[0] << " kelimesinden dosya4.html dosyasinda " << adet2html[i] << " adet vardir ve ";
						if (i == 0) {
							listele(root2_1html);
						}
						else if (i == 1) {
							listele(root2_2html);
						}
						else {
							listele(root2_3html);
						}
						cout << "kelimelerinde bulunmustur." << endl << endl;
						cout << "dosya4.html dosyasinda arama islemi " << olculenZamanhtml << " saniye surmustur." << endl << endl;

						dosyayaYaz << kelimelerDist2txt[0] << " kelimesinden dosya4.html dosyasinda " << adet2html[i] << " adet vardir ve ";
						if (i == 0) {
							while (root2_1html != NULL) {
								dosyayaYaz << root2_1html->data << ". ";
								root2_1html = root2_1html->next;
							}
						}
						else if (i == 1) {
							while (root2_2html != NULL) {
								dosyayaYaz << root2_2html->data << ". ";
								root2_2html = root2_2html->next;
							}
						}
						else {
							while (root2_3html != NULL) {
								dosyayaYaz << root2_3html->data << ". ";
								root2_3html = root2_3html->next;
							}
						}
						dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						dosyayaYaz << "dosya4.html dosyasinda arama islemi " << olculenZamanhtml << " saniye surmustur." << endl << endl;
					}//if(kelimelerDist2html[i]==kelimelerDist2txt[0]) bitisi
					//html dosyasi icin yazdirma islemi tamamlandi
				}//for dongusu bitisi
			}//if(cevapKontrol==1) bitisi
			else {
				if (adet2txt[1] > 0) {
					for (int i = 1; i < 3; i++) {
						if (adet2txt[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist2txt[i] << " kelimesinden dosya1.txt dosyasinda " << adet2txt[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist2txt[i] << " kelimesinden dosya1.txt dosyasinda " << adet2txt[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 1) {
								listele(root2_2txt);
								while (root2_2txt != NULL) {
									dosyayaYaz << root2_2txt->data << ". ";
									root2_2txt = root2_2txt->next;
								}
							}
							else {
								listele(root2_3txt);
								while (root2_3txt != NULL) {
									dosyayaYaz << root2_3txt->data << ". ";
									root2_3txt = root2_3txt->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet1txt[i]>0) bitisi
					}//for (int i=1; i<3; i++) bitisi
					cout << "dosya1.txt dosyasinda arama islemi " << olculenZamantxt << " saniye surmustur." << endl << endl;
					dosyayaYaz << "dosya1.txt dosyasinda arama islemi " << olculenZamantxt << " saniye surmustur." << endl << endl;
				}//if(adet1txt[1]>0 || adet2txt[0]>0) bitisi
				if (adet2dat[0] > 0) {
					for (int i = 0; i < 3; i++) {
						if (adet2dat[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist2dat[i] << " kelimesinden dosya2.dat dosyasinda " << adet2dat[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist2dat[i] << " kelimesinden dosya2.dat dosyasinda " << adet2dat[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 0) {
								listele(root2_1dat);
								while (root2_1dat != NULL) {
									dosyayaYaz << root2_1dat->data << ". ";
									root2_1dat = root2_1dat->next;
								}
							}
							else if (i == 1) {
								listele(root2_2dat);
								while (root2_2dat != NULL) {
									dosyayaYaz << root2_2dat->data << ". ";
									root2_2dat = root2_2dat->next;
								}
							}
							else {
								listele(root2_3dat);
								while (root2_3dat != NULL) {
									dosyayaYaz << root2_3dat->data << ". ";
									root2_3dat = root2_3dat->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet2dat[i]>0) bitisi
					}//for(int i=0; i<3; i++) bitisi
					cout << "dosya2.dat dosyasinda arama islemi " << olculenZamandat << " saniye surmustur." << endl << endl;
					dosyayaYaz << "dosya2.dat dosyasinda arama islemi " << olculenZamandat << " saniye surmustur." << endl << endl;
				}//if(adet2dat[0]>0) bitisi
				if (adet2rtf[0] > 0) {
					for (int i = 0; i < 3; i++) {
						if (adet2rtf[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist2rtf[i] << " kelimesinden dosya3.rtf dosyasinda " << adet2rtf[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist2rtf[i] << " kelimesinden dosya3.rtf dosyasinda " << adet2rtf[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 0) {
								listele(root2_1rtf);
								while (root2_1rtf != NULL) {
									dosyayaYaz << root2_1rtf->data << ". ";
									root2_1rtf = root2_1rtf->next;
								}
							}
							else if (i == 1) {
								listele(root2_2rtf);
								while (root2_2rtf != NULL) {
									dosyayaYaz << root2_2rtf->data << ". ";
									root2_2rtf = root2_2rtf->next;
								}
							}
							else {
								listele(root2_3rtf);
								while (root2_3rtf != NULL) {
									dosyayaYaz << root2_3rtf->data << ". ";
									root2_3rtf = root2_3rtf->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet2rtf[i]>0) bitisi
					}//for(int i=0; i<3; i++) bitisi
					cout << "dosya3.rtf dosyasinda arama islemi " << olculenZamanrtf << " saniye surmustur." << endl << endl;
					dosyayaYaz << "dosya3.rtf dosyasinda arama islemi " << olculenZamanrtf << " saniye surmustur." << endl << endl;
				}//if(adet2rtf[0]>0) bitisi
				if (adet2html[0] > 0) {
					for (int i = 0; i < 3; i++) {
						if (adet2html[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist2html[i] << " kelimesinden dosya4.html dosyasinda " << adet2html[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist2html[i] << " kelimesinden dosya4.html dosyasinda " << adet2html[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 0) {
								listele(root2_1html);
								while (root2_1html != NULL) {
									dosyayaYaz << root2_1html->data << ". ";
									root2_1html = root2_1html->next;
								}
							}
							else if (i == 1) {
								listele(root2_2html);
								while (root2_2html != NULL) {
									dosyayaYaz << root2_2html->data << ". ";
									root2_2html = root2_2html->next;
								}
							}
							else {
								listele(root2_3html);
								while (root2_3html != NULL) {
									dosyayaYaz << root2_3html->data << ". ";
									root2_3html = root2_3html->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet2html[i]>0) bitisi
					}//for(int i=0; i<3; i++) bitisi
					cout << "dosya4.html dosyasinda arama islemi " << olculenZamanhtml << " saniye surmustur." << endl << endl;
					dosyayaYaz << "dosya4.html dosyasinda arama islemi " << olculenZamanhtml << " saniye surmustur." << endl << endl;
				}//if(adet1html[0]>0 || adet2html[0]>0) bitisi
				if (adet2txt[1] == 0 && adet2dat[0] == 0 && adet2rtf[0] == 0 && adet2html[0] == 0) {
					cout << "Aradiginiz kelimeye ait baþka bir veriye ulaþýlamadi.";
					dosyayaYaz << "Aradiginiz kelimeye ait baþka bir veriye ulaþýlamadi.";
				}
			}//else (cevapKontrol==2) ise bitisi
		}//if(adet2txt[0]>0) bitisi
		else if (adet2dat[0] > 0) {
			cout << kelimelerDist2dat[0] << endl << "1- Evet" << endl << "2- Hayir" << endl << "Cevap: ";
			cin >> cevapKontrol;
			if (cevapKontrol == 1) {
				cout << kelimelerDist2dat[0] << " kelimesinden dosya2.dat dosyasinda " << adet2dat[0] << " adet vardir ve ";
				listele(root2_1dat);
				cout << "kelimelerinde bulunmustur." << endl << endl;
				cout << "dosya2.dat dosyasinda arama islemi " << olculenZamandat << " sanyie surmustur." << endl << endl;

				dosyayaYaz << kelimelerDist2dat[0] << " kelimesinden dosya2.dat dosyasinda " << adet2dat[0] << " adet vardir ve ";
				while (root2_1dat != NULL) {
					dosyayaYaz << root2_1dat->data << ". ";
					root2_1dat = root2_1dat->next;
				}
				dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
				dosyayaYaz << "dosya2.dat dosyasinda arama islemi " << olculenZamandat << " saniye surmustur." << endl << endl;
				//dat dosyasi icin yazdirma islemi tamamlandi
				for (int i = 0; i < 3; i++) {
					if (kelimelerDist2rtf[i] == kelimelerDist2dat[0]) {
						cout << kelimelerDist2txt[0] << " kelimesinden dosya3.rtf dosyasinda " << adet2rtf[i] << " adet vardir ve ";
						if (i == 0) {
							listele(root2_1rtf);
						}
						else if (i == 1) {
							listele(root2_2rtf);
						}
						else {
							listele(root2_3rtf);
						}
						cout << "kelimelerinde bulunmustur." << endl << endl;
						cout << "dosya3.rtf dosyasinda arama islemi " << olculenZamanrtf << " saniye surmustur." << endl << endl;

						dosyayaYaz << kelimelerDist2dat[0] << " kelimesinden dosya3.rtf dosyasinda " << adet2rtf[i] << " adet vardir ve ";
						if (i == 0) {
							while (root2_1rtf != NULL) {
								dosyayaYaz << root2_1rtf->data << ". ";
								root2_1rtf = root2_1rtf->next;
							}
						}
						else if (i == 1) {
							while (root2_2rtf != NULL) {
								dosyayaYaz << root2_2rtf->data << ". ";
								root2_2rtf = root2_2rtf->next;
							}
						}
						else {
							while (root2_3rtf != NULL) {
								dosyayaYaz << root2_3rtf->data << ". ";
								root2_3rtf = root2_3rtf->next;
							}
						}
						dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						dosyayaYaz << "dosya3.rtf dosyasinda arama islemi " << olculenZamanrtf << " saniye surmustur." << endl << endl;
					}//if(kelimelerDist1rtf[i]==kelimelerDist1txt[0]) bitisi
					//rtf dosyasi icin yazdirma islemi tamamlandi
					if (kelimelerDist2html[i] == kelimelerDist2dat[0]) {
						cout << kelimelerDist2dat[0] << " kelimesinden dosya4.html dosyasinda " << adet2html[i] << " adet vardir ve ";
						if (i == 0) {
							listele(root2_1html);
						}
						else if (i == 1) {
							listele(root2_2html);
						}
						else {
							listele(root2_3html);
						}
						cout << "kelimelerinde bulunmustur." << endl << endl;
						cout << "dosya4.html dosyasinda arama islemi " << olculenZamanhtml << " saniye surmustur." << endl << endl;

						dosyayaYaz << kelimelerDist2dat[0] << " kelimesinden dosya4.html dosyasinda " << adet2html[i] << " adet vardir ve ";
						if (i == 0) {
							while (root2_1html != NULL) {
								dosyayaYaz << root2_1html->data << ". ";
								root2_1html = root2_1html->next;
							}
						}
						else if (i == 1) {
							while (root2_2html != NULL) {
								dosyayaYaz << root2_2html->data << ". ";
								root2_2html = root2_2html->next;
							}
						}
						else {
							while (root2_3html != NULL) {
								dosyayaYaz << root2_3html->data << ". ";
								root2_3html = root2_3html->next;
							}
						}
						dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						dosyayaYaz << "dosya4.html dosyasinda arama islemi " << olculenZamanhtml << " saniye surmustur." << endl << endl;
					}//if(kelimelerDist2html[i]==kelimelerDist2txt[0]) bitisi
					//html dosyasi icin yazdirma islemi tamamlandi
				}//for dongusu bitisi
			}//if(cevapKontrol==1) bitisi
			else {
				if (adet2dat[1] > 0) {
					for (int i = 1; i < 3; i++) {
						if (adet2dat[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist2dat[i] << " kelimesinden dosya2.dat dosyasinda " << adet2dat[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist2dat[i] << " kelimesinden dosya2.dat dosyasinda " << adet2dat[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 1) {
								listele(root2_2dat);
								while (root2_2dat != NULL) {
									dosyayaYaz << root2_2dat->data << ". ";
									root2_2dat = root2_2dat->next;
								}
							}
							else {
								listele(root2_3dat);
								while (root2_3dat != NULL) {
									dosyayaYaz << root2_3dat->data << ". ";
									root2_3dat = root2_3dat->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet2dat[i]>0) bitisi
					}//for(int i=1; i<3; i++) bitisi
					cout << "dosya2.dat dosyasinda arama islemi " << olculenZamandat << " saniye surmustur." << endl << endl;
					dosyayaYaz << "dosya2.dat dosyasinda arama islemi " << olculenZamandat << " saniye surmustur." << endl << endl;
				}//if(adet2dat[1]>0) bitisi
				if (adet2rtf[0] > 0) {
					for (int i = 0; i < 3; i++) {
						if (adet2rtf[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist2rtf[i] << " kelimesinden dosya3.rtf dosyasinda " << adet2rtf[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist2rtf[i] << " kelimesinden dosya3.rtf dosyasinda " << adet2rtf[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 0) {
								listele(root2_1rtf);
								while (root2_1rtf != NULL) {
									dosyayaYaz << root2_1rtf->data << ". ";
									root2_1rtf = root2_1rtf->next;
								}
							}
							else if (i == 1) {
								listele(root2_2rtf);
								while (root2_2rtf != NULL) {
									dosyayaYaz << root2_2rtf->data << ". ";
									root2_2rtf = root2_2rtf->next;
								}
							}
							else {
								listele(root2_3rtf);
								while (root2_3rtf != NULL) {
									dosyayaYaz << root2_3rtf->data << ". ";
									root2_3rtf = root2_3rtf->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet2rtf[i]>0) bitisi
					}//for(int i=0; i<3; i++) bitisi
					cout << "dosya3.rtf dosyasinda arama islemi " << olculenZamanrtf << " saniye surmustur." << endl << endl;
					dosyayaYaz << "dosya3.rtf dosyasinda arama islemi " << olculenZamanrtf << " saniye surmustur." << endl << endl;
				}//if(adet2rtf[0]>0) bitisi
				if (adet2html[0] > 0) {
					for (int i = 0; i < 3; i++) {
						if (adet2html[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist2html[i] << " kelimesinden dosya4.html dosyasinda " << adet2html[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist2html[i] << " kelimesinden dosya4.html dosyasinda " << adet2html[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 0) {
								listele(root2_1html);
								while (root2_1html != NULL) {
									dosyayaYaz << root2_1html->data << ". ";
									root2_1html = root2_1html->next;
								}
							}
							else if (i == 1) {
								listele(root2_2html);
								while (root2_2html != NULL) {
									dosyayaYaz << root2_2html->data << ". ";
									root2_2html = root2_2html->next;
								}
							}
							else {
								listele(root2_3html);
								while (root2_3html != NULL) {
									dosyayaYaz << root2_3html->data << ". ";
									root2_3html = root2_3html->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet2html[i]>0) bitisi
					}//for(int i=0; i<3; i++) bitisi
					cout << "dosya4.html dosyasinda arama islemi " << olculenZamanhtml << " saniye surmustur." << endl << endl;
					dosyayaYaz << "dosya4.html dosyasinda arama islemi " << olculenZamanhtml << " saniye surmustur." << endl << endl;
				}//if(adet1html[0]>0 || adet2html[0]>0) bitisi
				if (adet2dat[1] == 0 && adet2rtf[0] == 0 && adet2html[0] == 0) {
					cout << "Aradiginiz kelimeye ait baþka bir veriye ulaþýlamadi.";
					dosyayaYaz << "Aradiginiz kelimeye ait baþka bir veriye ulaþýlamadi.";
				}
			}//else (cevapKontrol==2) ise bitisi
		}//if(adet2dat[0]>0) bitisi
		else if (adet2rtf[0] > 0) {
			cout << kelimelerDist2rtf[0] << endl << "1- Evet" << endl << "2- Hayir" << endl << "Cevap: ";
			cin >> cevapKontrol;
			if (cevapKontrol == 1) {
				cout << kelimelerDist2rtf[0] << " kelimesinden dosya3.rtf dosyasinda " << adet2rtf[0] << " adet vardir ve ";
				listele(root2_1rtf);
				cout << "kelimelerinde bulunmustur." << endl << endl;
				cout << "dosya3.rtf dosyasinda arama islemi " << olculenZamanrtf << " sanyie surmustur." << endl << endl;

				dosyayaYaz << kelimelerDist2rtf[0] << " kelimesinden dosya3.rtf dosyasinda " << adet2rtf[0] << " adet vardir ve ";
				while (root2_1rtf != NULL) {
					dosyayaYaz << root2_1rtf->data << ". ";
					root2_1rtf = root2_1rtf->next;
				}
				dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
				dosyayaYaz << "dosya3.rtf dosyasinda arama islemi " << olculenZamanrtf << " saniye surmustur." << endl << endl;
				//dat dosyasi icin yazdirma islemi tamamlandi
				for (int i = 0; i < 3; i++) {
					if (kelimelerDist2html[i] == kelimelerDist2rtf[0]) {
						cout << kelimelerDist2rtf[0] << " kelimesinden dosya4.html dosyasinda " << adet2html[i] << " adet vardir ve ";
						if (i == 0) {
							listele(root2_1html);
						}
						else if (i == 1) {
							listele(root2_2html);
						}
						else {
							listele(root2_3html);
						}
						cout << "kelimelerinde bulunmustur." << endl << endl;
						cout << "dosya4.html dosyasinda arama islemi " << olculenZamanhtml << " saniye surmustur." << endl << endl;

						dosyayaYaz << kelimelerDist2rtf[0] << " kelimesinden dosya4.html dosyasinda " << adet2html[i] << " adet vardir ve ";
						if (i == 0) {
							while (root2_1html != NULL) {
								dosyayaYaz << root2_1html->data << ". ";
								root2_1html = root2_1html->next;
							}
						}
						else if (i == 1) {
							while (root2_2html != NULL) {
								dosyayaYaz << root2_2html->data << ". ";
								root2_2html = root2_2html->next;
							}
						}
						else {
							while (root2_3html != NULL) {
								dosyayaYaz << root2_3html->data << ". ";
								root2_3html = root2_3html->next;
							}
						}
						dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						dosyayaYaz << "dosya4.html dosyasinda arama islemi " << olculenZamanhtml << " saniye surmustur." << endl << endl;
					}//if(kelimelerDist2html[i]==kelimelerDist2rtf[0]) bitisi
					//html dosyasi icin yazdirma islemi tamamlandi
				}//for dongusu bitisi
			}//if(cevapKontrol==1) bitisi
			else {
				if (adet2rtf[1] > 0) {
					for (int i = 1; i < 3; i++) {
						if (adet2rtf[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist2rtf[i] << " kelimesinden dosya3.rtf dosyasinda " << adet2rtf[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist2rtf[i] << " kelimesinden dosya3.rtf dosyasinda " << adet2rtf[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 1) {
								listele(root2_2rtf);
								while (root2_2rtf != NULL) {
									dosyayaYaz << root2_2rtf->data << ". ";
									root2_2rtf = root2_2rtf->next;
								}
							}
							else {
								listele(root2_3rtf);
								while (root2_3rtf != NULL) {
									dosyayaYaz << root2_3rtf->data << ". ";
									root2_3rtf = root2_3rtf->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet2rtf[i]>0) bitisi
					}//for(int i=0; i<3; i++) bitisi
					cout << "dosya3.rtf dosyasinda arama islemi " << olculenZamanrtf << " saniye surmustur." << endl << endl;
					dosyayaYaz << "dosya3.rtf dosyasinda arama islemi " << olculenZamanrtf << " saniye surmustur." << endl << endl;
				}//if(adet2rtf[1]>0) bitisi
				if (adet2html[0] > 0) {
					for (int i = 0; i < 3; i++) {
						if (adet2html[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist2html[i] << " kelimesinden dosya4.html dosyasinda " << adet2html[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist2html[i] << " kelimesinden dosya4.html dosyasinda " << adet2html[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 0) {
								listele(root2_1html);
								while (root2_1html != NULL) {
									dosyayaYaz << root2_1html->data << ". ";
									root2_1html = root2_1html->next;
								}
							}
							else if (i == 1) {
								listele(root2_2html);
								while (root2_2html != NULL) {
									dosyayaYaz << root2_2html->data << ". ";
									root2_2html = root2_2html->next;
								}
							}
							else {
								listele(root2_3html);
								while (root2_3html != NULL) {
									dosyayaYaz << root2_3html->data << ". ";
									root2_3html = root2_3html->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet2html[i]>0) bitisi
					}//for(int i=0; i<3; i++) bitisi
					cout << "dosya4.html dosyasinda arama islemi " << olculenZamanhtml << " saniye surmustur." << endl << endl;
					dosyayaYaz << "dosya4.html dosyasinda arama islemi " << olculenZamanhtml << " saniye surmustur." << endl << endl;
				}//if( adet2html[0]>0) bitisi
				if (adet2rtf[1] == 0 && adet2html[0] == 0) {
					cout << "Aradiginiz kelimeye ait baþka bir veriye ulaþýlamadi.";
					dosyayaYaz << "Aradiginiz kelimeye ait baþka bir veriye ulaþýlamadi.";
				}
			}//else (cevapKontrol==2) ise bitisi
		}//if(adet2rtf[0]>0) bitisi
		else if (adet2html[0] > 0) {
			cout << kelimelerDist2html[0] << endl << "1- Evet" << endl << "2- Hayir" << endl << "Cevap: ";
			cin >> cevapKontrol;
			if (cevapKontrol == 1) {
				cout << kelimelerDist2html[0] << " kelimesinden dosya3.rtf dosyasinda " << adet2html[0] << " adet vardir ve ";
				listele(root2_1html);
				cout << "kelimelerinde bulunmustur." << endl << endl;
				cout << "dosya4.html dosyasinda arama islemi " << olculenZamanhtml << " sanyie surmustur." << endl << endl;

				dosyayaYaz << kelimelerDist2html[0] << " kelimesinden dosya4.html dosyasinda " << adet2html[0] << " adet vardir ve ";
				while (root2_1html != NULL) {
					dosyayaYaz << root2_1html->data << ". ";
					root2_1html = root2_1html->next;
				}
				dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
				dosyayaYaz << "dosya4.html dosyasinda arama islemi " << olculenZamanhtml << " saniye surmustur." << endl << endl;
				//html dosyasi icin yazdirma islemi tamamlandi
			}//if(cevapKontrol==1) bitisi
			else {
				if (adet2html[1] > 0) {
					for (int i = 1; i < 3; i++) {
						if (adet2html[i] > 0) {
							cout << secenekSirasi << "- " << kelimelerDist2html[i] << " kelimesinden dosya4.html dosyasinda " << adet2html[i] << " adet vardir ve ";
							dosyayaYaz << secenekSirasi << "- " << kelimelerDist2html[i] << " kelimesinden dosya4.html dosyasinda " << adet2html[i] << " adet vardir ve ";
							secenekSirasi++;
							if (i == 1) {
								listele(root2_2html);
								while (root2_2html != NULL) {
									dosyayaYaz << root2_2html->data << ". ";
									root2_2html = root2_2html->next;
								}
							}
							else {
								listele(root2_3html);
								while (root2_3html != NULL) {
									dosyayaYaz << root2_3html->data << ". ";
									root2_3html = root2_3html->next;
								}
							}
							cout << "kelimelerinde bulunmustur." << endl << endl;
							dosyayaYaz << "kelimelerinde bulunmustur." << endl << endl;
						}//if(adet2html[i]>0) bitisi
					}//for(int i=0; i<3; i++) bitisi
					cout << "dosya4.html dosyasinda arama islemi " << olculenZamanhtml << " saniye surmustur." << endl << endl;
					dosyayaYaz << "dosya4.html dosyasinda arama islemi " << olculenZamanhtml << " saniye surmustur." << endl << endl;
				}//if( adet2html[0]>0) bitisi
				if (adet2html[1] == 0) {
					cout << "Aradiginiz kelimeye ait baþka bir veriye ulaþýlamadi.";
					dosyayaYaz << "Aradiginiz kelimeye ait baþka bir veriye ulaþýlamadi.";
				}
			}//else (cevapKontrol==2) ise bitisi
		}//else if(adet2html[0]>0) bitisi
	}//else if(adet2txt[0]>0 || adet2dat[0]>0 || adet2rtf[0]>0 || adet2html[0]>0)
	///////////////
	else {
		cout << "Aradiginiz kelimeye ait baþka bir veriye ulaþýlamadi.";
		dosyayaYaz << "Aradiginiz kelimeye ait baþka bir veriye ulaþýlamadi.";
	}
	cout << "Arama islemi toplam  " << olculenZamantxt + olculenZamandat + olculenZamanrtf + olculenZamanhtml << " saniye surmustur.";
	dosyayaYaz << "Arama islemi toplam " << olculenZamantxt + olculenZamandat + olculenZamanrtf + olculenZamanhtml << " saniye surmustur.";
	////////////////
	dosyayaYaz.close();
	/////////////////////////////
}//dosyalamaIslemleri bitisi
//	menu
void menu() {
	cout << "-----------" << endl;
	cout << "Aramak istenilen kelimeyi giriniz: ";
	string aramakIstenilenKelime;
	cin >> aramakIstenilenKelime;
	dosyalamaIslemleri(aramakIstenilenKelime);


}
// main function
void main() {
	menu();
	system("C:\\Users\\ex\\Desktop\\VisualStudioProgramlama\\ProjeCalisma\\ProjeDeneme4\\ProjeDeneme4\\sonuc.txt"); // dosyayi ekrana verme
	system("pause");
}