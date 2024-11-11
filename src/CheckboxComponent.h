#ifndef CHECKBOX_COMPONENT_H
#define CHECKBOX_COMPONENT_H

#include <wx/wx.h>

class CheckboxComponent : public wxPanel {
    public:
        CheckboxComponent(wxWindow *parent, const wxString &reqLabel = "Label");

        bool getInputValue() const;


    private:
        wxCheckBox *checkBox;
};

#endif