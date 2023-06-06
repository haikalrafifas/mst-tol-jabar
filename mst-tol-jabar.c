/*
Tugas akhir semester 2 (2023) Praktikum Struktur Data dan Algoritma S1 Sistem Informasi UPN Veteran Jakarta
dalam mencari Minimum Spanning Tree dari sistem jalan tol menggunakan algoritma Prim.

Konteks =
Pada teori graf, terdapat beberapa istilah seperti Nodes, Edges, dan Weight. Berikut adalah representasinya pada program ini:
- Nodes = Diartikan sebagai simpul graf, di representasikan oleh kota-kota
- Edges = Diartikan sebagai sisi graf, di representasikan oleh jalan tol yang menghubungkan antar kota
- Weight = Diartikan sebagai bobot sisi graf, di representasikan oleh jarak tiap jalan tol
*/

#include <stdio.h>           // Untuk input-output
#include <stdbool.h>         // Untuk nilai boolean (true/false)
#include <string.h>          // Untuk manipulasi string

#define LIMIT 64             // Batas ukuran pendeklarasian larik
#define MAX_WEIGHT 999999    // Inisialisasi jarak (bobot) terjauh (KM)
#define MAX_CHAR 32          // Batas ukuran char

char nodes[LIMIT][MAX_CHAR]; // Larik yang berisi daftar nama-nama kota (nodes)
int edges[LIMIT][LIMIT];     // Koneksi antar kota melalui jalan tol (edges) menggunakan "Adjacent Matrix" yang berisi jarak (weight)
int jumlahKota = 0;          // Inisialisasi jumlah banyaknya kota

// Fungsi untuk mencari indeks kota (node) dengan jalan tol (edge) terpendek
int cariNodeMinimal(int weight[], bool nodes[]) {
    int min = MAX_WEIGHT, indeksNode;
    for (int n = 0; n < jumlahKota; n++) {
        // Jika kota (nodes) belum dimasukkan ke MST dan jarak (weight) lebih kecil dari jarak terjauh
        if (nodes[n] == false && weight[n] < min) {
            min = weight[n];
            indeksNode = n;
        }
    }
    return indeksNode;
}

// Fungsi untuk mencetak Minimum Spanning Tree (MST)
void cetakMST(int hasil[]) {
    char hr[45]; // Garis horizontal sama seperti <hr> pada HTML
    int total = 0;
    for (int i = 0; i < 44; i++) { hr[i] = '-'; } hr[44] = '\0'; // Null terminator
    
    printf("%s\nMinimum Spanning Tree dengan Algoritma Prim\n%s\n", hr, hr);
    for (int n = 1; n < jumlahKota; n++) {
        if ( edges[n][hasil[n]] > 0 ) {
            char temp[40]; // Menampung nama kota sementara untuk dicetak
            sprintf(temp, "%s - %s", nodes[hasil[n]], nodes[n]);
            printf("%-36s%d KM\n", temp, edges[n][hasil[n]]);
            total += edges[n][hasil[n]];
        }
    }
    printf("%s\nTOTAL = %d KM", hr, total);
}

// Fungsi untuk membuat dan mencetak Minimum Spanning Tree (MST) menggunakan algoritma Prim
void MST(int awal) {
    int hasil[jumlahKota];   // Larik untuk menampung urutan hasil MST
    int weight[jumlahKota];  // Larik untuk menampung jarak (bobot) terdekat pada jalan tol (edge)
    bool nodes[jumlahKota];  // Sekumpulan kota (nodes) di dalam graf yang telah/belum dimasukkan ke dalam MST

    // Inisialisasi nilai jarak (weight) menjadi jarak terjauh dan kota-kota (nodes) menjadi false untuk merepresentasikan MST kosong
    for (int n = 0; n < jumlahKota; n++) {
        weight[n] = MAX_WEIGHT;
        nodes[n] = false;
    }

    weight[awal] = 0;   // Jadikan jarak (weight) kota (node) yang dipilih menjadi 0 sebagai tanda awal MST
    hasil[awal] = -1;   // Jadikan urutan hasil MST kota (node) yang dipilih menjadi yang paling awal (root)

    // Perulangan untuk membuat MST
    for (int _ = 0; _ < jumlahKota - 1; _++) {
        // Mencari indeks kota (node) dengan jalan tol terpendek (edge) pada daftar kota-kota (nodes) yang belum dimasukkan ke dalam MST
        int i = cariNodeMinimal(weight, nodes);
        nodes[i] = true; // Tambahkan kota (node) tersebut ke dalam MST

        /*
        Perbarui nilai variabel `hasil` dan `weight` jika ketiga kondisi ini benar semua:
        1. Kota (node) tersebut belum dimasukkan ke dalam MST
        2. Terdapat jalan tol (edge) yang menghubungkan antar kota (node) dari kota tersebut
        3. Jarak jalan tol (edge) tersebut lebih kecil dari daftar jarak (weight) yang ada
        */
        for (int n = 0; n < jumlahKota; n++) {
            if (nodes[n] == false && edges[i][n] && edges[i][n] < weight[n]) {
                hasil[n] = i;
                weight[n] = edges[i][n];
            }
        }
    }

    cetakMST(hasil);  // Cetak MST yang sudah dibuat
}

// Fungsi untuk mencari indeks kota pada larik berdasarkan nama kota
int cariIndeksKota(const char* namaKota) {
    for (int i = 0; i < jumlahKota; i++) {
        if (strcmp(namaKota, nodes[i]) == 0) return i;
    }
    return -1;
}

// Fungsi untuk menambahkan kota (nodes) ke dalam larik `kota`
void tambahKota(const char* daftarKota[], int jumlahKota) {
    for (int i = 0; i < jumlahKota; i++) strcpy(nodes[i], daftarKota[i]);
    jumlahKota = jumlahKota;
}

// Fungsi untuk menambahkan jalan tol (edges) ke dalam larik `jalan`
void tambahJalan(int asal, int tujuan, int jarak) {
    edges[asal][tujuan] = jarak;
    edges[tujuan][asal] = jarak;
}

int main() {
    char inputKota[32];
    const char* daftarKota[] = {
        "Cibitung",
        "Karawang Timur",
        "Cikampek",
        "Subang",
        "Purwakarta",
        "Cimahi",
        "Kota Bandung",
        "Kabupaten Bandung",
        "Soreang",
        "Jatinangor",
        "Sumedang",
        "Kabupaten Majalengka",
        "Cirebon"
    };

    jumlahKota = sizeof(daftarKota) / sizeof(daftarKota[0]);
    tambahKota(daftarKota, jumlahKota);

    // Menghubungkan antar kota menggunakan jalan tol (asal, tujuan, jarak)
    tambahJalan(0, 1, 45);    // Cibitung - Karawang Timur
    tambahJalan(1, 2, 19);    // Karawang Timur - Cikampek
    tambahJalan(2, 3, 53);    // Cikampek - Subang
    tambahJalan(3, 11, 88);   // Subang - Kabupaten Majalengka
    tambahJalan(11, 12, 51);  // Kabupaten Majalengka - Cirebon
    tambahJalan(1, 4, 37);    // Karawang Timur - Purwakarta
    tambahJalan(4, 5, 53);    // Purwakarta - Cimahi
    tambahJalan(5, 6, 14);    // Cimahi - Kota Bandung
    tambahJalan(5, 7, 56);    // Cimahi - Kabupaten Bandung
    tambahJalan(7, 8, 32);    // Kabupaten Bandung - Soreang
    tambahJalan(7, 9, 39);    // Kabupaten Bandung - Jatinangor
    tambahJalan(9, 10, 38);   // Jatinangor - Sumedang
    tambahJalan(10, 11, 53);  // Sumedang - Kabupaten Majalengka

    printf("Masukkan kota asal untuk mencari Minimum Spanning Tree\n> ");
    fgets(inputKota, sizeof(inputKota), stdin);
    inputKota[strcspn(inputKota, "\n")] = '\0';  // Memperbolehkan gap spasi

    int awal = cariIndeksKota(inputKota);
    if ( awal == -1 ) { printf("Kota tidak ditemukan dalam daftar kota!"); return 0; }

    MST(awal);  // Cari Minimum Spanning Tree dengan algoritma Prim

    return 0;
}
