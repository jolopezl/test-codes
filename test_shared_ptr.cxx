#include <memory>
// #include <iostream>

// using namespace std;

// #define MSIZE = 10;

// struct sdata
// {
//     size_t _xs;
//     shared_ptr<float[]> _data;
//     sdata(size_t xc) : _xs(xc) {}
//     ~sdata() {
//         cout << "~sdata()" << endl;
//     }
//     void init() {
//         _data = shared_ptr<float[]>(new float[_xs]);
//     }
//     void set(size_t loc, float val) {
//         _data[loc] = val;
//     }
//     void show() {
//         for (int i = 0; i < _xs; i++)
//             cout << _data[i] << " ";
//         cout << endl;
//     }    
// };

// int
// main ( int argc, char **argv ) {
    // sdata s(10);
    // s.init();
    // s.show();
    // s.set(0, 1.1);
    // s.set(1, 1.2);
    // s.set(2, 1.3);
    // s.show();
    // // s._data.reset(new float[10]);
    // s.show();
    // shared_ptr<float[]> p = s._data;
    // std::destroy_at(&s._data);
    // for (int i = 0; i < 10; i++)
    //         cout << p[i] << " ";
    //     cout << endl;



    // shared_ptr<float[]> p1;
    // p1 = shared_ptr<float[]>(new float[10]);


#include <memory>

int
main ( int argc, char **argv ) {
    std::shared_ptr<float[]> d(new float[argc]);
    return 0;
}