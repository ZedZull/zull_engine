enum Keys {
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_W,
    KEY_A,
    KEY_S,
    KEY_D,
    KEY_ESCAPE,
    NUM_KEYS
};

internal s32 key_state[NUM_KEYS];

internal void keyboard_callback(GLFWwindow *window, s32 key, s32 scancode, s32 action, s32 mods) {
    switch (key) {
        case GLFW_KEY_UP: { key_state[KEY_UP] = action; break; }
        case GLFW_KEY_DOWN: { key_state[KEY_DOWN] = action; break; }
        case GLFW_KEY_LEFT: { key_state[KEY_LEFT] = action; break; }
        case GLFW_KEY_RIGHT: { key_state[KEY_RIGHT] = action; break; }
        case GLFW_KEY_W: { key_state[KEY_W] = action; break; }
        case GLFW_KEY_A: { key_state[KEY_A] = action; break; }
        case GLFW_KEY_S: { key_state[KEY_S] = action; break; }
        case GLFW_KEY_D: { key_state[KEY_D] = action; break; }
        case GLFW_KEY_ESCAPE: { key_state[KEY_ESCAPE] = action; break; }
    }
}

void input_init(GLFWwindow *window) {
    glfwSetKeyCallback(window, keyboard_callback);

    for (s32 i = 0; i < NUM_KEYS; ++i) {
        key_state[i] = -1;
    }
}

void input_update() {
    for (s32 i = 0; i < NUM_KEYS; ++i) {
        key_state[i] = -1;
    }
}

bool input_was_key_pressed(Keys key) {
    return (key_state[key] == GLFW_PRESS);
}

bool input_was_key_released(Keys key) {
    return (key_state[key] == GLFW_RELEASE);
}

bool input_is_key_down(Keys key) {
    return (key_state[key] == GLFW_PRESS || key_state[key] == GLFW_REPEAT);
}
