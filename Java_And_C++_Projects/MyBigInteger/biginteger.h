//Класс BigInteger для подсчета длинных целых чисел

#ifndef biginteger_h
#define biginteger_h

#include <limits>
#include <string>
typedef uint32_t uint;

const uint64_t B = uint64_t(std::numeric_limits<uint>::max()) + 1; //Основание по которому хранятся длинные числа 2^32
const int MAX_DIGITS = 10;
class BigInteger{
public:
    
    
    BigInteger();
    BigInteger(uint);
    BigInteger(int);
    BigInteger(unsigned long long);
    BigInteger(long);
    BigInteger(long long);
    BigInteger(unsigned long);
    BigInteger(std::string);
    BigInteger(bool, uint, uint*);//нужен для возвращения из функций длинных чисел с контролем лишних нулей и -0
    BigInteger(const BigInteger&);
    BigInteger(BigInteger &&);
    ~BigInteger();
    
    BigInteger& operator=(const BigInteger&);
    BigInteger& operator=(BigInteger&&);
    
    BigInteger operator- () const;
    BigInteger operator+ () const;
    bool operator== (const BigInteger&) const;
    bool operator< (const BigInteger&) const;
    bool operator> (const BigInteger&) const;
    bool operator<= (const BigInteger&) const;
    bool operator>= (const BigInteger&) const;
    bool operator!= (const BigInteger&) const;
    
    BigInteger operator+ (const BigInteger&) const;
    BigInteger& operator+=(const BigInteger&);
    BigInteger operator- (const BigInteger&) const;
    BigInteger& operator-=(const BigInteger&);
    BigInteger& operator++ ();
    BigInteger operator++ (int);
    BigInteger& operator-- ();
    BigInteger operator-- (int);
    
    BigInteger operator* (const BigInteger&) const;//умножение столбиком
    BigInteger& operator*= (const BigInteger&);
    BigInteger operator/ (const BigInteger&) const;
    BigInteger& operator/= (const BigInteger&);
    BigInteger operator% (const BigInteger&) const;
    BigInteger& operator%= (const BigInteger&);
    
    BigInteger operator<< (const int);
    BigInteger& operator<<= (int);
    BigInteger operator>> (const int);
    BigInteger& operator>>= (int);
    
    BigInteger operator~ () const;
    
    BigInteger operator| (const BigInteger&) const;
    BigInteger& operator|= (const BigInteger&);
    
    BigInteger operator& (const BigInteger&) const;
    BigInteger& operator&= (const BigInteger&);
    
    BigInteger operator^ (const BigInteger&) const;
    BigInteger& operator^= (const BigInteger&);
    
    uint* ToUInt32Array(int&) const;
    
    friend std::string to_string(const BigInteger& );
private:
    const int kcbitUint = 32;//количество бит в uint32_t
    
    bool sign = true;
    uint len;
    uint *Number;
    
};


//возвращает массив дополненный до двух, каждый элемент инвертируем и добавляем единицу
uint* reverseBitArray(uint*,const int);

//перемножение, сложение и деление строк, нужно для конструкторов и для вывода числа
std::string stringMult(const std::string& , const std::string& );
std::string stringSum(const std::string& , const std::string& );
uint stringDiv(std::string&);

//Шаблоны на случай, если слева от длинного числа будет стоять обычное число
template<typename T>
BigInteger operator* (const T Left, const BigInteger& Right){
    return BigInteger(Left) * Right;
};

template<typename T>
BigInteger operator+ (const T Left, const BigInteger& Right){
    return BigInteger(Left) + Right;
};

template<typename T>
BigInteger operator- (const T Left, const BigInteger& Right){
    return BigInteger(Left) - Right;
};

template<typename T>
bool operator== (const T Left, const BigInteger& Right){
    return BigInteger(Left) == Right;
}

template<typename T>
BigInteger operator/ (const T Left, const BigInteger& Right){
    return BigInteger(Left) / Right;
}

template<typename T>
BigInteger operator% (const T Left, const BigInteger& Right){
    return BigInteger(Left) % Right;
}
#endif 
