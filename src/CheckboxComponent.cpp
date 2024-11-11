#include <wx/wx.h>
#include "CheckboxComponent.h"
#include <iostream>

CheckboxComponent::CheckboxComponent(wxWindow *parent, const wxString &reqLabel) : wxPanel(parent, wxID_ANY) {
    SetBackgroundColour(wxColour(240, 240, 240)); // Light gray color
    
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

    checkBox = new wxCheckBox(this, wxID_ANY, reqLabel);//, wxPoint(20, 20));
    vbox->Add(checkBox, 0, wxALL, 5);

    this->SetSizer(vbox);
}

bool CheckboxComponent::getInputValue() const {
    return checkBox->IsChecked();
}