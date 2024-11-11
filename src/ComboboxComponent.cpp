#include <wx/wx.h>
#include "ComboboxComponent.h"
#include <iostream>

ComboboxComponent::ComboboxComponent(
    wxWindow *parent, 
    int id,
    const std::vector<std::string>& options, 
    const wxString &reqLabel
) : wxPanel(parent, id) 
{
    SetBackgroundColour(wxColour(240, 240, 240)); // Light gray color
    
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

    wxStaticText *label = new wxStaticText(this, wxID_ANY, reqLabel);
    vbox->Add(label, 0, wxEXPAND | wxALL, 5);

    comboBox = new wxComboBox(this, wxID_ANY, "Select an option", wxPoint(20, 20), wxSize(150, -1));//, wxPoint(20, 20));
    for (std::string option : options) {
        comboBox->Append(option);
    }
    comboBox->SetValue(options.at(0));
    vbox->Add(comboBox, 0, wxALL, 5);

    // bind events
    comboBox->Bind(wxEVT_COMBOBOX, &ComboboxComponent::OnChanged, this);

    this->SetSizer(vbox);
}

wxString ComboboxComponent::getInputValue() const {
    return comboBox->GetValue();
}

void ComboboxComponent::OnChanged(wxCommandEvent& event) {
    // // Forward the event to MainWindow with the selected value
    wxCommandEvent newEvent(wxEVT_COMBOBOX, GetId());
    newEvent.SetString(comboBox->GetValue());
    wxPostEvent(GetParent(), newEvent);
}

void ComboboxComponent::Disable() {
    comboBox->Disable();
}

void ComboboxComponent::Enable() {
    comboBox->Enable();
}

void ComboboxComponent::SetComboBoxValue(std::string value) {
    comboBox->SetValue(value);
}