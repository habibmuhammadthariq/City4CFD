#ifndef CITYCFD_CONFIG_H
#define CITYCFD_CONFIG_H

#include "definitions.h"

namespace config {
    //-- Output info
    extern std::string fileName;

    //-- Domain size
   extern Point_2      pointOfInterest;
   extern double       radiusOfInfluRegion;
   extern double       dimOfDomain;
   extern double       topHeight;

   //-- Reconstruction
   extern double       buildingPercentile;

   //-- Output flags
   extern OutputFormat outputFormat;
   extern bool         outputSeparately;
    // note: handle when radiusOfInterst is larger than dimOfDomain

    bool read_config_file();
};

#endif //CITYCFD_CONFIG_H