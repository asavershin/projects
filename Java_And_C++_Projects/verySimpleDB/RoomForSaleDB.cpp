// Here is the main function. It works with user and parses his commands

#include "DataBase.h"
#include "CheckFunc.h"
const int STRING_LENGTH = 128;
void menu(char command[]) {//Showing interface and reading command with arguments
    
    std::cout << std::endl;
    std::cout << "1) add дата объявления, количество комнат, этаж, площадь, адрес, цена" << std::endl;
    std::cout << "2) save имя_файла_с_БД" << std::endl;
    std::cout << "3) load имя_файла_с_БД" << std::endl;
    std::cout << "4) export имя_файла" << std::endl;
    std::cout << "5) print N" << std::endl;
    std::cout << "6) find ID" << std::endl;
    std::cout << "7) del ID" << std::endl;
    std::cout << "8) print" << std::endl;
    std::cout << "9) exit" << std::endl;
    std::cout << "Enter your command: ";
    std::cin >> command;
    command[STRING_LENGTH - 1] = '\0'; // If user sleep on keyboard
    std::cout << std::endl;
}


int main(){
    
    DataBase DB = {0,0, nullptr};
    
    do {
        
        int Max = 0;// variable allows not to pass the whole user's string
        
        char error[STRING_LENGTH]{'\0'};
        char args[STRING_LENGTH]{'\0'};
        char command[STRING_LENGTH]{'\0'};
        menu(command);
        int ArgsCount = parsing(args, Max);
        
        if( !strcmp(command,"load") ){
            
            if(ArgsCount > 1){
                std::cout << "Wrong argument\n";
                continue;
            }
            
            if(fileProcessing(args, ArgsCount, error, Max)){
                if(loadDB(DB, args, error)){
                    std::cout << error << std::endl;
                }
            }else{
                std::cout << error << std::endl;
            }

            
        }else if(strcmp(command,"save") == 0){
            if(ArgsCount > 1){
                std::cout << "Wrong argument\n";
                continue;
            }

            if(fileProcessing(args, ArgsCount, error, Max)){
                if(saveDB(DB, args, error)){
                    std::cout << error << std::endl;
                }
            }else{
                std::cout << error << std::endl;
            }
       
            
        }else if(strcmp(command,"add") == 0){
            int num1 = 0;
            int num2 = 0;
            int num3 = 0;
            int num4 = 0;
            if(ArgsCount != 6 ){
                std::cout << "Wrong arguments or too long arguments" << std::endl;
                continue;
            }
            char* Beg,* End;
            if(parsingForAdd(args, Max, num1, num2, num3, num4, Beg, End, error)){
                std::cout << error << std::endl;
            }else{
                if(num1 == 0 or num3 == 0){
                    std::cout << "Wrong arguments\n";
                    continue;
                }
                addRecord(DB, args, num1, num2, num3, Beg, End, num4);
            }
            
            
        }else if(strcmp(command,"del") == 0){
            int num1 = 0;
            if(ArgsCount != 1){
                std::cout << "Wrong argument\n";
                continue;
            }
            if(checkNum(args, Max, num1)){
                std::cout << "wrong argument" << std::endl;
                continue;
            }
            if(delID(DB, num1, error)){
                std::cout << error << std::endl;
            }
         
            
        }else if(strcmp(command,"print") == 0 and ArgsCount){
            int num1 = 0;
            if(ArgsCount > 1){
                std::cout << "Wrong arguments" << std::endl;
                continue;
            }
            if(checkNum(args, Max, num1)){
                std::cout << "Wrong argument\n";
            }else{
                if(num1 == 0){
                    std::cout << "Wrong argument\n";
                    continue;
                }
                sort(DB);
                print(DB, num1);
            }
            
        }else if(strcmp(command,"print") == 0){
            sort(DB);
            print(DB);
            
        }else if(strcmp(command,"export") == 0){
            if(ArgsCount > 1){
                std::cout << "Wrong argument\n";
                continue;
            }
            if(fileProcessing(args, ArgsCount, error, Max)){
                if(exprt(DB, args, error)){
                    std::cout << error << std::endl;
                }
            }else{
                std::cout << error << std::endl;
            }
          
            
        }else if(strcmp(command,"find") == 0){
            int num1 = 0;
            if(ArgsCount > 1){
                std::cout << "Wrong arguments" << std::endl;
                continue;
            }
            checkNum(args, Max, num1);
            if(num1 == 0){
                std::cout << "Wrong argument\n";
                continue;
            }
            if( (num1 = findID(DB, num1, error)) == 0 ){
                std::cout << error << std::endl;
            }else{
                std::cout << "Your ID" << num1;
            }
            
            
        }else if(strcmp(command,"exit") == 0){
            break;
        }else{
            std::cout << "wrong command: " << command << std::endl;
        }
    } while (true);
    
    return 0;
}

