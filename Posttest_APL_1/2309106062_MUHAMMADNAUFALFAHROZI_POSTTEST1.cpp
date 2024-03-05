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

void konversi() {
    int pilihan;
    double kecepatan;
    while(true) {
        cout << "Pilih menu:\n";
        cout << "[1] Konversi Kilometer/jam ke (Centimeter/detik, Meter/detik, Mil/jam)\n";
        cout << "[2] Konversi Centimeter/detik ke (Kilometer/jam, Meter/detik, Mil/jam)\n";
        cout << "[3] Konversi Meter/detik ke (Kilometer/jam, Meter/detik, Mil/jam)\n";
        cout << "[4] Konversi Mil/jam ke (Kilometer/jam, Centimeter/detik, Meter/detik)\n";
        cout << "[0] Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;
        if(pilihan == 0) {
            cout << "May thy knife chip and shatter!";
            break;
        }
        if(pilihan < 1 || pilihan > 4) {
            cout << "Pilihan tidak valid. Silakan pilih menu yang sesuai.\n";
            continue;
        }
        cout << "Masukkan kecepatan: ";
        cin >> kecepatan;
        cout << "================================================================================\n";
        switch(pilihan) {
            case 1:
                cout << "Centimeter/detik   : " << kecepatan * 27.7777777778 << "\n";
                cout << "Meter/detik        : " << kecepatan * 0.2777777778 << "\n";
                cout << "Mil/jam            : " << kecepatan * 0.6213711922 << "\n";
                break;
            case 2:
                cout << "Kilometer/jam      : " << kecepatan * 0.036 << "\n";
                cout << "Meter/detik        : " << kecepatan * 0.01 << "\n";
                cout << "Mil/jam            : " << kecepatan * 0.0223693629 << "\n";
                break;
            case 3:
                cout << "Kilometer/jam      : " << kecepatan * 3.6 << "\n";
                cout << "Centimeter/detik   : " << kecepatan * 100 << "\n";
                cout << "Mil/jam            : " << kecepatan * 2.2369362921 << "\n";
                break;
            case 4:
                cout << "Kilometer/jam      : " << kecepatan * 1.609344 << "\n";
                cout << "Centimeter/detik   : " << kecepatan * 44.704 << "\n";
                cout << "Meter/detik        : " << kecepatan * 0.44704 << "\n";
                break;
        }
    }
}

int main() {
    if(login()) {
        konversi();
    } else {
        cout << "Upaya masuk terlalu sering. Silakan coba lagi nanti!.\n";
    }
    return 0;
}