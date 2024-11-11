#include <wx/wx.h>
#include <wx/tglbtn.h>
#include "ToggleComponent.h"
#include <iostream>

ToggleComponent::ToggleComponent(wxWindow *parent, const wxString &reqLabel) : wxPanel(parent, wxID_ANY) {
    SetBackgroundColour(wxColour(240, 240, 240)); // Light gray color
    
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

    wxStaticText *label = new wxStaticText(this, wxID_ANY, reqLabel);
    vbox->Add(label, 0, wxEXPAND | wxALL, 5);

    toggleBtn = new wxToggleButton(this, wxID_ANY, "OFF");//, wxPoint(20, 20));
    vbox->Add(toggleBtn, 0, wxALL, 5);

    toggleBtn->Bind(wxEVT_TOGGLEBUTTON, &ToggleComponent::OnClick, this);
    
    this->SetSizer(vbox);
}

int ToggleComponent::getInputValue() const {
    return toggleBtn->GetValue();
}

void ToggleComponent::OnClick(wxCommandEvent& event) {
    toggleBtn->SetLabel(toggleBtn->GetValue() ? "ON" : "OFF");
}