#ifndef CITYCFD_TYPES_H
#define CITYCFD_TYPES_H

#include "nlohmann/json.hpp"

//-- Typedefs for smart pointers
class Building;    class Boundary; class TopoFeature;
class PolyFeature; class Terrain;  class SurfaceLayer;
typedef std::shared_ptr<Terrain>                               Terrainptr;
typedef std::vector<std::shared_ptr<Building>>                 Buildings;
typedef std::vector<std::shared_ptr<Boundary>>                 Boundaries;
typedef std::vector<std::shared_ptr<TopoFeature>>              OutputFeatures;
typedef std::vector<std::shared_ptr<PolyFeature>>              PolyFeatures;
typedef std::vector<std::shared_ptr<SurfaceLayer>>             SurfaceLayers;
typedef std::vector<std::unique_ptr<nlohmann::json>>           JsonPolygons;

//-- TopoClasses
typedef enum { // temp
    TERRAIN          = 0,
    BUILDING         = 1,
    SIDES            = 2,
    TOP              = 3,
    SURFACELAYER     = 4,
} TopoClass;

//-- Domain types
typedef enum {
    ROUND     = 0,
    RECTANGLE = 1,
    OVAL      = 2
} DomainType;

//-- Output Formats
typedef enum {
    OBJ       = 0,
    CityJSON  = 1,
    STL       = 2,
} OutputFormat;

//-- Global Constants
const double g_largnum  = 1e7;
const double g_smallnum = 1e-7;

#endif //CITYCFD_TYPES_H