// https://stackoverflow.com/questions/45069888/c17-c1z-parallel-usage-of-stdfor-each

#include <algorithm>
#include <execution>
#include <iostream>
#include <vector>

#define PRINT_VECTOR(vec)           \
    {                               \
        for (const auto& v : vec) { \
            std::cout << v << "\t"; \
        }                           \
        std::cout << std::endl;     \
    }

int main()
{
    std::vector<float> signals{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::vector<float> scale_factor(10, 0.5);

    PRINT_VECTOR(signals);
    PRINT_VECTOR(scale_factor);

    std::transform( //std::execution::par_unseq,
      signals.begin(),
      signals.end(),
      signals.begin(),
      signals.end(),
      [&](float val) {
          // modifies value in place
          return val + val * scale_factor;
      });

    return 0;
}