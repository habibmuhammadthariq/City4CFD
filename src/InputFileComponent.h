#include <wx/wx.h>

class InputFileComponent: public wxPanel {
    public:
        InputFileComponent(wxWindow *parent, const wxString &reqLabel = "Label", wxString defaultValue = "");

        wxString getInputValue() const;

        bool isEmpty() const;
    
    private:
        wxTextCtrl *textInput;
        wxString filePath;

        void OnChooseFile(wxCommandEvent& event);
};
