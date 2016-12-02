#ifndef TRANSAKSI_H_INCLUDED
#define TRANSAKSI_H_INCLUDED

#include "obat.h"
#include <iostream>
#include <sstream>
using namespace std;

#define info(P)  P->info
#define next(P)  P->next
#define prev(P)  P->prev
#define barang(P) P->barang
#define listBarang(L) L->listBarang
#define first(L)   L.first
#define last(L)    L.last
#define SSTR( x ) static_cast< std::ostringstream & >( \
                ( std::ostringstream() << std::dec << x ) ).str()
struct barang{
    string invoice;
    int no,jumlah;
    float total_awal;
};

typedef barang infotypeBRG;
typedef struct elmBRG *addressBRG;
typedef struct elmTRX *addressTRX;

struct elmBRG{
    infotypeBRG info;
    addressBRG next, prev;
    address barang;
};

struct listBRG{
    addressBRG first, last;
};

//transaksi
struct transaksi{
    string no_transaksi;
    float total_akhir;
};

typedef transaksi infotypeTRX;

struct elmTRX{
    infotypeTRX info;
    addressTRX next;
    listBRG listBarang;
};

struct listTRX{
    addressTRX first, last;
};

void transaksi(listTRX &L, listObat O);
//TRANSAKSI ZONE
void insertTRX(listTRX &L, infotypeTRX x);
void createTransaksi(listTRX &L);
addressTRX alokasiTRX(infotypeTRX x);
void printTRX(listTRX L);
void deleteTransaksi(listTRX &L, addressTRX P);
void deleteFirstTransaksi(listTRX &L);
void deleteAfterTransaksi(listTRX &L, addressTRX P);
void deleteLastTransaksi(listTRX &L);
addressTRX findTRX(listTRX L, string x);

//BARANG ZONE
void insertBRG(listBRG &L, infotypeBRG x,address Q);
void createBarang(listBRG &L);
addressBRG alokasiBRG(infotypeBRG x);
void printBRG(listBRG L,int &i, int &j);
void deleteBarang(listBRG &L, addressBRG P);
void deleteFirstBarang(listBRG &L);
void deleteAfterBarang(listBRG &L, addressBRG P);
void deleteLastBarang(listBRG &L);
addressBRG findBRG(listBRG L, int x);
#endif // TRANSAKSI_H_INCLUDED
