// g++ -std=c++11 test_parse_C_array.cxx

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>

using namespace std;

int main()
{
    string to_parse = "open -a firefox https://www.google.com";
    vector<string> args_vec;
    istringstream iss(to_parse);
    copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(args_vec));

    for (const auto& arg : args_vec) {
        cout << arg << endl;
    }

    char** args;
    args = (char**)malloc((args_vec.size() + 1) * sizeof(*args));

    for (int i = 0; i < args_vec.size(); ++i) {
        cout << "Filling element " << i << " with " << args_vec[i].c_str() << endl;
        args[i] = (char*)malloc(args_vec[i].size() * sizeof(*args[i]));
        strcpy(args[i], args_vec[i].c_str());
        cout << "Filled " << args[i] << endl;
    }
    args[args_vec.size()] = NULL;

    execv(args[0], args);
}
