#include <iostream>
#include <fstream>

//Используем кольцевой массив
class CycleArray {
    char arr[52]{0};
    int f = 26;
    int l = 26;
    int count = 0;

public:

    void append(char a) {
        ++count;
        f = (f + 51) % 52;
        arr[(f + 52) % 52] = a;
    }

    char get() {
        if (count == 0) {
            return 0;
        }
        --count;
        char ans = arr[(l + 51) % 52];
        arr[(l + 51) % 52] = 0;
        l = (l + 51) % 52;
        return ans;
    }

    char look(int num) {
        if (count - num == 0) {
            return 0;
        }
        return arr[(l - num + 51) % 52];
    }
};


//Используем два кольцевого массива, можно было бы на трех, было бы читаемее. Но на двух эффективнее по памяти
int battle(CycleArray players[]) {
    int num = 0;
    char up1;
    char up2;
    for (int k = 1e6; k > 0; --k) {
        up1 = players[0].look(num);
        up2 = players[1].look(num);
        if (up1 == 0 and up2 == 0) {
            return 0;
        }
        if (up1 == 0) {
            return 2;
        }
        if (up2 == 0) {
            return 1;
        }
        if (up1 == up2) {
            ++num;
            continue;
        }
        if (int(up1) == 14 and int(up2) == 2) {
            for (int i = 0; i <= num; ++i) {
                players[1].append(char(players[0].get()));
                players[1].append(char(players[1].get()));
            }
        }
        else if (int(up1) == 2 and int(up2) == 14) {
            for (int i = 0; i <= num; ++i) {
                players[0].append(char(players[0].get()));
                players[0].append(char(players[1].get()));
            }
        }
        else if (int(up2) > int(up1)) {
            for (int i = 0; i <= num; ++i) {
                players[1].append(char(players[0].get()));
                players[1].append(char(players[1].get()));
            }
        }
        else if (int(up2) < int(up1)) {
            for (int i = 0; i <= num; ++i) {
                players[0].append(char(players[0].get()));
                players[0].append(char(players[1].get()));
            }
        }
        num = 0;
    }

    return -1;
}

int fileRead(const char a[]) {
    switch (a[0]) {
        case 'A':
            return 14;
        case 'K':
            return 13;
        case 'Q':
            return 12;
        case 'J':
            return 11;
        case '1':
            return 10;
        case '9':
            return 9;
        case '8':
            return 8;
        case '7':
            return 7;
        case '6':
            return 6;        
        case '5':
            return 5;
        case '4':
            return 4;
        case '3':
            return 3;
        case '2':
            return 2;
        default:
            return 0;
    }
}

int main(int argc, char* argv[])
{   
    std::ifstream inFile(argv[1]);
    CycleArray players[2];
    char a[3]{0};
    char b;

    for (int i = 0; i < 26; ++i) {
        inFile >> a >> b;
        players[0].append(char(fileRead(a)));
    }
    for (int i = 0; i < 26; ++i) {
        inFile >> a >> b;
        players[1].append(char(fileRead(a)));
    }
    inFile.close();
    int result = battle(players);
    switch (result)
    {
    case 0:
        std::cout << "draw";
        break;
    case 1:
        std::cout << "first";
        break;
    case 2:
        std::cout << "second";
        break;
    default:
        std::cout << "unknown";
        break;
    }
    return 0;
}
