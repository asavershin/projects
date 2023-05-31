
#include <fstream>


//Организуем к-тую порядковую статистику с помощью быстрой сортировки на стеках
void kth(int M[], int Len, int k1, int k2) {

    int start = 0;
    int N = Len, size = 1;
    --Len;
    while (N > 0) {
        N >>= 1;
        ++size;
    }

    int* StackLeft = new int[size];
    int* StackRight = new int[size];
    int topInStack = 0;

    StackLeft[topInStack] = start + 0;
    StackRight[topInStack] = start + Len;

    while (topInStack >- 1) {
        int left = StackLeft[topInStack];
        int right = StackRight[topInStack];
        --topInStack;
        if(left >= right){
            continue;
        }

        int i = left, j = right;
        int pindex = i + (j - i) / 2;
        int p = M[pindex];
        while (i <= j) {
            while (M[i] < p) {
                ++i;
            }
            while (p < M[j]) {
                --j;
            }
            if (i >= j) {
                break;
            }
            if (i < j) {
                std::swap(M[i++], M[j--]);
            }

        }
        if(j <= k2){
            ++topInStack;
            StackLeft[topInStack] = j + 1;
            StackRight[topInStack] = right;
        }

        if(j >= k1){
            ++topInStack;
            StackLeft[topInStack] = left;
            StackRight[topInStack] = j;
        }

    }
    delete[] StackLeft;
    delete[] StackRight;
}

int main(int argc, char* argv[]) {

    if (argc < 3) {
        return 1;
    }
    std::ifstream inFile(argv[1]);
    std::ofstream outFile(argv[2]);
    if (!inFile or !outFile) {
        return 2;
    }

    int n;
    int k1;
    int k2;
    inFile >> n >> k1 >> k2;
    int A;
    int B;
    int C;
    int* arr = new int[n];
    inFile >> A >> B >> C >> arr[0] >> arr[1];
    for (int i = 2; i < n; ++i) {
        arr[i] = A * arr[i - 2] + B * arr[i - 1] + C;
    }

    kth(arr,n, k1 - 1, k2 - 1 );

    --k1;
    --k2;
    while(k1 < k2){
        outFile << arr[k1] << " ";
        ++k1;
    }
    outFile << arr[k1];
    
    delete[]arr;
    inFile.close();
    outFile.close();
    return 0;
}
