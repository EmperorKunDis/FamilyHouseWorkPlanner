#include "MainFrame.h"
#include "Task.h"
#include "Member.h"
#include <wx/wx.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <algorithm>

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {


	CreateControls();
	CreateStatusBar();

	BindEventHandlers();
	
	std::vector<Member> members = Member::LoadData();
	std::vector<Task> tasks = Task::LoadData();
for (const auto& member : members) {
	listboxMembers->Insert(member.name, listboxMembers->GetCount());
}

for (const auto& task : tasks) {
	listboxTasks->Insert(task.taskName, listboxTasks->GetCount());
}

}
void delay(int seconds) {
	std::this_thread::sleep_for(std::chrono::seconds(seconds));
	wxLogStatus("Created by: Martin Švanda						P.S.: Im looking for job so please write me to martin.k.svanda@gmail.com"); // Log the status
}
void MainFrame::OnKeyEvent(wxKeyEvent& evt) {
	if (evt.GetKeyCode() == WXK_TAB) {
		wxWindow* myWin = (wxWindow*)evt.GetEventObject(); // Get the window that triggered the even
		myWin->Navigate(); // Navigate to the next window)
	}
}
void MainFrame::OnButtonClicked(wxCommandEvent& evt) {
	wxString nameTextMember = wxString::Format("%s", textFieldMember->GetValue()); // Get the text from the text box and store it in a string;
	wxString nameTextTask = wxString::Format("%s", textFieldTask->GetValue()); // Get the text from the text box and store it in a string
	wxLogStatus("Family Member with name : " + nameTextMember + " has been added"); // Log the status
	wxLogStatus("Family Member with name : " + nameTextTask + " has been added"); // Log the status
	std::thread delayThread(delay, 3); // 3 seconds
	delayThread.detach(); // Detach the thread
}
void MainFrame::CreateControls()
{
	const int windowHeight = 800;
	const int windowWidth = 1500;
	const int buttonHeight = 30;
	const int buttonWidth = 130;
	wxString nameTextMember;
	wxString nameTextTask;
	panel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(windowWidth, windowHeight));
	panelLeftSide = new wxPanel(panel, wxID_ANY, wxPoint(0, 0), wxSize(windowWidth / 5, windowHeight - 40));
	panelMidSide = new wxPanel(panel, wxID_ANY, wxPoint(windowWidth / 5, 0), wxSize((windowWidth / 5), windowHeight - 40));
	panelRightSide = new wxPanel(panel, wxID_ANY, wxPoint((windowWidth / 5) * 2, 0), wxSize((windowWidth / 5) * 3, windowHeight - 40));
	//PANEL 1	*panelLeftSide*
	textStatic = new wxStaticText(panelLeftSide, wxID_ANY, "Members of Your Family:",
		wxPoint(30, 30), wxSize(windowWidth - 300, 30));
	listboxMembers = new wxListBox(panelLeftSide, wxID_ANY, wxPoint(30, 70),
		wxSize((windowWidth / 5) - 40, windowHeight - 260));
	textStaticMembers = new wxStaticText(panelLeftSide, wxID_ANY, "Name :",
		wxPoint(30, windowHeight - 190), wxSize(100, 30));
	textFieldMember = new wxTextCtrl(panelLeftSide, wxID_ANY, nameTextMember,
		wxPoint(30, windowHeight - 160), wxSize(100, 30), wxTE_PROCESS_ENTER);
	checkboxMembers = new wxCheckBox(panelLeftSide, wxID_ANY, "Is that Member Adult ?",
		wxPoint(windowWidth / 5 - 130, windowHeight - 160), wxSize(130, 30));
	btn1 = new wxButton(panelLeftSide, wxID_ANY, "+++ Add Member +++",
		wxPoint(30, windowHeight - 100), wxSize(buttonWidth, buttonHeight));
	btn2 = new wxButton(panelLeftSide, wxID_ANY, "--- Delete Member ---",
		wxPoint((windowWidth / 5) - (buttonWidth + 10), windowHeight - 100), wxSize(buttonWidth, buttonHeight));
	//PANEL 2	*panelMidSide*
	btn3 = new wxButton(panelMidSide, wxID_ANY, "+++ Add Task +++",
		wxPoint(30, windowHeight - 100), wxSize(buttonWidth, buttonHeight));
	textStatic2 = new wxStaticText(panelMidSide, wxID_ANY, "Tasks what must be done at your home :",
		wxPoint(30, 30), wxSize(windowWidth - 300, 30));
	textStaticTasks = new wxStaticText(panelMidSide, wxID_ANY, "Work what you want include tu Planer :",
		wxPoint(30, windowHeight - 190), wxSize(windowWidth / 5, 30));
	listboxTasks = new wxListBox(panelMidSide, wxID_ANY,
		wxPoint(30, 70), wxSize((windowWidth / 5) - 40, windowHeight - 260));
	textFieldTask = new wxTextCtrl(panelMidSide, wxID_ANY, nameTextTask,
		wxPoint(30, windowHeight - 160), wxSize(100, 30), wxTE_PROCESS_ENTER);
	checkboxTasks = new wxCheckBox(panelMidSide, wxID_ANY, "Is this work for Adult ?",
		wxPoint(windowWidth / 5 - 130, windowHeight - 160), wxSize(130, 30));
	btn4 = new wxButton(panelMidSide, wxID_ANY, "--- Delete Task ---",
		wxPoint((windowWidth / 5) - (buttonWidth + 10), windowHeight - 100), wxSize(buttonWidth, buttonHeight));
	//PANEL 3	*panelRightSide*
	btn5 = new wxButton(panelRightSide, wxID_ANY, "Edit",
		wxPoint(30, windowHeight - 100), wxSize(buttonWidth, buttonHeight));
	textStatic3 = new wxStaticText(panelRightSide, wxID_ANY, "Properties of Selected Component : ",
		wxPoint(30, 30), wxSize(windowWidth - 300, 30));
	listboxProperties = new wxListBox(panelRightSide, wxID_ANY,
		wxPoint(30, 70), wxSize(((windowWidth / 5) * 3) - 60, windowHeight - 260));
}
void MainFrame::BindEventHandlers()
{
	btn1->Bind(wxEVT_BUTTON, &MainFrame::OnAddMemberClicked, this);
	textFieldMember->Bind(wxEVT_TEXT_ENTER, &MainFrame::OnInputMemberEnter, this);
	listboxMembers->Bind(wxEVT_KEY_DOWN, &MainFrame::OnListKeyDown, this); // For checkbox
	btn2->Bind(wxEVT_BUTTON, &MainFrame::OnDelMemberClicked, this);
	btn3->Bind(wxEVT_BUTTON, &MainFrame::OnAddTaskClicked, this);
	textFieldTask->Bind(wxEVT_TEXT_ENTER, &MainFrame::OnInputTaskEnter, this);
	listboxTasks->Bind(wxEVT_KEY_DOWN, &MainFrame::OnListKeyDown, this); // For checkbox
	btn4->Bind(wxEVT_BUTTON, &MainFrame::OnDelTaskClicked, this);
}
void MainFrame::OnAddMemberClicked(wxCommandEvent& evt) {
	AddMemberFromInput();
}
void MainFrame::OnDelMemberClicked(wxCommandEvent& evt) {
	DelMemberFromList();
}
void MainFrame::OnAddTaskClicked(wxCommandEvent& evt) {
	AddTaskFromInput();
}
void MainFrame::OnDelTaskClicked(wxCommandEvent& evt) {
	DelTaskFromList();
}

void MainFrame::OnInputMemberEnter(wxCommandEvent& evt) {
	AddMemberFromInput();
}
void MainFrame::OnInputTaskEnter(wxCommandEvent& evt) {
	AddTaskFromInput();
}
void MainFrame::OnListKeyDown(wxKeyEvent& evt) {
	switch (evt.GetKeyCode()) {
	case WXK_SPACE:
		DelMemberFromList();
		break;
	}
}
void MainFrame::AddMemberFromInput() { // Refere
	wxString name = textFieldMember->GetValue();
	bool isAdult = checkboxMembers->GetValue(); // Nastav
	Member::SaveData(members);
	// Ovìøení, zda je jméno prázdné
	if (!name.IsEmpty()) {
		// Pøidání nového èlena s výchozími hodnotami pro ostatní atributy
		members.emplace_back(name.ToStdString(), isAdult, 0, "", ""); // Zde jsou ostatní hodnoty prázdné

		// Pøidání jména do seznamu
		listboxMembers->Insert(name, listboxMembers->GetCount());

		

		// Vyprázdnìní textového pole
		textFieldMember->Clear();
	}
}
void MainFrame::DelMemberFromList()
{
	
	int selectedIndex = listboxMembers->GetSelection(); // Getselected
	Member::SaveData(members);
	if (selectedIndex == wxNOT_FOUND) {
		return; // Do no
	}
	listboxMembers->Delete(selectedIndex); // Delete the selected item
	members.erase(members.begin() + selectedIndex);
	
}
void MainFrame::AddTaskFromInput() {
	wxString taskName = textFieldTask->GetValue();											// Get task name from the input field
	bool isForAdult = checkboxMembers->GetValue();
	if (!taskName.IsEmpty()) {																// Create a Task object and populate its fields
		tasks.emplace_back(taskName.ToStdString(), isForAdult, 0, 0);						// Insert the task into the listbox for GUI display
		listboxTasks->Insert(taskName, listboxTasks->GetCount());
		Task::SaveData(tasks);																			// Add the task to the allTasks vector														// Clear the input field after adding
		textFieldTask->Clear();																// Save the tasks to file
	}
}

void MainFrame::DelTaskFromList()
{
	int selectedIndex = listboxTasks->GetSelection(); // Get the selected task's index
	if (selectedIndex == wxNOT_FOUND) {
		return; // No task selected, do nothing
	}
	tasks.erase(tasks.begin() + selectedIndex);
																			// Add the task to the allTasks vector														// Clear the input field after adding
	// Remove the task from the listbox (GUI)
	listboxTasks->Delete(selectedIndex);	
	Task::SaveData(tasks);
}


void MainFrame::Properties() {

	int selectedMember = listboxMembers->GetSelection();
	int selectedTask = listboxTasks->GetSelection();

	// Clear the properties list box
	listboxProperties->Clear();

	// Check if a member is selected
	if (selectedMember >= 0)
	{
		// Display member properties
		listboxProperties->Append("This member has name: ");
		textFieldNameMember = new wxTextCtrl(this, wxID_ANY, members[selectedMember].name);
		listboxProperties->Show(textFieldNameMember);

		wxString adultStatus = members[selectedMember].isAdult ? "This member is Adult and can make hard work too" : "This member is not Adult or avalailibe";
		listboxProperties->Append(adultStatus);
		checkboxAdultMember = new wxCheckBox(this, wxID_ANY, "Is Adult?");
		checkboxAdultMember->SetValue(members[selectedMember].isAdult);
		listboxProperties->Show(checkboxAdultMember);

		listboxProperties->Append("This member has points at start: ");
		textFieldPointsMember = new wxTextCtrl(this, wxID_ANY, wxString::Format("%d", members[selectedMember].points));
		listboxProperties->Show(textFieldPointsMember);

		listboxProperties->Append(wxString::Format("Id of this member is: %d", members[selectedMember].id));
		textFieldIdMember = new wxTextCtrl(this, wxID_ANY, wxString::Format("%d", members[selectedMember].id));
		listboxProperties->Show(textFieldIdMember);

		listboxProperties->Append("This member has a telephone number: ");
		textFieldPhoneMember = new wxTextCtrl(this, wxID_ANY, members[selectedMember].phoneNumber);
		listboxProperties->Show(textFieldPhoneMember);
	}
	// Check if a task is selected
	else if (selectedTask >= 0)
	{
		// Display task properties
		listboxProperties->Append("Task name: ");
		textFieldNameTask = new wxTextCtrl(this, wxID_ANY, tasks[selectedTask].taskName);
		listboxProperties->Show(textFieldNameTask);

		listboxProperties->Append("Is this task for adults: ");
		checkboxForAdultTask = new wxCheckBox(this, wxID_ANY, "Is for Adult");
		checkboxForAdultTask->SetValue(tasks[selectedTask].isForAdult);
		listboxProperties->Show(checkboxForAdultTask);

		listboxProperties->Append("Task points: ");
		wxArrayString pointChoices;
		for (int i = 1; i <= 5; ++i)
		{
			pointChoices.Add(wxString::Format("%d", i));
		}
		comboBoxPointsTask = new wxComboBox(this, wxID_ANY, wxString::Format("%d", tasks[selectedTask].taskPoints), wxDefaultPosition, wxDefaultSize, pointChoices);
		listboxProperties->Show(comboBoxPointsTask);

		listboxProperties->Append("Task frequency: ");
		wxArrayString frequencyChoices = { "One time daily", "One time weekly", "Two times weekly", "Three times weekly", "One time monthly", "Two times monthly" };
		comboBoxFrequencyTask = new wxComboBox(this, wxID_ANY,wxEmptyString, wxDefaultPosition, wxDefaultSize, frequencyChoices);
		listboxProperties->Show(comboBoxFrequencyTask);
	}
}


