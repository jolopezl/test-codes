#include <cstdio>
#include <chrono>
#include <iostream>
#include <vector>

const char cIdSensDr = 'J';
const char cIdSensAm = 'K';

void printStatus(const char* p1, const char* p2)
{
    char idr;
    int idc;
    int ret = std::sscanf(p1, "U%c%d_1", &idr, &idc);
    if (ret == 2) {
        if (idr == 'J') {
            // std::cout << p1 << " corresponds to drift in detsec " << idc << std::endl;
        } else if (idr == 'K') {
            // std::cout << p1 << " corresponds to amplification in detsec " << idc << std::endl;
        } else {
            // std::cout << "problem with " << p1 << std::endl;
        }
    } else {
        // std::cout << "parsing went wrong with " << p1 << std::endl;
    }

    int trd;
    int ret2 = std::sscanf(p2, "BTRD%d_1", &trd);
    if (ret2 == 1) {
        // std::cout << p2 << ", trd sm: " << trd << std::endl;
    } else {
        // std::cout << "parsing went wrong with " << p2 << std::endl;
    }
}

void printStatusLong(const char* p)
{
    int sector1;
    int sector2;
    // char foo1[10];
    // char foo2[10];
    // char foo3[10];
    // char foo4[10];
    // char foo5[10];
    // char foo6[10];
    char id;
    int plane;
    int ret = std::sscanf(p,
                          "/cave_1/barrel_1/B077_1/BSEGMO%d_1/BTRD%*d_1/U%3*s_1/U%3*s_1/U%3*s_1/U%3*s_1/U%3*s_1/U%3*s_1/U%c%d_1",
                          &sector1, &id, &plane);
    // std::cout << p << std::endl;
    // std::cout << "ret: " << ret << std::endl;
    // std::cout << "sector1: " << sector1 << std::endl;
    // std::cout << "sector2: " << sector2 << std::endl;
    // std::cout << "foo1: " << foo1 << std::endl;
    // std::cout << "foo2: " << foo2 << std::endl;
    // std::cout << "foo3: " << foo3 << std::endl;
    // std::cout << "foo4: " << foo4 << std::endl;
    // std::cout << "foo5: " << foo5 << std::endl;
    // std::cout << "foo6: " << foo6 << std::endl;
    // std::cout << "id: " << id << std::endl;
    // std::cout << "plane: " << plane << std::endl;
}

int main()
{

    uint MAX_CALLS = 1e7;

    const char* p = "/cave_1/barrel_1/B077_1/BSEGMO13_1/BTRD13_1/UTR1_1/UTS1_1/UTI1_1/UT12_1/UA12_1/UB12_1/UJ12_1";
    // printStatusLong(p);
    // return 0;

    const char* p1 = "UJ12";
    const char* p2 = "BTRD18";

    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < MAX_CALLS; ++i) {
        printStatus(p1, p2);
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    std::cout << "two sscanf calls duration: " << duration1 << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < MAX_CALLS; ++i) {
        printStatusLong(p);
    }
    t2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    std::cout << "single sscanf call duration: " << duration2 << std::endl;

    std::cout << duration2 / duration1 << std::endl;

    return 0;
}
