#include <iostream>
#include <stdlib.h>
#include <time.h>
#define max 10
#include <windows.h>
using namespace std;

typedef char infotype;
typedef struct TElmtList *address;
typedef struct TElmtList{
 infotype info;
 address next;

 address prev;
} ElmtList;

typedef struct {
 address first;
 address last;
}List ;

 //SELEKTOR
#define Info(P) (P)->info
#define Next(P) (P)->next
#define Prev(P) (P)->prev
#define First(L) ((L).first)
#define Last(L) ((L).last)

//KONSTANTA
#define Nil NULL
#define Infinity 99999


/****************** TEST LIST KOSONG ******************/
bool IsEmpty(List L) {
/* Mengirim true jika list kosong. Lihat definisi di atas. */
 return (First(L) == NULL && Last(L) == NULL);
}


/****************** PEMBUATAN LIST KOSONG ******************/
void createList(List *L) {
 First(*L) = NULL;
 Last(*L) = NULL;
}

/****************** Manajemen Memori ******************/
address Allocation(infotype x) {
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil. */
/* Misalnya: menghasilkan P, maka Info(P)=X, Next(P)=Nil, Prev(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil. */
 address NewElmt;
 NewElmt = (ElmtList*) malloc (sizeof(ElmtList));
 Info(NewElmt) = x;
 Next(NewElmt) = Nil;
 Prev(NewElmt) = Nil;
 return NewElmt;
}

void Deallocation(address hapus) {
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
 free(hapus);
}


/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
address Search (List L, infotype X){
/* Mencari apakah ada elemen list dengan Info(P)=X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
	address P = First(L);
	while (P != Nil){
		if (Info(P) == X){
			return P;
		}
		P = Next(P);
	}
	return Nil;
}


/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsertFirst(List *L, infotype x) {
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
 address NewElmt;
 NewElmt = Allocation(x);
 if (NewElmt != NULL) {
 if(IsEmpty(*L)){
 First(*L) = NewElmt;
 Last(*L) = NewElmt;
 } else{
 Next(NewElmt) = First(*L);
 Prev(First(*L)) = NewElmt;
 First(*L) = NewElmt;
 }
 }
}

void InsertLast(List *L, infotype x) {
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
 address NewElmt;
 NewElmt = Allocation(x);
 if (NewElmt != NULL) {
 if(IsEmpty(*L)){
 InsertFirst(L,x);
 } else{
 Next(Last(*L)) = NewElmt;
 Prev(NewElmt) = Last(*L);
 Last(*L) = NewElmt;
 }
 }
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst (List *L, address P){
/* I.S. Sembarang, P sudah dialokasi */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
	if(IsEmpty(*L)){
 First(*L) = P;
 Last(*L) = P;
 } else{
 Next(P) = First(*L);
 Prev(First(*L)) = P;
 First(*L) = P;
 }
}

void InsertLast (List *L, address P){
/* I.S. Sembarang, P sudah dialokasi */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
	if(IsEmpty(*L)){
 InsertFirst(L,P);
 } else{
 Next(Last(*L)) = P;
 Prev(P) = Last(*L);
 Last(*L) = P;
 }
}

void InsertAfter (List *L, address P, address Prec){
/* I.S. Prec pastilah elemen list; P sudah dialokasi */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
	if(Next(Prec) == Nil){
	InsertLast(L,P);
	}else{
	Next(P) = Next(Prec);
	Prev(P) = Prec;
	Prev(Next(Prec))= P;
	Next(Prec) = P;
	}
}

void InsertBefore (List *L, address P, address Succ){
/* I.S. Succ pastilah elemen list; P sudah dialokasi */
/* F.S. Insert P sebagai elemen sebelum elemen beralamat Succ */
	if(Succ == First(*L)){
	InsertFirst(L,P);
	}else{
	Next(Prev(Succ)) = P;
	Prev(P) = Prev(Succ);
	Next(P) = Succ;
	Prev(Succ) = P;
	}
}


/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintForward (List L){
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, isi list dicetak dari elemen pertama */
/* ke elemen terakhir secara horizontal ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
	cout<<"[";
	if(!IsEmpty(L)){
	address temp =First(L);
	while(Next(temp)!=NULL){
	if(Info(temp) == 0){
		cout<<"_"<<" ";
	}
	else{
		cout<<Info(temp)<<" ";
	}
	temp=Next(temp);
	}
	if(Info(temp) == 0){
		cout<<"_"<<" ";
	}
	else{
		cout<<Info(temp);
	}
}
	cout<<"]"<<endl;
}

void konvert(int random, List *L){
	if(random == 1){
		InsertLast(L, '1');
	} else if(random == 2){
		InsertLast(L, '2');
	} else if(random == 3){
		InsertLast(L, '3');
	} else if(random == 4){
		InsertLast(L, '4');
	} else if(random == 5){
		InsertLast(L, '5');
	} else if(random == 6){
		InsertLast(L, '6');
	} else if(random == 7){
		InsertLast(L, '7');
	} else if(random == 8){
		InsertLast(L, '8');
	} else if(random == 9){
		InsertLast(L, '9');
	} else if(random == 0){
		InsertLast(L, '0');
	}
}

void random_angka (List *L){
	int random,k=0;
	srand(time(0));
	for(int i=0;i<10;i++){
		random=rand()%9;
		if(k<5){
			InsertLast(L, '_');
			k++;
		}else{
			konvert(random, L);
		}
	}
}
void random_angka2 (List *L){
	int random,k=0;
	//srand(time(0));
	for(int i=0;i<10;i++){
		random=rand()%9;
		if(k<5){
			InsertLast(L, '_');
			k++;
		}else{
			konvert(random, L);
		}
	}
}

address mencari (List L, infotype x,infotype y){
	address P=First(L);

	while (P!=NULL){
		if(Prev(P)!=NULL&&Next(P)!=NULL&&Info(Next(P))==y&&Info(Prev(P))==x){
		if(Info(P)=='_'){
			cout<<Info(P)<<endl;
			return P;
		}
	}
		P=Next(P);
	}
	return NULL;
}

bool cekawal(List L,address temp){
	return (Info(temp) == Info(Next(First(L))) && Info(temp) == Info(Next(Next(First(L)))));
}
bool cekakhir(List L,address temp){
	return (Info(temp) == Info(Prev(First(L))) && Info(temp) == Info(Prev(Prev(First(L)))));
}
bool cekPrev(List L,address temp){
	address Prec = Prev(temp);
	bool status = true;
	if(temp!=Nil)
	{
		if(Prec!=Nil)
		{
			if(Prev(Prec)!=Nil)
			{
				if((Info(temp) == Info(Prec))&&(Info(temp) == Info(Prev(Prec))))
				{
					status = true;
				}
				else
				{
					status = false;
				}
			}
			else
			{
				status = false;
			}
		}
		else{
			status = false;
		}
	}
	else
	{
		status = false;
	}
	return (status);
}
bool cekNext(List L,address temp){
	address Succ = Next(temp);
	bool status = true;
	if(temp!=Nil)
	{
		if(Succ!=Nil)
		{
			if(Next(Succ)!=Nil)
			{
				if((Info(temp) == Info(Succ))&&(Info(temp) == Info(Next(Succ))))
				{
					status = true;
				}
				else
				{
					status = false;
				}
			}
			else
			{
				status = false;
			}
		}
		else{
			status = false;
		}
	}
	else
	{
		status = false;
	}
	return (status);
}
bool cekBetween(List L,address temp){
	address Prec = Prev(temp);
	address Succ = Next(temp);
	bool status = true;
	if(temp!=Nil)
	{
		if(Prec!=Nil && Succ!=Nil)
		{
		
			if(Info(temp) == Info(Prec) && Info(temp) == Info(Succ))
			{
				status = true;
			}
			else
			{
				status = false;
			}
		}
		else{
			status = false;
		}
			

	}
	else
	{
		status = false;
	}
	return (status);
}

bool cekList(List L,address temp){
	if(cekPrev(L,temp) || cekNext(L,temp)){
		return true;
	}
	else{
		if(cekBetween(L,temp)){
			return true;
		}
		else{
			return false;
		}
	}
}


void menu(List *L, List *Q){
	Menu:
		cout<<endl;
		int menu1,n,keluar,ksmptn;
	cout<<"==================================================================================================="<<endl;
	cout<<" Ketentuan Cara Bermain GAME ZUMA "<<endl;
	cout<<" 1.Permainan ini harus Pilih soal terlebih dahulu"<<endl;
	cout<<" 2.Sebelum bermain,tentukan banyak percobaan"<<endl;
	cout<<" 3.Setelah melakukan step by step diatas, maka anda bisa bermain game zuma "<<endl;
	cout<<"==================================================================================================="<<endl;
	cout<<endl;
	cout<<endl;
	cout<<" Selamat Datang di Game ZUMA"<<endl;
	cout<<" 1. Pilih Soal"<<endl;
	cout<<" 2. Pilih Banyak Percobaan"<<endl;
	cout<<" 3. Mulai Permainan"<<endl;
	cout<<" 4. Keluar"<<endl;
	cout<<" Pilih Menu : ";cin>>menu1;

	switch(menu1){
		case 1 :
			random_angka(L);
			random_angka2(Q);
			cout<<" 1. "; PrintForward(*L);
			cout<<endl;
			cout<<" 2. "; PrintForward(*Q);
			cout<<" Pilih Soal : ";
			cin>>n;

			if(n==2){
				*L=*Q;
			}

			goto Menu;
			break;

		case 2 :
			cout<<" Banyak Percobaan :  ";cin>>ksmptn;
			goto Menu;
			break;
		case 3 :
			break;

		case 4 :
			cout<<endl;
			cout<<" KELUAR DARI PERMAINAN ? "<<endl;
			cout<<endl;
			cout<<" 1. Keluar "<<endl;
			cout<<" 2. Tidak "<<endl;
			cout<<endl;
			cout<<" keluar/tidak ? ";cin>>keluar;
			if(keluar == 1){
				cout<<endl;
				cout<<" ANDA MENINGGALKAN PERMAINAN ";
				exit (0);
			}
			if(keluar == 2){
				goto Menu;
			}
			break;

	}

	while (ksmptn>0){
	char pilih;
	infotype tebak,tebakangka1,tebakangka2;
	address temp;
	PrintForward(*L);

	cout<<" Kesempatan anda bermain = "<<ksmptn<<endl;;
	cout<<" Masukan Angka tebakan anda : ";
	cin>>tebak;
	cout<<" Posisi Angka Tebakan Anda : "<<endl;
	cout<<" a. Sebelum "<<endl;
	cout<<" b. Setelah "<<endl;
	cout<<" c. Awal"<<endl;
	cout<<" d. Akhir"<<endl;
	cout<<" Masukkan Posisi : ";cin>>pilih;

	switch (pilih){
		case 'a':
			cout<<" sebelum Angka : ";
			cin>>tebakangka1;
			cout<<" Setelah Angka : ";
			cin>>tebakangka2;
			temp=mencari (*L,tebakangka2,tebakangka1);
			if(temp!=NULL){
				Info(temp)=tebak;
			}

			PrintForward(*L);

			if(temp!=NULL&&(cekPrev(*L,temp) || cekBetween(*L,temp) || cekNext(*L,temp))){

			cout<<"==========================================================================="<<endl;
			cout<<"==                        SELAMAT ANDA BERUNTUNG                         =="<<endl;
			cout<<"==========================================================================="<<endl;
			cout<<endl;
			exit(0);
			break;
	}
		break;
		case 'b':
			cout<<" Setelah Angka : ";
			cin>>tebakangka2;
			cout<<" Sebelum Angka : ";
			cin>>tebakangka1;
			temp=mencari (*L,tebakangka2,tebakangka1);
			if(temp!=NULL){
				Info(temp)=tebak;
			}

			PrintForward(*L);

			if(temp!=NULL&&(cekPrev(*L,temp) || cekBetween(*L,temp) || cekNext(*L,temp))){

			cout<<"==========================================================================="<<endl;
			cout<<"==                        SELAMAT ANDA BERUNTUNG                         =="<<endl;
			cout<<"==========================================================================="<<endl;
			cout<<endl;
			exit(0);
			break;
	}
		break;
		case 'c':
			Info(First(*L))=tebak;
			temp=First(*L);

			PrintForward(*L);

			if(temp!=NULL&&cekawal(*L,temp)){

			cout<<"==========================================================================="<<endl;
			cout<<"==                        SELAMAT ANDA BERUNTUNG                         =="<<endl;
			cout<<"==========================================================================="<<endl;
			cout<<endl;
			exit(0);
			break;
	}
		break;
		case 'd':
			Info(Last(*L))=tebak;
			temp=Last(*L);

			PrintForward(*L);

			if(temp!=NULL&&cekakhir(*L,temp)){

			cout<<"==========================================================================="<<endl;
			cout<<"==                        SELAMAT ANDA BERUNTUNG                         =="<<endl;
			cout<<"==========================================================================="<<endl;
			cout<<endl;
			exit(0);
			break;
	}
			break;
	}

	ksmptn--;
}
	if(ksmptn<1){
		PrintForward(*L);
		cout<<endl;
		cout<<endl;

		cout<<"==========================================================================="<<endl;
		cout<<"==                         ANDA KURANG BERUNTUNG                         == "<<endl;
		cout<<"==========================================================================="<<endl;


	}


}
int main(){
	List L, Q;
	createList(&L);
	createList(&Q);
	srand(unsigned(time(0)));
	
	cout<<"==================================================================================================="<<endl;
	cout<<"==================================================================================================="<<endl;
	cout<<"====        ===========       ====    ====     ==== ===     === ====        = ==== =           ===="<<endl;
	cout<<"====        ==========        ====    ====     ====   ===  ===  ====     ====      ====        ===="<<endl;
	cout<<"====             ====         ====    ====     ====    ==  ==   ====     ====      ====        ===="<<endl;
	cout<<"====            ====          ====    ====     ====      ==     ====     ==============        ===="<<endl;
	cout<<"====           ==========     ====    ====     ====             ====     ====      ====        ===="<<endl;
	cout<<"====          ===========      ==========      ====             ====     ====      ====        ===="<<endl;
	cout<<"==================================================================================================="<<endl;
	cout<<"==================================================================================================="<<endl;
	cout<<endl;
	

     menu(&L, &Q);




	return 0;
}
