#include <iostream>
#include <iomanip>
#include <fstream>
#include <conio.h>
#include <cstring>
#include <sstream>
using namespace std;

struct data00{
    string id;
    string name;
    int stock;
    int price;
};

void header(){
    cout << setfill('-') << setw(35) << "-" << endl;
    cout << "|" << setfill(' ') << setw(23) << "STORE MANAGER" << setw(12) << "|\n";
    cout << setfill('-') << setw(35) << "-" << endl;
}

void data_input(data00 _data[], int &count);

void data_output(data00 _data[], int qty);

void sort_by_name(data00 _data[], int count);

void sort_by_price(data00 _data[], int count);

void sequential_search(data00 _data[], int count);

void data_edit(data00 _data[], int &count);

void data_delete(data00 _data[], int &count);

int main(){
    data00 _data[500]; int count = 0, menu00;
    char exit_c;
    ifstream inFile("data00.dat");
    if (!inFile) {
        cerr << "Terjadi Kesalahan saat Membaca File!" << endl;
        cerr << "Membuat File Baru...";
        fstream newfile;
        newfile.open("data00.dat", ios::out);
        newfile.close();
        cerr << "\nSilakan Mulai Ulang Program.";
        getch();
        return 1;
    }
    string line;
    while (getline(inFile, line) && count < 500) {
        stringstream ss(line);
        getline(ss, _data[count].id, ',');
        getline(ss, _data[count].name, ',');
        string stockstr, pricestr;
        getline(ss, stockstr, ',');
        getline(ss, pricestr, ',');
        _data[count].stock = stoi(stockstr);
        _data[count].price = stoi(pricestr);
        count++;
    }
    inFile.close();
    
    do{
        if (exit_c == 'n' || exit_c == 'N'){
        cout << "\033c";
        cout << setfill('=') << setw(35) << "=" << endl;
        cout << "|" << setfill(' ') << setw(24) << "Terima kasih" << setw(11) << "|\n";
        cout << setfill('=') << setw(35) << "=" << endl;
        getch();
        exit(0);
        }
        system("cls");
        header();
        cout << "Menu :\n";
        cout << "1. Tambahkan Item\n";
        cout << "2. Cari Item\n";
        cout << "3. Urutkan Item\n";
        cout << "4. Tampilkan Item\n";
        cout << "5. Edit Item\n";
        cout << "6. Hapus Item\n";
        cout << "7. Keluar\n";
        cout << "Pilih : "; cin >> menu00;
        switch(menu00){
            case 1: data_input(_data, count);
                    break;

            case 2: sequential_search(_data, count);
                    break;

            case 3: int menu_c2;
                    cout<<"\033c";
                    header();
                    cout<<"Urutkan Item Berdasarkan : \n";
                    cout<<"1. Nama Item\n";
                    cout<<"2. Harga Item\n";
                    cout<<"Pilih : "; cin>>menu_c2;
                    do{
                        switch(menu_c2){
                            case 1: sort_by_name(_data, count);
                                    break;
                            case 2: sort_by_price(_data, count);
                                    break;
                            default: cout<<"Input Error!";
                                     getch();
                                     break;
                        }
                    } while (menu_c2 != 1 && menu_c2 != 2);
                    break;

            case 4: system("cls");
                    header();
                    data_output(_data, count);
                    getch();
                    break;

            case 5: data_edit(_data, count);
                    break;

            case 6: data_delete(_data, count);
                    break;

            case 7: cout<<"Terima Kasih!";
                    getch();
                    exit(1);
                    break;

            default: cout<<"Input Invalid!";
                     getch();
                     break;
        }
        }while (menu00 != 7);
}

void data_input(data00 _data[], int &count){
    int qty;
    char confirm;
    system("cls");
    do{
        cout<<"\033c";
        header();
        cout<<"Masukkan jumlah item yang ingin ditambahkan : ";
        cin>>qty;
        cin.ignore();
        if (qty < 1){
            cout<<"Input Invalid!";
            getch();
        }
    } while (qty < 1);
    data00 temp[qty];
    for(int i = 0; i < qty; i++){
        cout<<"Item #"<<i + 1;
        cout<<"\nID    : "; cin>>temp[i].id; cin.ignore();
        cout<<"Nama  : ";getline(cin, temp[i].name);
        cout<<"Stock : ";cin>>temp[i].stock;
        cout<<"Price : ";cin>>temp[i].price;
    }
    cout<<"Apakah Anda ingin menambahkan data tersebut? (y/n) ";
    cin>>confirm;
    if (confirm == 'y' || confirm == 'Y'){
        for (int i = 0; i < qty; i++){
            FILE* outdata;
            outdata = fopen("data00.dat", "a");
            if (outdata == NULL){
                cout<<"Terjadi Kesalahan saat Membaca File!";
                getch();
                main();
            }
            fprintf(outdata, "%s,%s,%d,%d\n", temp[i].id.c_str(), temp[i].name.c_str(), temp[i].stock, temp[i].price);
            fclose(outdata);
            _data[count].id = temp[i].id;
            _data[count].name = temp[i].name;
            _data[count].stock = temp[i].stock;
            _data[count].price = temp[i].price;
            count++;
        }
        cout<<"Data berhasil ditambahkan!";
    }
    getch();
}

void data_output(data00 _data[], int qty){
    cout << setiosflags (ios::left);
    cout << setfill ('-') << setw (72) << "-" << endl;
    cout<<"|"
    <<setfill(' ')
    <<setw(6) << "ID" << "|"
    <<setw(45) << "Nama Produk" << "|"
    <<setw(5) << "QTY" << "|"
    <<setw(11) << "Harga" << "|" << endl;
    cout<<setfill('-') << setw(72) << "-" << endl;
    if(qty == 0){
        cout << "|" << setfill(' ') << setw(25) << " " 
             << setw(45) << "Tidak ada data!" << "|" << endl;
    }
    for (int i = 0; i < qty; i++) {
        cout <<"|"
             << setfill(' ')
             << setw (6) << _data[i].id << "|"
             << setw (45) << _data[i].name << "|"
             << setw (5) << _data[i].stock << "|"
             << setw (11) << _data[i].price << "|" << endl;
    }
    cout << setfill ('-') << setw (72) << "-" << endl;
    cout << resetiosflags (ios::left);
}

void sort_by_name(data00 _data[], int count){
    int i, j;
    data00 temp;
    cout<<"\033c";
    header();
    if (count == 0){
        cerr << "Data tidak ada!";
        getch();
        main();
    }
    cout<<"Daftar Barang Sebelum Diurutkan : \n";
    data_output(_data, count);
    getch();
    for (i = 1; i < count; i++){
        temp = _data[i];
        j = i - 1;
        while (j >= 0 && _data[j].name > temp.name){
            _data[j + 1] = _data[j];
            j = j - 1;
        }
        _data[j + 1] = temp;
    }
    cout<<"\033c";
    header();
    cout<<"Daftar Barang Setelah Diurutkan : \n";
    data_output(_data, count);
    getch();
}

void sort_by_price(data00 _data[], int count){
    cout<<"\033c";
    header();
    if (count == 0){
        cerr << "Data tidak ada!";
        getch();
        main();
    }
    cout<<"Daftar Barang Sebelum Diurutkan : \n";
    data_output(_data, count);
    getch();
    for (int i = 0; i < count - 1; i++){
        int awal = i;
        for(int j = i + 1; j < count; j++ ){
            if (_data[j].price < _data[awal].price){
                awal = j;
            }
        }
        swap(_data[awal], _data[i]);
    }
    cout<<"\033c";
    header();
    cout<<"Daftar Barang Setelah Diurutkan : \n";
    data_output(_data, count);
    getch();
}

void sequential_search(data00 _data[], int count){
    string name_;
    int price_;
    bool found = false;
    cout<<"\033c";
    char outp;
    header();
    if (count == 0){
        cerr << "Data tidak ada!";
        getch();
        main();
    }
    cout << "Tampilkan Produk? (y/n) "; cin >> outp;
    if (outp == 'y' || outp == 'Y'){
        cout << "\033c";
        header();
        data_output(_data, count);
        getch();
    }
    cout<<"\033c";
    header();
    int menu_c1;
    cout<<"Cari Item Berdasarkan : \n";
    cout<<"1. Nama Item\n";
    cout<<"2. Harga Item\n";
    cout<<"Pilih : "; cin>>menu_c1;
    do{
        switch (menu_c1){
            case 1: cout << "Masukkan Nama Item : "; cin.ignore(); getline(cin, name_);
                    break;
            case 2: cout << "Masukkan Harga Item : "; cin>> price_;
                    break;
            default: cout<<"Input Invalid!";
                     break;
        }
    } while (menu_c1 != 1 && menu_c1 != 2);
    int i = 0;
    while ((i < count) && (!found)){
        if (_data[i].name == name_ || _data[i].price == price_)
        {
            found = true;
        } else{
            i = i + 1;
        }
    }
    if (found) {
        cout<<"\033c";
        header();
        if (menu_c1 == 1){
            cout << "\"" << name_ << "\" ditemukan pada index #" << i<<endl;
        } else if (menu_c1 == 2){
            cout << "\"" << price_ << "\" ditemukan pada index #" << i<<endl;
        }
        cout << setiosflags (ios::left);
        cout << setfill ('-') << setw (72) << "-" << endl;
        cout<<"|"
            <<setfill(' ')
            <<setw(6) << "ID" << "|"
            <<setw(45) << "Nama Produk" << "|"
            <<setw(5) << "QTY" << "|"
            <<setw(11) << "Harga" << "|" << endl;
        cout<<setfill('-') << setw(72) << "-" << endl;
        cout <<"|"
             << setfill(' ')
             << setw (6) << _data[i].id << "|"
             << setw (45) << _data[i].name << "|"
             << setw (5) << _data[i].stock << "|"
             << setw (11) << _data[i].price << "|" << endl;
        cout << setfill ('-') << setw (72) << "-" << endl;
        cout << resetiosflags (ios::left);
    } else {
        if(menu_c1 == 1){
            cout<<"Nilai \""<<name_<<"\""<<" tidak ditemukan:(";
        } else if(menu_c1 == 2){
            cout<<"Nilai \""<<price_<<"\""<<" tidak ditemukan:(";
        }
    }
    getch();
}

void data_edit(data00 _data[], int &count){
    char outp, outp01;
    string id_;
    string line;
    data00 temp;
    cout<<"\033c";
    header();
    if (count == 0){
        cerr << "Data tidak ada!";
        getch();
        main();
    }
    cout << "Tampilkan Produk? (y/n) "; cin >> outp;
    if (outp == 'y' || outp == 'Y'){
        cout << "\033c";
        header();
        data_output(_data, count);
        getch();
    }
    cout<<"\033c";
    header();
    cout<<"Masukkan ID Item yang akan diubah : ";
    cin>>id_;
    ifstream infile("data00.dat");
    ofstream tempfile("temp00.dat");
    if(!infile || !tempfile) {
        cerr << "Terjadi Kesalahan saat Membuka File.\n";
        getch();
        main();
    }
    cout<<"\033c";
    header();
    cout<<"ID    : "; cin>>temp.id; cin.ignore();
    cout<<"Nama  : ";getline(cin, temp.name);
    cout<<"Stock : ";cin>>temp.stock;
    cout<<"Price : ";cin>>temp.price;
    cout<<"Ubah item ini? (y/n) ";
    cin>>outp01;
    ostringstream oss;
    oss << temp.id << "," << temp.name << "," << temp.stock << "," << temp.price;
    if(outp01 == 'y' || outp01 == 'Y'){
        while (getline(infile, line)) {
            if (line.find(id_) != string::npos) {
                line = oss.str();
            }
            tempfile << line << '\n';
        }
    }
    infile.close();
    tempfile.close();
    remove("data00.dat");
    rename("temp00.dat", "data00.dat");
    cout<<"Data Berhasil Diubah.";
    getch();
    main();
}

void data_delete(data00 _data[], int &count){
    char outp;
    string id_;
    string line;
    cout<<"\033c";
    header();
    if (count == 0){
        cerr << "Data tidak ada!";
        getch();
        main();
    }
    cout << "Tampilkan Produk? (y/n) "; cin >> outp;
    if (outp == 'y' || outp == 'Y'){
        cout << "\033c";
        header();
        data_output(_data, count);
        getch();
    }
    cout<<"\033c";
    header();
    cout<<"Masukkan ID Item yang akan dihapus : ";
    cin>>id_;
    ifstream infile("data00.dat");
    ofstream tempfile("temp00.dat");
    if(!infile || !tempfile) {
        cerr << "Terjadi Kesalahan saat Membuka File.\n";
        getch();
        main();
    }
    while (getline(infile, line)) {
        if (line.find(id_) != string::npos) {
            continue;
        }
        tempfile << line << '\n';
    }
    infile.close();
    tempfile.close();
    remove("data00.dat");
    rename("temp00.dat", "data00.dat");
    cout<<"Data Berhasil Dihapus.";
    getch();
    main();
}