//here are the functions that parse the command
//All bool funtions help us to cath the mistakes

#include "CheckFunc.h"

bool yearCheck(const int Y){// Function return information: year is leap or not
    return (((Y % 4 == 0) and (Y % 100 != 0)) or (Y % 400 == 0)) ? true : false;
}

bool dateCheck(const char date[], char error[]){// Function return information: date with day and month is correct or not

    if(date[2] != '.' or date[5] != '.'){
        strcpy(error, "Wrong date format: ");
        for(int k = 19, i = 0; date[i] != ','; ++k, ++i){
            error[k] = date[i];
        }
        return true;
    }
    if(date[10] != '\0' and date[10] != ','){
        strcpy(error, "Wrong date format: ");
        for(int k = 19, i = 0; date[i] != ','; ++k, ++i){
            error[k] = date[i];
        }
        return true;
    }
    
    for(int i = 0; i < 10; ++i){ // проверка на ошибку ввода
        if(i != 2 && i != 5){
            if(date[i] < '0' || date[i] > '9'){
                strcpy(error, "Wrong date format: ");
                for(int k = 19, i = 0; date[i] != ','; ++k, ++i){
                    error[k] = date[i];
                }
                return true;
            }
        }
    }
    int day = (date[0] - '0') * 10 + (date[1] - '0');
    int month = (date[3] - '0') * 10 + (date[4] - '0');
    int year = (date[6] - '0') * 1000 + (date[7] - '0')+100 + (date[8] - '0') * 10 + (date[9] - '0');
    
    //Checking on correct day or month bellow
    if( !(month > 0 and month < 13)){
        strcpy(error, "Month value is invalid: ");
        error[24] = date[3];
        error[25] = date[4];
        return true;
    }
    if(day <= 0 || day > 31){
        strcpy(error, "Day value is invalid: ");
        error[22] = date[0];
        error[23] = date[1];
        return true;
    }
    if(month == 2){
        if(day > 29){
            strcpy(error, "Day value is invalid: ");
            strcpy(&error[22], &date[0]);
            return true;
        }
        if(day == 29 && !yearCheck(year)){
            strcpy(error, "Day value is invalid: ");
            strcpy(&error[22], &date[0]);
            return true;
        }
    }
    if( (month == 4 || month == 6 || month == 9 || month == 11) && day > 30 ){
        strcpy(error, "Day value is invalid: ");
        strcpy(&error[22], &date[0]);
        return true;
    }
    return false;
}

bool fileProcessing(char args[], int ArgsCount, char error[], int Max){//The function takes filename
    if(ArgsCount != 1){
        strcpy(error, "Wrong argument");
        return false;
    }
    
    char* pointer = &args[Max];
    while(*pointer == ' '){
        *pointer = '\0';
        --pointer;
    }
    return true;
}

int parsing(char args[],int& End){//First parsing of string and arguments counting
    char ch;
    int ArgCount = 0;
    bool flag = true;
    int i = 0;
    int Max = 0;
    // From left to right and delete significant spaces
    while((ch = std::cin.get()) != '\n' and ch != EOF){
        ++Max;
        if(Max >= 128){
            ArgCount = 7;
            return ArgCount;
        }
        if(ch != ' ' && flag){
            flag = false;
            ++ArgCount;
        }else if(ch == ' ' && flag){
            continue;
        }
        if(ch == ','){
            flag = true;
        }
        args[i] = ch;
        ++i;
    }
    End = i - 1;
    if(ArgCount == 0){
        return 0;
    }
    return ArgCount;
}

bool parsingForAdd(char args[], int Max, int& num1, int& num2, int& num3,
                   int& num4, char*& Beg, char*& End, char error[]){//The function gets the arguments from the string
    //From right to left and delete significant spaces
    char* pointer = &args[Max];

    if(checkNum(args, pointer, num4)){
        strcpy(error, "Wrong price");
        return true;
    }
    --pointer;

    while(*pointer == ' '){
        --pointer;
    }
    End = pointer;// Last significant character of the address
    int AdressSize = 0;
    while(*pointer != ','){
        --pointer;
        ++AdressSize;
    }
    Beg = pointer + 1;// First significant character of the address

    if(AdressSize > 64 or AdressSize == 0){
        strcpy(error, "Wrong adress");
        return true;
    }

    if(checkNum(args, --pointer, num3)){
        strcpy(error, "Wrong area");
        return true;
    }

    if(checkNum(args, --pointer, num2)){
        strcpy(error, "Wrong floor");
        return true;
    }

    if(checkNum(args, --pointer, num1)){
        strcpy(error, "Wrong number of rooms");
        return true;
    }
    --pointer;
    while(*pointer == ' '){
        *pointer = '\0';
        --pointer;
    }
    if(dateCheck(args, error)){
        return true;
    }
    return false;
}

bool checkNum(const char args[], char*& pointer, int& arg){// Takes the number and check on correct
    while(*pointer == ' '){
        --pointer;
    }
    if(*pointer == ','){
        return true;
    }
    for(int i = 1; *pointer != ',' and pointer >= args; --pointer){
        if(*pointer < '0' or *pointer > '9'){
            return true;
        }
        arg = arg + (*pointer - '0') * i;
        i *= 10;
    }
    return false;
}

bool checkNum(const char args[], int Max, int& arg){ //Takes the number and check on correct(for command with one argument)
    
    while(args[Max] == ' '){
        --Max;
    }
    
    for(int i = 1; args[Max]!= ',' and Max > -1; --Max){
        if(args[Max] < '0' or args[Max] > '9'){
            return true;
        }
        arg = arg + (args[Max] -'0') * i;
        i *= 10;
    }
    return false;
}
