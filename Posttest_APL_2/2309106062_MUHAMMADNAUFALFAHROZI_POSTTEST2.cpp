// Nama : Muhammad Naufal Fahrozi
// NIM  : 2309106062

#include <iostream>
#include <string>

using namespace std;

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

int main() {
    if(!login()) {
        cout << "Upaya masuk terlalu sering. Silakan coba lagi nanti!.\n";
        return 0;
    }

    int jml = 5, menu, idx;
    string series[10] = {"Breaking Bad", "The Sopranos", "Game of Thrones", "Better Call Saul", "Band of Brothers"};
    string ulang = "y";

    while (ulang == "y") {
        cout << " \n";
        cout << "TV Series Terfavorit versi Fahrozi:\n";
        cout << " \n";
        cout << "[1] Tambah Series\n";
        cout << "[2] Ubah Judul Series\n";
        cout << "[3] Lihat Series\n";
        cout << "[4] Hapus Series\n";
        cout << "[0] Keluar\n";
        cout << "Pilih menu: ";

        cin >> menu;
        if (menu == 1) {
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
        else if (menu == 2) {
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
        else if (menu == 3) {
            cout << "Tampilkan Series\n";
            for (int i = 0; i < jml; i++) {
                cout << "Peringkat ke-" << i + 1 << ": " << series[i] << endl;
                cout << "--------------------------------------------------\n";
            }
        }
        else if (menu == 4) {
            cout << "Hapus Judul Series\n";
            cout << "Masukkan peringkat Series yang ingin dihapus: ";
            cin >> idx;
            if (idx >= 1 && idx <= jml) {
                for (int i = idx - 1; i < jml - 1; i++) {
                    series[i] = series[i + 1];
                }
                jml--;
                cout << "Judul Series berhasil dihapus\n";
            } 
            else {
                cout << "Peringkat tidak valid.\n";
            }
        }
        else if(menu == 0) {
            cout << "May thy knife chip and shatter!";
            break;
        } 
        else {
            cout << "Menu tidak ada\n";
        }

        cout << "Apakah Anda ingin mengulang? (y/n)\n";
        cin >> ulang;
        if (ulang != "y") {
            cout << "May thy knife chip and shatter!";
            break;
        }
    }
    return 0;
}