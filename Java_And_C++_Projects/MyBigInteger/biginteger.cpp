//Описание класса BigInteger

#include "biginteger.h"



BigInteger::BigInteger(){
    len = 1;
    sign = true;
    Number = new uint[len];
    Number[0] = 0;
}

BigInteger::BigInteger(uint X){
    len = 1;
    sign = true;
    Number = new uint[len];
    Number[0] = X;
}

BigInteger::BigInteger(int X){
    if(X < 0){
        sign = false;
        X = -X;
    }else{
        sign = true;
    }
    len = 1;
    Number = new uint[len];
    Number[0] = X;
};

BigInteger::BigInteger(unsigned long long X){
    sign = true;
    len = 0;
    unsigned long long tmp = X;
    do {
        tmp /= B;
        ++len;
    } while (tmp != 0);
    Number = new uint[len];
    for(int64_t k = 0; k < len; ++k){
        Number[k] = uint(X % B);
        X /= B;
    }
};

BigInteger::BigInteger(long X){
    if(X < 0){
        sign = false;
        X = -X;
    }else{
        sign = true;
    }
    len = 0;
    long tmp = X;
    do {
        tmp /= B;
        ++len;
    } while (tmp != 0);
    Number = new uint[len];
    for(int64_t k = 0; k < len; ++k){
        Number[k] = uint(X % B);
        X /= B;
    }
};

BigInteger::BigInteger(long long X){
    if(X < 0){
        sign = false;
        X = -X;
    }else{
        sign = true;
    }
    len = 0;
    long long tmp = X;
    do {
        tmp /= B;
        ++len;
    } while (tmp != 0);
    Number = new uint[len];
    for(int64_t k = 0; k < len; ++k){
        Number[k] = uint(X % B);
        X /= B;
    }
};

BigInteger::BigInteger(unsigned long X){
    sign = true;
    len = 0;
    uint64_t tmp = X;
    do {
        tmp /= B;
        ++len;
    } while (tmp != 0);
    Number = new uint[len];
    for(int64_t k = 0; k < len; ++k){
        Number[k] = uint(X % B);
        X /= B;
    }
};

BigInteger::BigInteger(std::string str){
    len = 0;
    
    if(str == "+" || str == "-" || str.length() == 0){
        throw std::invalid_argument("Wrong number");
    }
    
    if(str == "0" || str == "+0" || str == "-0"){
        sign = true;
        len = 1;
        Number = new uint[1];
        Number[0] = 0;
        return;
    }
    if(str.length() == 1 && str[0] == '0'){
        len = 1;
        sign = true;
        Number = new uint[len];
        Number[0] = 0;
    }
    if(str[0] == '-'){
        str.erase(0,1);
        sign = false;
    }else{
        sign = true;
    }
    
    for(int64_t k = 0; k < str.length(); ++k){
        if(str[k] < '0' || str[k] > '9'){
            throw std::invalid_argument("Wrong number");
        }
    }
    
    for(int64_t k = 0; k < str.length(); ++k){
        if(str[k] == '0'){
            str.erase(0,1);
            --k;
        }else{
            break;
        }
    }
    if(str.length() == 0){
        len = 1;
        sign = true;
        Number = new uint[len];
        Number[0] = 0;
        return;
    }
    std::string tmpStr = str;
    
    while (tmpStr != "0"){
        
        stringDiv(tmpStr);
        ++len;
    }
    tmpStr = str;
    
    Number = new uint[len];
    for (int64_t i = 0; i < len; ++i){
        Number[i] = stringDiv(tmpStr);
    }
}

BigInteger::BigInteger(bool sign_, uint len_, uint *num_) : sign(sign_), len(len_), Number(num_){
    
    if ( Number[len - 1] == 0 && len > 1 ) {
        
        for(; Number[len - 1] == 0 && len > 1; --len);
        
        uint *array = new uint[len];
        for(int64_t k = 0; k < len; ++k){
            array[k] = Number[k];
        }
        delete[] Number;
        Number = array;
        
    }
    sign = (len == 1 && Number[0] == 0)? true : sign;
}

BigInteger::BigInteger(const BigInteger& X){
    len = X.len;
    sign = X.sign;
    Number = new uint[len];
    for(int64_t k = 0; k < len; ++k){
        Number[k] = X.Number[k];
    }
}

BigInteger::BigInteger(BigInteger&& X){
    len = X.len;
    sign = X.sign;
    Number = X.Number;
    X.Number = nullptr;
    X.len = 0;
    X.sign = true;
}

BigInteger::~BigInteger(){

    sign = true;
    len = 0;
    delete []Number;

}

BigInteger& BigInteger::operator=(const BigInteger& X){
    if(this != &X){
        if(Number){
            delete []Number;
        }
        len = X.len;
        sign = X.sign;
        Number = new uint[len];
        for(int64_t k = 0; k < len; ++k){
            Number[k] = X.Number[k];
        }
    }
    return *this;
}


BigInteger& BigInteger::operator=(BigInteger&& X){
    
    if (this != &X) {
        if (Number){
            delete[] Number;
        }
        len = X.len;
        sign = X.sign;
        Number = X.Number;
        X.Number = nullptr;
        X.len = 0;
        X.sign = true;
    }
    return *this;
}

BigInteger BigInteger::operator- () const{
    uint *ans = new uint[len]{0};
    memcpy(ans, this->Number, len * sizeof(uint));
    return BigInteger(!sign, len, ans);
};

BigInteger BigInteger::operator+ () const{
    return *this;
}

bool BigInteger::operator== (const BigInteger& X) const{
    
    if(sign != X.sign){
        return false;
    }
    if(len != X.len){
        return false;
    }
    for(int64_t k = 0; k < len; ++k){
        if(Number[k] != X.Number[k]){
            return false;
        }
    }
    return true;
};



bool BigInteger::operator<(const BigInteger& X) const{
    if (*this == X){
        return false;
    }
    if (!sign) {
        if (!X.sign) {
            return ((-X) < (-*this));
        }
        else return true;
    }
    else if (!X.sign) {
        return false;
    }
    else {
        if (len != X.len) {
            return len < X.len;
        }
        else {
            for (int64_t i = len - 1; i > -1; --i) {
                if (Number[i] != X.Number[i]){
                    return Number[i] < X.Number[i];
                }
            }
            return false;
        }
    }
};

bool BigInteger::operator!=(const BigInteger& X) const{
    return !(*this == X);
}

bool BigInteger::operator<=(const BigInteger& X) const{
    return (*this == X) || (*this < X);
}

bool BigInteger::operator>(const BigInteger& X) const{
    return !(*this <= X);
}

bool BigInteger::operator>=(const BigInteger& X) const{
    return !(*this < X);
}


BigInteger BigInteger::operator+ (const BigInteger& right)const{
    if (!sign) {
        if (!right.sign) {
            return -(-*this + (-right));
        }
        else {
            return right - (-*this);
        }
    }else if(!right.sign) {
        return *this - (-right);
    }
    uint64_t tmp = 0;
    int max = (len > right.len)? len : right.len;
    
    uint lenAns = max + 1;
    uint *Ans = new uint[lenAns]{0};
    for(int64_t k = 0; k < max; ++k){
        Ans[k] += tmp;//перенос разряда при переполнении
        if(k < len){
            tmp += Number[k];
        }
        if(k < right.len){
            tmp += right.Number[k];
        }
        if(tmp < B){
            Ans[k] = uint(tmp);
            tmp = 0;
        }else{
            Ans[k] = uint(tmp -= B);
            tmp = 1;
        }
        
    }
    return BigInteger(true, lenAns, Ans);
};

BigInteger& BigInteger::operator+=(const BigInteger& X){
    return *this = (*this + X);
};

BigInteger BigInteger::operator- (const BigInteger& right) const{
    if (!right.sign) {
        return *this + (-right);
    }
    else if (!this->sign) {
        return -(-*this + right);
    }
    else if (*this < right) {
        return -(right - *this);
    }
    uint lenAns = this->len;
    uint *Ans = new uint[lenAns]{0};
    int flag = 0;
    int64_t tmp = 0;
    for (int64_t k = 0; k < len; ++k) {
        tmp = int64_t(Number[k]) - flag - int64_t((k < right.len ? right.Number[k] : 0));
        
        flag = tmp < 0;//контроль на случай, когда разряд числа слева меньше разряда числа справа
        
        if (flag != 0) {
            Ans[k] = uint(tmp + B);
        }else{
            
            Ans[k] = uint(tmp);
        }
        
    }
    return BigInteger(true, lenAns, Ans);
}

BigInteger& BigInteger::operator-=(const BigInteger& X){
    return *this = (*this - X);
};

// префиксный инкремент
BigInteger& BigInteger::operator++() {
    return (*this += 1);
}


// постфиксный инкремент
BigInteger BigInteger::operator++ (int) {
    BigInteger tmp = *this;
    *this += 1;
    return tmp;
}

// префиксный декремент
BigInteger& BigInteger::operator-- () {
    return *this -= 1;
}

// постфиксный декремент
BigInteger BigInteger::operator-- (int) {
    BigInteger tmp = *this;
    *this -= 1;
    return tmp;
}

BigInteger BigInteger::operator* (const BigInteger& right)const{
    uint lenAns = len + right.len;
    uint *Ans = new uint[lenAns]{0};
    for (int64_t i = 0; i < len; ++i){
        uint64_t carry = 0;
        for (int64_t j = 0; j < right.len || carry != 0; ++j){
            uint64_t cur = (uint64_t)Ans[i + j] +
            (uint64_t)Number[i] * (j < right.len ? right.Number[j] : 0) + carry;
            Ans[i + j] = uint(cur % B);
            carry = uint(cur / B);
        }
    }
    
    return BigInteger(sign == right.sign, lenAns, Ans);
}

BigInteger& BigInteger::operator*= (const BigInteger& Right){
    return *this = *this * Right;
};

BigInteger BigInteger::operator/ (const BigInteger& Right) const{
    
    
    if (Right.len == 1)//отдельный случай, когда справа не длинноче число
    {
        uint* ans = new uint[len];
        uint64_t tmp = 0;
        uint64_t v = Right.Number[0];
        for (int64_t k = len - 1; k > -1; --k) {
            ans[k] = uint((tmp * B + Number[k]) / v);
            tmp = (tmp * B + Number[k]) % v;
        }
        return BigInteger(sign == Right.sign, len, ans);
    }
    
    
    const int n = Right.len;
    const int m = len - n;
    
    uint64_t d = B / (Right.Number[n - 1] + 1);//нормализация
    BigInteger U = *this * d;
    if (U.len <= len) {
        ++U.len;
        uint *array = new uint[U.len];
        for(int64_t k = 0; k < U.len; ++k){
            array[k] = U.Number[k];
        }
        array[U.len - 1] = 0;
        delete []U.Number;
        U.Number = array;
    }
    BigInteger V = Right * d;
    uint lenAns = m + 1;
    uint* ans = new uint[lenAns];
    
    for (int64_t j = m; j >= 0; --j) {//цикл с делением, дающий один разряд чстного q
        
        uint64_t q = (B * U.Number[j + n] + U.Number[j + n - 1]) / V.Number[n - 1];
        uint64_t r = (B * U.Number[j + n] + U.Number[j + n - 1]) % V.Number[n - 1];
        
        while(true){
            
            if((q == B) || (q * V.Number[n - 2] > (B * r + U.Number[j + n - 2]))) {
                --q;
                r += V.Number[n - 1];
                if(r < B){
                    continue;
                }
            }
            break;
        }
        ans[j] = uint(q);
        
        int k = 0;
        int64_t t;
        for (int64_t i = 0; i < n; ++i){
            uint64_t p = q * V.Number[i];
            //поразрядное умножение и вычитание, и контроль переполнения
            t = U.Number[i + j] - k - (p & std::numeric_limits<uint>::max());
            U.Number[i + j] = uint(t);
            //Перенос разряда
            k = int((p >> kcbitUint) - (t >> kcbitUint));
        }
        
        t = U.Number[j + n] - k;
        U.Number[j + n] = uint(t);
        
        if (t < 0)//если вычли много, вернемся назад
        {
            ans[j] = ans[j] - 1;
            k = 0;
            for (int64_t i = 0; i < n; ++i)
            {
                t = U.Number[i + j] + V.Number[i] + k;
                U.Number[i + j] = uint(t);
                k = int(t >> kcbitUint);
            }
            U.Number[j + n] += k;
        }
    }
    return BigInteger(sign == Right.sign, lenAns, ans);
};

BigInteger& BigInteger::operator /=(const BigInteger& Right){
    return *this = *this / Right;
}

BigInteger BigInteger::operator%(const BigInteger& Right) const{
    
    if (Right.len == 1)//отдельный случай, когда справа не длинноче число
    {
        uint* ans = new uint[len]{0};
        long long tmp = 0;
        uint64_t v = Right.Number[0];
        for (int64_t k = len - 1; k > -1; --k) {
            ans[k] = uint((tmp * B + Number[k]) / v);
            tmp = (tmp * B + Number[k]) % v;
        }
        return sign ? tmp : -tmp;
    }
    
    
    const int n = Right.len;
    const int m = len - n;
    
    uint64_t d = B / (Right.Number[n - 1] + 1);//нормализация
    BigInteger U = *this * d;
    if (U.len <= len) {
        ++U.len;
        uint *array = new uint[U.len];
        for(int64_t k = 0; k < U.len; ++k){
            array[k] = U.Number[k];
        }
        array[U.len - 1] = 0;
        delete []U.Number;
        U.Number = array;
    }
    BigInteger V = Right * d;
    
    uint lenAns = m + 1;
    uint* ans = new uint[lenAns];
    
    for (int64_t j = m; j >= 0; --j) { //цикл с делением, дающий один разряд чстного q
        
        uint64_t q = (B * U.Number[j + n] + U.Number[j + n - 1]) / V.Number[n - 1];
        
        uint64_t r = (B * U.Number[j + n] + U.Number[j + n - 1]) % V.Number[n - 1];
        
        while(true){
            
            if((q == B) || (q * V.Number[n - 2] > (B * r + U.Number[j + n - 2]))) {
                --q;
                r += V.Number[n - 1];
                if(r < B){
                    continue;
                }
            }
            break;
        }
        ans[j] = uint(q);
        
        int k = 0;
        int64_t t;
        for (int64_t i = 0; i < n; ++i) {
            uint64_t p = q * V.Number[i];
            //поразрядное умножение и вычитание, и контроль переполнения
            t = U.Number[i + j] - k - (p & std::numeric_limits<uint>::max());
            U.Number[i + j] = uint(t);
            //Перенос разряда
            k = uint((p >> kcbitUint) - (t >> kcbitUint));
        }
        
        t = U.Number[j + n] - k;
        U.Number[j + n] = uint(t);
        
        if (t < 0) //если вычли много, вернемся назад
        {
            ans[j] = ans[j] - 1;
            k = 0;
            for (int64_t i = 0; i < n; ++i)
            {
                t = U.Number[i + j] + V.Number[i] + k;
                U.Number[i + j] = uint(t);
                k = int(t >> kcbitUint);
            }
            U.Number[j + n] += k;
        }
    }
    return U / d;
};

BigInteger& BigInteger::operator%= (const BigInteger& Right){
    return *this = *this % Right;
};

BigInteger BigInteger::operator<< (const int shift){
    
    if (shift == 0) {
        return *this;
    }else if (shift == std::numeric_limits<int32_t>::min()){
        return (*this >> std::numeric_limits<int32_t>::max()) >> 1;
    }
    else if (shift < 0) {
        return *this >> -shift;
    }
    
    int digitShift = shift / kcbitUint;
    int smallShift = shift - (digitShift * kcbitUint);
    
    
    uint lenAns = this -> len + digitShift + 1;
    uint *ans = new uint[lenAns];
    
    if (smallShift == 0) {
        for (int64_t i = 0; i < len; i++) {
            ans[i + digitShift] = Number[i];
        }
        
    } else {
        int carryShift = kcbitUint - smallShift;
        uint carry = 0;
        int64_t i = 0;
        for (; i < len; i++) {
            uint rot = Number[i];
            ans[i + digitShift] = rot << smallShift | carry;
            carry = rot >> carryShift;
        }
        ans[i + digitShift] = carry;
    }
    
    return BigInteger(sign, lenAns, ans);
    
};

BigInteger& BigInteger::operator<<= (int shift){
    return *this = *this << shift;
}

BigInteger BigInteger::operator>> (const int shift){
    if (shift == 0) {
        return *this;
    }
    else if (shift == std::numeric_limits<int32_t>::min()) {
        return ((*this << std::numeric_limits<int32_t>::min()) << 1);
    }
    else if (shift < 0) {
        return *this << -shift;
    }
    
    int digitShift = shift / kcbitUint;
    int smallShift = shift - (digitShift * kcbitUint);
    
    uint *tmp;
    
    if (!sign) {
        
        if (shift >= (kcbitUint * len)) {
            return BigInteger(-1);
        }
        
        tmp = new uint[len];
        for (int64_t i = 0; i < len; ++i) {
            tmp[i] = Number[i];
        }
        reverseBitArray(tmp, len);
    }else{
        tmp = Number;
    }
    
    uint lenAns = len - digitShift;
    lenAns = (lenAns < 0)? 0 : lenAns;
    uint *ans = new uint[lenAns];
    
    if (smallShift == 0) {
        for (int64_t i = len - 1; i >= digitShift; i--) {
            ans[i - digitShift] = tmp[i];
        }
    } else {
        int carryShift = kcbitUint - smallShift;
        uint carry = 0;
        for (int64_t i = len - 1; i >= digitShift; i--) {
            uint rot = tmp[i];
            if (!sign && i == len - 1)
                ans[i - digitShift] = (rot >> smallShift) | (std::numeric_limits<uint>::max() << carryShift);
            else
                ans[i - digitShift] = (rot >> smallShift) | carry;
            carry = rot << carryShift;
        }
    }
    
    if (!sign) {
        reverseBitArray(ans, lenAns);
        delete[] tmp;
    }
    return BigInteger(sign, lenAns, ans);
}

BigInteger& BigInteger::operator>>= (int shift){
    return *this = *this >> shift;
}

BigInteger BigInteger::operator~ () const{
    BigInteger ans = *this;
    ans = -(ans + BigInteger(1));
    if(ans.len == 1 && ans.Number[0] == 0 && ans.sign == false){
        ans = -ans;
    }
    return ans;
}

BigInteger BigInteger::operator| (const BigInteger& Num) const{
    
    if (*this == 0)
        return Num;
    if (Num == 0)
        return *this;
    int len1 = 0;
    int len2 = 0;
    
    uint* x, * y;
    x = ToUInt32Array(len1);
    y = Num.ToUInt32Array(len2);
    int len3 = (len1 > len2) ? len1 : len2;
    uint *z = new uint[len3];
    uint xExtend = (!sign)  ? std::numeric_limits<uint>::max() : 0;
    uint yExtend = (!Num.sign) ? std::numeric_limits<uint>::max() : 0;
    
    for (int64_t i = 0; i < len3; i++) {
        uint xu = (i < len1) ? x[i] : xExtend;
        uint yu = (i < len2) ? y[i] : yExtend;
        z[i] = xu | yu;
    }
    bool NewSign = sign && Num.sign;
    if(!(NewSign)){
        reverseBitArray(z, len3);
    }
    delete []x;
    delete []y;
    return BigInteger(NewSign, len3, z);
};

BigInteger& BigInteger::operator|= (const BigInteger& Right){
    return *this = *this | Right;
};

BigInteger BigInteger::operator& (const BigInteger& Num) const{
    if (*this == 0 || Num == 0) {
        return BigInteger(0);
    }
    
    int len1 = 0, len2 = 0;
    uint* x, * y;
    x = ToUInt32Array(len1);
    y = Num.ToUInt32Array(len2);
    int len3 = (len1 > len2) ? len1 : len2;
    uint *z = new uint[len3];
    uint xExtend = (!sign)  ? std::numeric_limits<uint>::max() : 0;
    uint yExtend = (!Num.sign) ? std::numeric_limits<uint>::max() : 0;
    
    for (int64_t i = 0; i < len3; i++) {
        uint xu = (i < len1) ? x[i] : xExtend;
        uint yu = (i < len2) ? y[i] : yExtend;
        z[i] = xu & yu;
    }
    
    if (!(sign || Num.sign)) {
        reverseBitArray(z, len3);
    }
    
    delete []x;
    delete []y;
    return BigInteger(sign || Num.sign, len3, z);
};

BigInteger& BigInteger::operator&= (const BigInteger& Right){
    return *this = *this & Right;
}

BigInteger BigInteger::operator^ (const BigInteger& Num) const{
    
    int len1 = 0, len2 = 0;
    uint* x, * y;
    x = ToUInt32Array(len1);
    y = Num.ToUInt32Array(len2);
    int len3 = (len1 > len2) ? len1 : len2;
    uint *z = new uint[len3];
    uint xExtend = (!sign)  ? std::numeric_limits<uint>::max() : 0;
    uint yExtend = (!Num.sign) ? std::numeric_limits<uint>::max() : 0;
    
    for (int64_t i = 0; i < len3; i++) {
        uint xu = (i < len1) ? x[i] : xExtend;
        uint yu = (i < len2) ? y[i] : yExtend;
        z[i] = xu ^ yu;
    }
    
    if (sign ^ Num.sign) {
        reverseBitArray(z, len3);
    }
    
    delete[] x;
    delete[] y;
    return BigInteger(! (sign ^ Num.sign), len3, z);
};

BigInteger& BigInteger::operator^= (const BigInteger& Right){
    return *this = *this ^ Right;
};

uint* BigInteger::ToUInt32Array(int& len2) const{
    uint *array;
    if (Number[0] == 0 && sign == true && len == 1){
        array = new uint[1]{0};
        len2 = 1;
        return array;
    }
    uint* dwords;
    uint highDWord;
    
    if(sign == false) {
        
        dwords = new uint[len];
        for(int64_t k = 0; k < len; ++k){
            dwords[k] = Number[k];
        }
        
        reverseBitArray(dwords, len);
        highDWord = std::numeric_limits<uint>::max();
    } else {
        
        dwords = Number;
        highDWord = 0;
    }
    

    int64_t msb;
    for (msb = len - 1; msb > 0; --msb) {
        if (dwords[msb] != highDWord) break;
    }
    
    uint lenAns = uint(msb + 1);
    array = new uint[msb + 1];
    memcpy(array, dwords, (msb + 1) * sizeof(uint));
    if(sign == false)
        delete []dwords;
    len2 = lenAns;
    return array;
}

std::string to_string(const BigInteger& A){
    const std::string base32("4294967296");
    std::string tmp("1");
    std::string ans("0");
    
    for (int64_t i = 0;i < A.len; i++) {
        ans = stringSum(ans, stringMult(std::to_string(A.Number[i]), tmp));
        tmp = stringMult(tmp, base32);
        
    }
    if (!A.sign) {
        ans = "-" + ans;
    }
    return ans;
};

uint* reverseBitArray(uint* Number, const int len){
    int64_t i = 0;
    uint v = 0;
    for (; i < len; i++) {
        v = ~Number[i] + 1;
        Number[i] = v;
        if (v != 0) {
            i++;
            break;
        }
    }
    if (v != 0) {
        for (; i < len; i++) {
            Number[i] = ~Number[i];
        }
    }
    else {
        throw "Negative null";//Если встретился -0, кидаем исключение
    }
    return Number;
}

std::string stringSum(const std::string& A, const std::string& B){
    
    std::string str;
    int len1 = int(A.length());
    int len2 = int(B.length());
    int tmp = 0;
    
    if(len1 > len2){
        
        for(int64_t k = len2 - 1;k > -1; --k){
            tmp += (B[k] - '0') + (A[k + len1 - len2] - '0');
            str.push_back('0' + tmp % 10);
            tmp /= 10;
        }
        for(int64_t k = len1 - len2 - 1; k > -1; --k){
            
            tmp += A[k] - '0';
            str.push_back('0' + tmp % 10);
            tmp /= 10;
        }
        if(tmp > 0){
            str.push_back('0' + tmp % 10);
        }
    }else{
        for(int64_t k = len1 - 1;k > -1; --k){
            tmp += (A[k] - '0') + (B[k + len2 - len1] - '0');
            str.push_back('0' + tmp % 10);
            tmp /= 10;
        }
        for(int64_t k = len2 - len1 - 1; k > -1; --k){
            tmp += B[k] - '0';
            str.push_back('0' + tmp % 10);
            tmp /= 10;
        }
        if(tmp > 0){
            str.push_back('0' + tmp % 10);
        }
    }
    std::reverse(str.begin(), str.end());
    return str;
    
};

std::string stringMult(const std::string& A, const std::string& B){
    
    int len1 = int(A.length());
    int len2 = int(B.length());
    
    int *pos = new int[len1 + len2]{0};
    
    for (int64_t i = len1 - 1; i > -1; i--) {
        for (int64_t j = len2 - 1; j > -1; j--) {
            int mul = (A[i] - '0') * (B[j] - '0');
            int64_t p1 = i + j;
            int64_t p2 = i + j + 1;
            int sum = mul + pos[p2];
            pos[p1] += sum / 10;
            pos[p2] = sum % 10;
        }
    }
    std::string ans;
    for (int64_t p = 0; p < (len1 + len2); ++p) {
        if (!(ans.length() == 0 && pos[p] == 0)) {
            ans.push_back('0' + pos[p]);
        }
    }
    
    delete[] pos;
    return (ans.length() == 0) ? "0" : ans;
}

uint stringDiv(std::string& str){
    
    uint64_t rem = 0;
    std::string tmpStr("");
    int len = int(str.length());
    
    uint64_t i = 1;
    for(int64_t k = (len > MAX_DIGITS) ? (MAX_DIGITS) : len - 1; k > -1; --k, i *= 10){
        
        rem += (str[k] - '0') * i;
    }
    
    if (MAX_DIGITS >= len && rem < B){
        str = "0";
        return uint(rem);
    }
    tmpStr += std::to_string(int(rem / B));
    rem = rem % B;
    for(int64_t k = MAX_DIGITS + 1; k < len; ++k){
        rem = rem * 10 + str[k] - '0';
        tmpStr += std::to_string(int(rem / B));
        rem %= B;
    }
    rem %= B;
    str = tmpStr;
    return uint(rem);
};
