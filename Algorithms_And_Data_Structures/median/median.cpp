#include <iostream>
#include <fstream>

class Student{
    int id;
    double averageScore;
public:
    void setId(int id_){
        id = id_;
    }
    void setAverageScore(double averageScore_){
        averageScore = averageScore_;
    }
    double getAverageScore() const{
        return averageScore;
    }
    int getId() const{
        return id;
    }
};

void myShellSort(Student* first, Student* last){
    for (long long d = (last - first) / 2; d != 0; d /= 2){
        for (Student* i = first + d; i != last; ++i ){
            for (Student* j = i; (j - first >= d && (j->getAverageScore() < (j - d)->getAverageScore())); j -= d){
                std::swap(*j, *(j - d));
            }
        }
    }
}

int main(int argc, const char *argv[]){
  
    if (argc<2){
        return 1;
    }

    std::ifstream inFile(argv[1]);
    if (!inFile.is_open()){
        std::cout << "Файл: " <<argv[1] << " не может быть открыт" << std::endl;
        return 2;
    }

    int n;
    double x;
    inFile >> n;

    Student st[99999];
    for (int i = 0; i < n; ++i){
        inFile >> x;
        st[i].setId((i + 1));
        st[i].setAverageScore(x);
    }
    inFile.close();

    myShellSort(st, st + n);

    std::cout << st[0].getId() << " " << st[(n - 1) / 2].getId() << " " << st[n - 1].getId();

    return 0;
}
