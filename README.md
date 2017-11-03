#TUGAS IF3130 Jarkom

## Petunjuk penggunaan program
 1. lakukan compile program di terminal dengan menuliskan command make
 2. kemudian jalankann program dengan menuliskan command make run

## Penjelasan singkat setiap Phase
## Phase 1
1. function getValidSubnet langsung mengembalikan subnet "0.0.0.0/0" yang merupakan subnet yang selalu valid untuk host apapun

## Phase 2
1. Pertama-tama kita mencari subnet mask dari subnet dengan menggunakan function getMask
2. lalu kita melakukan pengurangan  32 (yakni 4 x 8 bit) / jumlah max mask dengan subnet mask.
3. jumlah host yang available menjadi 2 dipangkatkan dengan hasil pengurangan max mask dengan subnet mask.

## Phase 3
1. pertama-tama kita mengambil nilai subnet Mask lalu
2. lalu dilakukan pengurangan antara max mask dengan subnet mask
3. lalu kita ubah tiap string dari subnet dan host menjadi array of int
4. lalu kita lakukan penggabungan value dari masing-masing array of int dengan operasi bit sehingga satu array menjadi satu kesatuan
5. lalu kita lakukan operasi bit untuk masing-masing array dengan nilai yang sesuai dengan selisih dari max mask dengan subnet mask
6. lalu kita samakan array dari subnet dan array dari host
