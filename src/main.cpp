// TODO(zedzull): Make the screen size configurable through Lua
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

internal void keyboard_callback(GLFWwindow *window, s32 key, s32 scancode, s32 action, s32 mods) {
    // TODO(zedzull): Input needs to be passed to Lua instead of handled directly
    if (key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, true);
    }
}

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

    if (!script_init()) {
        return -1;
    }

    f64 delta_time = 1.0 / 60.0;
    f64 time_accumulator = 0.0;

    while (!glfwWindowShouldClose(window)) {
        f64 start_time = glfwGetTime();

        while (time_accumulator >= delta_time) {
            script_update(delta_time);
            time_accumulator -= delta_time;
        }
        
        graphics_begin_frame();
        
        script_draw();
        
        graphics_end_frame();

        glfwSwapBuffers(window);

        glfwPollEvents();

        time_accumulator += glfwGetTime() - start_time;
    }

    script_shutdown();

    glfwTerminate();

    return 0;
}
