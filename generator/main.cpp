#include <fstream>
#include <iostream>
#include <stdexcept>

#include "../src/map.h"

void generateMap(const std::string &mapName, const MapInfo &info);

int main(int argc, char **argv) {
    try {
        MapInfo map;

        map.fourcc = FOURCC_MAP;

        map.alienHealthFactor = 1.0f;
        map.alienSpeedFactor = 1.0f;
        map.alienStrengthFactor = 1.0f;
        generateMap("starfield", map);

        map.alienHealthFactor = 1.5f;
        map.alienSpeedFactor = 1.0f;
        map.alienStrengthFactor = 1.0f;
        generateMap("asteroids", map);

        map.alienHealthFactor = 1.0f;
        map.alienSpeedFactor = 1.5f;
        map.alienStrengthFactor = 1.0f;
        generateMap("nebula", map);

        map.alienHealthFactor = 1.0f;
        map.alienSpeedFactor = 1.0f;
        map.alienStrengthFactor = 1.5f;
        generateMap("kepler", map);

        map.alienHealthFactor = 1.5f;
        map.alienSpeedFactor = 1.5f;
        map.alienStrengthFactor = 1.5f;
        generateMap("gargantua", map);
    } catch (const std::exception &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }

    return 0;
}

void generateMap(const std::string &mapName, const MapInfo &info) {
    std::ofstream mapFile((std::string("assets/maps/") + mapName + ".map").c_str());
    if (!mapFile.is_open()) {
        throw std::runtime_error(std::string("Unable to write map: ") + mapName);
    }
    if (info.fourcc != FOURCC_MAP) {
        throw std::runtime_error(std::string("Invalid map: ") + mapName);
    }
    mapFile.write(reinterpret_cast<const char *>(&info), sizeof(MapInfo));
    mapFile.close();
}

