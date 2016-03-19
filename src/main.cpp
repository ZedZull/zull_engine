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

    const GLFWvidmode *video_mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(window, (video_mode->width / 2) - (SCREEN_WIDTH / 2), (video_mode->height / 2) - (SCREEN_HEIGHT / 2));

    glfwSetKeyCallback(window, keyboard_callback);

    load_opengl_functions();

    graphics_init(SCREEN_WIDTH, SCREEN_HEIGHT);

    if (!script_init()) {
        return -1;
    }

    while (!glfwWindowShouldClose(window)) {
        // TODO(zedzull): Updating and rendering a frame needs to be independant
        // TODO(zedzull): The delta time between updates needs to be passed to Lua
        script_update();
        
        graphics_begin_frame();

        graphics_draw_sprite(32.0f, 32.0f, 64.0f, 64.0f);

        script_draw();
        
        graphics_end_frame();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    script_shutdown();

    glfwTerminate();

    return 0;
}
