 
#include <wx/wx.h>

#include <iostream>
using namespace std;

#include "MainWindow.h"
#include "Process.h"

// #include <nlohmann/json.hpp>
// using json = nlohmann::json;
#include <fstream>
#include <filesystem>

enum
{
    ID_Hello = 1,
    ID_Btn_Sample = 2,
    ID_Scrolled_Window = 3,
    ID_Process = 4,
    ID_Separated_Result = 5,
    ID_Reconstruct = 5,
    ID_LOD = 6,
    ID_Extension = 7
};
 
MainWindow::MainWindow()
    : wxFrame(nullptr, wxID_ANY, "City 4 CFD")
{
    SetSize(1200, 1000);

    configPath = "/home/habib/gui_example/City4CFD/examples/TUDCampus/sample.json";
    jsonfile = new JSON(configPath);

    /* Menu Bar */
    wxMenu *menuFile = new wxMenu;
    // menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
    //                  "Help string shown in status bar for this menu item");
    // menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
 
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
 
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
 
    SetMenuBar( menuBar );
 
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");

    /* Main Menu*/
    mainWindow = new wxScrolledWindow(this, ID_Scrolled_Window, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxHSCROLL);
    mainWindow->SetScrollRate(10, 10);
    mainWindow->FitInside();
    // mainWindow->SetVirtualSize(400, 800);

    mainSizer = new wxBoxSizer(wxVERTICAL);

    /* Components definition */
    inputGroundPointCloud = new InputFileComponent(mainWindow, "Choose Ground Point Cloud*");
    mainSizer->Add(inputGroundPointCloud, 0, wxEXPAND | wxALL, 5);

    inputBuildingPointCloud = new InputFileComponent(mainWindow, "Choose Building Point Cloud*");
    mainSizer->Add(inputBuildingPointCloud, 0, wxEXPAND | wxALL, 5);

    inputBO = new InputFileComponent(mainWindow, "Choose Building Outline (Geojson)*");
    mainSizer->Add(inputBO, 0, wxEXPAND | wxALL, 5);

    uniqueId = new InputTextComponent(mainWindow, "Unique ID", "uuid");
    mainSizer->Add(uniqueId, 0, wxEXPAND | wxALL, 5);

    pointOfInterestLat = new InputTextComponent(mainWindow, "Point of Interest Latitude*");
    mainSizer->Add(pointOfInterestLat, 0, wxEXPAND | wxALL, 5);

    pointOfInterestLong = new InputTextComponent(mainWindow, "Point of Interest Longitude*");
    mainSizer->Add(pointOfInterestLong, 0, wxEXPAND | wxALL, 5);

    inputResultFilepath = new InputDirectoryComponent(mainWindow, "Choose Output Path");
    mainSizer->Add(inputResultFilepath, 0, wxEXPAND | wxALL, 5);

    // inputVegetation = new InputFileComponent(mainWindow, "Choose Vegetation");
    // mainSizer->Add(inputVegetation, 0, wxEXPAND | wxALL, 5);
    
    // inputWater = new InputFileComponent(mainWindow, "Choose Water");
    // mainSizer->Add(inputWater, 0, wxEXPAND | wxALL, 5);
    // toggleSeparatedResult = new ToggleComponent(mainWindow, "Separated Result");
    // mainSizer->Add(toggleSeparatedResult, 0, wxALL, 5);

    cbSeparatedResult = new CheckboxComponent(mainWindow, "Separated Result");
    mainSizer->Add(cbSeparatedResult, 0, wxALL, 5);

    cbReconstructBoundaries = new CheckboxComponent(mainWindow, "Reconstruct Boundaries");
    mainSizer->Add(cbReconstructBoundaries, 0, wxALL, 5);

    vector<string> extensionOptions = {"obj", "stl", "cityjson"};
    cmbExtension = new ComboboxComponent(mainWindow, ID_Extension, extensionOptions, "Output Format");
    mainSizer->Add(cmbExtension, 0, wxALL, 5);

    vector<string> LODOptions = {"1.2", "1.3", "2.2"};
    cmbLOD = new ComboboxComponent(mainWindow, ID_LOD, LODOptions, "LOD");
    mainSizer->Add(cmbLOD, 0, wxALL, 5);

    buildingPercentile = new InputTextComponent(mainWindow, "Building Percentile*", "90");
    mainSizer->Add(buildingPercentile, 0, wxEXPAND | wxALL, 5);

    lod13StepHeight = new InputTextComponent(mainWindow, "Minimum Step Height (m)*", "25");
    lod13StepHeight->Hide();
    mainSizer->Add(lod13StepHeight, 0, wxEXPAND | wxALL, 5);

    complexityFactor = new InputTextComponent(mainWindow, "Complexity Factor*", "0.7");
    mainSizer->Add(complexityFactor, 0, wxEXPAND | wxALL, 5);

    outputFilename = new InputTextComponent(mainWindow, "Output Filename", "result");
    mainSizer->Add(outputFilename, 0, wxEXPAND | wxALL, 5);

    // Process button
    wxButton* processButton = new wxButton(mainWindow, ID_Process, "Process");
    mainSizer->Add(processButton, 0, wxALIGN_CENTER | wxALL, 1);
 
    /* Binding Event*/
    Bind(wxEVT_MENU, &MainWindow::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MainWindow::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainWindow::OnExit, this, wxID_EXIT);
    Bind(wxEVT_BUTTON, &MainWindow::OnProcess, this, ID_Process);
    Bind(wxEVT_CLOSE_WINDOW, &MainWindow::OnClose, this);
    Bind(wxEVT_COMBOBOX, &MainWindow::OnComboBoxChanged, this);

    /* set sizer */
    mainWindow->SetSizer(mainSizer);
}
 
void MainWindow::OnExit(wxCommandEvent& event)
{
    // Remove temporary config file
    if (filesystem::exists(configPath.ToStdString())) {
        jsonfile->removeJson();
    }
    Close(true);
}

void MainWindow::OnClose(wxCloseEvent& event)
{
    // Remove temporary config file
    if (filesystem::exists(configPath.ToStdString())) {
        jsonfile->removeJson();
    }
    event.Skip();
    // if (wxMessageBox("Are you sure you want to close?", "Confirm",
    //                     wxYES_NO | wxICON_QUESTION) == wxYES) {
    //     // Remove temporary config file
    //     if (filesystem::exists(configPath.ToStdString())) {
    //         jsonfile->removeJson();
    //     }
    //     // Proceed with default close action
    //     event.Skip(); // Allows the close action to proceed
    // } else {
    //     // Prevent the frame from closing
    //     event.Veto();
    // }
}
 
void MainWindow::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is City4CFD Application in a Desktop Version",
                 "About", wxOK | wxICON_INFORMATION);
}
 
void MainWindow::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}

void MainWindow::OnBtnClicked(wxCommandEvent& event)
{
    wxMessageBox("Youre just clicked this button", "Information", wxOK | wxICON_INFORMATION);
}

void MainWindow::OnComboBoxChanged(wxCommandEvent& event) {
    wxString selectedValue = event.GetString();
    int eventId = event.GetId();

    if (eventId == ID_LOD) {
        OnLODChanged();
    } else if (eventId == ID_Extension) {
        OnExtensionChanged();
    }
}

void MainWindow::OnLODChanged() {
    if (cmbLOD->getInputValue().ToStdString() == "1.2") {
        // buildingPercentile->Show();
        lod13StepHeight->Hide();
    } else if (cmbLOD->getInputValue().ToStdString() == "1.3") {
        // buildingPercentile->Hide();
        lod13StepHeight->Show();
    } else if (cmbLOD->getInputValue().ToStdString() == "2.2") {
        // buildingPercentile->Hide();
        lod13StepHeight->Hide();
    }
    mainWindow->FitInside();
    mainWindow->Layout();
}

void MainWindow::OnExtensionChanged() {
    // if (cmbExtension->getInputValue().ToStdString() == "cityjson") {
    //     cmbLOD->SetComboBoxValue("1.2");
    //     cmbLOD->Disable();
    // } else {
    //     cmbLOD->Enable();
    // }
}

void MainWindow::OnProcess(wxCommandEvent& event) {
    if (
        inputGroundPointCloud->isEmpty() ||
        inputBuildingPointCloud->isEmpty() ||
        inputBO->isEmpty() ||
        uniqueId->isEmpty() ||
        pointOfInterestLat->isEmpty() ||
        pointOfInterestLong->isEmpty() ||
        buildingPercentile->isEmpty() ||
        complexityFactor->isEmpty()
    ) {
        wxMessageBox("All required fields must be completed before proceeding.", "Error", wxOK | wxICON_ERROR);
        return;
    }
    
    string outputDir = "/home/habib/gui_example/data/SBYSample/results";

    std::filesystem::path rootDir = std::filesystem::current_path();
    std::string rootDirStr = rootDir.string();
    cout << rootDirStr << endl;

    jsonfile->saveJson(
        inputGroundPointCloud->getInputValue().ToStdString(), 
        inputBuildingPointCloud->getInputValue().ToStdString(), 
        inputBO->getInputValue().ToStdString(), 
        uniqueId->getInputValue().ToStdString(),
        pointOfInterestLat->getInputValue().ToStdString(), 
        pointOfInterestLong->getInputValue().ToStdString(),
        outputFilename->getInputValue().ToStdString(),
        cmbLOD->getInputValue().ToStdString(),
        cmbExtension->getInputValue().ToStdString(),
        stof(complexityFactor->getInputValue().ToStdString()),
        stoi(buildingPercentile->getInputValue().ToStdString()),
        stof(lod13StepHeight->getInputValue().ToStdString()),
        cbSeparatedResult->getInputValue(),
        cbReconstructBoundaries->getInputValue()
    );
    // jsonfile->saveJson(
    //     "/home/habib/gui_example/City4CFD/data/SBYSample/point_cloud/Ground.laz", 
    //     "/home/habib/gui_example/City4CFD/data/SBYSample/point_cloud/Building.laz", 
    //     "/home/habib/gui_example/City4CFD/data/SBYSample/polygons/Building.geojson", 
    //     "uuid",
    //     "692676.72", 
    //     "9196753.58",
    //     "mesh22",
    //     "1.3",
    //     "stl",
    //     0.7,
    //     90,
    //     25,
    //     true,
    //     false
    // );

    // configPath = "/home/habib/gui_example/data/DKISample/config.json";

    Process process;
    string result = process.StartProcess(configPath.ToStdString(), inputResultFilepath->getInputValue().ToStdString(), ""); // outputFilename->getInputValue().ToStdString());
    
    if (result == "success") {
        wxMessageBox("Process Finished", "Information", wxOK | wxICON_INFORMATION);
    } else {
        wxMessageBox("Process failed! Reason " + result, "Information", wxOK | wxICON_INFORMATION);
    }

}

// std::filesystem::path filePath = "/home/user/documents/example.txt";
    
// // Extract the directory path and convert it to a string
// std::string directoryPath = filePath.parent_path().string();