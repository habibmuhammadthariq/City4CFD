#ifndef INPUT_TEXT_COMPONENT_H
#define INPUT_TEXT_COMPONENT_H

#include <wx/wx.h>

class InputTextComponent : public wxPanel {
    public:
        InputTextComponent(wxWindow *parent, const wxString &reqLabel = "Label", wxString defaultValue = "");

        wxString getInputValue() const;

        bool isEmpty() const;

    private:
        wxTextCtrl *inputText;
};

#endif