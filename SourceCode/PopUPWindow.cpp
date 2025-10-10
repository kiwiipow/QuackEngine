#include "PopUpWindow.h"

PopUpWindow::PopUpWindow()
{

}
PopUpWindow::~PopUpWindow()
{

}

void PopUpWindow::StartPopUpWindow(const char* name, const char* content)
{
    if(show)
    {
        ImGui::Begin(name, &show);
        ImGui::Text(content);
        ImGui::End();
    }
    else 
    {
        //should log error
    }
   
}

void  PopUpWindow::SetShow(bool Show)
{
    show = Show;
}
bool  PopUpWindow::GetShow()
{
    return show;
}