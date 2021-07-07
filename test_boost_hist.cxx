#include <algorithm>           // std::for_each
#include <boost/format.hpp>    // only needed for printing
#include <boost/histogram.hpp> // make_histogram, regular, weight, indexed
#include <cassert>             // assert (used to test this example for correctness)
#include <functional>          // std::ref
#include <iostream>            // std::cout, std::flush
#include <sstream>             // std::ostringstream

#include <random>

int main()
{
    using namespace boost::histogram; // strip the boost::histogram prefix
                                      // auto h = make_histogram(
                                      //   axis::regular<>(11, 0, 1.0, "x1"),
                                      //   axis::regular<>(11, 0, 1.0, "x2"),
                                      //   axis::regular<>(11, 0, 1.0, "x3"),
                                      //   axis::regular<>(11, 0, 1.0, "x4"),
                                      //   axis::regular<>(11, 0, 1.0, "x5"));

    // std::random_device rd;
    // std::mt19937 mt(rd());
    // std::uniform_real_distribution<double> dist(0.0, 1.0);

    // for (int i = 0; i < 10; ++i) {
    //   h(dist(mt),
    //     dist(mt),
    //     dist(mt),
    //     dist(mt),
    //     dist(mt));
    // }

    // std::ostringstream os;
    // for (auto&& x : indexed(h, coverage::all)) {
    //   os << boost::format("bin %2i [%4.1f, %4.1f): %i\n") % x.index() % x.bin().lower() % x.bin().upper() % *x;
    // }

    // std::cout << os.str() << std::flush;

    // assert(os.str() ==
    //        "bin -1 [-inf, -1.0): 1\n"
    //        "bin  0 [-1.0, -0.5): 1\n"
    //        "bin  1 [-0.5, -0.0): 1\n"
    //        "bin  2 [-0.0,  0.5): 2\n"
    //        "bin  3 [ 0.5,  1.0): 0\n"
    //        "bin  4 [ 1.0,  1.5): 1\n"
    //        "bin  5 [ 1.5,  2.0): 1\n"
    //        "bin  6 [ 2.0,  inf): 2\n");

    // auto hist = make_histogram(axis::regular<>(3, 0, 1));
    // hist.at(0) = 0;
    // hist.at(1) = 1;
    // hist.at(2) = 2;

    // // assert(*std::find_if(hist.begin(), hist.end(), 1) == 1);
    // for (auto const &h:hist) {
    //   std::cout << h << std::endl;
    // }

    auto a = axis::regular<>(10, 0, 1);
    std::cout << "index of 0.05 is " << a.index(0.05) << std::endl;
    std::cout << "index of 0.5 is " << a.index(0.5) << std::endl;
    std::cout << "index of 0.55 is " << a.index(0.55) << std::endl;
    std::cout << "index of 0.99 is " << a.index(0.99) << std::endl;
    std::cout << "index of 1.1 is " << a.index(1.1) << std::endl;

    auto ai = axis::integer<>(0, 10);
    std::cout << "index of 0 is " << ai.index(0) << std::endl;
    std::cout << "index of 1 is " << ai.index(1) << std::endl;
    std::cout << "index of 2 is " << ai.index(2) << std::endl;
    std::cout << "index of 9 is " << ai.index(9) << std::endl;
    std::cout << "index of 10 is " << ai.index(10) << std::endl;
    std::cout << "index of 15 is " << ai.index(11) << std::endl;

    auto hist = make_histogram(axis::integer<>(1, 10));
    hist(1);
    hist(1);
    hist(1);
    hist(5);
    hist(5);
    hist(10);
    hist(10);
    hist(15);
    hist(15);
    hist(15);
    hist(15);
    hist(15);
    hist(15);

    int i = -1;
    for (auto const& h : hist) {
        std::cout << i << ": " << h << std::endl;
        ++i;
    }

    // std::ostringstream os;
    // for (auto&& x : indexed(h, coverage::all)) {
    //   os << boost::format("bin %2i [%4.1f, %4.1f): %i\n") % x.index() % x.bin().lower() % x.bin().upper() % *x;
    // }
}
