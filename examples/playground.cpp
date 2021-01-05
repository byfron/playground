#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_opengl3.h>
#include <GL/gl3w.h> 
#include <stdio.h>
#include <SDL2/SDL.h>
#include <common/Camera.hpp>
#include <renderer/Sphere.hpp>
#include <vector>
#include <memory>

Color ray_color(const Ray& r) {
    Vec3d unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*Color(1.0, 1.0, 1.0) + t*Color(0.5, 0.7, 1.0);
}

void renderScene(SDL_Renderer* renderer, std::vector<std::shared_ptr<Object> > objects, Camera* camera) {
    
    for (int j = camera->image_height()-1; j >= 0; --j) {
        for (int i = 0; i < camera->image_width(); ++i) {
            auto u = double(i) / (camera->image_width()-1);
            auto v = double(j) / (camera->image_height()-1);
            auto ray = camera->compute_ray(u, v);

            Color pixel_color = ray_color(ray);
            for (auto& object : objects) {
                HitRecord record;
                if (object->hit(ray, 0, 10, record)) {
                    pixel_color = 0.5*Color(record.normal.x()+1, record.normal.y()+1, record.normal.z()+1);
                }
            }

            SDL_SetRenderDrawColor(renderer, pixel_color.x() * 255, pixel_color.y() * 255, pixel_color.z() * 255, 255);
            SDL_RenderDrawPoint(renderer, i, j);
        }
    }
}

int main() {

    std::vector<std::shared_ptr<Object> > objects;
    objects.push_back(std::make_shared<Sphere>(Point3(0,0,-1), 0.5));

    double aspect_ratio = 16.0 / 9.0;
    int width = 600;
    int height = static_cast<int>(width / aspect_ratio);
    Camera camera = Camera(width, height);

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window* window = SDL_CreateWindow("Playground", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, window_flags);

    const char* glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

    
    SDL_GL_SetSwapInterval(1); // Enable vsync
    SDL_GLContext gl_context =  SDL_GL_GetCurrentContext();//SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (gl3wInit() != 0)
    {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }

	IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    //ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Platform/Renderer backends
    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    bool done = false;
    while (!done)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();

        /*
        ImGui::Begin("Hello, world!");
        ImGui::Text("This is some useful text.");
        ImGui::Button("Search");
        ImGui::End();
        */

        // Rendering
        ImGui::Render();
        
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        renderScene(renderer, objects, &camera);

        
        SDL_RenderPresent(renderer);
        //SDL_RenderClear(renderer);
        
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;

}