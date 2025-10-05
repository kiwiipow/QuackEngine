//ImGUI
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"

class PopUpWindow
{
private:
	bool show;

public:
	PopUpWindow();
	~PopUpWindow();

	void StartPopUpWindow(const char* name, const char* content);

	void SetShow(bool show);
	bool GetShow();
	
};