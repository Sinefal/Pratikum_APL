// Muhammad Naufal Fahrozi
// 2309106062

#include <iostream>
#include <string>
using namespace std;

// Struct untuk Review
struct Review {
    int rating;
    string ulasan;
};

// Struct Judul
struct title {
    string judul;
    int tahunRilis;
    Review tambahan;
};

// Deklarasi Prototipe Fungsi
bool login();
void tampilkanMenu(int jml, title series[]);
void tampilkanSeries(int jml, title series[], int idx = 0);
void tambahSeries(int &jml, title series[]);
void ubahSeries(int jml, title series[]);
void hapusSeries(int &jml, title series[]);

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
void tampilkanMenu(int jml, title series[]) {
    cout << "\n";
    cout << "Daftar TV Series Terfavorit:\n";
    cout << "\n";
    cout << "[1] Lihat Series\n";
    cout << "[2] Tambah Series\n";
    cout << "[3] Edit Series\n";
    cout << "[4] Hapus Series\n";
    cout << "[0] Keluar\n";
    cout << "Pilih menu: ";
}

// Fungsi rekursif untuk menampilkan judul TV series dan reviewnya
void tampilkanSeries(int jml, title series[], int idx) {
    if (idx < jml) {
        cout << "" << endl;
        cout << "#" << idx + 1 << endl;
        cout << "Judul  : " << series[idx].judul << " (" << series[idx].tahunRilis << ")" << endl;
        cout << "Rating : " << series[idx].tambahan.rating << endl;
        cout << "Ulasan : " << series[idx].tambahan.ulasan << endl;
        cout << "--------------------------------------------------\n";
        tampilkanSeries(jml, series, idx + 1);
    }
}

// Prosedur untuk menambah judul TV series
void tambahSeries(int &jml, title series[]) {
    if (jml < 10) {
        cin.ignore();
        cout << "Tambah Series\n";
        cout << "Masukkan Judul Series: ";
        getline(cin, series[jml].judul);
        cout << "Masukkan Tahun Rilis: ";
        cin >> series[jml].tahunRilis;
        while (true) {
            if (series[jml].tahunRilis < 1900 || series[jml].tahunRilis > 2024) {
                cout << "Tahun rilis harus diantara 1900-2024\n";
                cout << "Masukkan Tahun Rilis: ";
                cin >> series[jml].tahunRilis;
            } else {
                break;
            }
        }
        cout << "Masukkan Rating (1-10): ";
        cin >> series[jml].tambahan.rating;
        while (true){
            if (series[jml].tambahan.rating < 1 || series[jml].tambahan.rating > 10) {
                cout << "Rating harus diantara 1-10\n";
                cout << "Masukkan Rating (1-10): ";
                cin >> series[jml].tambahan.rating;
            } else {
                break;
            }
        }
        cout << "Masukkan Ulasan: ";
        cin.ignore();
        getline(cin, series[jml].tambahan.ulasan);
        jml++;
        cout << "Judul Series berhasil ditambahkan\n";
    } else {
        cout << "Daftar series maksimal 10 peringkat!\n";
    }
}

// Prosedur untuk mengubah judul TV series
void ubahSeries(int jml, title series[]) {
    int idx;
    cout << "Edit Series\n";
    tampilkanSeries(jml, series);
    cout << "Masukkan index Series yang ingin diedit: ";
    cin >> idx;
    if (idx >= 1 && idx <= jml) {
        cout << "Masukkan Judul Series: ";
        cin.ignore();
        getline(cin, series[idx - 1].judul);
        cout << "Masukkan Tahun Rilis: ";
        cin >> series[idx - 1].tahunRilis;
        while (true) {
            if (series[idx - 1].tahunRilis < 1900 || series[idx - 1].tahunRilis > 2024) {
                cout << "Tahun rilis harus diantara 1900-2024\n";
                cout << "Masukkan Tahun Rilis: ";
                cin >> series[idx - 1].tahunRilis;
            } else {
                break;
            }
        }
        cout << "Masukkan Rating (1-10): ";
        cin >> series[idx - 1].tambahan.rating;
        while (true){
            if (series[idx - 1].tambahan.rating < 1 || series[idx - 1].tambahan.rating > 10) {
                cout << "Rating harus diantara 1-10\n";
                cout << "Masukkan Rating (1-10): ";
                cin >> series[idx - 1].tambahan.rating;
            } else {
                break;
            }
        }
        cout << "Masukkan Ulasan: ";
        cin >> series[idx - 1].tambahan.ulasan;
        cout << "Data Series berhasil diedit\n";
    } else {
        cout << "Peringkat tidak valid.\n";
    }
}

// Prosedur untuk menghapus judul TV series
void hapusSeries(int &jml, title series[]) {
    int idx;
    cout << "Hapus Judul Series\n";
    tampilkanSeries(jml, series);
    cout << "Masukkan index Series yang ingin dihapus: ";
    cin >> idx;
    if (idx >= 1 && idx <= jml) {
        for (int i = idx - 1; i < jml - 1; i++) {
            series[i] = series[i + 1];
        }
        jml--;
        cout << "Series berhasil dihapus\n";
    } else {
        cout << "Index tidak valid.\n";
    }
}

// Fungsi main
int main() {
    if (!login()) {
        cout << "Upaya masuk terlalu sering. Silakan coba lagi nanti!.\n";
        return 0;
    }
    int jml = 5, menu;
    title series[10] = {
        {"Breaking Bad", 2008, {10, "Say my name."}},
        {"The Sopranos", 1999, {8, "Gabagool"}},
        {"Game of Thrones", 2011, {9, "Lannister always pays his debts"}},
        {"Better Call Saul", 2015, {8, "It's all good man"}},
        {"Band of Brothers", 2001, {7, "Currahee!"}}
    };
    do {
        while (true) {
            tampilkanMenu(jml, series);
            cin >> menu;
            if (cin.fail()) {
                cin.clear();
                cin.ignore();
                cout << "Input tidak valid. Silakan coba lagi.\n";
            } else {
                break;
            }
        }
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
    } while (menu != 0);
    return 0;
}