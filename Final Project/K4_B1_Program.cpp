#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Show {
    int idJudul;
    string nama;
    int rating;
    string komentar;
    string user;
};

struct JudulShow {
    int id;
    string nama;
};

const int MAX_Series = 1000;
Show* Series = new Show[MAX_Series];
JudulShow judulSeries[MAX_Series];
int jumlahShow = 0;
int jumlahJudulShow = 0;
string loggedInUser;

// Fungsi untuk split string berdasarkan delimiter
void split(const string& s, char delimiter, string result[], int size) {
    istringstream tokenStream(s);
    string token;
    int i = 0;
    while (getline(tokenStream, token, delimiter) && i < size) {
        result[i++] = token;
    }
}

// Fungsi untuk mengecek apakah string mengandung spasi
bool cekSpasi(const string& str) {
    return str.find(' ') != string::npos;
}

// Fungsi untuk mengecek apakah username sudah ada di file CSV
bool cekUsername(const string& username) {
    ifstream file("Akun.csv");
    string line;
    while (getline(file, line)) {
        string user[2];
        split(line, ',', user, 2);
        if (user[0] == username) {
            return true;
        }
    }
    return false;
}

// Fungsi untuk membuat akun baru
void buatAkun() {
    string username, password;
    cin.ignore();
    cout << "Masukkan username  : ";
    getline(cin,username);
    cout << "Masukkan password  : ";
    getline(cin,password);

    if (username.empty() || password.empty()) {
        system("cls");
        cout << "Username atau password tidak boleh kosong!\n";
        cout << "\n";
        return;
    }

    if (cekSpasi(username) || cekSpasi(password)) {
        system("cls");
        cout << "Username dan password tidak boleh mengandung spasi!\n";
        cout << "\n";
        return;
    }

    if (cekUsername(username)) {
        system("cls");
        cout << "Username sudah ada. Gunakan username yang lain!" << endl;
        cout << "\n";
        return;
    }

    ofstream file;
    file.open("Akun.csv", ios::app);
    file << username << "," << password << endl;
    file.close();

    system("cls");
    cout << "Akun berhasil dibuat!\n";
    cout << "\n";
}

// Fungsi untuk login
bool login() {
    system("cls");
    cin.ignore();
    string username, password;
    cout << "Masukkan username  : ";
    getline(cin,username);
    cout << "Masukkan password  : ";
    getline(cin,password);

    ifstream file("Akun.csv");
    string line;
    while (getline(file, line)) {
        string user[2];
        split(line, ',', user, 2);
        if (user[0] == username && user[1] == password) {
            loggedInUser = username;
            return true;
        }
    }
    return false;
}

// Fungsi untuk membaca review dari file

bool parseInt(const string& str, int& result) {
    stringstream ss(str);
    ss >> result;
    return !ss.fail() && ss.eof();
}

int cariAtauTambahkanJudulShow(const string& nama) {
    for (int i = 0; i < jumlahJudulShow; ++i) {
        if (judulSeries[i].nama == nama) {
            return judulSeries[i].id;
        }
    }
    judulSeries[jumlahJudulShow].id = jumlahJudulShow + 1;
    judulSeries[jumlahJudulShow].nama = nama;
    return judulSeries[jumlahJudulShow++].id;
}

int bacaReview() {
    ifstream filein("review.csv");
    if (!filein.is_open()) {
        cout << "Gagal membuka file review.csv\n";
        return 0;
    }

    string line;
    while (getline(filein, line) && jumlahShow < MAX_Series) {
        stringstream ss(line);
        string temp;

        getline(ss, temp, ',');
        Series[jumlahShow].idJudul = stoi(temp);

        getline(ss, temp, ',');
        Series[jumlahShow].nama = temp;
        Series[jumlahShow].idJudul = cariAtauTambahkanJudulShow(temp);

        getline(ss, temp, ',');
        if (!parseInt(temp, Series[jumlahShow].rating)) continue;

        getline(ss, temp, ',');
        Series[jumlahShow].komentar = temp;

        getline(ss, temp, ',');
        Series[jumlahShow].user = temp;

        jumlahShow++;
    }

    filein.close();
    return jumlahShow;
}

// Algoritma Quick Sort untuk mengurutkan review berdasarkan rating secara descending
int partition(Show arr[], int low, int high) {
    int pivot = arr[high].rating;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j].rating > pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(Show arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

//Fungsi untuk menampilkan review
void tampilkanReview() {
    cout << "Daftar Series:\n";
    cout << "\n";
    for (int i = 0; i < jumlahJudulShow; ++i) {
        cout << "[" << judulSeries[i].id << "]   " << judulSeries[i].nama << endl;
    }
    cout << "\n";

    int pilihan;
    bool validInput = false;

    while (!validInput) { 
        cout << "Pilih Series (0 untuk kembali): ";
        cin >> pilihan;

        if (cin.fail()) {
            cin.clear(); 
            cin.ignore();
            system("cls");
            cout << "Input tidak valid!\n";
            cout << "\n";
            tampilkanReview();
        } else {
            validInput = true;
        }
    }

    if (pilihan == 0) {
        system("cls");
        return;
    } else if (pilihan > 0 && pilihan <= jumlahJudulShow) {
        system("cls");

        // Menghitung rata-rata rating
        double totalRating = 0;
        int reviewCount = 0;

        // Buat array sementara untuk review yang akan diurutkan
        Show tempSeries[MAX_Series];
        int tempIndex = 0;

        for (int i = 0; i < jumlahShow; ++i) {
            if (Series[i].idJudul == pilihan) {
                totalRating += Series[i].rating;
                reviewCount++;
                tempSeries[tempIndex++] = Series[i];
            }
        }

        // Urutkan review berdasarkan rating
        quickSort(tempSeries, 0, tempIndex - 1);

        double averageRating = reviewCount ? totalRating / reviewCount : 0;
        cout << "\n";
        cout << "===== " << judulSeries[pilihan - 1].nama << " =====\n";
        cout << "\n";
        cout << "Total review       : " << reviewCount << endl;
        cout << "Rating rata-rata   : " << averageRating << endl;
        cout << "\n";

        // Tampilkan review yang sudah diurutkan
        for (int i = 0; i < tempIndex; ++i) {
            cout << "Dari       : " << tempSeries[i].user << endl;
            cout << "Rating     : " << tempSeries[i].rating << endl;
            cout << "Komentar   : " << tempSeries[i].komentar << endl;
            cout << "-----------------------------------\n";
        }

        cout << "\n";
        cout << "Tekan Enter untuk kembali ke menu";
        cin.ignore();
        cin.get();
        system("cls");
        tampilkanReview();

    } else {
        system("cls");
        cout << "Pilihan tidak valid\n";
        cout << "\n";
        tampilkanReview();
    }
}

void kosongkanSeries() {
    jumlahShow = 0;                             // Reset jumlah Show ke 0
}

string toLowerCase(const string& str) {        // Fungsi untuk mengubah string menjadi huruf kecil
    string lowerStr = str;
    for (char& c : lowerStr) {
        c = tolower(c);
    }
    return lowerStr;
}

bool containsCharacter(const string& str, char ch) { // Fungsi untuk mengecek apakah string mengandung karakter tertentu
    for (char c : str) {
        if (tolower(c) == tolower(ch)) {
            return true;
        }
    }
    return false;
}

void tambahReview() { // Fungsi untuk menambahkan review
    if (jumlahShow >= MAX_Series) {
        cout << "Kapasitas maksimal Show telah tercapai.\n";
        return;
    }

    Show Show;
    cin.ignore();
    cout << "Judul          : ";
    getline(cin, Show.nama);
    if (Show.nama.empty()) {
        system("cls");
        cout << "Judul tidak boleh kosong!\n";
        cout << "\n";
        return;
    }

    // Cek apakah user sudah mereview Show ini
    for (int i = 0; i < jumlahShow; ++i) {
        if (Series[i].nama == Show.nama && Series[i].user == loggedInUser) {
            system("cls");
            cout << "Anda sudah mereview Show ini.\n";
            return;
        }
    }

    Show.idJudul = cariAtauTambahkanJudulShow(Show.nama); // Cari atau tambahkan judul Show ke dalam array

    bool validRating = false;
    while (!validRating) {
        cout << "Rating (1-10)  : ";
        string ratingInput;
        getline(cin, ratingInput);

        // Cek apakah input rating mengandung karakter koma
        if (ratingInput.find(',') != string::npos) {
            cout << "Rating tidak boleh mengandung koma!\n";
            cout << "\n";
            continue;
        }

        // Konversi input rating menjadi integer
        try {
            Show.rating = stoi(ratingInput);
        } catch (const exception& e) {
            cout << "Rating harus berupa angka!\n";
            cout << "\n";
            continue;
        }

        if (Show.rating < 1 || Show.rating > 10) { 
            cout << "Rating harus antara 1 dan 10.\n";
            cout << "\n";
        } else {
            validRating = true;
        }
    }

    cout << "Komentar       : ";
    getline(cin, Show.komentar);

    Show.user = loggedInUser; // Set user yang sedang login sebagai user yang mereview Show

    // Tambahkan Show ke dalam array
    Series[jumlahShow] = Show;
    jumlahShow++;

    // Tambahkan Show ke file
    ofstream fileout("review.csv", ios::app);
    if (!fileout.is_open()) {
        cout << "Gagal membuka file review.csv\n";
        return;
    }

    fileout << Show.idJudul << "," << Show.nama << "," << Show.rating << "," << Show.komentar << "," << Show.user << endl;
    fileout.close();

    system("cls");
    cout << "Review " << Show.nama << " berhasil ditambahkan.\n";
    cout << "\n";
}

void editReview() { // Fungsi untuk mengedit review

    int pilihan;
    bool validInput = false;

    while (!validInput) {
        cout << "Daftar Series:\n";
        cout << "\n";
        for (int i = 0; i < jumlahJudulShow; ++i) {
            cout << "[" << judulSeries[i].id << "]   " << judulSeries[i].nama << endl;
        }
        cout << "\n";
        cout << "Pilih Series (0 untuk kembali): ";
        cin >> pilihan;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(); 
            system("cls");
            cout << "Input tidak valid!\n";
            cout << "\n";
        } else {
            validInput = true;
        }
    }

    cin.ignore();

    if (pilihan == 0) {
        system("cls");
        return;
    } else if (pilihan > 0 && pilihan <= jumlahJudulShow) {
        system("cls");

        bool found = false;
        for (int i = 0; i < jumlahShow; ++i) {
            if (Series[i].idJudul == pilihan && Series[i].user == loggedInUser) {
                found = true;
                cout << "Rating lama    : " << Series[i].rating << "\n";
                cout << "Komentar lama  : " << Series[i].komentar << "\n";
                cout << "-----------------------------------\n";

                bool validRating = false;
                while (!validRating) {
                    cout << "Rating baru (1-10) : ";
                    string ratingInput;
                    getline(cin, ratingInput);

                    // Cek apakah input rating mengandung karakter koma
                    if (ratingInput.find(',') != string::npos) {
                        cout << "Rating tidak boleh mengandung koma!\n";
                        cout << "\n";
                        continue;
                    }

                    // Konversi input rating menjadi integer
                    try {
                        Series[i].rating = stoi(ratingInput);
                    } catch (const exception& e) {
                        cout << "Rating harus berupa angka!\n";
                        cout << "\n";
                        continue;
                    }

                    if (Series[i].rating < 1 || Series[i].rating > 10) {
                        cout << "Rating harus antara 1 dan 10.\n";
                        cout << "\n";
                    } else {
                        validRating = true;
                    }
                }

                    cout << "Komentar baru      : ";
                    getline(cin, Series[i].komentar);
                    break;
                }
            }

        if (found) {
            // Simpan array yang telah diperbarui ke dalam file
            ofstream fileout("review.csv");
            if (!fileout.is_open()) {
                cout << "Gagal membuka file review.csv\n";
                return;
            }

            for (int i = 0; i < jumlahShow; i++) {
                fileout << Series[i].idJudul << "," << Series[i].rating << "," << Series[i].komentar << "," << Series[i].user << endl;
            }

            fileout.close();
            system("cls");
            cout << "Review " << judulSeries[pilihan - 1].nama << " berhasil diedit.\n";
            cout << "\n";
        } else {
            cout << "Review tidak ditemukan atau Anda tidak memiliki hak untuk mengeditnya.\n";
            cout << "\n";
            editReview();
        }
    } else {
        system("cls");
        cout << "Pilihan tidak valid\n";
        cout << "\n";
        editReview();
    }
}

void hapusReview() { // Fungsi untuk menghapus review

    int pilihan;
    bool validInput = false;

    while (!validInput) {
        cout << "Daftar Series:\n";
        cout << "\n";
        for (int i = 0; i < jumlahJudulShow; ++i) {
            cout << "[" << judulSeries[i].id << "]   " << judulSeries[i].nama << endl;
        }
        cout << "\n";
        cout << "Pilih Series yang akan dihapus reviewnya (0 untuk kembali): ";
        cin >> pilihan;

        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            system("cls");
            cout << "Input tidak valid!\n";
            cout << "\n";
        } else {
            validInput = true;
        }
    }

    if (pilihan == 0) {
        system("cls");
        return;
    } else if (pilihan > 0 && pilihan <= jumlahJudulShow) {
        system("cls");

        bool found = false;
        for (int i = 0; i < jumlahShow; ++i) {
            if (Series[i].idJudul == pilihan && Series[i].user == loggedInUser) {
                found = true;
                for (int j = i; j < jumlahShow - 1; ++j) {
                    Series[j] = Series[j + 1];
                }
                jumlahShow--;
                break;
            }
        }

        if (found) {            // Simpan array yang telah diperbarui ke dalam file
            ofstream fileout("review.csv");
            if (!fileout.is_open()) {
                cout << "Gagal membuka file review.csv\n";
                return;
            }

            for (int i = 0; i < jumlahShow; i++) {
                fileout << Series[i].idJudul << "," << Series[i].nama << "," << Series[i].rating << "," << Series[i].komentar << "," << Series[i].user << endl;
            }

            fileout.close();
            cout << "Review berhasil dihapus.\n";
            cout << "\n";
        } else {
            cout << "Review tidak ditemukan atau Anda tidak memiliki hak untuk menghapusnya.\n";
            cout << "\n";
            hapusReview();
        }
    } else {
        system("cls");
        cout << "Pilihan tidak valid\n";
        cout << "\n";
        hapusReview();
    }
}

void cariJudul() { // Fungsi untuk mencari judul Show berdasarkan nama menggunakan algoritma Substring Matching
    string title;
    cout << "Masukkan judul atau bagian dari judul yang ingin dicari: ";
    cin.ignore();
    getline(cin, title);
    cout << "\n";

    bool found = false;
    for (int i = 0; i < jumlahShow; i++) {
        if (toLowerCase(Series[i].nama).find(toLowerCase(title)) != string::npos) {
            found = true;
            cout << "Judul      : " << Series[i].nama << endl;
            cout << "User       : " << Series[i].user << endl;
            cout << "Rating     : " << Series[i].rating << endl;
            cout << "Komentar   : " << Series[i].komentar << endl;
            cout << "--------------------------\n";
        }
    }

    if (!found) {
        cout << "Show dengan judul atau bagian dari judul \"" << title << "\" tidak ditemukan." << endl;
        cout << "\n";
    }

    cout << "Tekan Enter untuk kembali ke menu";
    cin.get();
    system("cls");
}

int coba = 0;                                       // Jumlah percobaan login yang gagal
int main() {                                        // Fungsi utama
    while (true) {
        cout << "Selamat datang di Serializd\n";
        cout << "\n";
        cout << "[1] Register\n";
        cout << "[2] Sign-in\n";
        cout << "[0] Exit\n";
        cout << "\n";

        int pilihan;
        bool validInput = false;

        while (!validInput) {
            cout << "Pilihan Anda: ";
            cin >> pilihan;
            if (cin.fail() || pilihan < 0 || pilihan > 2) {
                cin.clear();
                cin.ignore();
                system("cls");
                cout << "Input tidak valid! Silakan masukkan pilihan yang benar.\n";
                cout << "\n";
                cout << "[1] Register\n";
                cout << "[2] Sign-in\n";
                cout << "[0] Exit\n";
                cout << "\n";
            } else {
                validInput = true;
            }
        }
        switch (pilihan) {
            case 1:
                system("cls");
                buatAkun();
                break;
            case 2:
                if (login()) {
                    coba = 0;                                                   // Reset jumlah percobaan login yang gagal
                    system("cls");
                    cout << "Sign-in berhasil.\n";
                    cout << "Selamat datang, " << loggedInUser << "!\n";
                    cout << "\n";
                    kosongkanSeries();                                          // Kosongkan data Show saat login
                    int jumlah = bacaReview();
                    if (jumlah == 0) {
                        cout << "Tidak ada review yang dibaca atau gagal membuka file review.csv\n";
                    } else {
                        cout << "\n";
                        cout << "Berhasil membaca " << jumlah << " review\n";
                    }
                    cout << "\n";
                    cout << "Tekan Enter untuk melanjutkan";
                    cin.get();
                    system("cls");

                    int pilihanSubmenu;
                    do {
                        cout << "Menu Utama:\n";
                        cout << "\n";
                        cout << "[1] Lihat Review\n";
                        cout << "[2] Tambah Review\n";
                        cout << "[3] Edit Review\n";
                        cout << "[4] Hapus Review\n";
                        cout << "[5] Cari Judul Series Berdasarkan Nama\n";
                        cout << "[0] Sign-out\n";
                        cout << "\n";

                        bool validSubmenuInput = false;
                        while (!validSubmenuInput) {
                            cout << "Pilihan Anda: ";
                            cin >> pilihanSubmenu;

                            if (cin.fail() || pilihanSubmenu < 0 || pilihanSubmenu > 5) {
                                cin.clear();
                                cin.ignore();
                                system("cls");
                                cout << "Input tidak valid! Silakan masukkan pilihan yang benar.\n";
                                cout << "\n";
                                cout << "[1] Lihat Review\n";
                                cout << "[2] Tambah Review\n";
                                cout << "[3] Edit Review\n";
                                cout << "[4] Hapus Review\n";
                                cout << "[5] Cari Judul Series Berdasarkan Nama\n";
                                cout << "[0] Sign-out\n";
                                cout << "\n";
                            } else {
                                validSubmenuInput = true;
                            }
                        }
                        switch (pilihanSubmenu) {
                            case 1:
                                system("cls");
                                tampilkanReview();
                                break;
                            case 2:
                                system("cls");
                                tambahReview();
                                break;
                            case 3:
                                system("cls");
                                editReview();
                                break;
                            case 4:
                                system("cls");
                                hapusReview();
                                break;
                            case 5:
                                system("cls");
                                cariJudul();
                                break;
                            case 0:
                                system("cls");
                                cout << "Sign-out berhasil.\n";
                                cout << "\n";
                                break;
                            default:
                                system("cls");
                                cout << "Pilihan tidak valid!\n";
                                break;
                        }
                    } while (pilihanSubmenu != 0);
                    loggedInUser.clear();                                           // Kosongkan username yang sedang login
                } else {
                    if (coba >= 2) {
                        system("cls");
                        cout << "Upaya masuk terlalu sering. Coba lagi nanti!\n";
                        delete[] Series;                                            // Bebaskan memori sebelum keluar
                        return 0;
                    }
                    system("cls");
                    cout << "Username atau password salah! Silakan coba lagi\n";
                    cout << "\n";
                    coba++;
                }
                break;
            case 0:
                system("cls");
                delete[] Series;                                                    // Bebaskan memori sebelum keluar
                cout << "May thy knife chip and shatter.\n";
                return 0;
            default:
                cout << "Pilihan tidak valid! Silakan coba lagi\n";
                break;
        }
    }
    return 0;
}