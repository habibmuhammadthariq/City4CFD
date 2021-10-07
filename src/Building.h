#ifndef CITYCFD_BUILDING_H
#define CITYCFD_BUILDING_H

#include "config.h"
#include "geomtools.h"
#include "TopoFeature.h"
#include "LoD12.h"

class Building : public PolyFeature {
public:
    Building();
    Building(const nlohmann::json& poly);
    ~Building();

    void        threeDfy(const SearchTree& searchTree);
    void        get_cityjson_info(nlohmann::json& b) const override;
    void        get_cityjson_semantics(nlohmann::json& g) const override;
    std::string get_cityjson_primitive() const override;

    TopoClass   get_class() const override;
    std::string get_class_name() const override;

    double get_max_dim();

private:
    double _height;
};

#endif //CITYCFD_BUILDING_H