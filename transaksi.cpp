#include "transaksi.h"
int No_TRX = 0;

void transaksi(listTRX &L, listObat O){
    /*
    ** I.S. : menampilkan form input transaksi
    ** F.S. : - insert transaksi ke dalam elemen Parent
    **        - insert barang ke dalam elemen Child
    **        - Hapus elemen Parent jika tidak ada barang yang diinputkan
    */
    infotypeTRX x;
    infotypeBRG z;
    char pilih;
    int i=8;
    int No_BRG = 1;
    int kode_obat;

    No_TRX++;
    clrscr();
    gotoxy(33,0); cout << "Form Transaksi";
    gotoxy(2,2) ; cout  << "No Transaksi  = TRX - " << No_TRX;
    gotoxy(35,2) ; cout << "No invoice = -";
    gotoxy(35,3) ; cout << "No Barang  = -";
    gotoxy(1,5); cout << "-----------------------------------------------------------------------------";
    gotoxy(1,6); cout << "| No Invoice | Kode Obat | Obat            | Harga   | Jumlah | Total Awal  |";
    gotoxy(1,7); cout << "-----------------------------------------------------------------------------";

    x.no_transaksi = SSTR("TRX" << No_TRX);
    x.total_akhir = 0;
    float sum = 0;
    insertTRX(L,x);
        address Q;
        do{
            z.no = No_BRG;
            gotoxy(16,i);cout << "                                                       ";
            gotoxy(12,4);cout << "                                               ";
            z.invoice = SSTR(x.no_transaksi<< "-"<<No_BRG);
            gotoxy(48,3);cout << z.no;
            gotoxy(48,2);cout << z.invoice;

            gotoxy(3,i);cout << z.invoice;
            gotoxy(16,i);cin >> kode_obat;
            Q = findObat(O,kode_obat);
            if (Q==NULL){
                gotoxy(12,4);cout << "Kode Obat tidak ditemukan!";
                gotoxy(39,4);cout << "input lagi? N/(Y) "; cin >> pilih;
            } else{
                gotoxy(28,i);cout << info(Q).nama;
                gotoxy(46,i);cout << info(Q).harga;
                bool next;
                do {
                    next = true;
                    gotoxy(56,i);cout << "      ";
                    gotoxy(56,i);cin >> z.jumlah;
                    if (z.jumlah > info(Q).stok){
                        next = false;
                        gotoxy(12,4);cout << "Jumlah stok tidak mencukupi!";
                    }
                } while(not(next));
                if (z.jumlah>0){
                    info(Q).stok = info(Q).stok-z.jumlah;
                    gotoxy(12,4);cout << "                            ";
                    z.total_awal = z.jumlah*info(Q).harga;
                    gotoxy(65,i);cout << z.total_awal;

                    sum = sum+z.total_awal;
                    No_BRG++;
                    insertBRG(listBarang(last(L)),z,Q);
                    i++;

                }
                gotoxy(39,4);cout << "input lagi? N/(Y) "; cin >> pilih;
            }
            //z.no = No_BRG;
        } while((pilih !='N'));
    gotoxy(1,i); cout << "-----------------------------------------------------------------------------";
    gotoxy(1,i+1);cout << "                                              | Total Akhir : " << sum << " |";
    info(last(L)).total_akhir = sum;
    if (first(listBarang(last(L)))==NULL){
        deleteLastTransaksi(L);
        No_TRX--;
    }
}

void createTransaksi(listTRX &L){
    /*
    ** F.S. : set first(L)=NULL dan last(L)=NULL
    */
    first(L) = NULL;
    last(L) = NULL;
}
addressTRX alokasiTRX(infotypeTRX x){
    /*
    ** F.S. : - mendefinisika elemen baru
    **        - set info(P) = x, next(P) = NULL, dan createBarang(listBarang(P))
    **        - Mengembaliakn nilai P
    */
    addressTRX P = new elmTRX;
    next(P) = NULL;
    info(P).no_transaksi = x.no_transaksi;
    createBarang(listBarang(P));
    return P;
}

void insertTRX(listTRX &L, infotypeTRX x){
    /*
    ** F.S. : memasukan P kedalam list sebagai elemen terakhir
    */
    addressTRX P = alokasiTRX(x);
    if (first(L)==NULL){
        first(L) = P;
        last(L) = P;
    } else{
        next(last(L)) = P;
        last(L) = P;
    }
}

void printTRX(listTRX L){
    /*
    ** F.S. : menampilkan isi dari list transaksi dan list barang dari setiap transaksi
    */
    addressTRX P = first(L);
    int transaksi = 0, barang =0;
    clrscr();
    gotoxy(1,1);cout << "-----------------------------------------------------------------";
    gotoxy(1,2);cout << "| No Transaksi | Kode Obat | Nama Barang | Jumlah | Total Akhir |";
    gotoxy(1,3);cout << "+---------------------------------------------------------------+";
    if (P!=NULL){
        int i = 4;
        do{
            transaksi++;
            gotoxy(3,i);cout << info(P).no_transaksi;
            gotoxy(53,i);cout << info(P).total_akhir;
            printBRG(listBarang(P),i,barang);
            gotoxy(1,i);cout << "+---------------------------------------------------------------+";
            P = next(P);
            i++;
        } while (P!=NULL);

        gotoxy(39,i+1);cout << "Banyak Barang terjual : " << barang;
        gotoxy(39,i+2);cout << "Banyak Transaksi      : " << transaksi;
    } else{
            gotoxy(1,5);cout << "Belum ada data yang dimasukkan";
    }

}

void deleteTransaksi(listTRX &L, addressTRX P){
    /*
    ** I.S. : List dan P mungkin kosong
    ** F.S. : - menghapus semua isi dari list barang
    **        - menghapus elemen transaksi
    **        - procedure dapat menentukan kapan harus deletefirst, deletelast, atau deleteafter
    */
    if ((first(L)!=NULL) && (P!=NULL)){
        addressBRG B = first(listBarang(P));
        if (B!=NULL){
            do{
                B = next(B);
                deleteFirstBarang(listBarang(P));
            } while (B!=NULL);
        }

        if (P==first(L)){
            deleteFirstTransaksi(L);
        } else if (P==last(L)){
            deleteLastTransaksi(L);
        } else{
            deleteAfterTransaksi(L,P);
        }
        cout << "Data Berhasil dihapus";
    } else {
        cout << "Tidak ada data yang dihapus";
    }
    getch();
}
void deleteFirstTransaksi(listTRX &L){
    /*
    ** F.S. : menghapus elemen pertama
    */
    addressTRX P;
    if (next(first(L))!=NULL){
        P = first(L);
        first(L) = next(P);
        next(P) = NULL;
    } else {
        P = first(L);
        first(L) = NULL;
        last(L) = NULL;
    }
    delete P;

}
void deleteAfterTransaksi(listTRX &L,addressTRX P){
    /*
    ** F.S. : menghapus elemen P
    */
    addressTRX Q = first(L);
    while(next(Q)!=P){
        Q = next(Q);
    };
    next(Q) = next(P);
    next(P) = NULL;
}

void deleteLastTransaksi(listTRX &L){
    /*
    ** F.S. : menghapus elemen teralhir dari list
    */
    addressTRX P = first(L);
    addressTRX Q;
    if (P != NULL){
        if (next(P) == NULL) {
            first(L) = NULL;
            last(L) = NULL;
            delete P;
        } else {
            do{
                Q = P;
                P = next(P);
            } while (next(P)!=NULL);
            next(Q) = NULL;
            last(L) = Q;
            delete P;
        }
    }
}

addressTRX findTRX(listTRX L, string x){
    /*
    ** I.S. : list mungkin kosong
    ** F.S. : - menemukan elemen pada list berdasarkan no_transaksi
    **        - mengembalikan nilai P juka ditemukan
    **        - mengembalukan nilai NULL jika tidak ditemukan
    */
    if (first(L)!=NULL){
        addressTRX P = first(L);
        do {
            if (info(P).no_transaksi ==x){
                return P;
            }
            P = next(P);
        } while (P!=NULL);
    }
    return NULL;
}

//====================================================================
void createBarang(listBRG &L){
    /*
    ** F.S. : set first(L)=NULL dan last(L)=NULL
    */
    first(L) = NULL;
    last(L)  = NULL;
}

addressBRG alokasiBRG(infotypeBRG x){
    /*
    ** F.S. : - mendefinisika elemen baru
    **        - mengembalikan nilai P
    */
    addressBRG P = new elmBRG;
    next(P) = NULL;
    prev(P) = NULL;
    info(P).no = x.no;
    info(P).jumlah = x.jumlah;
    info(P).invoice = x.invoice;
    info(P).total_awal = x.total_awal;

    return P;
}

void insertBRG(listBRG &L, infotypeBRG x, address Q){
    /*
    ** F.S. : memasukan P kedalam list sebagai elemen terakhir
    */
    addressBRG P = alokasiBRG(x);
    barang(P) = Q;
    if (first(L)==NULL){
        first(L) = P;
        last(L) = P;
    } else{
        next(last(L)) = P;
        prev(P) = last(L);
        last(L) = P;
    }
}

void printBRG(listBRG L, int &i, int &j){
    /*
    ** I.S. : List mungkin kosong
    ** F.S. : menampilkan semua emelen dari list barang
    */
    addressBRG P = first(L);
    if (P != NULL){
        do{
            j = j + info(P).jumlah;
            gotoxy(1,i);cout << "|";
            gotoxy(16,i);cout << "|";
            gotoxy(28,i);cout << "|";
            gotoxy(42,i);cout << "|";
            gotoxy(51,i);cout << "|";
            gotoxy(65,i);cout << "|";
            gotoxy(18,i);cout << info(barang(P)).kode_obat;
            gotoxy(30,i);cout << info(barang(P)).nama;
            gotoxy(44,i);cout << info(P).jumlah;
            i++;
            P = next(P);
        } while( P != NULL);
    }
}

void deleteFirstBarang(listBRG &L){
    /*
    ** I.S. : List Mungkin Kosong
    ** F.S. : Menghapus elemen pertama pada list
    */
    addressBRG P;
    if (first(L)!=NULL){
        if (next(first(L))==NULL){
            first(L)= NULL;
            last(L) =NULL;
        }else {
            P = first(L);
            first(L) = next(P);
            next(P) = NULL;
            delete P;
        }
    }
}

void deleteAfterBarang(listBRG &L, addressBRG P){
    /*
    ** F.S. : Menghapus elemen P yang berada di tengah list
    */
    addressBRG Q = prev(P);
    next(Q) = next(P);
    prev(next(P)) = Q;
    prev(P) = NULL;
    next(P) = NULL;
}

void deleteLastBarang(listBRG &L){
    /*
    ** I.S. : List Mungkin Kosong
    ** F.S. : Menghapus elemen terakhir pada list
    */
    if (first(L)!=NULL){
        addressBRG P;
        P = last(L);
        last(L) = prev(P);
        next(last(L)) = NULL;
        prev(P) =NULL;
    }
}


addressBRG findBRG(listBRG L, int x){
    /*
    ** I.S. : mendefinisikan elemen B = first(L)
    ** F.S. : - mencari elemen berdasarkan no
    **        - mengembalikan nilai B jka ditemukan
    **        - Mengembaliakn nilai NULL jika tidak ditemukan
    */
    addressBRG B = first(L);
    while ((x!=info(B).no) && (B!=NULL)){
        B = next(B);
    }
    return B;
}

void deleteBarang(listBRG &L, addressBRG P){
    /*
    ** I.S. : List dan P mungkin kosong
    ** F.S. : - menghapus elemen barang
    **        - procedure dapat menentukan kapan harus deletefirst, deletelast, atau deleteafter
    */
    if ((first(L)!=NULL) && (P!=NULL)){
        if (P==first(L)){
            deleteFirstBarang(L);
        } else if (P==last(L)){
            deleteLastBarang(L);
        } else{
            deleteAfterBarang(L,P);
        }
        cout << "Data Berhasil dihapus";
    } else {
        cout << "Tidak ada data yang dihapus";
    }
    getch();
    //printBRG(L);
}
