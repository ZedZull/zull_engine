// TODO(zedzull): Make the screen size configurable through Lua
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main() {
    glfwInit();

    glfwWindowHint(GLFW_RESIZABLE, false);

    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Zull", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    const GLFWvidmode *video_mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(window, (video_mode->width / 2) - (SCREEN_WIDTH / 2), (video_mode->height / 2) - (SCREEN_HEIGHT / 2));

    glfwSetKeyCallback(window, keyboard_callback);

    load_opengl_functions();

    graphics_init(SCREEN_WIDTH, SCREEN_HEIGHT);

    if (!script_init("game/main.lua")) {
        return -1;
    }

    f64 delta_time = 1.0 / 60.0;

    f64 last_time = glfwGetTime();
    f64 unprocessed_time = 0.0;

    while (!glfwWindowShouldClose(window)) {
        f64 current_time = glfwGetTime();
        f64 elapsed_time = current_time - last_time;
        last_time = current_time;

        unprocessed_time += elapsed_time;

        while (unprocessed_time >= delta_time) {
            input_update();
            glfwPollEvents();

            if (input_was_key_pressed(KEY_ESCAPE)) {
                glfwSetWindowShouldClose(window, true);
            }

            script_update(delta_time);
            unprocessed_time -= delta_time;
        }
        
        graphics_begin_frame();
        
        script_draw();
        
        graphics_end_frame();

        glfwSwapBuffers(window);
    }

    script_shutdown();

    glfwTerminate();

    return 0;
}
