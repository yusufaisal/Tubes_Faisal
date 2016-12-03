#include "obat.h"

//=========================================================================
void clrscr()
{
   system("cls");
}

void gotoxy(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//=========================================================================

void inputObat(listObat &L){
    clrscr();
    address P = NULL;
    infotype x;
    gotoxy(8,1);cout << "===INPUT===";
    gotoxy(30,3);cout << "+-------------------+";
    gotoxy(30,4);cout << "|     Keterangan    |";
    gotoxy(30,5);cout << "+-------------------+";
    gotoxy(30,6);cout << "|                   |";
    gotoxy(30,7);cout << "+-------------------+";
    gotoxy(2,2);cout << "Kode Obat : ";
    gotoxy(2,4);cout << "Nama Obat : ";
    gotoxy(2,5);cout << "Jenis     : ";
    gotoxy(2,6);cout << "Kategori  : ";
    gotoxy(2,7);cout << "Harga     : ";
    gotoxy(2,8);cout << "Stok      : ";
    gotoxy(14,2); cin >> x.kode_obat;
    P = findObat(L,x.kode_obat);
    if  (P==NULL){
        gotoxy(14,4); cin >> x.nama;
        gotoxy(14,5); cin >> x.jenis;
        gotoxy(14,6); cin >> x.kategori;
        gotoxy(14,7); cin >> x.harga;
        gotoxy(14,8); cin >> x.stok;
        insertObat(L,x);
        gotoxy(31,6);cout << "Berhasil dimasukkan";
    } else {
        gotoxy(33,6);cout << "Kode sudah ada";
        gotoxy(14,4); cout << info(P).nama;
        gotoxy(14,5); cout << info(P).jenis;
        gotoxy(14,6); cout << info(P).kategori;
        gotoxy(14,7); cout << info(P).harga;
        gotoxy(14,8); cout << info(P).stok;
    }
}

void Search_View(listObat L, address &P){
    int kode;
    gotoxy(30,3);cout << "+-------------------+";
    gotoxy(30,4);cout << "|     Keterangan    |";
    gotoxy(30,5);cout << "+-------------------+";
    gotoxy(30,6);cout << "|                   |";
    gotoxy(30,7);cout << "+-------------------+";
    gotoxy(2,2);cout << "Kode Obat : ";
    gotoxy(2,4);cout << "Nama Obat : ";
    gotoxy(2,5);cout << "Jenis     : ";
    gotoxy(2,6);cout << "Kategori  : ";
    gotoxy(2,7);cout << "Harga     : ";
    gotoxy(2,8);cout << "Stok      : ";

    gotoxy(14,2);cin >> kode;
    P = findObat(L,kode);
    if (P==NULL){
        gotoxy(32,6);cout << "Tidak Ditemukan";
    } else{
        gotoxy(36,6);cout << "Ditemukan";
        gotoxy(14,4); cout << info(P).nama;
        gotoxy(14,5); cout << info(P).jenis;
        gotoxy(14,6); cout << info(P).kategori;
        gotoxy(14,7); cout << info(P).harga;
        gotoxy(14,8); cout << info(P).stok;
    }
}


void createListObat(listObat &L){
    /*
    ** F.S. : set first(L)=NULL dan last(L)=NULL
    */
    first(L) = NULL;
    last(L) = NULL;
}

void insertFirst(listObat &L, address P){
    /*
    ** I.S. : List kemingkinan kosong
    ** F.S. : memasukan P kedalam list sebagai elemen pertama
    */
    if (first(L)==NULL) {
        first(L) = P;
        last(L) = P;
    } else{
        next(P) = first(L);
        prev(first(L)) = P;
        first(L) = P;
    }
}

void insertLast(listObat &L, address P){
    /*
    ** F.S. : memasukan P kedalam list sebagai elemen terakhir
    */
    next(last(L)) = P;
    prev(P) = last(L);
    last(L) = P;
}

void insertAfter(listObat &L, address Q,address P){
    /*
    ** F.S. : - memasukan P kedalam list setelah elemen Q
    **        - jika info(P) lebih besar info(next(Q), maka panggil procedure insertAfter(L,next(Q),P)
    */
    if (info(P).kode_obat > info(next(Q)).kode_obat){
        insertAfter(L,next(Q),P);
    } else {
        next(P) = next(Q);
        prev(P) = Q;
        prev(next(Q)) = P;
        next(Q) = P;
    }
}

void insertObat(listObat &L, infotype x){
    /*
    ** I.S. : List dan P mungkin kosong
    ** F.S. : - menghapus elemen barang
    **        - procedure dapat menentukan kapan harus deletefirst, deletelast, atau deleteafter
    */
    address P = alokasi(x);
    if ((first(L)==NULL) or (x.kode_obat < info(first(L)).kode_obat)){
        insertFirst(L,P);
    } else if (x.kode_obat > info(last(L)).kode_obat){
        insertLast(L,P);
    } else {
        insertAfter(L,first(L),P);
    }
}

address deleteLast(listObat &L){
    /*
    ** F.S. : Menghapus elemen terakhir pada list
    */
    address P;

    P = last(L);
    last(L) = prev(P);
    prev(P) =NULL;
    next(last(L)) = NULL;

    return P;
}
address deleteFirst(listObat &L){
    /*
    ** I.S. : List Mungkin Kosong
    ** F.S. : Menghapus elemen pertama pada list
    */
    address P;
    if (next(first(L))==NULL){
        P = first(L);
        first(L) = NULL;
        last(L) = NULL;
    } else {
        P = first(L);
        first(L) = next(first(L));
        prev(first(L)) = NULL;
        next(P) = NULL;
    }
    return P;
}

address deleteAfter(listObat &L, address P){
    /*
    ** F.S. : Menghapus elemen P yang berada di tengah list
    */
    address Q = prev(P);
    next(Q) = next(P);
    prev(next(P)) = Q;
    next(P) = NULL;
    prev(P) = NULL;
    return P;

}

void deleteObat(listObat &L, address P){
    /*
    ** I.S. : List dan P mungkin kosong
    ** F.S. : - menghapus elemen barang
    **        - procedure dapat menentukan kapan harus deletefirst, deletelast, atau deleteafter
    */
    address Q;
    if (first(L)!=NULL){
        if (P==first(L)){
            Q = deleteFirst(L);
        } else if (P==last(L)){
            Q = deleteLast(L);
        } else {
            Q = deleteAfter(L,P);
        }
    }
}

address alokasi(infotype x){
    /*
    ** F.S. : - mendefinisika elemen baru
    **        - mengembalikan nilai P
    */
    address P = new elmObat;
    next(P) = NULL;
    prev(P) = NULL;

    info(P).kode_obat = x.kode_obat;
    info(P).nama = x.nama;
    info(P).jenis = x.jenis;
    info(P).kategori = x.kategori;
    info(P).stok = x.stok;
    info(P).harga = x.harga;

    return P;
}

address findObat(listObat L, int x){
    /*
    ** I.S. : mendefinisikan elemen P= first(L)
    ** F.S. : - mencari elemen berdasarkan Kode_Obat
    **        - mengembalikan nilai P jka ditemukan
    **        - Mengembaliakn nilai NULL jika tidak ditemukan
    */
    address P = first(L);
    if (P != NULL){
        while ((P != NULL) and (x != info(P).kode_obat)){
            P = next(P);
        };
    };
    return P;
}

void printObat(listObat L){
    /*
    ** I.S. : List mungkin kosong
    ** F.S. : menampilkan semua emelen dari list Obat
    */
    clrscr();
    if (first(L)!=NULL){
        address P = first(L);
        int i =3;
        gotoxy(1,0);cout << "---------------------------------------------------------------------------";
        gotoxy(1,1);cout << "| Kode   | Nama Obat      |  Jenis   |  Kategori  | Stok |     Harga      |";
        gotoxy(1,2);cout << "+--------+----------------+----------+------------+------+----------------+";
        do {
            gotoxy(1,i);cout << "|        |                |          |            |      |                |";
            gotoxy(3,i);cout << info(P).kode_obat;
            gotoxy(12,i);cout << info(P).nama;
            gotoxy(29,i);cout << info(P).jenis;
            gotoxy(40,i);cout << info(P).kategori;
            gotoxy(53,i);cout << info(P).stok;
            gotoxy(60,i);cout << info(P).harga;
            P = next(P);
            i++;
        } while (P!=NULL);
        gotoxy(1,i);cout << "---------------------------------------------------------------------------";

    }

}

