#include <iostream>
#include <string>

using namespace std;

int getSectorNumber(string& s)
{
    size_t found = s.find("BSEGMO");
    if (found != string::npos) {
        string str1 = s.substr(found);
        cout << str1 << endl;
        string str2 = str1.substr(6, 2);
        cout << "sector: " << str2 << ", and sector number: " << stoi(str2) << endl;
    }
    return 0;
}

int main()
{
    string path1 = "/cave_1/barrel_1/B077_1/BSEGMO";
    string path2 = "_1/BTRD";
    string path3 = "_1/UTR1_1/UTS1_1/UTI1_1/UT12_1/UA12_1/UB12_1/UJ12_1";

    for (int i = 0; i < 18; ++i) {
        string path = path1 + to_string(i) + path2 + to_string(i) + path3;
        getSectorNumber(path);
    }

    return 0;
}