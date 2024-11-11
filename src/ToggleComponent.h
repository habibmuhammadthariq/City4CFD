#ifndef TOGGLE_COMPONENT_H
#define TOGGLE_COMPONENT_H

#include <wx/wx.h>
#include <wx/tglbtn.h>

class ToggleComponent : public wxPanel {
    public:
        ToggleComponent(wxWindow *parent, const wxString &reqLabel = "Label");

        int getInputValue() const;


    private:
        void OnClick(wxCommandEvent& event);
        
        wxToggleButton *toggleBtn;
};

#endif