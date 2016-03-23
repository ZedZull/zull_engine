// TODO(zedzull): Make the screen size configurable through Lua
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL Error: %s\n", SDL_GetError());
        return -1;
    }


    SDL_Window *window = SDL_CreateWindow("Zull", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);
    
    GLenum err = glewInit();
    if(err != GLEW_OK) {
        printf("GLEW Error: %s\n", glewGetErrorString(err));
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        return -1;
    }

    graphics_init(SCREEN_WIDTH, SCREEN_HEIGHT);

    if (!script_init("game/main.lua")) {
        return -1;
    }

    f64 delta_time = 1.0 / 60.0;

    f64 last_time = SDL_GetTicks();
    f64 unprocessed_time = 0.0;

    int running = 1;
    while (running) {
        f64 current_time = SDL_GetTicks();
        f64 elapsed_time = current_time - last_time;
        last_time = current_time;

        unprocessed_time += elapsed_time;

        while (unprocessed_time >= delta_time) {
            SDL_Event event;
            while(SDL_PollEvent(&event)) {
                input_update(event);
                script_input_update(event);
                if(event.type == SDL_QUIT) {
                    running = 0;
                }
            }

            script_update(delta_time);
            unprocessed_time -= delta_time;
        }
        
        graphics_begin_frame();
        
        script_draw();
        
        graphics_end_frame();

        SDL_GL_SwapWindow(window);
    }

    script_shutdown();

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}