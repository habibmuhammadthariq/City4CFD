#include "JSON.h"
#include <wx/wx.h>
#include <fstream>
#include <iostream>
using namespace std;

#include <nlohmann/json.hpp>
using json = nlohmann::json;

// Constructor
JSON::JSON(const wxString &filename) : fileName(filename) {}

// Destructor
JSON::~JSON() {
    // Optionally delete the file on object destruction
    // removeJson();
}

wxString JSON::getFileName() const {
    return fileName;
}

void JSON::saveJson(
    string groundLaz,
    string buildingLaz,
    string BO,
    string uniqueId,
    string pointOfInterestLat,
    string pointOfInterestLong,
    string outputFilename,
    string lod,
    string outputFormat,
    float complexityFactor,
    int buildingPercentile,
    float lod13StepHeight,
    bool separatedOutput = false,
    bool reconstructBoundaries = false
) {
    json json_data;

    std::cout << std::endl;
    std::cout <<  "Separated result " << separatedOutput << std::endl;

    json_data["point_clouds"] =  {
        { "ground", groundLaz },
        { "buildings", buildingLaz }
    };

    json_data["polygons"] = {
        {
            { "type", "Building" },
            { "path", BO },
            { "unique_id", uniqueId }
        },
        // {
        //     { "type", "SurfaceLayer" },
        //     { "path", "polygons/Vegetation.geojson" },
        //     { "layer_name" , "Vegetation" }
        // },
        // {
        //     { "type",       "SurfaceLayer" },
        //     { "path",       "polygons/Water.geojson" },
        //     { "layer_name", "Water" }
        // }
    };
    
    json_data["reconstruction_regions"] = {
        {
            { "influence_region",  300 },
            { "lod", lod },
            { "complexity_factor", complexityFactor }
        },
        // {
        //     { "influence_region",  "polygons/infl  uRegion.geojson" },
        //     { "lod", "1.2" }
        // }
    };
    
    json_data["point_of_interest"] = { std::stof(pointOfInterestLat), std::stof(pointOfInterestLong) };
    json_data["domain_bnd"] = nullptr;
    // json_data["top_height"] = 300;

    json_data["bnd_type_bpg"] = "Rectangle";
    json_data["bpg_blockage_ratio"] = false;
    json_data["flow_direction"] = { 1, 1 };
    json_data["buffer_region"] = 20;
    json_data["reconstruct_boundaries"] = reconstructBoundaries;

    json_data["terrain_thinning"] = 10;
    json_data["smooth_terrain"] = {
        { "iterations" , 1 },
        { "max_pts" , 100000 }
    };

    // if (lod == "1.2") {
        json_data["building_percentile"] = buildingPercentile;
    // } else 
    if (lod == "1.3") {
        json_data["lod13_step_height"] = lod13StepHeight;
    }

    json_data["edge_max_len"] = 5;

    json_data["output_file_name"] = outputFilename;
    json_data["output_format"] = outputFormat;
    json_data["output_separately"] = separatedOutput;

    json_data["output_log"] = true;
    json_data["log_file"] = "logFile.log";
    

    ofstream jsonfile(fileName);
    if (jsonfile.is_open()) {
        jsonfile << json_data.dump(4);
        jsonfile.close();
        cout << "json file created successfully" << endl;
    } else {
        cerr << "Error : Could not create file " << endl;
        return;
    }
}

bool JSON::removeJson() {
    if (remove(fileName.c_str()) != 0) {
        cerr << "Error : Unable to delete file , " << fileName << endl;
        return false;
    }
    return true;
}