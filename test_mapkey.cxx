#include <iostream>

int main()
{
    uint16_t det; // TRD detector number, 0-539
    uint8_t row;  // pad row, 0-15
    uint8_t col;  // pad within pad row, 0-143

    uint32_t key;
    std::bitset<32> keybits;
    const std::bitset<32> mask_det = 0xFFFF0000;
    const std::bitset<32> mask_row = 0x0000FF00;
    const std::bitset<32> mask_col = 0x000000FF;

    for (det = 539; det < 540; det++) {
        for (row = 0; row < 16; row++) {
            for (col = 0; col < 144; col++) {
                key = det << 16 | row << 8 | col;
                keybits = key;
                std::printf("key = %d \t det = %d \t row = %d \t col = %d\n", key, det, row, col);
                std::printf(" keybits = (%s)\n", keybits.to_string().c_str());
                std::printf("mask_det = (%s) \t det = %lu\n", mask_det.to_string().c_str(), ((keybits & mask_det) >> 16).to_ulong());
                std::printf("mask_row = (%s) \t row = %lu\n", mask_row.to_string().c_str(), ((keybits & mask_row) >> 8).to_ulong());
                std::printf("mask_col = (%s) \t col = %lu\n", mask_col.to_string().c_str(), (keybits & mask_col).to_ulong());
                std::printf("------------------------------------------------------------\n");
            }
        }
        break;
    }
    return 0;
}