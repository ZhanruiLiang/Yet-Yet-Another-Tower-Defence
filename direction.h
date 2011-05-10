#ifndef DIRECTION_H
#define DIRECTION_H

// enum the directions
enum Direction {
    D_NONE        = 0x0,  // 0000
    D_LEFT        = 0x1,  // 0001
    D_RIGHT       = 0x2,  // 0010
    D_UP          = 0x4,  // 0100
    D_DOWN        = 0x8,  // 1000 
    D_TOPLEFT     = 0x5,  // 0101
    D_TOPRIGHT    = 0x6,  // 0110
    D_BOTTOMLEFT  = 0x9,  // 1001
    D_BOTTOMRIGHT = 0xA   // 1010
};

#endif
