#include <wx/wx.h>
#include "InputFileComponent.h"

InputFileComponent::InputFileComponent(wxWindow *parent, const wxString &reqLabel): wxPanel(parent, wxID_ANY) {
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
    fileButton->Bind(wxEVT_BUTTON, &InputFileComponent::OnChooseFile, this);

    // set sizer and layout
    this->SetSizer(mainSizer);
}

wxString InputFileComponent::getInputValue() const {
    return filePath;
}

bool InputFileComponent::isEmpty() const {
    return filePath.IsEmpty();
}

void InputFileComponent::OnChooseFile(wxCommandEvent& event) {
    wxFileDialog openFileDialog(this, "Choose a file", "", "", "*.*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_OK) {
        filePath = openFileDialog.GetPath();
        textInput->ChangeValue(filePath);
        event.Skip();
    }
}
