#include <iostream>
#include "nlohmann/json.hpp"
#include "definitions.h"
#include "Map3d.h"
#include <chrono>

int main() {
    auto startTime = std::chrono::steady_clock::now();

    //-- Data input - this needs to be sorted
    const char* points_xyz = "data/input/ground_simplified.ply";
    const char* gisdata    = "data/input/tudcampus.geojson";
    const char* buildings_xyz    = "data/input/building_simplified.xyz";
    const char* config = "";

    //-- Create the main class
    Map3d map3d;

    //-- Read configuration file TODO
    if(!map3d.read_config(config)){
        return 1;
    };

    //-- Read point cloud points
    if(!map3d.read_point_cloud(points_xyz)){
        return 1;
    };
    if(!map3d.read_point_cloud_buildings(buildings_xyz)){
        return 1;
    };

    //-- Read polygons
    if(!map3d.read_polygons(gisdata)){
        return 1;
    };

    //-- Calculate elevations and triangulate
    map3d.reconstruct();

    //-- Add semantics

    //-- Output data
    map3d.output();

    auto endTime = std::chrono::steady_clock::now();
    auto diffTime = endTime - startTime;
    std::cout << "-> All calculations executed in " << std::chrono::duration<double> (diffTime).count() << " s" << std::endl;

    return 0;
}