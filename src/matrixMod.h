#include <stdint.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
MatrixPanel_I2S_DMA *dma_display = nullptr;

uint16_t myBLACK, myWHITE, myRED, myGREEN, myBLUE;
const uint8_t font[36][5] = {
    {0x7E, 0x11, 0x11, 0x11, 0x7E}, // A
    {0x7F, 0x49, 0x49, 0x49, 0x36}, // B
    {0x3E, 0x41, 0x41, 0x41, 0x22}, // C
    {0x7F, 0x41, 0x41, 0x41, 0x3E}, // D
    {0x7F, 0x49, 0x49, 0x49, 0x41}, // E
    {0x7F, 0x09, 0x09, 0x09, 0x01}, // F
    {0x3E, 0x41, 0x49, 0x49, 0x7A}, // G
    {0x7F, 0x08, 0x08, 0x08, 0x7F}, // H
    {0x41, 0x41, 0x7F, 0x41, 0x41}, // I
    {0x20, 0x40, 0x41, 0x3F, 0x01}, // J
    {0x7F, 0x08, 0x14, 0x22, 0x41}, // K
    {0x7F, 0x40, 0x40, 0x40, 0x40}, // L
    {0x7F, 0x02, 0x0C, 0x02, 0x7F}, // M
    {0x7F, 0x04, 0x08, 0x10, 0x7F}, // N
    {0x3E, 0x41, 0x41, 0x41, 0x3E}, // O
    {0x7F, 0x09, 0x09, 0x09, 0x06}, // P
    {0x3E, 0x41, 0x51, 0x21, 0x5E}, // Q
    {0x7F, 0x09, 0x19, 0x29, 0x46}, // R
    {0x46, 0x49, 0x49, 0x49, 0x31}, // S
    {0x01, 0x01, 0x7F, 0x01, 0x01}, // T
    {0x3F, 0x40, 0x40, 0x40, 0x3F}, // U
    {0x1F, 0x20, 0x40, 0x20, 0x1F}, // V
    {0x3F, 0x40, 0x38, 0x40, 0x3F}, // W
    {0x63, 0x14, 0x08, 0x14, 0x63}, // X
    {0x07, 0x08, 0x70, 0x08, 0x07}, // Y
    {0x61, 0x51, 0x49, 0x45, 0x43}, // Z
    {0x3E, 0x51, 0x49, 0x45, 0x3E}, // 0
    {0x00, 0x42, 0x7F, 0x40, 0x00}, // 1
    {0x62, 0x51, 0x49, 0x49, 0x46}, // 2
    {0x22, 0x41, 0x49, 0x49, 0x36}, // 3
    {0x18, 0x14, 0x12, 0x7F, 0x10}, // 4
    {0x27, 0x45, 0x45, 0x45, 0x39}, // 5
    {0x3C, 0x4A, 0x49, 0x49, 0x30}, // 6
    {0x01, 0x01, 0x7F, 0x01, 0x01}, // 7
    {0x36, 0x49, 0x49, 0x49, 0x36}, // 8
    {0x06, 0x49, 0x49, 0x29, 0x1E}  // 9
};
const uint8_t smallFont[36][3] = {
    {0x1F, 0x05, 0x1F}, // A
    {0x1F, 0x15, 0x0A}, // B
    {0x0E, 0x11, 0x11}, // C
    {0x1F, 0x11, 0x0E}, // D
    {0x1F, 0x15, 0x15}, // E
    {0x1F, 0x05, 0x05}, // F
    {0x0E, 0x11, 0x1D}, // G
    {0x1F, 0x04, 0x1F}, // H
    {0x11, 0x1F, 0x11}, // I
    {0x08, 0x10, 0x0F}, // J
    {0x1F, 0x04, 0x1B}, // K
    {0x1F, 0x10, 0x10}, // L
    {0x1F, 0x06, 0x1F}, // M
    {0x1F, 0x0E, 0x1F}, // N
    {0x0E, 0x11, 0x0E}, // O
    {0x1F, 0x05, 0x02}, // P
    {0x0E, 0x11, 0x1E}, // Q
    {0x1F, 0x05, 0x1A}, // R
    {0x12, 0x15, 0x09}, // S
    {0x01, 0x1F, 0x01}, // T
    {0x0F, 0x10, 0x0F}, // U
    {0x07, 0x18, 0x07}, // V
    {0x1F, 0x0C, 0x1F}, // W
    {0x1B, 0x04, 0x1B}, // X
    {0x03, 0x1C, 0x03}, // Y
    {0x19, 0x15, 0x13}, // Z
    {0x0E, 0x11, 0x0E}, // 0
    {0x00, 0x1F, 0x00}, // 1
    {0x19, 0x15, 0x12}, // 2
    {0x11, 0x15, 0x0A}, // 3
    {0x07, 0x04, 0x1F}, // 4
    {0x17, 0x15, 0x09}, // 5
    {0x1E, 0x15, 0x1D}, // 6
    {0x01, 0x01, 0x1F}, // 7
    {0x1F, 0x15, 0x1F}, // 8
    {0x17, 0x15, 0x0F}  // 9
};
const uint8_t font4x6[36][4] = {
    {0x1E, 0x9, 0x9, 0x1E},   // A
    {0x1F, 0x15, 0x15, 0x0A}, // B
    {0x0E, 0x11, 0x11, 0x11}, // C
    {0x1F, 0x11, 0x11, 0x0E}, // D
    {0x1F, 0x15, 0x15, 0x15}, // E
    {0x1F, 0x05, 0x05, 0x05}, // F
    {0x0E, 0x11, 0x15, 0x0D}, // G
    {0x1F, 0x04, 0x04, 0x1F}, // H
    {0x11, 0x1F, 0x11, 0x00}, // I
    {0x08, 0x10, 0x10, 0x0F}, // J
    {0x1F, 0x04, 0x0A, 0x11}, // K
    {0x1F, 0x10, 0x10, 0x10}, // L
    {0x1F, 0x02, 0x04, 0x02}, // M
    {0x1F, 0x02, 0x04, 0x1F}, // N
    {0x0E, 0x11, 0x11, 0x0E}, // O
    {0x1F, 0x05, 0x05, 0x02}, // P
    {0x0E, 0x11, 0x19, 0x16}, // Q
    {0x1F, 0x05, 0x05, 0x1A}, // R
    {0x12, 0x15, 0x15, 0x09}, // S
    {0x01, 0x1F, 0x01, 0x01}, // T
    {0x0F, 0x10, 0x10, 0x0F}, // U
    {0x07, 0x18, 0x18, 0x07}, // V
    {0x1F, 0x08, 0x08, 0x1F}, // W
    {0x1B, 0x04, 0x04, 0x1B}, // X
    {0x03, 0x1C, 0x1C, 0x03}, // Y
    {0x19, 0x15, 0x15, 0x13}, // Z
    {0x0E, 0x11, 0x11, 0x0E}, // 0
    {0x00, 0x12, 0x1F, 0x10}, // 1
    {0x19, 0x15, 0x15, 0x12}, // 2
    {0x11, 0x15, 0x15, 0x0A}, // 3
    {0x07, 0x04, 0x1F, 0x04}, // 4
    {0x17, 0x15, 0x15, 0x09}, // 5
    {0x0E, 0x15, 0x15, 0x09}, // 6
    {0x01, 0x01, 0x1F, 0x01}, // 7
    {0x0A, 0x15, 0x15, 0x0A}, // 8
    {0x12, 0x15, 0x15, 0x0E}  // 9
};
const uint8_t font5x5[36][5] = {
    {0x1E, 0x05, 0x05, 0x05, 0x1E}, // A
    {0x1F, 0x15, 0x15, 0x15, 0x0A}, // B
    {0x0E, 0x11, 0x11, 0x11, 0x00}, // C
    {0x1F, 0x11, 0x11, 0x11, 0x0E}, // D
    {0x1F, 0x15, 0x15, 0x15, 0x11}, // E
    {0x1F, 0x05, 0x05, 0x05, 0x01}, // F
    {0x0E, 0x11, 0x15, 0x15, 0x1C}, // G
    {0x1F, 0x04, 0x04, 0x04, 0x1F}, // H
    {0x11, 0x1F, 0x11, 0x11, 0x00}, // I
    {0x10, 0x10, 0x11, 0x11, 0x0F}, // J
    {0x1F, 0x04, 0x0A, 0x11, 0x00}, // K
    {0x1F, 0x10, 0x10, 0x10, 0x10}, // L
    {0x1F, 0x02, 0x04, 0x02, 0x1F}, // M
    {0x1F, 0x02, 0x04, 0x08, 0x1F}, // N
    {0x0E, 0x11, 0x11, 0x11, 0x0E}, // O
    {0x1F, 0x05, 0x05, 0x05, 0x02}, // P
    {0x0E, 0x11, 0x11, 0x19, 0x1E}, // Q
    {0x1F, 0x05, 0x05, 0x0D, 0x12}, // R
    {0x12, 0x15, 0x15, 0x15, 0x09}, // S
    {0x01, 0x01, 0x1F, 0x01, 0x01}, // T
    {0x0F, 0x10, 0x10, 0x10, 0x0F}, // U
    {0x07, 0x08, 0x10, 0x08, 0x07}, // V
    {0x1F, 0x08, 0x04, 0x08, 0x1F}, // W
    {0x11, 0x0A, 0x04, 0x0A, 0x11}, // X
    {0x01, 0x02, 0x1C, 0x02, 0x01}, // Y
    {0x11, 0x19, 0x15, 0x13, 0x11}, // Z
    {0x0E, 0x11, 0x11, 0x11, 0x0E}, // 0
    {0x00, 0x12, 0x1F, 0x10, 0x00}, // 1
    {0x19, 0x15, 0x15, 0x15, 0x12}, // 2
    {0x11, 0x15, 0x15, 0x15, 0x0A}, // 3
    {0x07, 0x04, 0x1F, 0x04, 0x04}, // 4
    {0x17, 0x15, 0x15, 0x15, 0x09}, // 5
    {0x1E, 0x15, 0x15, 0x15, 0x08}, // 6
    {0x01, 0x01, 0x1D, 0x03, 0x01}, // 7
    {0x0A, 0x15, 0x15, 0x15, 0x0A}, // 8
    {0x02, 0x15, 0x15, 0x15, 0x0E}  // 9
};
const uint8_t font7x8[36][7] = {
    {0x7E, 0x11, 0x11, 0x11, 0x7E, 0x00, 0x00}, // A
    {0x7F, 0x49, 0x49, 0x49, 0x36, 0x00, 0x00}, // B
    {0x3E, 0x41, 0x41, 0x41, 0x22, 0x00, 0x00}, // C
    {0x7F, 0x41, 0x41, 0x41, 0x3E, 0x00, 0x00}, // D
    {0x7F, 0x49, 0x49, 0x49, 0x41, 0x00, 0x00}, // E
    {0x7F, 0x09, 0x09, 0x09, 0x01, 0x00, 0x00}, // F
    {0x3E, 0x41, 0x49, 0x49, 0x7A, 0x00, 0x00}, // G
    {0x7F, 0x08, 0x08, 0x08, 0x7F, 0x00, 0x00}, // H
    {0x41, 0x41, 0x7F, 0x41, 0x41, 0x00, 0x00}, // I
    {0x20, 0x40, 0x41, 0x3F, 0x01, 0x00, 0x00}, // J
    {0x7F, 0x08, 0x14, 0x22, 0x41, 0x00, 0x00}, // K
    {0x7F, 0x40, 0x40, 0x40, 0x00, 0x00, 0x00}, // L
    {0x7F, 0x02, 0x0C, 0x02, 0x7F, 0x00, 0x00}, // M
    {0x7F, 0x04, 0x08, 0x10, 0x7F, 0x00, 0x00}, // N
    {0x3E, 0x41, 0x41, 0x41, 0x3E, 0x00, 0x00}, // O
    {0x7F, 0x09, 0x09, 0x09, 0x06, 0x00, 0x00}, // P
    {0x3E, 0x41, 0x51, 0x21, 0x5E, 0x00, 0x00}, // Q
    {0x7F, 0x09, 0x19, 0x29, 0x46, 0x00, 0x00}, // R
    {0x46, 0x49, 0x49, 0x49, 0x31, 0x00, 0x00}, // S
    {0x01, 0x01, 0x7F, 0x01, 0x01, 0x00, 0x00}, // T
    {0x3F, 0x40, 0x40, 0x40, 0x3F, 0x00, 0x00}, // U
    {0x1F, 0x20, 0x40, 0x20, 0x1F, 0x00, 0x00}, // V
    {0x7F, 0x20, 0x10, 0x08, 0x10, 0x20, 0x7F}, // W
    {0x63, 0x14, 0x08, 0x14, 0x63, 0x00, 0x00}, // X
    {0x07, 0x08, 0x70, 0x08, 0x07, 0x00, 0x00}, // Y
    {0x61, 0x51, 0x49, 0x45, 0x43, 0x00, 0x00}, // Z
    {0x3E, 0x51, 0x49, 0x45, 0x3E, 0x00, 0x00}, // 0
    {0x00, 0x42, 0x7F, 0x40, 0x00, 0x00, 0x00}, // 1
    {0x62, 0x51, 0x49, 0x49, 0x46, 0x00, 0x00}, // 2
    {0x22, 0x41, 0x49, 0x49, 0x36, 0x00, 0x00}, // 3
    {0x18, 0x14, 0x12, 0x7F, 0x10, 0x00, 0x00}, // 4
    {0x27, 0x45, 0x45, 0x45, 0x39, 0x00, 0x00}, // 5
    {0x3C, 0x4A, 0x49, 0x49, 0x30, 0x00, 0x00}, // 6
    {0x01, 0x01, 0x7F, 0x01, 0x01, 0x00, 0x00}, // 7
    {0x36, 0x49, 0x49, 0x49, 0x36, 0x00, 0x00}, // 8
    {0x06, 0x49, 0x49, 0x29, 0x1E, 0x00, 0x00}  // 9
};
const uint16_t font9x8[36][9] = {
    {0x03FE, 0x0411, 0x0411, 0x0411, 0x0411, 0x0411, 0x03FE, 0x0000, 0x0000}, // A
    {0x07FF, 0x0489, 0x0489, 0x0489, 0x0489, 0x0489, 0x0376, 0x0000, 0x0000}, // B
    {0x03FE, 0x0401, 0x0401, 0x0401, 0x0401, 0x0401, 0x0202, 0x0000, 0x0000}, // C
    {0x07FF, 0x0401, 0x0401, 0x0401, 0x0401, 0x0401, 0x03FE, 0x0000, 0x0000}, // D
    {0x07FF, 0x0489, 0x0489, 0x0489, 0x0489, 0x0489, 0x0401, 0x0000, 0x0000}, // E
    {0x07FF, 0x0089, 0x0089, 0x0089, 0x0089, 0x0089, 0x0001, 0x0000, 0x0000}, // F
    {0x03FE, 0x0401, 0x0401, 0x0401, 0x0481, 0x0481, 0x0782, 0x0000, 0x0000}, // G
    {0x07FF, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x07FF, 0x0000, 0x0000}, // H
    {0x0401, 0x0401, 0x07FF, 0x0401, 0x0401, 0x0000, 0x0000, 0x0000, 0x0000}, // I
    {0x0200, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x03FF, 0x0000, 0x0000}, // J
    {0x07FF, 0x0080, 0x0140, 0x0220, 0x0410, 0x0000, 0x0000, 0x0000, 0x0000}, // K
    {0x07FF, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x0000, 0x0000, 0x0000}, // L
    {0x07FF, 0x0006, 0x0038, 0x00C0, 0x0038, 0x0006, 0x07FF, 0x0000, 0x0000}, // M
    {0x07FF, 0x0006, 0x0018, 0x0060, 0x0180, 0x07FF, 0x0000, 0x0000, 0x0000}, // N
    {0x03FE, 0x0401, 0x0401, 0x0401, 0x0401, 0x0401, 0x03FE, 0x0000, 0x0000}, // O
    {0x07FF, 0x0089, 0x0089, 0x0089, 0x0089, 0x0089, 0x0076, 0x0000, 0x0000}, // P
    {0x03FE, 0x0401, 0x0401, 0x0501, 0x0601, 0x0401, 0x07FE, 0x0000, 0x0000}, // Q
    {0x07FF, 0x0089, 0x0089, 0x0089, 0x0189, 0x0289, 0x0476, 0x0000, 0x0000}, // R
    {0x0206, 0x0489, 0x0489, 0x0489, 0x0489, 0x0489, 0x0372, 0x0000, 0x0000}, // S
    {0x0001, 0x0001, 0x07FF, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000}, // T
    {0x03FF, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x03FF, 0x0000, 0x0000}, // U
    {0x01FF, 0x0200, 0x0400, 0x0400, 0x0400, 0x0200, 0x01FF, 0x0000, 0x0000}, // V
    {0x07FF, 0x0200, 0x0180, 0x0200, 0x07FF, 0x0000, 0x0000, 0x0000, 0x0000}, // W
    {0x061C, 0x0122, 0x00C0, 0x00C0, 0x0122, 0x061C, 0x0000, 0x0000, 0x0000}, // X
    {0x001F, 0x0020, 0x07C0, 0x0020, 0x001F, 0x0000, 0x0000, 0x0000, 0x0000}, // Y
    {0x0611, 0x0511, 0x0491, 0x0451, 0x0431, 0x0000, 0x0000, 0x0000, 0x0000}, // Z
    {0x03FE, 0x0441, 0x0481, 0x0481, 0x0501, 0x03FE, 0x0000, 0x0000, 0x0000}, // 0
    {0x0402, 0x0401, 0x07FF, 0x0400, 0x0400, 0x0000, 0x0000, 0x0000, 0x0000}, // 1
    {0x0603, 0x0511, 0x0491, 0x0451, 0x043E, 0x0000, 0x0000, 0x0000, 0x0000}, // 2
    {0x0202, 0x0401, 0x0449, 0x0449, 0x03B6, 0x0000, 0x0000, 0x0000, 0x0000}, // 3
    {0x0300, 0x0280, 0x0240, 0x07FF, 0x0200, 0x0000, 0x0000, 0x0000, 0x0000}, // 4
    {0x020F, 0x0445, 0x0445, 0x0445, 0x0439, 0x0000, 0x0000, 0x0000, 0x0000}, // 5
    {0x03FC, 0x044A, 0x0449, 0x0449, 0x0430, 0x0000, 0x0000, 0x0000, 0x0000}, // 6
    {0x0001, 0x0001, 0x07F1, 0x0011, 0x000F, 0x0000, 0x0000, 0x0000, 0x0000}, // 7
    {0x03F6, 0x0449, 0x0449, 0x0449, 0x03F6, 0x0000, 0x0000, 0x0000, 0x0000}, // 8
    {0x007E, 0x0489, 0x0489, 0x0489, 0x03F2, 0x0000, 0x0000, 0x0000, 0x0000}  // 9
};
// const uint8_t font5x6[36][5] = {
//     {0x1E, 0x05, 0x05, 0x05, 0x1E}, // A
//     {0x1F, 0x15, 0x15, 0x15, 0x0A}, // B
//     {0x1E, 0x11, 0x11, 0x11, 0x0A}, // C
//     {0x1F, 0x11, 0x11, 0x11, 0x0E}, // D
//     {0x1F, 0x15, 0x15, 0x15, 0x11}, // E
//     {0x1F, 0x05, 0x05, 0x05, 0x01}, // F
//     {0x1E, 0x11, 0x15, 0x15, 0x1D}, // G
//     {0x1F, 0x04, 0x04, 0x04, 0x1F}, // H
//     {0x11, 0x11, 0x1F, 0x11, 0x11}, // I
//     {0x08, 0x10, 0x10, 0x10, 0x0F}, // J
//     {0x1F, 0x04, 0x0A, 0x11, 0x00}, // K
//     {0x1F, 0x10, 0x10, 0x10, 0x10}, // L
//     {0x1F, 0x02, 0x04, 0x02, 0x1F}, // M
//     {0x1F, 0x02, 0x04, 0x08, 0x1F}, // N
//     {0x1E, 0x11, 0x11, 0x11, 0x1E}, // O
//     {0x1F, 0x05, 0x05, 0x05, 0x02}, // P
//     {0x1E, 0x11, 0x19, 0x11, 0x1E}, // Q
//     {0x1F, 0x05, 0x0D, 0x15, 0x02}, // R
//     {0x12, 0x15, 0x15, 0x15, 0x09}, // S
//     {0x01, 0x01, 0x1F, 0x01, 0x01}, // T
//     {0x0F, 0x10, 0x10, 0x10, 0x0F}, // U
//     {0x07, 0x08, 0x10, 0x08, 0x07}, // V
//     {0x1F, 0x08, 0x04, 0x08, 0x1F}, // W
//     {0x11, 0x0A, 0x04, 0x0A, 0x11}, // X
//     {0x01, 0x02, 0x1C, 0x02, 0x01}, // Y
//     {0x11, 0x19, 0x15, 0x13, 0x11}, // Z
//     {0x1E, 0x11, 0x11, 0x11, 0x1E}, // 0
//     {0x00, 0x10, 0x1F, 0x00, 0x00}, // 1
//     {0x19, 0x15, 0x15, 0x15, 0x12}, // 2
//     {0x11, 0x15, 0x15, 0x15, 0x0A}, // 3
//     {0x07, 0x04, 0x04, 0x1F, 0x04}, // 4
//     {0x17, 0x15, 0x15, 0x15, 0x09}, // 5
//     {0x1E, 0x15, 0x15, 0x15, 0x09}, // 6
//     {0x01, 0x01, 0x01, 0x01, 0x1F}, // 7
//     {0x1A, 0x15, 0x15, 0x15, 0x1A}, // 8
//     {0x12, 0x15, 0x15, 0x15, 0x1E}  // 9
// };
const uint8_t font5x6[36][5] = {
    {0x1E, 0x11, 0x1F, 0x11, 0x11}, // A
    {0x1F, 0x15, 0x1F, 0x15, 0x1F}, // B
    {0x1E, 0x11, 0x10, 0x11, 0x1E}, // C
    {0x1F, 0x11, 0x11, 0x11, 0x1F}, // D
    {0x1F, 0x14, 0x1C, 0x14, 0x1F}, // E
    {0x1F, 0x14, 0x1C, 0x14, 0x10}, // F
    {0x1E, 0x11, 0x13, 0x11, 0x1E}, // G
    {0x11, 0x11, 0x1F, 0x11, 0x11}, // H
    {0x1F, 0x04, 0x04, 0x04, 0x1F}, // I
    {0x07, 0x02, 0x02, 0x12, 0x1E}, // J
    {0x11, 0x12, 0x1C, 0x12, 0x11}, // K
    {0x10, 0x10, 0x10, 0x10, 0x1F}, // L
    {0x11, 0x1B, 0x15, 0x11, 0x11}, // M
    {0x11, 0x19, 0x15, 0x13, 0x11}, // N
    {0x1E, 0x11, 0x11, 0x11, 0x1E}, // O
    {0x1F, 0x11, 0x1F, 0x10, 0x10}, // P
    {0x1E, 0x11, 0x15, 0x12, 0x1D}, // Q
    {0x1F, 0x11, 0x1F, 0x12, 0x11}, // R
    {0x1E, 0x10, 0x1E, 0x01, 0x1E}, // S
    {0x1F, 0x04, 0x04, 0x04, 0x04}, // T
    {0x11, 0x11, 0x11, 0x11, 0x1F}, // U
    {0x11, 0x11, 0x11, 0x0A, 0x04}, // V
    {0x11, 0x11, 0x15, 0x1B, 0x11}, // W
    {0x11, 0x0A, 0x04, 0x0A, 0x11}, // X
    {0x11, 0x11, 0x1F, 0x04, 0x04}, // Y
    {0x1F, 0x02, 0x04, 0x08, 0x1F}, // Z
    {0x1E, 0x15, 0x15, 0x15, 0x1E}, // 0
    {0x04, 0x0C, 0x04, 0x04, 0x1F}, // 1
    {0x1F, 0x02, 0x1E, 0x10, 0x1F}, // 2
    {0x1F, 0x02, 0x1E, 0x02, 0x1F}, // 3
    {0x11, 0x11, 0x1F, 0x02, 0x02}, // 4
    {0x1F, 0x10, 0x1E, 0x02, 0x1E}, // 5
    {0x1E, 0x10, 0x1E, 0x11, 0x1E}, // 6
    {0x1F, 0x02, 0x04, 0x08, 0x10}, // 7
    {0x1E, 0x11, 0x1E, 0x11, 0x1E}, // 8
    {0x1E, 0x11, 0x1E, 0x02, 0x1E}  // 9
};
const uint8_t font5x7[36][5] = {
    {0x7C, 0x12, 0x11, 0x12, 0x7C}, // A
    {0x7F, 0x49, 0x49, 0x49, 0x36}, // B
    {0x3E, 0x41, 0x41, 0x41, 0x22}, // C
    {0x7F, 0x41, 0x41, 0x22, 0x1C}, // D
    {0x7F, 0x49, 0x49, 0x49, 0x41}, // E
    {0x7F, 0x09, 0x09, 0x09, 0x01}, // F
    {0x3E, 0x41, 0x49, 0x49, 0x7A}, // G
    {0x7F, 0x08, 0x08, 0x08, 0x7F}, // H
    {0x41, 0x7F, 0x41, 0x00, 0x00}, // I
    {0x20, 0x40, 0x41, 0x3F, 0x01}, // J
    {0x7F, 0x08, 0x14, 0x22, 0x41}, // K
    {0x7F, 0x40, 0x40, 0x40, 0x40}, // L
    {0x7F, 0x02, 0x04, 0x02, 0x7F}, // M
    {0x7F, 0x02, 0x04, 0x08, 0x7F}, // N
    {0x3E, 0x41, 0x41, 0x41, 0x3E}, // O
    {0x7F, 0x09, 0x09, 0x09, 0x06}, // P
    {0x3E, 0x41, 0x51, 0x21, 0x5E}, // Q
    {0x7F, 0x09, 0x19, 0x29, 0x46}, // R
    {0x46, 0x49, 0x49, 0x49, 0x31}, // S
    {0x01, 0x01, 0x7F, 0x01, 0x01}, // T
    {0x3F, 0x40, 0x40, 0x40, 0x3F}, // U
    {0x1F, 0x20, 0x40, 0x20, 0x1F}, // V
    {0x7F, 0x20, 0x18, 0x20, 0x7F}, // W
    {0x63, 0x14, 0x08, 0x14, 0x63}, // X
    {0x03, 0x04, 0x78, 0x04, 0x03}, // Y
    {0x61, 0x51, 0x49, 0x45, 0x43}, // Z
    {0x3E, 0x41, 0x41, 0x41, 0x3E}, // 0
    {0x44, 0x42, 0x7F, 0x40, 0x40}, // 1
    {0x62, 0x51, 0x51, 0x49, 0x46}, // 2
    {0x41, 0x41, 0x49, 0x49, 0x36}, // 3
    {0x0F, 0x08, 0x08, 0x08, 0x7F}, // 4
    {0x4F, 0x49, 0x49, 0x49, 0x31}, // 5
    {0x3E, 0x49, 0x49, 0x49, 0x30}, // 6
    {0x01, 0x01, 0x71, 0x09, 0x07}, // 7
    {0x36, 0x49, 0x49, 0x49, 0x36}, // 8
    {0x06, 0x49, 0x49, 0x49, 0x3E}  // 9
};

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
// From: https://gist.github.com/davidegironi/3144efdc6d67e5df55438cc3cba613c8

uint16_t colorWheel(uint8_t pos)
{
  if (pos < 85)
  {
    return dma_display->color565(pos * 3, 255 - pos * 3, 0);
  }
  else if (pos < 170)
  {
    pos -= 85;
    return dma_display->color565(255 - pos * 3, 0, pos * 3);
  }
  else
  {
    pos -= 170;
    return dma_display->color565(0, pos * 3, 255 - pos * 3);
  }
}
void drawText(int colorWheelOffset)
{

  // draw text with a rotating colour
  dma_display->setTextSize(1);     // size 1 == 8 pixels high
  dma_display->setTextWrap(false); // Don't wrap at end of line - will do ourselves

  dma_display->setCursor(5, 0); // start at top left, with 8 pixel of spacing
  uint8_t w = 0;
  const char *str = "ESP32";
  for (w = 0; w < strlen(str); w++)
  {
    dma_display->setTextColor(colorWheel((w * 32) + colorWheelOffset));
    dma_display->print(str[w]);
  }

  dma_display->println();

  dma_display->println();

  dma_display->setTextColor(dma_display->color444(15, 15, 15));
  dma_display->println("LED");
  // Jump a half character
  dma_display->setCursor(34, 24);
  dma_display->setTextColor(dma_display->color444(0, 15, 15));
  dma_display->print("*");
  dma_display->setTextColor(dma_display->color444(15, 0, 0));
  dma_display->print('R');
  dma_display->setTextColor(dma_display->color444(0, 15, 0));
  dma_display->print('G');
  dma_display->setTextColor(dma_display->color444(0, 0, 15));
  dma_display->print("B");
  dma_display->setTextColor(dma_display->color444(15, 0, 8));
  dma_display->println("*");
}

void errdrawPixel(int x, int y, uint16_t color)
{
  // Hitung posisi pixel berdasarkan susunan 32x64
  int panelX = x;
  int panelY = y;
  int panelIndex = 0;

  if (y <= 7)
  {
    // panelY = y + 8;
    panelX = x + 64;
    dma_display->drawPixel(panelX, panelY, color);
  }
  else if (y <= 15)
  {
    panelY = y - 8;
    dma_display->drawPixel(panelX, panelY, color);
  }
  else if (y <= 23)
  {
    panelY = y - 8;
    panelX = x + 64;
    dma_display->drawPixel(panelX, panelY, color);
  }
  else if (y <= 31)
  {
    panelY = y - 16;
    dma_display->drawPixel(panelX, panelY, color);
  }
}
////////////////////////////
// Fungsi untuk menggambar pixel pada konfigurasi 32x64

// Fungsi untuk menggambar satu karakter dengan ukuran yang dapat diubah
void drawChar(char c, int x, int y, uint16_t color, int scale = 1)
{
  if ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
  {
    const uint8_t *bitmap = (c >= 'A') ? font[c - 'A'] : font[c - '0' + 26];

    for (int col = 0; col < 5; col++)
    {
      for (int row = 0; row < 7; row++)
      {
        if (bitmap[col] & (1 << row))
        {
          // Gambar piksel dengan ukuran diperbesar sesuai skala
          for (int dx = 0; dx < scale; dx++)
          {
            for (int dy = 0; dy < scale; dy++)
            {
              errdrawPixel(x + col * scale + dx, y + row * scale + dy, color);
            }
          }
        }
      }
    }
  }
}
void drawChar4x6(char c, int x, int y, uint16_t color)
{
  if ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
  {
    const uint8_t *bitmap = (c >= 'A') ? font4x6[c - 'A'] : font4x6[c - '0' + 26];

    for (int col = 0; col < 4; col++)
    {
      for (int row = 0; row < 6; row++)
      {
        if (bitmap[col] & (1 << row))
        {
          errdrawPixel(x + col, y + row, color);
        }
      }
    }
  }
}
void drawText4x6(String text, int x, int y, uint16_t color)
{
  for (size_t i = 0; i < text.length(); i++)
  {
    drawChar4x6(text[i], x + i * 5, y, color); // Jarak antar karakter adalah 5 piksel
  }
}
void drawSmallChar(char c, int x, int y, uint16_t color)
{
  if ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
  {
    const uint8_t *bitmap = (c >= 'A') ? smallFont[c - 'A'] : smallFont[c - '0' + 26];

    for (int col = 0; col < 3; col++)
    {
      for (int row = 0; row < 5; row++)
      {
        if (bitmap[col] & (1 << row))
        {
          errdrawPixel(x + col, y + row, color);
        }
      }
    }
  }
}
void drawSmallText(String text, int x, int y, uint16_t color)
{
  for (size_t i = 0; i < text.length(); i++)
  {
    drawSmallChar(text[i], x + i * 4, y, color); // Jarak antar karakter adalah 4 piksel
  }
}
void drawChar5x6(char c, int x, int y, uint16_t color)
{
  if ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
  {
    int index = (c >= 'A') ? c - 'A' : c - '0' + 26;
    for (int col = 0; col < 5; col++)
    {
      uint8_t columnData = font5x6[index][col];
      for (int row = 0; row < 6; row++)
      {
        if (columnData & (1 << row))
        {
          errdrawPixel(x + col, y + row, color);
        }
      }
    }
  }
}
void drawChar5x7(char c, int x, int y, uint16_t color)
{
  if ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
  {
    const uint8_t *bitmap = (c >= 'A') ? font5x7[c - 'A'] : font5x7[c - '0' + 26];

    for (int col = 0; col < 5; col++)
    { // 5 columns
      for (int row = 0; row < 7; row++)
      { // 7 rows
        if (bitmap[col] & (1 << row))
        {                                        // Check if the bit is set
          errdrawPixel(x + col, y + row, color); // Replace `errdrawPixel` with your pixel-drawing function
        }
      }
    }
  }
}

// Fungsi untuk menggambar teks dengan ukuran yang dapat diubah
void drawText(String text, int x, int y, uint16_t color, int scale = 1)
{
  for (size_t i = 0; i < text.length(); i++)
  {
    drawChar(text[i], x + i * (5 * scale + scale), y, color, scale); // Spasi antar karakter sesuai skala
  }
}
void drawChar5x5(char c, int x, int y, uint16_t color)
{
  if ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
  {
    const uint8_t *bitmap = (c >= 'A') ? font5x5[c - 'A'] : font5x5[c - '0' + 26];

    for (int col = 0; col < 5; col++)
    {
      for (int row = 0; row < 5; row++)
      {
        if (bitmap[col] & (1 << row))
        {
          errdrawPixel(x + col, y + row, color);
        }
      }
    }
  }
}
void drawText5x5(String text, int x, int y, uint16_t color)
{
  for (size_t i = 0; i < text.length(); i++)
  {
    drawChar5x5(text[i], x + i * 6, y, color); // Jarak antar karakter adalah 6 piksel
  }
}
void scrollText(String text, int speed, uint16_t color)
{
  int textWidth = text.length() * 6; // Lebar total teks dalam piksel
  int panelWidth = 64;               // Lebar panel dalam piksel
  int x = panelWidth;                // Mulai dari luar sisi kanan panel

  while (x > -textWidth)
  {
    dma_display->clearScreen();

    // Gambar teks berjalan
    drawText5x5(text, x, 0, color);

    //  dma_display->show(); // Perbarui layar
    delay(speed); // Kecepatan scrolling

    x--; // Gerakkan teks ke kiri
  }
}
void drawText7x8(String text, int x, int y, uint16_t color)
{
  for (int i = 0; i < text.length(); i++)
  {
    char c = text[i];

    // Cek apakah karakter valid (A-Z atau 0-9)
    if ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
    {
      int charIndex = (c >= 'A') ? c - 'A' : c - '0' + 26;

      // Gambar karakter per piksel
      for (int col = 0; col < 7; col++)
      {
        uint8_t columnData = font7x8[charIndex][col];
        for (int row = 0; row < 8; row++)
        {
          if (columnData & (1 << row))
          {
            errdrawPixel(x + col + i * 8, y + row, color);
          }
        }
      }
    }
  }
}
// void drawChar9x8(char c, int x, int y)
// {
//   if (c >= 'A' && c <= 'Z')
//   {
//     c -= 'A'; // Offset untuk huruf A-Z
//   }
//   else if (c >= '0' && c <= '9')
//   {
//     c = c - '0' + 26; // Offset untuk angka 0-9
//   }
//   else
//   {
//     return; // Abaikan karakter di luar A-Z dan 0-9
//   }
//
//   for (int row = 0; row < 8; row++)
//   {
//     uint16_t rowData = font9x8[c][row];
//     for (int col = 0; col < 9; col++)
//     {
//       if (rowData & (1 << (8 - col)))
//       {
//         drawPixel(x + col, y + row, true); // Nyalakan piksel
//       }
//       else
//       {
//         errdrawPixel(x + col, y + row, false); // Matikan piksel
//       }
//     }
//   }
// }
void drawText9x8(String text, int x, int y, uint16_t color)
{
  for (int i = 0; i < text.length(); i++)
  {
    char c = text[i];

    // Cek apakah karakter valid (A-Z atau 0-9)
    if ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
    {
      int charIndex = (c >= 'A') ? c - 'A' : c - '0' + 26;

      // Gambar karakter per piksel
      for (int col = 0; col < 9; col++)
      {
        uint8_t columnData = font9x8[charIndex][col];
        for (int row = 0; row < 8; row++)
        {
          if (columnData & (1 << row))
          {
            errdrawPixel(x + col + i * 10, y + row, color); // Offset karakter setiap 10 piksel
          }
        }
      }
    }
  }
}
void drawText5x6(String text, int x, int y, uint16_t color)
{
  for (int i = 0; i < text.length(); i++)
  {
    char c = text[i];

    // Hanya mendukung karakter A-Z dan 0-9
    if ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
    {
      const uint8_t *bitmap = (c >= 'A') ? font5x6[c - 'A'] : font5x6[c - '0' + 26];

      for (int col = 0; col < 5; col++)
      { // Lebar 5 piksel
        for (int row = 0; row < 6; row++)
        { // Tinggi 6 piksel
          if (bitmap[col] & (1 << row))
          { // Periksa bit aktif
            errdrawPixel(x + col, y + row, color);
          }
        }
      }
    }

    // Geser posisi x untuk karakter berikutnya
    x += 6; // Tambahkan 5 piksel lebar + 1 piksel jarak antar karakter
  }
}
void drawText5x7(String text, int x, int y, uint16_t color)
{
  int spacing = 1; // Space between characters
  for (int i = 0; i < text.length(); i++)
  {
    char c = text[i];
    drawChar5x7(c, x + (i * (5 + spacing)), y, color);
  }
}
String last1 = "";
String last2 = "";
String last3 = "";
String last4 = ""; 
void drawline(int n, String val)
{

  // dma_display->clearScreen();
  // dma_display->clearScreen();
  for (int i = 0; i < 32; i++)
  {
    errdrawPixel(32, i, myRED);
    delay(1);
  }
  for (int i = 0; i < 64; i++)
  {
    errdrawPixel(i, 16, myRED);
    delay(1);
  }
  //  String val = "WL";
  int geser = 0;

  if (n == 1)
  {
    
    drawText7x8(last1, 15 - (last1.length() * 7 / 2) + geser, 0, dma_display->color565(0, 0, 0));
    drawText7x8(val, 15 - (val.length() * 7 / 2)+ geser, 0, dma_display->color565(255, 255, 255));
    last1 = val;
    // drawText7x8("L", 10 + geser, 0, dma_display->color565(255, 255, 255));
  }
  else if (n == 2)
  {
    drawText7x8(last2, 47 - (last2.length() * 7 / 2)+ geser, 0, dma_display->color565(0, 0, 0));
    drawText7x8(val, 47 - (val.length() * 7 / 2)+ geser, 0, dma_display->color565(255, 255, 255));
    last2 = val;
    // drawText7x8("L", 43 + geser, 0, dma_display->color565(255, 255, 255));
  }
  else if (n == 3)
  {
    drawText7x8(last3, 15 - (last3.length() * 7 / 2)+ geser, 17, dma_display->color565(0, 0, 0));
    drawText7x8(val, 15 - (val.length() * 7 / 2)+ geser, 17, dma_display->color565(255, 255, 255));
    last3 = val;
    // drawText7x8("L", 10 + geser, 17, dma_display->color565(255, 255, 255));
  }
  else if (n == 4)
  {
    drawText7x8(last4, 47 - (last4.length() * 7 / 2)+ geser, 17, dma_display->color565(0, 0, 0));
    drawText7x8(val, 47 - (val.length() * 7 / 2)+ geser, 17, dma_display->color565(255, 255, 255));
    last4 = val;
    // drawText7x8("L", 43 + geser, 17, dma_display->color565(255, 255, 255));
  }
  else {
    drawText7x8(last1, 15 - (last1.length() * 7 / 2), 0, dma_display->color565(0, 0, 0));
    drawText7x8(last2, 47 - (last2.length() * 7 / 2), 0, dma_display->color565(0, 0, 0));
    drawText7x8(last3, 15 - (last3.length() * 7 / 2), 17, dma_display->color565(0, 0, 0));
    drawText7x8(last4, 47 - (last4.length() * 7 / 2), 17, dma_display->color565(0, 0, 0));
    
    drawText7x8(last1, 15 - (last1.length() * 7 / 2)+ geser, 0, dma_display->color565(0, 0, 0));
    drawText7x8(last2, 47 - (last2.length() * 7 / 2)+ geser, 0, dma_display->color565(0, 0, 0));
    drawText7x8(last3, 15 - (last3.length() * 7 / 2)+ geser, 17, dma_display->color565(0, 0, 0));
    drawText7x8(last4, 47 - (last4.length() * 7 / 2)+ geser, 17, dma_display->color565(0, 0, 0));
    last1 = val;
    last2 = val;
    last3 = val;
    last4 = val;
    drawText7x8(val, 15 - (val.length() * 7 / 2), 0, dma_display->color565(255, 255, 255));
    drawText7x8(val, 47 - (val.length() * 7 / 2), 0, dma_display->color565(255, 255, 255));
    drawText7x8(val, 15 - (val.length() * 7 / 2), 17, dma_display->color565(255, 255, 255));
    drawText7x8(val, 47 - (val.length() * 7 / 2), 17, dma_display->color565(255, 255, 255));
  }
}
