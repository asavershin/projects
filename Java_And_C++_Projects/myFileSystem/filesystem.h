#pragma once

#include <map>
#include <string>

size_t stringToSizet(std::string size){
    size_t coef = 1;
    size_t ans = 0;
    if(size[size.length() - 1] == 'K'){
        coef = 1024;
        size_t k = 1;
        for(long i = size.length() - 2; i > -1; --i, k *= 10){
            ans += (size[i] - '0' ) * k;
        }
        return ans * coef;
    }else if(size[size.length() - 1] == 'M'){
        coef = 1048576;
        size_t k = 1;
        for(long i = size.length() - 2; i > -1; --i, k *= 10){
            ans += (size[i] - '0' ) * k;
        }
        return ans * coef;
    }
    size_t k = 1;
    for(long i = size.length() - 1; i > -1; --i, k *= 10){
        ans += (size[i] - '0' ) * k;
    }
    return ans * coef;
}



class FileSystem;

struct Catalog{//Структура для системной информации в начале файловой системы

    friend class FileSystem;
    char fileName[32]{'\0'};
    size_t next = -1; //Можно использовать ptrdiff_t, size_t(-1) -- слишком большое число, оно не встретится, так что используем его как маркер
    size_t fileSize = 0;
    char firstInFAT = 0;
    char free = 0;// 0 - свободно 1 - занято
};

class FileSystem {
private:
    int MaxFD = 0;// следим за уникальностью дескриптора файла
    size_t System;// количество системных файлов
    size_t size;// размер файловой системы
    size_t blockSize;// размер блока пользовательской информации
    std::string fsName;// имя файловой системы
    Catalog* catalog;// массив системной информации файловой системы
    
    std::map<int, std::pair<size_t, bool>> OF; // карта открытых файлов, bool следит: используется файл или нет. size_t - номер первого блока файла, int - дескриптор
    
    void saveFS(){//сохранение файловой системы
        std::fstream outFile(fsName);
        if (!outFile.is_open()) {
            throw "fsName incorrect";
        }
        outFile.seekp(std::ios_base::beg);
        outFile.write((const char *)catalog, sizeof(Catalog) * System);
        outFile.close();
    }
    
public:
    FileSystem(const char* fsName_, std::string size_, std::string blockSize_){
        //для удобства примем, что blockSize_ - системная информация + пользовательская
        //Пользователю нужно лишь следить, чтобы size_ было кратно blockSize_
        fsName = fsName_;
        std::ifstream inFile(fsName);
        
        size = stringToSizet(size_);
        blockSize = stringToSizet(blockSize_) - sizeof(Catalog);//пользовательские блоки
        System = size/(blockSize + sizeof(Catalog));
        catalog = new Catalog[System];
        
        if ( !inFile.is_open() ) {
            
            std::ofstream file(fsName);
            for(int i = 0; i < size; ++i){
                file.put('a');
            }
            file.close();
            inFile.close();
            saveFS();
        }else{
            size_t i = 0;
            for(; inFile.peek() != EOF; ++i){
                inFile.get();
            };
            if(i != size){
                throw "Wrong size";
            }
            inFile.seekg(std::ios_base::beg);
            inFile.read((char*) catalog, sizeof(Catalog) * System);
            inFile.close();
        }
        
    };
    
    ~FileSystem(){
        delete []catalog;
    };
    
    int create(const char* fileName){
        
        if(std::string(fileName).length() > 32 && std::string(fileName).length() == 0){
            return -1;
        }
        
        for(size_t i = 0; i < System; ++i){
            if(std::string(catalog[i].fileName) == std::string(fileName)){
                return -1;// названия файлов уникальны
            }
        }
        
        for(size_t i = 0; i < System; ++i){
            if(catalog[i].free == 0){
                catalog[i].free = 1;
                catalog[i].firstInFAT = 1;
                strcpy(catalog[i].fileName, fileName);
                catalog[i].fileSize = 0;
                catalog[i].next = -1;
                saveFS();
                return 0;
            }
        }
        return -1;
    };
    
    int del(const char* fileName){
        if(std::string(fileName).length() > 31 && std::string(fileName).length() == 0){//31 тк учитываем символ конца строки
            return -1;
        }
        
        std::string tmp(fileName);
        for(size_t i = 0; i < System; ++i){
            if(std::string(catalog[i].fileName) == tmp && catalog[i].free == 1){
                catalog[i].free = 0;
                catalog[i].fileName[0] = '\0';
                catalog[i].firstInFAT = 0;
                catalog[i].fileSize = 0;
                if(catalog[i].next != -1){
                    i = catalog[i].next;
                    while(catalog[i].next != -1){
                        catalog[i].free = 0;
                        catalog[i].fileName[0] = '\0';
                        catalog[i].firstInFAT = 0;
                        catalog[i].fileSize = 0;
                        i = catalog[i].next;
                    }
                    catalog[i].fileSize = 0;
                    catalog[i].firstInFAT = 0;
                    catalog[i].free = 0;
                    catalog[i].fileName[0] = '\0';
                }
                saveFS();
                return 0;
            }
        }
        return -1;
    };
    
    int open(const char* fileName){

        if(std::string(fileName).length() > 32 && std::string(fileName).length() == 0){
            return -1;
        }

        std::string tmp(fileName);
        for(int i = 0; i < System; ++i){
            if(std::string(catalog[i].fileName) == tmp && catalog[i].firstInFAT == 1 && catalog[i].free == 1){
                OF[MaxFD] = std::pair<size_t, bool>(i, false);
                ++MaxFD;
                return 0;
            }
        }
        return -1;

    };

    int close(int fd){
        if(OF.find(fd) == OF.end()){
            return -1;
        }else{
            OF.erase(fd);
            saveFS();
            return 0;
        }
    };
    
    ptrdiff_t write(int fd, const char* buffer, size_t Size){
        std::map <int, std::pair<size_t, bool>> :: iterator it;
        it = OF.find(fd);
        if(it == OF.end())
            return -1;
        if(it->second.second)
            return -1;
        
        it->second.second = true;
        
        if(Size == 0){
            it->second.second = false;
            return 0;
        }
        
        std::fstream file(fsName);

        size_t fSize = catalog[it->second.first].fileSize;
        size_t startBlock = it->second.first;
        size_t end = startBlock;

        while(true){//Поиск последнего блока файла
            if(catalog[end].next == -1){
                break;
            }else{
                end = catalog[end].next;
            }
        }

            size_t k = 0;
            if(fSize % blockSize != 0 || fSize == 0){// Запись кусочка, который является остатком от деления на blockSize
                file.seekp(std::ios_base::beg + System * sizeof(Catalog) + end * blockSize + fSize % blockSize);
                for(; k < (blockSize - fSize % blockSize) && Size > 0 ; ++k, --Size, ++catalog[startBlock].fileSize){
                    file.put(buffer[k]);
                }
            }
            size_t i = 0;
            while(Size > 0){

                for(;i < System; ++i){
                    if(catalog[i].free == 0){
                        catalog[end].next = i;
                        catalog[i].free = 1;
                        catalog[i].next = -1;
                        end = i;
                        break;
                    }
                }

                if(i == System){
                    it->second.second = false;
                    file.close();
                    return k;
                }
                file.seekp(std::ios_base::beg + System * sizeof(Catalog) + end * blockSize);
                for(int i = 0; i < blockSize && Size > 0; ++i, ++k, --Size, ++catalog[startBlock].fileSize){
                    
                    file.put(buffer[k]);
                }

            }

        it->second.second = false;
        file.close();
        return 0;

    };
    
    ptrdiff_t read(int fd, char* buffer, size_t Size){
        std::map <int, std::pair<size_t, bool>> :: iterator it;
        it = OF.find(fd);
        if(it == OF.end())
            return -1;
        if(it->second.second == true)
            return -1;
        it->second.second = true;

        std::ifstream file(fsName);

        size_t fSize = catalog[it->second.first].fileSize;
        size_t curBlock = it->second.first;

        size_t k = 0;
        if(fSize == 0){
            file.close();
            return -1;//файл пустой, там нечего читать
        }
        
        // Разбиваем заранее на несколько случаев, потому что они несколько отличаются
        if(fSize <= blockSize){

            file.seekg(std::ios_base::beg + System * sizeof(Catalog) + curBlock * blockSize);
            for(;k < fSize && k < Size; ++k){
                buffer[k] = file.get();
            }
            
            file.close();
            it->second.second = false;
            return (k < Size)? k : 0;

        }else if(fSize <= Size){

            for(int i = 0; i < fSize / blockSize; ++i){

                file.seekg(std::ios_base::beg + System * sizeof(Catalog) + curBlock * blockSize);
                for(int j = 0; j < blockSize; ++j, ++k){
                    buffer[k] = file.get();
                }
                curBlock = catalog[curBlock].next;

            }

            if(curBlock == -1){
                file.close();
                it->second.second = false;
                return (fSize == Size)? 0 : k;
            }else{
                file.seekg(std::ios_base::beg + System * sizeof(Catalog) + curBlock * blockSize);
                for(int j = 0; j < fSize % blockSize; ++j, ++k){
                    buffer[k] = file.get();
                }
            }
            
            it->second.second = false;
            file.close();
            return (fSize == Size)? 0 : k;

        }else{

            for(int i = 0; i < Size / blockSize; ++i){

                file.seekg(std::ios_base::beg + System * sizeof(Catalog) + curBlock * blockSize);
                for(int j = 0; j < blockSize; ++j, ++k){
                    buffer[k] = file.get();
                }
                curBlock = catalog[curBlock].next;

            }


            file.seekg(std::ios_base::beg + System * sizeof(Catalog) + curBlock * blockSize);
            for(int j = 0; j < Size % blockSize; ++j, ++k){
                buffer[k] = file.get();
            }

            it->second.second = false;
            file.close();
            return 0;

        }
    };
};
