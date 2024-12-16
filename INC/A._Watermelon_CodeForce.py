# Input dengan validasi
while True: # => Memulai infinite loop (while True) untuk terus meminta input dari user sampai input yang valid diterima.
    try:
        w = int(input())
    # “Try block” digunakan untuk:
    # Membaca input dari user menggunakan input().
    # Mengkonversi input menjadi sebuah integer menggunakan int() dan di assign ke variabel w.
        if 1 <= w <= 100: # => Memeriksa apakah input w berada dalam rentang yang valid dari 1 hingga 100.
            break # Jika w valid, pernyataan break akan keluar dari perulangan.

        else:
            print("Please enter a number between 1 and 100.")
        # Jika w berada di luar range yang valid, user akan diberikan sebuah pesan untuk memintanya agar memasukkan angka antara 1 dan 100.
    except ValueError:
        print("Invalid input. Please enter a valid number.")
    # Jika input tidak dapat dikonversi menjadi bilangan bulat (misalnya, jika pengguna memasukkan nilai non-numerik), ValueError akan dimunculkan.
    # Blok except digunakan untuk menangkap kesalahan dan menampilkan pesan kesalahan.

# Cek kondisi
if w > 2 and w % 2 == 0:
    print("YES")
else:
    print("NO")
#Setelah keluar dari perulangan dengan input w yang valid, kode akan mengevaluasi kondisi berikut:
# 1. w > 2 => Memeriksa apakah w lebih besar dari 2.
# 2. w % 2 == 0 => Memeriksa apakah w habis dibagi 2 (bilangan genap).
# Jika kedua kondisi tersebut "benar", maka akan ditampilkan pesan “YA”.
# Jika "tidak" atau "salah", maka akan menampilkan pesan “TIDAK”.
