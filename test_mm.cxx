#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <time.h>
#include <random>

#include "test_mm.h"

int main()
{
    constexpr unsigned int kNDET = 100;
    constexpr unsigned long kNEVENTS = 1e6;

    typedef basic_hit<int, float> example_hit;
    typedef MMAPICompare<int, float> example_mmapi_compare;

    // example of use with vector
    std::vector<example_hit> vec_hitContainer;

    // example using multiset
    std::multiset<example_hit> ms_hitContainer;

    // example using multimap
    std::multimap<int, example_hit> mm_hitContainer;

    // setup random number generaltion
    std::random_device rd;                                        // to obtain a seed for the random number engine
    std::mt19937 gen(rd());                                       // standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<int> dis_integer(0, kNDET - 1); // random integer
    std::uniform_real_distribution<float> dis_real(-0.1, 1.0);    // random float - dummy limits

    // fill the containers
    for (unsigned long n = 0; n < kNEVENTS; ++n) {
        const int det = dis_integer(gen);
        const float val = dis_real(gen);
        vec_hitContainer.push_back(example_hit(det, val));
        ms_hitContainer.insert(example_hit(det, val));
        mm_hitContainer.insert(std::make_pair(det, example_hit(det, val)));
    }

    // loop over set of objects in vector
    int start = clock();
    std::sort(vec_hitContainer.begin(), vec_hitContainer.end(),
              [](const example_hit& a, const example_hit& b) {
                  return a.getDet() < b.getDet();
              });
    auto it_start = vec_hitContainer.begin();
    auto it_end = vec_hitContainer.end();
    int vec_counter = 0;
    for (int det = 0; det < kNDET; ++det) {
        for (std::vector<example_hit>::iterator it = it_start; it < it_end; ++it) {
            if ((*it).getDet() != det) {
                it_start = it;
                break;
            }
            // std::cout << "Accessing elements of vector for key = " << det << std::endl;
            // std::cout << (*it).getDet() << "\t" << (*it).getVal() << std::endl;
            ++vec_counter;
        }
    }
    int end = clock(); //Now check what amount of ticks we have now.
    std::cout << "It took " << end - start << " ticks, or " << ((float)end - start) / CLOCKS_PER_SEC << "seconds." << std::endl;
    std::cout << vec_counter << " processed events using a vector type" << std::endl;

    // loop over set of objects in multimap
    start = clock();
    int mm_counter = 0;
    for (int det = 0; det < 100; ++det) {
        auto iter = mm_hitContainer.equal_range(det);
        if (std::distance(iter.first, iter.second) == 0) {
            continue;
        }

        // std::cout << "Accessing elements of multimap for key = " << det << std::endl;

        std::multimap<int, example_hit>::iterator it;
        for (it = iter.first; it != iter.second; ++it) {
            // std::cout << (it->second).getDet() << "\t" << (it->second).getVal() << std::endl;
            ++mm_counter;
        }
    }
    end = clock(); //Now check what amount of ticks we have now.
    std::cout << "It took " << end - start << " ticks, or " << ((float)end - start) / CLOCKS_PER_SEC << "seconds." << std::endl;
    std::cout << mm_counter << " processed events using a multimap type" << std::endl;

    // return with no errors
    return 0;
}
