#include <vector>
#include <iostream>

using namespace std;

void do_something(vector<int>& in)
{
    vector<int> out(1e9);
    for (auto& v : out) {
        v = 1;
    }
    // in.resize(100);
    // in.assign(out.begin(), out.end());
    in = out;
}

int main()
{
    vector<int> in(10);

    for (const auto& v : in) {
        cout << v << " ";
    }
    cout << endl;

    do_something(in);

    // for (const auto &v : in) {
    //     cout << v << " ";
    // }

    // cout << endl;

    return 0;
}