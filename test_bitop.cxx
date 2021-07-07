#include <iostream>
#include <vector>

using namespace std;

typedef int key_t;

constexpr int kNDET = 540;
constexpr int kNROW = 16;
constexpr int kNCOL = 144;

class Digit
{
   public:
    static int calculateKey(const int det, const int row, const int col)
    {
        return ((det << 12) | (row << 8) | col);
    }
    static int getDetectorFromKey(const int key)
    {
        return (key >> 12) & 0xFFF;
    }
    static int getRowFromKey(const int key)
    {
        return (key >> 8) & 0xF;
    }
    static int getColFromKey(const int key)
    {
        return key & 0xFF;
    }
};

int main()
{
    vector<key_t> keyAccum;
    bool error = false;
    for (int det = 0; det < kNDET; ++det) {
        for (int row = 0; row < kNROW; ++row) {
            for (int col = 0; col < kNCOL; ++col) {
                const key_t key = Digit::calculateKey(det, row, col);
                cout << "KEY(" << det << ", " << row << ", " << col << ") = " << key
                     << "\t reverse key(" << Digit::getDetectorFromKey(key) << ", " << Digit::getRowFromKey(key) << ", " << Digit::getColFromKey(key) << ")"
                     << endl;
                if (det != Digit::getDetectorFromKey(key)) {
                    cout << det << " " << row << " " << col << " had the wrong key " << key;
                    error = true;
                }
                if (row != Digit::getRowFromKey(key)) {
                    cout << det << " " << row << " " << col << " had the wrong key " << key;
                    error = true;
                }
                if (col != Digit::getColFromKey(key)) {
                    cout << det << " " << row << " " << col << " had the wrong key " << key;
                    error = true;
                }
                if (error) {
                    cout << "ERROR" << endl;
                    return 1;
                }
            }
        }
    }
    return 0;
}
