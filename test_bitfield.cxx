#include <iostream>

using namespace std;

class DigitIndex
{
   public:
    DigitIndex() = default;
    ~DigitIndex() = default;
    DigitIndex(const int det, const int row, const int pad, const int index)
      : mDetector(det), mRow(row), mPad(pad), mIndex(index) {}
    DigitIndex(const DigitIndex&) = default;
    // Modifiers
    void setDetector(int det) { mDetector = det; }
    void setRow(int row) { mRow = row; }
    void setPad(int pad) { mPad = pad; }
    void setIndex(int index) { mIndex = index; }
    // Get methods
    int getDetector() const { return mDetector; }
    int getRow() const { return mRow; }
    int getPad() const { return mPad; }
    int getIndex() const { return mIndex; }

   private:
    union {
        uint32_t word = 0x0;
        struct
        {
            uint32_t mDetector : 10; // 10 TRD detector number, 0-539
            uint32_t mRow : 4;       // 4 pad row, 0-15
            uint32_t mPad : 8;       // 8 pad within pad row, 0-14
            uint32_t mIndex : 26;    // 26 index of first time-bin data within adc_data array, max value 540*16*144*30=37324800, needs 26 bits
        };
    };
};

int main()
{
    DigitIndex di;
    di.setDetector(139);
    di.setRow(2);
    di.setPad(7);
    di.setIndex(37324800);
    cout << "detector number " << di.getDetector() << endl;
    cout << "row number      " << di.getRow() << endl;
    cout << "pad number      " << di.getPad() << endl;
    cout << "index number    " << di.getIndex() << endl;

    for (int i = 0; i < 540; ++i) {
        di.setDetector(i);
        if (di.getDetector() != i) {
            cout << "Problems here at " << i << endl;
        }
    }

    for (int i = 0; i < 16; ++i) {
        di.setRow(i);
        if (di.getRow() != i) {
            cout << "Problems here at " << i << endl;
        }
    }

    for (int i = 0; i < 15; ++i) {
        di.setPad(i);
        if (di.getPad() != i) {
            cout << "Problems here at " << i << endl;
        }
    }

    for (int i = 0; i <= 37324800; ++i) {
        di.setIndex(i);
        if (di.getIndex() != i) {
            cout << "Problems here at index " << i << endl;
        }
    }

    // Testing bit field initialization
    cout << "Testing initialization 1" << endl;
    DigitIndex di1;
    cout << di1.getDetector() << endl;
    cout << di1.getRow() << endl;
    cout << di1.getPad() << endl;
    cout << di1.getIndex() << endl;

    cout << "Testing initialization 2" << endl;
    DigitIndex di2(539, 15, 14, 37324800);
    cout << di2.getDetector() << endl;
    cout << di2.getRow() << endl;
    cout << di2.getPad() << endl;
    cout << di2.getIndex() << endl;

    return 0;
}
