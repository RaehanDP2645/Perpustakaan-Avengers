#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <windows.h>
using namespace std;

//Hiasan
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Struct buku
struct Buku {
    string judul;
    string isbn;
    string pengarang;
    string penerbit;
    string tahunTerbit;
    string genre;
    string jumhal;
    bool tersedia;
};

// Struct peminjaman
struct Peminjaman {
    string namaPeminjam;
    string bukuDipinjam;
    string isbnBuku;
    string tglPinjam;
    int durasiPinjam; // Durasi pinjam per hari
};

// Array data buku dan peminjaman
Buku daftarBuku[100]; //maksimal kapasitas perpus
int jumlahBuku = 0;
Peminjaman listPinjaman[100]; //maks kapasitas peminjaman
int jumlahPinjaman = 0;

//====== 1. TAMBAH BUKU ======///
void tambahBuku() {
	char yn;
    do {
    	system("cls");
    	setColor(2); cout << " ======== Tambahkan Buku ========\n\n" << endl;
    	
		setColor(7); cout << "Masukkan Judul Buku		: ";
    	cin.ignore();
    	getline(cin, daftarBuku[jumlahBuku].judul);
    
    	cout << "Masukkan Genre Buku		: ";
    	getline(cin, daftarBuku[jumlahBuku].genre);
    
    	cout << "Masukkan Pengarang Buku		: ";
    	getline(cin, daftarBuku[jumlahBuku].pengarang);
    
    	cout << "Masukkan Penerbit Buku		: ";
    	getline(cin, daftarBuku[jumlahBuku].penerbit);
    
    	cout << "Masukkan Tahun Terbit Buku	: ";
    	getline(cin, daftarBuku[jumlahBuku].tahunTerbit);
    
		cout << "Masukkan Jumlah Halaman Buku	: ";
    	getline(cin, daftarBuku[jumlahBuku].jumhal);
    
    	cout << "Masukkan ISBN Buku		: ";
    	getline(cin, daftarBuku[jumlahBuku].isbn);
    
    
    	daftarBuku[jumlahBuku].tersedia = true;
    	jumlahBuku++;
    	
    	system("cls");
		setColor(10); cout << "Buku berhasil ditambahkan!\n";
		this_thread::sleep_for(chrono::seconds(1));
	
		//penentuan kondisi
		setColor(7); cout << "\nIngin Menambahkan Buku Lain? (Y/N)"; cin >> yn;
	} while (yn == 'y' || yn == 'Y');
	
	setColor(7); cout << "Kembali ke menu utama (Tekan Enter)...\n";
	cin.ignore();
    cin.get();
    system("cls");
}

//===== 2. LIHAT BUKU =====///
void lihatBuku() {
    if (jumlahBuku == 0) {
    	system("cls");
        setColor(12); cout << "Belum ada buku yang tersedia.\n";
        setColor(7); cout << "1. Tambahkan Buku\n2. Kembali ke Menu Utama\nPilihan: ";
        int pilihan;
        cin >> pilihan;
        if (pilihan == 1) {
            tambahBuku();
        }
        return;
    }

	system("cls");
    setColor(10); cout << " ======== Daftar Buku ========\n\n";
    for (int i = 0; i < jumlahBuku; i++) {
        setColor(7); cout << "Judul		: " << daftarBuku[i].judul << endl;
        cout << "Genre		: " << daftarBuku[i].genre << endl;
        cout << "Pengarang	: " << daftarBuku[i].pengarang << endl;
    	cout << "Penerbit	: " << daftarBuku[i].penerbit << endl;
        cout << "Tahun Terbit	: " << daftarBuku[i].tahunTerbit << endl;
        cout << "Jumlah Halaman	: " << daftarBuku[i].jumhal << endl;
        cout << "ISBN		: " << daftarBuku[i].isbn << endl;
		cout << "Tersedia	: " << (daftarBuku[i].tersedia ? "Ya" : "Tidak") << "\n==============================" << endl;
    }
	setColor(6); cout << "\n\nTekan enter untuk kembali ke menu utama...";
	cin.ignore();
	cin.get();
	system("cls");
}

//====== 3. PINJAM BUKU======//
void pinjamBuku() {
    string namaPeminjam, judulBuku, isbnBuku;
    
	cin.ignore();
	system("cls");
	setColor(14); cout << " ======== Pinjam Buku ========\n\n";
	
    setColor(7); cout << "Masukkan nama peminjam: ";
    getline(cin, namaPeminjam);
    
    cout << "Masukkan judul buku yang ingin dipinjam: ";
    getline(cin, judulBuku);

    // Cari buku yang dipinjam
    int indeksBuku = -1;
    for (int p = 0; p < jumlahBuku; p++) {
        if (daftarBuku[p].judul == judulBuku && daftarBuku[p].tersedia) {
            indeksBuku = p;
            break;
        }
    }

    if (indeksBuku == -1) {
        system("cls");
		setColor(12); cout << "Buku tidak tersedia atau tidak ditemukan.\n";
		this_thread::sleep_for(chrono::seconds(2));
        return;
    }

    setColor(7); cout << "Masukkan ISBN buku: ";
    getline(cin, isbnBuku);
    if (isbnBuku != daftarBuku[indeksBuku].isbn) {
    	system("cls");
        setColor(12); cout << "ISBN tidak cocok dengan buku yang dipilih.\n";
        this_thread::sleep_for(chrono::seconds(2));
        return;
    }

    setColor(7); cout << "Masukkan tanggal pinjam (format: dd-mm-yyyy): ";
    string tanggalPinjam;
    getline(cin, tanggalPinjam);
    
    cout << "Masukkan durasi pinjam (dalam hari): ";
    int durasiPinjam;
    cin >> durasiPinjam;

    // Simpan data peminjaman
    listPinjaman[jumlahPinjaman] = {namaPeminjam, judulBuku, isbnBuku, tanggalPinjam, durasiPinjam};
    jumlahPinjaman++;
    daftarBuku[indeksBuku].tersedia = false;

    system("cls");
	setColor(10); cout << "Buku berhasil dipinjam!\n";
	this_thread::sleep_for(chrono::seconds(2));
}

//====== 4. KEMBALIKAN BUKU =====//
void kembalikanBuku() {
    if (jumlahPinjaman == 0) {
    	system("cls");
        setColor(12); cout << "Tidak ada buku yang sedang dipinjam.\n";
        this_thread::sleep_for(chrono::seconds(2));
        return;
    }

    string namaPeminjam, judulBuku, isbnBuku;
    cin.ignore();
    system("cls");
    setColor(5); cout << " ======== Kembalikan Buku ========\n\n";
    
	setColor(7); cout << "Masukkan nama peminjam: ";
    getline(cin, namaPeminjam);
    
	cout << "Masukkan judul buku: ";
    getline(cin, judulBuku);
    
	cout << "Masukkan ISBN buku: ";
    getline(cin, isbnBuku);

    // Cari data peminjaman
    int indeksPeminjaman = -1;
    for (int i = 0; i < jumlahPinjaman; i++) {
        if (listPinjaman[i].namaPeminjam == namaPeminjam &&
            listPinjaman[i].bukuDipinjam == judulBuku &&
            listPinjaman[i].isbnBuku == isbnBuku) {
            indeksPeminjaman = i;
            break;
        }
    }

    if (indeksPeminjaman == -1) {
    	system("cls");
        setColor(12); cout << "Data peminjaman tidak ditemukan.\n";
        this_thread::sleep_for(chrono::seconds(2));
        return;
    }

    setColor(7); cout << "Masukkan jumlah hari buku dipinjam: ";
    int hariDipinjam;
    cin >> hariDipinjam;
	
	//Perhitungan denda
    int durasiPinjam = listPinjaman[indeksPeminjaman].durasiPinjam;
    if (hariDipinjam > durasiPinjam) {
        int telat = hariDipinjam - durasiPinjam;
        int denda = telat * 5000; // Denda Rp5000 per hari
        system("cls");
        setColor(12); cout << "Anda terlambat mengembalikan buku selama " << telat << " hari. Denda: Rp" << denda << ".\n";
        cout << "Silahkan bayar denda ke Resepsionis sebesar: Rp" << denda << "\n";
        cin.ignore();
        cin.get();
    } else {
    	system("cls");
        setColor(10); cout << "Buku dikembalikan tepat waktu. Tidak ada denda.\n";
        this_thread::sleep_for(chrono::seconds(2));
    }

    // Mengatur status buku menjadi tersedia kembali
    for (int i = 0; i < jumlahBuku; i++) {
        if (daftarBuku[i].judul == judulBuku && daftarBuku[i].isbn == isbnBuku) {
            daftarBuku[i].tersedia = true;
            break;
        }
    }

    // Hapus data peminjaman
    for (int i = indeksPeminjaman; i < jumlahPinjaman - 1; i++) {
        listPinjaman[i] = listPinjaman[i + 1];
    }
    jumlahPinjaman--;

    system("cls");
	setColor(10); cout << "Pengembalian buku berhasil dicatat.\n";
	this_thread::sleep_for(chrono::seconds(3));
}

//====== 5. CARI BUKU ======//
void cariBuku() {
    string kataKunci;
    int pilihan;

	system("cls");
	setColor(3); cout << " ======== Cari Buku ========\n\n";
    setColor(7); cout << "Pilih kriteria pencarian:\n";
    cout << "1. Judul\n";
    cout << "2. ISBN\n";
    cout << "3. Pengarang\n";
    cout << "Pilihan: ";
    cin >> pilihan;

    cin.ignore();
    system("cls");
    setColor(7); cout << "Masukkan kata kunci: ";
    getline(cin, kataKunci);
	
	system("cls");
    setColor(10); cout << "\n=== Hasil Pencarian ===\n";
    bool ditemukan = false;
    for (int i = 0; i < jumlahBuku; i++) {
        if ((pilihan == 1 && daftarBuku[i].judul.find(kataKunci) != string::npos) ||
            (pilihan == 2 && daftarBuku[i].isbn.find(kataKunci) != string::npos) ||
            (pilihan == 3 && daftarBuku[i].pengarang.find(kataKunci) != string::npos)) {
            setColor(7); cout << "\nJudul		: " << daftarBuku[i].judul << endl;
        	cout << "Genre		: " << daftarBuku[i].genre << endl;
        	cout << "Pengarang	: " << daftarBuku[i].pengarang << endl;
    		cout << "Penerbit	: " << daftarBuku[i].penerbit << endl;
        	cout << "Tahun Terbit	: " << daftarBuku[i].tahunTerbit << endl;
        	cout << "Jumlah Halaman	: " << daftarBuku[i].jumhal << endl;
        	cout << "ISBN		: " << daftarBuku[i].isbn << endl;
			cout << "Tersedia	: " << (daftarBuku[i].tersedia ? "Ya" : "Tidak") << "\n==============================" << endl;
            
            setColor(6); cout << "\nTekan enter untuk kembali...";
            cin.get();
            ditemukan = true;
        }
    }

    if (!ditemukan) {
    	system("cls");
        setColor(12); cout << "Buku tidak ditemukan.\n";
        this_thread::sleep_for(chrono::seconds(2));
    }
};

//====== MENU UTAMA ======/
void menuUtama() {
    int pilihan;

    do {
    	system("cls");
        setColor(1); cout << "\n=== Perpustakaan Avengers ===\n \n";
        setColor(2); cout << "1. Tambahkan Buku\n";
        setColor(4); cout << "2. Lihat Buku\n";
        setColor(6); cout << "3. Pinjam Buku\n";
        setColor(5); cout << "4. Kembalikan Buku\n";
        setColor(3); cout << "5. Cari Buku\n";
        setColor(7); cout << "6. Keluar\n \n";
        setColor(13);cout << "Pilihan: ";
        setColor(96); cin >> pilihan; setColor(7);

        switch (pilihan) {
            case 1:
                tambahBuku();
                break;
            case 2:
				lihatBuku();
                break;
            case 3:
                pinjamBuku();
                break;
            case 4:
                kembalikanBuku();
                break;
            case 5:
            	cariBuku();
            	break;
            case 6:
            	system("cls");
                setColor(4); cout << "Thanks "; 
				setColor(10); cout << "for "; 
				setColor(9); cout << "All!\n";
                this_thread::sleep_for(chrono::seconds(3));
                setColor(7);
                break;
            default:
            	system("cls");
                setColor(4); cout << "invalid. Coba lagi.\n"; setColor(7);
                this_thread::sleep_for(chrono::seconds(3));
        }
    } while (pilihan != 6);
}

int main() {
    menuUtama();
    return 0;
}

