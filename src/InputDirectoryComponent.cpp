#include <wx/wx.h>
#include "InputDirectoryComponent.h"

InputDirectoryComponent::InputDirectoryComponent(wxWindow *parent, const wxString &reqLabel): wxPanel(parent, wxID_ANY) {
    SetBackgroundColour(wxColour(240, 240, 240)); // Light gray color
    
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *label = new wxStaticText(this, wxID_ANY, reqLabel);
    mainSizer->Add(label, 0, wxEXPAND | wxALL, 5);

    mainSizer->Add(hSizer, 0, wxEXPAND | wxALL, 5);

    // text input
    textInput = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(250, -1));
    textInput->SetBackgroundColour(wxColour(255, 255, 204));  // Light yellow color
    textInput->Disable();
    hSizer->Add(textInput, 1, wxEXPAND, 5);

    wxButton *fileButton = new wxButton(this, wxID_ANY, "Choose File");
    fileButton->SetBackgroundColour(wxColour(173, 216, 230));  // Light blue color
    hSizer->Add(fileButton, 0, wxLEFT, 5);
    
    // Bind events
    fileButton->Bind(wxEVT_BUTTON, &InputDirectoryComponent::OnChooseDirectory, this);

    // set sizer and layout
    this->SetSizer(mainSizer);
}

wxString InputDirectoryComponent::getInputValue() const {
    return dirPath;
}

bool InputDirectoryComponent::isEmpty() const {
    return dirPath.IsEmpty();
}

void InputDirectoryComponent::OnChooseDirectory(wxCommandEvent& event) {
    wxDirDialog openDirDialog(this, "Choose a directory", "", wxDD_DEFAULT_STYLE);
    if (openDirDialog.ShowModal() == wxID_OK) {
        dirPath = openDirDialog.GetPath();
        textInput->ChangeValue(dirPath);
        event.Skip();
    }
}
