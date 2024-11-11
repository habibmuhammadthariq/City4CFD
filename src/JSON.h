#ifndef JSON_H
#define JSON_H

#include <wx/wx.h>
#include <iostream>

class JSON {
    public:
        JSON(const wxString &filename);
        ~JSON();

        void saveJson(
            std::string groundLaz,
            std::string buildingLaz,
            std::string BO,
            std::string uniqueId,
            std::string pointOfInterestLat,
            std::string pointOfInterestLong,
            std::string outputFilename,
            std::string lod,
            std::string outputFormat,
            float complexityFactor,
            int buildingPercentile,
            float lod13StepHeight,
            bool separatedOutput,
            bool reconstructBoundaries
        );

        bool removeJson();

        wxString getFileName() const;

    private:
        wxString fileName;
};

#endif