#ifndef COMBOBOX_COMPONENT_H
#define COMBOBOX_COMPONENT_H

#include <wx/wx.h>
#include <iostream>

class ComboboxComponent : public wxPanel {
    public:
        ComboboxComponent(
            wxWindow *parent, 
            int id,
            const std::vector<std::string>& options, 
            const wxString &reqLabel = "Label"
        );

        wxString getInputValue() const;

        void SetComboBoxValue(std::string value);
        void Disable();
        void Enable();


    private:
        wxComboBox *comboBox;

        void OnChanged(wxCommandEvent& event);
};

#endif