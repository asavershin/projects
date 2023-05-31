//Header file with struct Room which stores information about the apartment

#ifndef Rooms_hpp
#define Rooms_hpp
#include <iostream>

struct Room{
    int ID = 0;
    char date[11]{'\0'};
    int Number = 0; //Num of rooms
    int Floor = 0;
    int Area = 0;
    int Price = 0;
    char Adress[65]{'\0'};
};

std::ostream& operator<< (std::ostream& out, const Room& st);

#endif
