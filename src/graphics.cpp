void graphics_init() {
    glEnable(GL_CULL_FACE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // TODO(zedzull): The clear color needs to be configurable
    glClearColor((100.0f / 255.0f), (149.0f / 255.0f), (237.0f / 255.0f), 1.0f);
}

void graphics_begin_frame() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void graphics_end_frame() {

}

void graphics_clear() {
    // TODO(zedzull): Remove this once the Lua function binding test that uses this isn't needed
}

void graphics_draw_sprite(f32 x, f32 y) {

}
