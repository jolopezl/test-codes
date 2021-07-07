#include <iostream>
#include <algorithm>
#include <cmath>

const float _min_val = 0.0f;
const float _bin_width = 1.0f;
const int _num_bins = 10;

int getBinNumber(float val)
{
    const int bin_number = std::clamp((int)((val - _min_val) / _bin_width), 0, _num_bins - 1);
    return bin_number;
}

void print_msg(float val)
{
    std::printf("VALUE = %f goes in BIN = %d\n", val, getBinNumber(val));
}

int main()
{
    print_msg(-1.0);
    for (float value = 0.5; value < 10; value += 1.0f)
        print_msg(value);

    for (float value = 0.0; value < 11; value += 1.0f)
        print_msg(value);

    print_msg(1.0);
    print_msg(5.0);

    print_msg(10.0001);
    print_msg(12.0);

    std::printf("%f \t %f\n", -1.00, std::clamp(-1.00, 0.0, 1.0));
    std::printf("%f \t %f\n", 0.00, std::clamp(0.00, 0.0, 1.0));
    std::printf("%f \t %f\n", 0.25, std::clamp(0.25, 0.0, 1.0));
    std::printf("%f \t %f\n", 0.50, std::clamp(0.50, 0.0, 1.0));
    std::printf("%f \t %f\n", 1.00, std::clamp(1.00, 0.0, 1.0));

    bool test1 = NAN < 1.0f;
    bool test2 = NAN > 1.0f;
    std::printf("%d\n", test1);
    std::printf("%d\n", test2);

    float res = -1;
    res = std::clamp(NAN, 0.0f, 1.0f);
    std::printf("test of clamp agains NaN = %f\n", res);
    bool test = false;
    if (res)
        test = true;
    std::printf("final test is = %d\n", test);

    if (0.0 <= NAN && NAN <= 1.0) {
        std::printf("It's true\n");
    } else {
        std::printf("It's false\n");
    }

    int answer = std::clamp(NAN, 0.0f, 1.0f);
    if (answer) {
        std::printf("It's true\n");
    } else {
        std::printf("It's false\n");
    }
}