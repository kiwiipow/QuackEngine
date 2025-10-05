#pragma once
//sdl3 for console
#include <vector>
#include <string>
#include <imgui.h> 
class EngineConsole
{
private:
    std::vector<std::string> logs;

public:

    EngineConsole();
    ~EngineConsole();
    void Log(const std::string& message);
    void Draw(const char* title, bool* open = nullptr);
  
};
