#pragma once

#define FOURCC_MAP  0xE68FC649

#pragma pack(push, 1)
struct MapInfo {
    unsigned int fourcc;
    float alienHealthFactor;
    float alienSpeedFactor;
    float alienStrengthFactor;
};
#pragma pack(pop)

