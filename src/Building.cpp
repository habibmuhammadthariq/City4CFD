#include "Building.h"

Building::Building() = default;

Building::Building(const nlohmann::json& poly)
    : PolyFeature(poly), _height(-infty) {}

Building::~Building() = default;

void Building::calc_footprint_elevation(const SearchTree& searchTree) {
    //-- Calculate elevation of polygon outer boundary
    //-- Point elevation is the average of 5 nearest neighbors from the PC
    for (auto& polypt : _poly.outer_boundary()) {
        Point_3 query(polypt.x() , polypt.y(), 0);
        Neighbor_search search(searchTree, query, 5);
        // TODO: radius search instead of NN?
//        Fuzzy_sphere search_radius(query, 5);
//        std::list<Point_3> result;
//        searchTree.search(std::back_inserter(result), search_radius);

        std::vector<double> poly_height;
        for (Neighbor_search::iterator it = search.begin(); it != search.end(); ++it) {
            poly_height.push_back(it->first.z());
        }
//        for (auto& pt : result) {
//            poly_height.push_back(pt.z());
//        }
        _base_heights.emplace_back(geomtools::avg(poly_height));
    }

    //-- In case of inner rings, set inner points as average of outer points, as the last element in _baseHeights
    if (_poly.has_holes()) {
        _base_heights.emplace_back(geomtools::avg(_base_heights));
    }
}

void Building::threeDfy(const SearchTree& searchTree) {
    //-- Take tree subset bounded by the polygon
    std::vector<Point_3> subsetPts;
    Point_3 bbox1(_poly.bbox().xmin(), _poly.bbox().ymin(), -infty);
    Point_3 bbox2(_poly.bbox().xmax(), _poly.bbox().ymax(), infty);
    Fuzzy_iso_box pts_range(bbox1, bbox2);
    searchTree.search(std::back_inserter(subsetPts), pts_range);

    //-- Check if subset point lies inside the polygon
    std::vector<double> building_pts;
    for (auto& pt : subsetPts) {
        if (geomtools::check_inside(pt, _poly)) {
            building_pts.push_back(pt.z());
        }
    }

    //-- Don't reconstruct if there are no points belonging to the polygon
    // TODO: exception/warning handling
    if (building_pts.empty()) {
        this->deactivate();
        return;
    }

    //-- LoD12 reconstruction
    LoD12 lod12(_poly, _base_heights, building_pts);
    lod12.lod12reconstruct(_mesh, _height);

    double lowHeight = 4.0; // Hardcoded low height here
    // TODO: exception/warning handling
    if (lod12.get_height() < lowHeight) { // in case of a small height
//        std::cerr << "Building with a low height, building ID: " << this->get_id() << std::endl;
        this->deactivate();
        return;
    }
}

void Building::get_cityjson_info(nlohmann::json& b) const {
    b["type"] = "Building";
//  b["attributes"];
//    get_cityjson_attributes(b, _attributes);
//    float hbase = z_to_float(this->get_height_base());
//    float h = z_to_float(this->get_height());
//    b["attributes"]["TerrainHeight"] = _baseHeights.back(); // temp - will calculate avg for every footprint
    b["attributes"]["measuredHeight"] = _height - _base_heights.back();
}

void Building::get_cityjson_semantics(nlohmann::json& g) const { // Temp for checking CGAL mesh properties
    Face_property semantics;
    bool foundProperty;
    boost::tie(semantics, foundProperty) = _mesh.property_map<face_descriptor, std::string>("f:semantics");
    //   auto semantics = _mesh.property_map<face_descriptor, std::string>("f:semantics");
    if (!foundProperty) throw std::runtime_error("Semantic property map not found!");

    std::unordered_map<std::string, int> surfaceId;
    surfaceId["RoofSurface"]   = 0; g["semantics"]["surfaces"][0]["type"] = "RoofSurface";
    surfaceId["GroundSurface"] = 1; g["semantics"]["surfaces"][1]["type"] = "GroundSurface";
    surfaceId["WallSurface"]   = 2; g["semantics"]["surfaces"][2]["type"] = "WallSurface";

    for (auto& faceIdx : _mesh.faces()) {
        auto it = surfaceId.find(semantics[faceIdx]);
        if (it == surfaceId.end()) throw std::runtime_error("Could not find semantic attribute!");

        g["semantics"]["values"][faceIdx.idx()] = it->second;
    }
}

std::string Building::get_cityjson_primitive() const {
    return "MultiSurface";
};

TopoClass Building::get_class() const {
    return BUILDING;
}

std::string Building::get_class_name() const {
    return "Building";
}