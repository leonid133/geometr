// Render.cpp : main project file.

#include "stdafx.h"
#include "geometr.h"
#include "my_scene.h"
#include "Form1.h"

using namespace Render;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew Form1());
	return 0;
}
