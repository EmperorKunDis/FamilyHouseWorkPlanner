#include "MyApp.h"
#include <wx/wx.h>
#include "MainFrame.h"

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
	MainFrame* mainFrame = new MainFrame("Family House Work Planner");
	mainFrame->SetClientSize(1500, 800);
	mainFrame->Centre();
	mainFrame->Show();

	return true;
}