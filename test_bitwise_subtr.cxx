#include <bitset>
#include <iostream>
#include <cstdint>

using namespace std;

template <typename T>
T bitwise_subtr(T a, T b)
{
    const size_t SIZE_BITS = sizeof(a) * CHAR_BIT;
    bitset<SIZE_BITS> a_bits(a);
    bitset<SIZE_BITS> b_bits(b);
    cout << "a: " << a_bits.to_string() << "\t(" << +a << ")" << endl;
    cout << "b: " << b_bits.to_string() << "\t(" << +b << ")" << endl;
    size_t i = 0;
    while (b != 0)
    {
        T borrow = (~a) & b;
        a = a ^ b;
        b = borrow << 1;

        a_bits = bitset<SIZE_BITS>(a);
        b_bits = bitset<SIZE_BITS>(b);
        cout << "iteration: " << i++ << endl;
        cout << "a: " << a_bits.to_string() << "\t(" << +a << ")" << endl;
        cout << "b: " << b_bits.to_string() << "\t(" << +b << ")" << endl;
    }
    return a;
}

int main()
{
    int32_t a = 0;
    int32_t b = 1;

    cout << "a = " << +a << endl;
    cout << "b = " << +b << endl;
    
    cout << a - b << endl;

    cout << +(bitwise_subtr<decltype(a)>(a, b)) << endl;

    return 0;
}