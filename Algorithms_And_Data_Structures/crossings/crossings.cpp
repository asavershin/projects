#include <iostream>
#include <fstream>


class Segment{
    int start;
    int end;
public:

    void setStart(int start_){
        start = start_;
    }

    void setEnd(int end_){
        end = end_;
    }

    int getStart() const{
        return start;
    }

    int getEnd() const{
        return end;
    }

};

template <typename compare>
long long MergeSortA(Segment M[], int Len, compare comp) {
    long long ans = 0;
    Segment* tmp = new Segment[Len];
    Segment* from = M;
    Segment* to = tmp;
    for (int step = 1; step < Len; step *= 2) {
        int start1;
        int end1;
        int start2;
        int end2;
        int ind = 0; // индекс в массиве to

        for (int start = 0; start < Len; start += 2*step) {

            start1 = start;
            end1 = start1 + step;
            end1 = (end1 < Len) ? end1 : Len;
            start2 = end1;
            end2 = start2 + step;
            end2 = (end2 < Len) ? end2 : Len;

            while (start1<end1 && start2<end2) {
                if(comp(from + start1, from + start2)){
                    to[ind++] = from[start1++];
                }else{
                    ans += end1 - start1;
                    to[ind++] = from[start2++];
                }

            }
            while (start1 < end1) {
                to[ind++] = from[start1++];
            }
            while (start2 < end2) {
                to[ind++] = from[start2++];
            }
        }

        std::swap(from, to);
    }

    if (from != M) {
        int i = 0;
        while (i < Len) {
            M[i] = tmp[i];
            ++i;
        }
    }

    delete[] tmp;
    return ans;
}

bool comp1(Segment* f, Segment* s){
    return f->getStart() < s->getStart();
}

bool comp2(Segment* f, Segment* s){
    return f->getEnd() < s->getEnd();
}

int main(int argc, char* argv[]) {
    if (argc<2){
        return 1;
    }
    std::ifstream inFile(argv[1]);
    if (!inFile.is_open()){
        std::cout << "File: " <<argv[1] << " could not be open" << std::endl;
        return 2;
    }

    int n;
    int x1;
    int x2;
    inFile >> n;
    Segment* sg = new Segment[n];
    for (int i = 0; i < n; ++i){
        inFile >> x1;
        inFile >> x2;
        sg[i].setStart(x1);
        sg[i].setEnd(x2);
    }

    MergeSortA(sg,n,comp1);

    inFile.close();

    std::cout << MergeSortA(sg,n,comp2);

    delete[]sg;
    return 0;
}
