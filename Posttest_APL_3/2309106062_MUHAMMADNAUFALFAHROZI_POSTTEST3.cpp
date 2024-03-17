#include <iostream>
#include <string>

using namespace std;

// Deklarasi Prototipe Fungsi
bool login();
void tampilkanMenu(int jml, string series[]);
void tampilkanSeries(int jml, string series[], int idx = 0);
void tambahSeries(int &jml, string series[]);
void ubahSeries(int jml, string series[]);
void hapusSeries(int &jml, string series[]);

// Fungsi login
bool login() {
    string nama, nim;
    for(int i = 0; i < 3; i++) {
        cout << "Masukkan Nama  : ";
        getline(cin, nama);
        cout << "Masukkan NIM   : ";
        cin >> nim;
        cin.ignore();
        if(nama == "Muhammad Naufal Fahrozi" && nim == "2309106062") {
            return true;
        } else {
            cout << "Nama atau NIM salah. Silahkan coba lagi.\n";
        }
    }
    return false;
}

// Prosedur untuk menampilkan menu
void tampilkanMenu(int jml, string series[]) {
    cout << " \n";
    cout << "Daftar TV Series Terfavorit:\n";
    cout << " \n";
    cout << "[1] Lihat Series\n";
    cout << "[2] Tambah Series\n";
    cout << "[3] Ubah Judul Series\n";
    cout << "[4] Hapus Series\n";
    cout << "[0] Keluar\n";
    cout << "Pilih menu: ";
}

// Fungsi rekursif untuk menampilkan peringkat dan judul TV series
void tampilkanSeries(int jml, string series[], int idx) {
    if (idx < jml) {
        cout << "Peringkat ke-" << idx + 1 << ": " << series[idx] << endl;
        cout << "--------------------------------------------------\n";
        tampilkanSeries(jml, series, idx + 1);
    }
}

// Prosedur untuk menambah judul TV series
void tambahSeries(int &jml, string series[]) {
    if (jml < 10) {
        cout << "Tambah Series\n";
        cout << "Masukkan Judul Series: ";
        cin.ignore(); 
        getline(cin, series[jml]);
        jml++;
        cout << "Judul Series berhasil ditambahkan\n";
    } else {
        cout << "Daftar series maksimal 10 peringkat!\n";
    }
}

// Prosedur untuk mengubah judul TV series
void ubahSeries(int jml, string series[]) {
    int idx;
    cout << "Ubah Judul Series\n";
    cout << "Masukkan peringkat Series: ";
    cin >> idx;
    if (idx >= 1 && idx <= jml) {
        cout << "Masukkan Judul Series: ";
        cin.ignore();
        getline(cin, series[idx - 1]);
        cout << "Judul Series berhasil diubah\n";
    } else {
        cout << "Peringkat tidak valid.\n";
    }
}

// Prosedur untuk menghapus judul TV series
void hapusSeries(int &jml, string series[]) {
    int idx;
    cout << "Hapus Judul Series\n";
    cout << "Masukkan peringkat Series yang ingin dihapus: ";
    cin >> idx;
    if (idx >= 1 && idx <= jml) {
        for (int i = idx - 1; i < jml - 1; i++) {
            series[i] = series[i + 1];
        }
        jml--;
        cout << "Judul Series berhasil dihapus\n";
    } else {
        cout << "Peringkat tidak valid.\n";
    }
}

// Fungsi main
int main() {
    if(!login()) {
        cout << "Upaya masuk terlalu sering. Silakan coba lagi nanti!.\n";
        return 0;
    }

    int jml = 5, menu;
    string series[10] = {"Breaking Bad", "The Sopranos", "Game of Thrones", "Better Call Saul", "Band of Brothers"};
    string ulang = "y";

    while (ulang == "y") {
        tampilkanMenu(jml, series);
        cin >> menu;
        switch (menu) {
            case 1:
                tampilkanSeries(jml, series);
                break;
            case 2:
                tambahSeries(jml, series);
                break;
            case 3:
                ubahSeries(jml, series);
                break;
            case 4:
                hapusSeries(jml, series);
                break;
            case 0:
                cout << "May thy knife chip and shatter!";
                return 0;
            default:
                cout << "Menu tidak ada\n";
                break;
        }
    }
    return 0;
}