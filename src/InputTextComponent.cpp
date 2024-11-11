#include <wx/wx.h>
#include "InputTextComponent.h"

InputTextComponent::InputTextComponent(wxWindow *parent, const wxString &reqLabel, wxString defaultValue) : wxPanel(parent, wxID_ANY) {
    SetBackgroundColour(wxColour(240, 240, 240)); // Light gray color
    
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

    wxStaticText *label = new wxStaticText(this, wxID_ANY, reqLabel);
    vbox->Add(label, 0, wxEXPAND | wxALL, 5);

    inputText = new wxTextCtrl(this, wxID_ANY);
    inputText->SetValue(defaultValue);
    vbox->Add(inputText, 0, wxEXPAND | wxALL, 5);

    this->SetSizer(vbox);
}

wxString InputTextComponent::getInputValue() const {
    return inputText->GetValue();
}

bool InputTextComponent::isEmpty() const {
    return inputText->IsEmpty();
}