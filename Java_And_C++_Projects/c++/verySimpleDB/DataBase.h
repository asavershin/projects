//Header file with struct DataBase which stores apartments database
// Here are function names that execute user commands
#ifndef DataBase_hpp
#define DataBase_hpp
#include "Rooms.h"
#include <fstream>

struct DataBase{
    int max; // This variable store information about count of apartment for all time. Used for ID
    int count;
    Room* room;
    
    
};

void sort(DataBase& DB);
void print(const DataBase& DB, const int rooms);
void print(const DataBase& DB);


int addRecord(DataBase& DB, const char date[], const int Number, const int Floor,
              const int Area, const char* beg, const char* end, const int Price );

bool saveDB(const DataBase& DB, const char filename[], char error[]);
bool loadDB(DataBase& DB, const char filename[], char error[]);
bool exprt(const DataBase& DB, const char filename[],char error[]);

bool delID(DataBase& DB, const int ID, char error[]);
int findID(const DataBase& DB, const int ID, char error[]);

#endif
