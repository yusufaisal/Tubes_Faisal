#include "obat.h"
#include "transaksi.h"

//variable zone START
    listObat Obat;
    listTRX trans;
//variable zone END

void inputTransaksi(listObat O);
void ObatinDong(listObat &L);
void menuDeleteBarang(listObat &Obat, listTRX &trans);
void menuDeleteObat(listObat &Obat);
void menuInfoObat(listObat &Obat);
void menuDeleteTransaksi(listTRX &trans);

int main()
{
    createListObat(Obat);
    createTransaksi(trans);
    ObatinDong(Obat);

    //printObat(Obat);
    //inputTransaksi(Obat);
    //printTRX(trans);
    int pilih;
    do {
        clrscr();
        gotoxy(1,1);cout << "1. Input Obat" ;
        gotoxy(1,2);cout << "2. Input Transaksi";
        gotoxy(1,3);cout << "3. Search Obat";
        gotoxy(1,4);cout << "4. Delete Obat";
        gotoxy(1,5);cout << "5. Delete Transaksi (Transaksi)";
        gotoxy(1,6);cout << "6. Delete Transaksi (Barang)";
        gotoxy(1,7);cout << "7. View Obat";
        gotoxy(1,8);cout << "8. View Transaksi";
        gotoxy(1,9);cout << "0. Exit";
        gotoxy(1,11);cout << "menu > ";cin >> pilih;

        if (pilih == 1) {
            inputObat(Obat);
        } else if (pilih ==2){
            transaksi(trans, Obat);
        } else if (pilih ==3){
            clrscr();
            menuInfoObat(Obat);
        } else if (pilih == 4){
            clrscr();
            menuDeleteObat(Obat);
        } else if (pilih==5){
            clrscr();
            menuDeleteTransaksi(trans);
        } else if (pilih==6){
            clrscr();
            menuDeleteBarang(Obat,trans);
        } else if (pilih==7){
            printObat(Obat);
        } else if (pilih==8){
            printTRX(trans);
        }
        getch();
    } while (pilih != 0);

    return 0;
}

void ObatinDong(listObat &L){
    infotype x;

    x.kode_obat = 12345;
    x.jenis = "kapsul";
    x.nama = "Paramorex";
    x.kategori = "Mabuk";
    x.harga = 11000;
    x.stok = 13;
    insertObat(Obat,x);

    x.kode_obat = 43231;
    x.jenis = "kapsul";
    x.nama = "Panadol";
    x.kategori = "Mabuk";
    x.stok = 13;
    x.harga = 30000;
    insertObat(Obat,x);

    x.kode_obat = 3231;
    x.jenis = "kapsul";
    x.nama = "Panadol";
    x.kategori = "Mabuk";
    x.stok = 13;
    x.harga = 90000;
    insertObat(Obat,x);

    x.kode_obat = 12346;
    x.jenis = "kapsul";
    x.nama = "Panadol";
    x.kategori = "Mabuk";
    x.stok = 13;
    x.harga = 340000;
    insertObat(Obat,x);

    x.kode_obat = 12349;
    x.jenis = "kapsul";
    x.nama = "Panadol";
    x.kategori = "Mabuk";
    x.stok = 13;
    x.harga = 38000;
    insertObat(Obat,x);
}

void menuDeleteObat(listObat &Obat){
    string Pilih;
    gotoxy(8,1);cout << "===Delete===";

    address P;
    Search_View(Obat, P);
    if (P!=NULL){
        gotoxy(30,9);cout << "Yakin ingin dihapus? (N)/Y "; cin >> Pilih;
        if (Pilih == "Y"){
            deleteObat(Obat,P);
            gotoxy(32,6);cout << "Berhasil Dihapus";
        } else{
            gotoxy(32,6);cout << "Dibatalkan";
        }
    }
}

void menuInfoObat(listObat &Obat){
    gotoxy(8,1);cout << "===INFO===";
    address P;
    Search_View(Obat, P);
}
void menuDeleteBarang(listObat &Obat, listTRX &trans){
    string idtransaksi;
    int idBarang, BRG;

    gotoxy(1,4);cout << "-----------------------------------------------------------------";
    gotoxy(1,5);cout << "| No Transaksi | Kode Obat | Nama Barang | Jumlah | Total Akhir |";
    gotoxy(1,6);cout << "+---------------------------------------------------------------+";
    gotoxy(1,2);cout << "ID Transaksi : "; cin >> idtransaksi;
    addressTRX P = findTRX(trans, idtransaksi);
    if (P != NULL ) {
        int i = 7;
        gotoxy(3,i) ;cout << info(P).no_transaksi;
        gotoxy(53,i);cout << info(P).total_akhir;

        printBRG(listBarang(P),i,BRG);
        gotoxy(1,i) ;cout << "+---------------------------------------------------------------+";

        cout << "No Barang : "; cin >> idBarang;
        addressBRG B = findBRG(listBarang(P),idBarang);

        if (B != NULL){
            deleteBarang(listBarang(P),B);
        } else {
            cout << "Barang tidak ditemukan";
        }
    } else {
        cout << "Transaksi tidak ditemukan";
    }
}

void menuDeleteTransaksi(listTRX &trans){
    string idtransaksi;
    cout << "ID Transaksi : "; cin >> idtransaksi;
    addressTRX P = findTRX(trans, idtransaksi);
    deleteTransaksi(trans,P);
}

