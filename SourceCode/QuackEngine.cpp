#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// OpenGL
#include <glad/glad.h>
#include <SDL3/SDL.h>

//ImGUI
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"

//JSON parser
#include <nlohmann/json.hpp>
#include <fstream>

//sdl3 for console
#include <vector>
#include <string>

#include "EngineConsole.h"


//class EngineConsole
//{
//private:
//    std::vector<std::string> logs;
//
//public:
//
//    EngineConsole()
//    {
//
//    }
//    void Log(const std::string& message)
//    {
//        logs.push_back(message);
//    }
//
//    void Draw(const char* title, bool* open = nullptr)
//    {
//        if (!ImGui::Begin(title, open))
//        {
//            ImGui::End();
//            return;
//        }
//
//        for (const auto& line : logs)
//        {
//            ImGui::TextUnformatted(line.c_str());
//        }
//
//        ImGui::End();
//    }
//
//
//};

nlohmann::json LoadConfig(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cerr << "[ERROR] Could not open config file: " << path << std::endl;
        return nullptr;
    }

    nlohmann::json config;
    try
    {
        file >> config;
    }
    catch (const std::exception& e)
    {
        std::cerr << "[ERROR] Failed to parse JSON: " << e.what() << std::endl;
        return nullptr;
    }

    return config;
}

void MenuBar(bool& showInspector, bool& showOutliner, bool& showAbout, bool& showConsole)
{
    if (ImGui::BeginMainMenuBar())
    {
        // FILE MENU
        if (ImGui::BeginMenu("File"))//Creates and starts menu or submenu 
        {
            if (ImGui::MenuItem("Exit"))
            {
                // close sdl window and quit
                SDL_Event quit_event;
                quit_event.type = SDL_EVENT_QUIT;
                SDL_PushEvent(&quit_event);
            }
            ImGui::MenuItem("Save"); // creates item as in action or window pop up
            if (ImGui::BeginMenu("Save Copy"))
            {
                ImGui::MenuItem("Png.");
                ImGui::MenuItem("Jpg.");

                ImGui::EndMenu();
            }

            ImGui::EndMenu();//closes menu or submenu, must always be at the end of each BaginMenu
        }

        // VIEW MENU
        if (ImGui::BeginMenu("View"))
        {

            ImGui::MenuItem("Inspector", NULL, &showInspector);
            ImGui::MenuItem("Outliner", NULL, &showOutliner);
            ImGui::MenuItem("Console", NULL, &showConsole);

            ImGui::EndMenu();
        }

        //HELP MENU
        if (ImGui::BeginMenu("Help"))
        {
            ImGui::MenuItem("About", NULL, &showAbout);
            if (ImGui::MenuItem("GitHub documentation"))
            {
                SDL_OpenURL("https://github.com/UPC-GameEngines-BCN-2025/QuackEngine");
            }
            if (ImGui::MenuItem("Report a bug"))
            {
                SDL_OpenURL("https://github.com/UPC-GameEngines-BCN-2025/QuackEngine/issues");
            }
            if (ImGui::MenuItem("Download latest"))
            {
                SDL_OpenURL("https://github.com/UPC-GameEngines-BCN-2025/QuackEngine/releases");
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }


    //POP UP WINDOWS
    if (showInspector)
    {
        ImGui::Begin("Inspector", &showInspector);
        ImGui::Text("This is the Inspector.");
        ImGui::End();
    }
    if (showOutliner)
    {
        ImGui::Begin("Outliner", &showOutliner);
        ImGui::Text("This is the Outliner.");
        ImGui::End();
    }
    if (showAbout)
    {
        ImGui::Begin("About", &showAbout);
        ImGui::Text("Quack Engine.\n 1.0.\n Members: \n kiwiipow: Paula Laguna \n Wakiren: Francisco Javier  \n Aria00015: Alba Fern�ndez");
        ImGui::Text("Libraries: \nOpenGl, \nSDL3, \nGLAD, \nImGui.\n");
        ImGui::TextWrapped(R"(License: MIT License
            Copyright (c) 2025 CITM - UPC
            Permission is hereby granted, free of charge, to any person obtaining a copy
            of this software and associated documentation files (the "Software"), to deal
            in the Software without restriction, including without limitation the rights
            to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
            copies of the Software, and to permit persons to whom the Software is
            furnished to do so, subject to the following conditions:
            The above copyright notice and this permission notice shall be included in all
            copies or substantial portions of the Software.
            THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
            IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
            FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
            AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
            LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
            OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
            SOFTWARE.)");
        ImGui::End();
    }


}

int main()
{
    //init console
    EngineConsole ConsoleLog;
    bool showConsole = true;

    // Window Resolution

    nlohmann::json config = LoadConfig("config.json");

    int SCREEN_WIDTH = 1920;
    int SCREEN_HEIGHT = 1080;

    //does not work
    if (config.contains("window"))
    {
        SCREEN_WIDTH = config["window"].value("width",10);
        SCREEN_HEIGHT = config["window"].value("height",10);
    }

   // Init SDL

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
       ConsoleLog.Log("SDL not initialized");
        return -1;
    }
    else
    {
        ConsoleLog.Log("SDL Initialized");
    }

    // Setup Min/Major version for using OpenGL 4.6
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    // Set Core Profile Mode
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Create OpenGL window using SDL
    SDL_Window* window = SDL_CreateWindow("EnginishGL",
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    // Early out if window not valid
    if (window == nullptr)
    {
        ConsoleLog.Log("OpenGl window not valid");
        SDL_Quit();
        return -1;
    }
    else
    {
        ConsoleLog.Log("OpenGl window valid");
    }

    // OpenGL is context based and thread local
    // Link OpenGL context to SDL, after this you can load OpenGL functions and start rendering
    // Multi-threading -> Define multiple context and make them current
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext)
    {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Init all OpenGL function pointers at runtime (not linked at compile time)
    gladLoadGL();

    // Used for mapping NDC coordinates (-1.0f to 1.0f) to pixel coordinates (e.g. 1920x1080)
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init();




    bool isRunning = true;
    bool showInspector, showOutliner, showAbout = true;//bool to enable disable windows from  ImGui::Begin
    while (isRunning)
    {
        // INPUT
        // SDL EVENTS
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT)
            {
                isRunning = false;
            }

            if (event.type == SDL_EVENT_MOUSE_BUTTON_UP
                && event.button.button == SDL_BUTTON_RIGHT)
            {
            }

            if ((event.type == SDL_EVENT_MOUSE_BUTTON_DOWN
                && event.button.button == SDL_BUTTON_RIGHT))
            {
            }

        }

        // SDL KEYS
        int numKeys;
        const bool* keys = SDL_GetKeyboardState(&numKeys);
        if (keys[SDL_SCANCODE_W])
        {
        }

        // UPDATE
        // [...] 


        // RENDER
        // Clear screen color
        glClearColor(0.1f, 0.2f, 0.2f, 1.0f);

        // Clear Color Buffer and Depth Buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // RENDER
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        // Show sample demo from ImGui 
        // ImGui::ShowDemoWindow();

        //Show test menu bar
        MenuBar(showInspector, showOutliner, showAbout, showConsole);

        //shows popup window the rest of calls for other windows are in menu bar function should make it a class ui or something
        if (showConsole)
        {
             ConsoleLog.Draw("Console", &showConsole);
        }
           

        // Render ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  

        // Swap window
        SDL_GL_SwapWindow(window);

        // FRAME CONTROL
        // [...]
    }

    // Deinit ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    // DeInit SDL
    SDL_GL_DestroyContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
