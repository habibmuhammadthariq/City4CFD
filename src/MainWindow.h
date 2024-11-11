#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <wx/wx.h>
#include "InputTextComponent.h"
#include "InputFileComponent.h"
#include "InputDirectoryComponent.h"
#include "ToggleComponent.h"
#include "CheckboxComponent.h"
#include "JSON.h"
#include "ComboboxComponent.h"

class MainWindow : public wxFrame
{
    public:
        MainWindow();
    
    private:
        void OnHello(wxCommandEvent& event);
        void OnExit(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnBtnClicked(wxCommandEvent& event);
        void OnFilePickerClicked(wxCommandEvent& event);
        void OnProcess(wxCommandEvent& event);

        void OnComboBoxChanged(wxCommandEvent& event);

        void OnLODChanged();
        void OnExtensionChanged();
        
        wxScrolledWindow *mainWindow;
        wxBoxSizer *mainSizer;

        JSON *jsonfile;
        wxString configPath;

        InputDirectoryComponent *inputResultFilepath;

        InputFileComponent *inputGroundPointCloud;
        InputFileComponent *inputBuildingPointCloud;
        InputFileComponent *inputBO;
        InputFileComponent *inputVegetation;
        InputFileComponent *inputWater;
        
        InputTextComponent *outputFilename;
        InputTextComponent *pointOfInterestLat;
        InputTextComponent *pointOfInterestLong;
        InputTextComponent *uniqueId;
        InputTextComponent *complexityFactor;
        InputTextComponent *lod13StepHeight;
        InputTextComponent *buildingPercentile;

        ToggleComponent *toggleSeparatedResult;

        CheckboxComponent *cbSeparatedResult;
        CheckboxComponent *cbReconstructBoundaries;

        ComboboxComponent *cmbLOD;
        ComboboxComponent *cmbExtension;

        
};

#endif