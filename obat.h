#ifndef OBAT_H_INCLUDED
#define OBAT_H_INCLUDED

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>

using namespace std;

#define info(P)  P->info
#define next(P)  P->next
#define prev(P)  P->prev
#define first(L) L.first
#define last(L)  L.last


struct obat{
    int kode_obat;
    string nama;
    string jenis;
    string kategori;
    int stok;
    double harga;
};

typedef  obat infotype;
typedef struct elmObat *address;

struct elmObat{
    infotype info;
    address next, prev;
};

struct listObat{
    address first, last;
};

void inputObat(listObat &L);
void Search_View(listObat L, address &P);

void createListObat(listObat &L);
address alokasi(infotype x);

void insertObat(listObat &L, infotype x);
void insertFirst(listObat &L, address P);
void insertLast(listObat &L, address P);
void insertAfter(listObat &L, address Q,address P);

void deleteObat(listObat &L, address P);
address deleteLast(listObat &L);
address deleteFirst(listObat &L);
address deleteAfter(listObat &L, address P);

address findObat(listObat L, int x); //by Kode_Obat
void printObat(listObat L);


//=========================================================================
void clrscr();
void gotoxy(int x, int y);
//=========================================================================


#endif // OBAT_H_INCLUDED
