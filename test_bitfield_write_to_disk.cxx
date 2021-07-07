#include <iostream>

#include <TObject.h>

using namespace std;

class DigitIndexUInt : public TObject
{
   public:
    DigitIndex() = default;
    ~DigitIndex() = default;
    DigitIndex(const int det, const int row, const int pad, const int index)
      : mDetector(det), mRow(row), mPad(pad) {}
    DigitIndex(const DigitIndex&) = default;
    // Modifiers
    void setDetector(int det) { mDetector = det; }
    void setRow(int row) { mRow = row; }
    void setPad(int pad) { mPad = pad; }
    // Get methods
    int getDetector() const { return mDetector; }
    int getRow() const { return mRow; }
    int getPad() const { return mPad; }

   private:
    std::uint16_t mDetector; // 10 TRD detector number, 0-539
    std::uint8_t mRow;       // 4 pad row, 0-15
    std::uint8_t mPad;       // 8 pad within pad row, 0-14
};

class DigitIndexBitField : public TObject
{
   public:
    DigitIndex() = default;
    ~DigitIndex() = default;
    DigitIndex(const int det, const int row, const int pad, const int index)
      : mDetector(det), mRow(row), mPad(pad) {}
    DigitIndex(const DigitIndex&) = default;
    // Modifiers
    void setDetector(int det) { mDetector = det; }
    void setRow(int row) { mRow = row; }
    void setPad(int pad) { mPad = pad; }
    // Get methods
    int getDetector() const { return mDetector; }
    int getRow() const { return mRow; }
    int getPad() const { return mPad; }

   private:
    union {
        uint32_t word = 0x0;
        struct
        {
            uint32_t mDetector : 10; // 10 TRD detector number, 0-539
            uint32_t mRow : 4;       // 4 pad row, 0-15
            uint32_t mPad : 8;       // 8 pad within pad row, 0-14
        };
    };
};

int main()
{
    // Test ROOT I/O

    return 0;
}
