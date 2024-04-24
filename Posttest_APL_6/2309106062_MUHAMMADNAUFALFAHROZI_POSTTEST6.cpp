#include <iostream>
using namespace std;

// Struct Review
struct Review {
    int rating;
    string ulasan;
};

// Struct Judul
struct title {
    string judul;
    int tahunRilis;
    Review kritik;
};

// Deklarasi Prototipe Fungsi
bool login();
void tampilkanMenu();
void tampilkanReview(int jml, title *series);
void tambahReview(int &jml, title *series);
void editReview(int jml, title *series);
void hapusReview(int &jml, title *series);
void urutNamaDesc(int jml, title *series);
void urutTahunAsc(int jml, title *series);
void urutRatingDesc(int jml, title *series);
void cariJudulNama(int jml, title *series);
void cariTahun(int jml, title *series);


// Fungsi login
bool login() {
    string nama, nim;
    for(int i = 0; i < 3; i++) {
        cout << "Masukkan Nama  : ";
        getline(cin, nama);
        cout << "Masukkan NIM   : ";
        cin >> nim;
        cin.ignore();
        if(nama == "2" && nim == "2") {
            return true;
        } else {
            cout << "Nama atau NIM salah. Silahkan coba lagi.\n";
        }
    }
    return false;
}

// Prosedur untuk menampilkan menu
void tampilkanMenu() {
    cout << "\n";
    cout << "Daftar Review TV Series:\n";
    cout << "\n";
    cout << "[1] Lihat Review\n";
    cout << "[2] Tambah Review\n";
    cout << "[3] Edit Review\n";
    cout << "[4] Hapus Review\n";
    cout << "[0] Keluar\n";
    cout << "Pilih menu: ";
}

// Fungsi rekursif untuk review
void tampilkanReview(int jml, title *series) {
    for (int i = 0; i < jml; i++) {
        cout << "\n";
        cout << "#" << i + 1 << endl;
        cout << "Judul  : " << series[i].judul << " (" << series[i].tahunRilis << ")" << endl;
        cout << "Rating : " << series[i].kritik.rating << endl;
        cout << "Ulasan : " << series[i].kritik.ulasan << endl;
        cout << "--------------------------------------------------\n";
    }
}

// Prosedur untuk menambah review
void tambahReview(int &jml, title *series) {
    if (jml < 10) {
        cin.ignore();
        cout << "Tambah Series\n";
        cout << "Masukkan Judul Series: ";
        getline(cin, series[jml].judul);
        cout << "Masukkan Tahun Rilis: ";
        cin >> series[jml].tahunRilis;
        while (true) {
            if (series[jml].tahunRilis < 1900 || series[jml].tahunRilis > 2024) {
                cout << "Tahun rilis harus di antara 1900-2024\n";
                cout << "Masukkan Tahun Rilis: ";
                cin >> series[jml].tahunRilis;
            } else {
                break;
            }
        }
        cout << "Masukkan Rating (1-10): ";
        cin >> series[jml].kritik.rating;
        while (true){
            if (series[jml].kritik.rating < 1 || series[jml].kritik.rating > 10) {
                cout << "Rating harus di antara 1-10\n";
                cout << "Masukkan Rating (1-10): ";
                cin >> series[jml].kritik.rating;
            } else {
                break;
            }
        }
        cout << "Masukkan Ulasan: ";
        cin.ignore();
        getline(cin, series[jml].kritik.ulasan);
        jml++;
        cout << "Review berhasil ditambahkan\n";
    } else {
        cout << "Maksimal review 10 judul series!\n";
    }
}

// Prosedur untuk mengedit review
void editReview(int jml, title *series) {
    int idx;
    cout << "Edit Series\n";
    tampilkanReview(jml, series);
    cout << "Masukkan index Series yang ingin diedit: ";
    cin >> idx;
    cin.ignore();
    if (idx >= 1 && idx <= jml) {
        cout << "Masukkan Judul Series: ";
        getline(cin, series[idx - 1].judul);
        cout << "Masukkan Tahun Rilis: ";
        cin >> series[idx - 1].tahunRilis;
        while (true) {
            if (series[idx - 1].tahunRilis < 1900 || series[idx - 1].tahunRilis > 2024) {
                cout << "Tahun rilis harus di antara 1900-2024\n";
                cout << "Masukkan Tahun Rilis: ";
                cin >> series[idx - 1].tahunRilis;
            } else {
                break;
            }
        }
        cout << "Masukkan Rating (1-10): ";
        cin >> series[idx - 1].kritik.rating;
        while (series[idx - 1].kritik.rating < 1 || series[idx - 1].kritik.rating > 10) {
            cout << "Rating harus di antara 1-10\n";
            cout << "Masukkan Rating (1-10): ";
            cin >> series[idx - 1].kritik.rating;
        }
        cin.ignore();
        cout << "Masukkan Ulasan: ";
        getline(cin, series[idx - 1].kritik.ulasan);
        cout << "Review berhasil diedit\n";
    } else {
        cout << "Index tidak valid.\n";
    }
}

// Prosedur untuk menghapus review
void hapusReview(int &jml, title *series) {
    int idx;
    cout << "Hapus Review\n";
    tampilkanReview(jml, series);
    cout << "Masukkan index Review yang ingin dihapus: ";
    cin >> idx;
    if (idx >= 1 && idx <= jml) {
        for (int i = idx - 1; i < jml - 1; i++) {
            series[i] = series[i + 1];
        }
        jml--;
        cout << "Review berhasil dihapus\n";
    } else {
        cout << "Index tidak valid.\n";
    }
}

// Urutkan berdasarkan nama (descending) dengan Quick Sort:
void quickSort(title *series, int low, int high);
int partitionNama(title *series, int low, int high);

void urutNamaDesc(int jml, title *series) {
    quickSort(series, 0, jml - 1);
}

void quickSort(title *series, int low, int high) {
    if (low < high) {
        int pi = partitionNama(series, low, high);
        quickSort(series, low, pi - 1);
        quickSort(series, pi + 1, high);
    }
}

int partitionNama(title *series, int low, int high) {
    string pivot = series[high].judul;
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (series[j].judul > pivot) {
            i++;
            swap(series[i], series[j]);
        }
    }
    swap(series[i + 1], series[high]);
    return (i + 1);
}

// Urutkan berdasarkan tahun rilis (ascending) dengan Bubble Sort: 
void urutTahunAsc(int jml, title *series) {
    for (int i = 0; i < jml - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < jml - i - 1; j++) {
            if (series[j].tahunRilis > series[j + 1].tahunRilis) {
                title temp = series[j];
                series[j] = series[j + 1];
                series[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

// Urutkan berdasarkan rating (descending) dengan Insertion Sort:
void insertionSort(title *series, int n);

void urutRatingDesc(int jml, title *series) {
    insertionSort(series, jml);
}

void insertionSort(title *series, int n) {
    int i, j;
    title key;
    for (i = 1; i < n; i++) {
        key = series[i];
        j = i - 1;
        while (j >= 0 && series[j].kritik.rating < key.kritik.rating) {
            series[j + 1] = series[j];
            j = j - 1;
        }
        series[j + 1] = key;
    }
}


// Cari berdasarkan nama dengan Binary Search:
int binarySearchNama(title *series, int low, int high, string key);
void cariJudulNama(int jml, title *series) {
    string judulCari;
    cout << "Masukkan nama judul yang ingin dicari: ";
    cin.ignore();
    getline(cin, judulCari);
    int result = binarySearchNama(series, 0, jml - 1, judulCari);
    if (result != -1) {
        cout << "Judul: " << series[result].judul << " (" << series[result].tahunRilis << ")\n";
        cout << "Rating: " << series[result].kritik.rating << "\n";
        cout << "Ulasan: " << series[result].kritik.ulasan << "\n";
    } else {
        cout << "Series tidak ditemukan.\n";
    }
}

int binarySearchNama(title *series, int low, int high, string key) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (series[mid].judul == key) {
            return mid;
        }
        if (series[mid].judul < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

// Cari berdasarkan tahun rilis dengan Interpolation Search:
int interpolationSearchTahun(title *series, int low, int high, int key);
void cariTahun(int jml, title *series) {
    int tahunCari;
    cout << "Masukkan tahun rilis series yang ingin dicari: ";
    cin >> tahunCari;
    int result = interpolationSearchTahun(series, 0, jml - 1, tahunCari);
    if (result != -1) {
        cout << "Judul: " << series[result].judul << " (" << series[result].tahunRilis << ")\n";
        cout << "Rating: " << series[result].kritik.rating << "\n";
        cout << "Ulasan: " << series[result].kritik.ulasan << "\n";
    } else {
        cout << "Series tidak ditemukan.\n";
    }
}

int interpolationSearchTahun(title *series, int low, int high, int key) {
    while (low <= high && key >= series[low].tahunRilis && key <= series[high].tahunRilis) {
        int pos = low + (((double)(high - low) / (series[high].tahunRilis - series[low].tahunRilis)) * (key - series[low].tahunRilis));
        if (series[pos].tahunRilis == key) {
            return pos;
        }
        if (series[pos].tahunRilis < key) {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }
    return -1;
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
        {"The Sopranos", 1999, {8, "Gabagool."}},
        {"Game of Thrones", 2011, {9, "Lannister always pays his debts"}},
        {"Better Call Saul", 2015, {8, "It's all good man"}},
        {"Band of Brothers", 2001, {7, "Currahee!"}}
    };
    do {
        while (true) {
            tampilkanMenu();
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
                cout << "Daftar Review TV Series:\n";
                tampilkanReview(jml, series);
                cout << "\n";
                cout << "[1] Urutkan berdasarkan nama (descending)\n";
                cout << "[2] Urutkan berdasarkan tahun rilis (ascending)\n";
                cout << "[3] Urutkan berdasarkan rating (descending)\n";
                cout << "[4] Cari berdasarkan nama\n";
                cout << "[5] Cari berdasarkan tahun rilis\n";
                cout << "[0] Kembali\n";
                cout << "Pilih menu: ";
                break;
            case 2:
                tambahReview(jml, series);
                break;
            case 3:
                editReview(jml, series);
                break;
            case 4:
                hapusReview(jml, series);
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
