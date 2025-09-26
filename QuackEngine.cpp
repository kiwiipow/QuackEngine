#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <SDL3/SDL_opengl.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_opengl3.h> 

int main()
{
	/*glm::mat4 rotationMatrix(1.0f);

	std::cout << "Hello CMake and vcpkg." << std::endl;*/
    const int WindowWidth = 1080;
    const int WindowHeight = 720;

    // Init SDL
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        return -1;
    }

    //make window
    SDL_Window* window = SDL_CreateWindow("EnginishGL",WindowWidth, WindowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	return 0;

    //// IMGUI
    //IMGUI_CHECKVERSION();
    //ImGui::CreateContext();
    //ImGuiIO& io = ImGui::GetIO();
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}
