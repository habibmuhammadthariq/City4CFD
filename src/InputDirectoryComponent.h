#include <wx/wx.h>

class InputDirectoryComponent: public wxPanel {
    public:
        InputDirectoryComponent(wxWindow *parent, const wxString &reqLabel = "Label");

        wxString getInputValue() const;

        bool isEmpty() const;
    
    private:
        wxTextCtrl *textInput;
        wxString dirPath;

        void OnChooseDirectory(wxCommandEvent& event);
};
