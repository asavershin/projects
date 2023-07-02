//Here are realisations of functions that execute user commands

#include "DataBase.h"

bool delID(DataBase& DB, const int ID, char error[]){// function delete apartment with this ID
    
    bool flag = true;
    int k = 0;
    for(; k < DB.count; ++k){
        if(DB.room[k].ID == ID){
            flag = false;
            break;
        }
    }
    
    if(flag){
        strcpy(error, "Wrong ID");
        return true;
    }
    
    Room* tmp = new Room[DB.count - 1];
    for (int i = 0; i < k; ++i){
        tmp[i] = DB.room[i];
    }
    for (int i = k + 1; i < DB.count; ++i){
        tmp[i - 1] = DB.room[i];
    }
    if (DB.room) //проверка на nullptr
        delete[] DB.room;
    DB.room = tmp;
    --DB.count;
    return false;
}

void print(const DataBase& DB, const int rooms){//The function displays apartments with our Num of rooms sorted by price
    
    int count = DB.count;
    
    for(int k = 0; k < count; ++k){
        if(DB.room[k].Number == rooms){
            std::cout << DB.room[k];
        }
    }
}

void print(const DataBase& DB){//The function displays apartments sorted by price
    int count = DB.count;
    for(int k = 0; k < count; ++k){
        std::cout << DB.room[k];
    }
}

bool exprt(const DataBase& DB, const char filename[], char error[]){//The fucntion exports list of apartments to file
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        strcpy(error, "Can not open file ");
        strcpy(&error[18], filename);
        return true;
    }
    int count = DB.count;
    for(int k = 0; k < count; ++k){
        outFile << DB.room[k];
    }
    outFile.close();
    return false;
}

int addRecord(DataBase& DB, const char date[], const int Number, const int Floor,
              const int Area, const char* beg, const char* end, const int Price ){//The function adds new apartment
    Room* tmp = new Room[DB.count + 1];
    for (int i = 0; i < DB.count; ++i)
        tmp[i] = DB.room[i];
    if (DB.room) //check on nullptr
        delete[] DB.room;
    DB.room = tmp;
    
    for(int i = 0; i < 10; ++i){
        DB.room[DB.count].date[i] = date[i];
    }
    DB.room[DB.count].Number = Number;
    DB.room[DB.count].Floor = Floor;
    DB.room[DB.count].Area = Area;
    DB.room[DB.count].Price = Price;
    
    for(int i = 0; beg <= end; ++beg, ++i){
        DB.room[DB.count].Adress[i] = *beg;
    }
    ++DB.count;
    ++DB.max;
    DB.room[DB.count - 1].ID = DB.max;
    return DB.count;
}

bool saveDB(const DataBase& DB, const char filename[], char error[]){// save database to file and check on correct
    std::ofstream outFile(filename, std::ios_base::binary);
    if (!outFile.is_open()) {
        strcpy(error, "Can not open file ");
        strcpy(&error[18], filename);
        return true;
    }
    outFile.write( (const char *)&DB.max, sizeof(int));
    outFile.write( (const char *)&DB.count, sizeof(int));
    outFile.write((const char*) DB.room, sizeof(Room) * DB.count);
    outFile.close();
    return false;
}

bool loadDB(DataBase& DB, const char filename[], char error[]) {// load database from file and check on correct
    std::ifstream inFile(filename, std::ios_base::binary);
    if (!inFile.is_open()) {
        strcpy(error, "Can not open file ");
        strcpy(&error[18], filename);
        return true;
    }
    int count;
    int max;
    inFile.read((char*)&max, sizeof(int));
    inFile.read((char*)&count, sizeof(int));
    if (DB.room)// если есть данные, то очистить
        delete[] DB.room;
    DB.room = new Room[count];
    DB.count = count;
    DB.max = max;
    inFile.read((char*) DB.room, sizeof(Room) * DB.count);
    inFile.close();
    return false;
}

int findID(const DataBase& DB, const int ID,char error[]){
    // Search with the same floor, number of rooms and area with a difference of 20%
    int count = DB.count;
    int k = 0;
    for(; k < count; ++k){
        if(DB.room[k].ID == ID){
            break;
        }
    }
    if(k == count){
        strcpy(error, "Wrong ID");
        return 0;
    }
    
    double min = (double)DB.room[k].Area * 0.8;
    double max = (double)DB.room[k].Area * 1.2;
    
    for(int i = 0; i < k; ++i){//search for a suitable apartment
        if((DB.room[i].Number == DB.room[k].Number) and (DB.room[i].Floor == DB.room[k].Floor)){
            if((double)DB.room[i].Area >= min and (double)DB.room[i].Area <= max){
                return DB.room[i].ID;
            }
        }
    }
    for(int i = k + 1; i < count; ++i){//search for a suitable apartment
        if((DB.room[i].Number == DB.room[k].Number) and (DB.room[i].Floor == DB.room[k].Floor)){
            if((double)DB.room[i].Area >= min and (double)DB.room[i].Area <= max){
                return DB.room[i].ID;
            }
        }
    }
    strcpy(error, "No such ID");
    return 0;
}

void sort(DataBase& DB) { // HeapSort for our Database


    // make heap
    for (int i = 1; i < DB.count; ++i) {
        int pos = i;
        while (pos != 0) {
            int parent = (pos - 1) / 2;
            
            if (DB.room[parent].Price < DB.room[pos].Price) {
                std::swap(DB.room[parent], DB.room[pos]);
                pos = parent;
                
            }
            else break;
        }
    }
    
    // shift down each element
    int size = DB.count;
    for (int i = 1; i < DB.count; ++i) {
        
        if (DB.room[size - 1].Price < DB.room[0].Price) {
            std::swap(DB.room[0], DB.room[size - 1]);
            
        }
        --size;
        int pos = 0;
        int posMaxChild;
        while (( posMaxChild = 2 * pos + 1 ) < size) {
            if (posMaxChild + 1 < size) {
                
                if (DB.room[posMaxChild].Price < DB.room[posMaxChild + 1].Price)
                    ++posMaxChild;
            }
            
            if (DB.room[pos].Price < DB.room[posMaxChild].Price) {
                std::swap(DB.room[pos], DB.room[posMaxChild]);
                pos = posMaxChild;
                
            }
            else break;
        }
    }
    
}
