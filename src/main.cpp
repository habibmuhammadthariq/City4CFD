// Start of wxWidgets "Hello World" Program
#include <wx/wx.h>
#include "MainWindow.h"

class MyApp : public wxApp
{
public:
    bool OnInit() override;
};
 
wxIMPLEMENT_APP(MyApp);
 
bool MyApp::OnInit()
{
    MainWindow *frame = new MainWindow();
    frame->Show(true);
    return true;
}
