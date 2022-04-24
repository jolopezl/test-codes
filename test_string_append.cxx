#include <string>
#include <iostream>
using namespace std;
int main(int argc, char** argv) {
    string all;
    all = "Hi, ";
    all = all.append(argv[1]);
    cout << all << endl;
    return 0;
}
