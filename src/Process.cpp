
#include "Process.h"
#include "Config.h"
#include "io.h"
#include "Map3d.h"
#include <iostream>

#include  <boost/algorithm/string/predicate.hpp>

std::string Process::StartProcess(std::string configPath, std::string outputDir, std::string filename="") {
    try {
        auto startTime = std::chrono::steady_clock::now();

        Config::get().outputDir = fs::absolute(outputDir);
        if (!fs::exists(Config::get().outputDir)) throw std::invalid_argument(std::string("Output directory '" + Config::get().outputDir.string() + "' does not exist!"));
        
        if (!filename.empty()) {
            Config::get().outputFileName = filename;
        }

        //-- Read configuration file
        IO::read_config(configPath);

        //-- Create the main class
        Map3d map3d;

        //-- Read point cloud and polygons, and store them in Map3d
        map3d.read_data();

        //-- Calculate elevations and triangulate
        map3d.reconstruct();

        //-- Output data
        map3d.output();

        //-- Output log
        IO::output_log(map3d.get_failed_buildings());

        auto endTime = std::chrono::steady_clock::now();
        auto diffTime = endTime - startTime;
        std::cout << "\nProgram executed in " << std::chrono::duration<double>(diffTime).count() << " s" << std::endl;
        std:: cout << "End" << std::endl;

        return "success";
    } catch (std::exception& e) {
        //-- Output log
        IO::output_log();

        std::cerr << "\nProgram failed! Reason: " << e.what() << std::endl;
        std::cout << "End" << std::endl;
        return e.what();
    }
}

