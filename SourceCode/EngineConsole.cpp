#include "EngineConsole.h"

EngineConsole::EngineConsole()
{
}

EngineConsole::~EngineConsole()
{
}

void EngineConsole::Log(const std::string& message)
{
    logs.push_back(message);
}

void EngineConsole::Draw(const char* title, bool* open)
{
    if (!ImGui::Begin(title, open))
    {
        ImGui::End();
        return;
    }

    for (const auto& line : logs)
    {
        ImGui::TextUnformatted(line.c_str());
    }

    ImGui::End();
}
