# Membaca jumlah test case
t = int(input()) # => fungsi ini untuk membaca input jumlah test case (t) dan merepresentasikan jumlah test case.

# Memproses setiap test case
results = [] # => dibuat untuk menyimpan output untuk setiap test case. 
for _ in range(t):
    n = int(input())
    
# Ini digunakkan untuk memulai perulangan yang berjalan selama t kali => (for _ in range(t):)
# “_” adalah variabel penampung karena indeks perulangan tidak diperlukan. => (for _ in range(t):)
# Pada setiap iterasi, program membaca sebuah bilangan bulat “n”, yang merupakan input untuk test case saat ini.

    results.append((n // 2) + (n % 2))
    # "(n % 2)” memeriksa apakah ada sisa (1 jika n ganjil, 0 jika genap).
    # “+” Menambahkan dua nilai untuk menentukan jumlah kelompok terkecil dari ukuran 2 yang diperlukan.
    # Menambahkan hasil ke daftar hasil.
    
# Print results
print('\n'.join(map(str, results)))
# Mengonversi setiap hasil dalam daftar hasil menjadi sebuah string menggunakan map(str, hasil).
# Menggabungkan string dengan karakter baris baru \n, membuat satu string di mana setiap hasil muncul pada baris baru.
# Mencetak string, menampilkan satu hasil per baris.
