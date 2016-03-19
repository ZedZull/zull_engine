#define GLSL(src) #src

#define MAX_SPRITES 2048
#define MAX_VERTICES MAX_SPRITES * 4 * 7
#define MAX_INDICES MAX_SPRITES * 6

internal const char *vertex_shader_src = GLSL(
    attribute vec2 a_pos;
    attribute vec3 a_color;
    attribute vec2 a_texcoord;

    varying vec3 v_color;
    varying vec2 v_texcoord;

    uniform mat4 u_projection;

    void main() {
        gl_Position = u_projection * vec4(a_pos, 0.0, 1.0);

        v_color = a_color;
        v_texcoord = a_texcoord;
    }
);

internal const char *fragment_shader_src = GLSL(
    varying vec3 v_color;
    varying vec2 v_texcoord;

    uniform sampler2D u_sampler;

    void main() {
        gl_FragColor = vec4(v_color, 1.0) * texture2D(u_sampler, v_texcoord);
    }
);

internal GLuint vertex_buffer;
internal GLuint index_buffer;

internal f32 vertices[MAX_VERTICES];
internal u16 indices[MAX_INDICES];

internal s32 num_sprites = 0;

internal GLuint compile_shader(const char *source, GLenum type) {
    GLuint shader = glCreateShader(type);

    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    return shader;
}

internal void use_ortho_matrix(GLuint shader_program, f32 left, f32 right, f32 bottom, f32 top, f32 nearv, f32 farv) {
    f32 matrix[16] = { 0.0f };
    matrix[0] = 2.0f / (right - left);
    matrix[5] = 2.0f / (top - bottom);
    matrix[10] = -2.0f / (farv - nearv);
    matrix[12] = -(right + left) / (right - left);
    matrix[13] = -(top + bottom) / (top - bottom);
    matrix[14] = -(farv + nearv) / (farv - nearv);
    matrix[15] = 1.0f;

    GLint uniform_loc = glGetUniformLocation(shader_program, "u_projection");
    glUniformMatrix4fv(uniform_loc, 1, GL_FALSE, matrix);
}

internal void flush_batch() {
    if (num_sprites == 0) {
        return;
    }

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, num_sprites * 4 * 7 * sizeof(f32), vertices);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(f32), (void *)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(f32), (void *)(2 * sizeof(f32)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(f32), (void *)(5 * sizeof(f32)));

    glDrawElements(GL_TRIANGLES, num_sprites * 6, GL_UNSIGNED_SHORT, NULL);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

    num_sprites = 0;
}

void graphics_init(s32 width, s32 height) {
    // Set the initial OpenGL state
    {
        glEnable(GL_CULL_FACE);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // TODO(zedzull): The clear color needs to be configurable
        glClearColor((100.0f / 255.0f), (149.0f / 255.0f), (237.0f / 255.0f), 1.0f);
    }

    // Create the shader program
    {
        GLuint vertex_shader = compile_shader(vertex_shader_src, GL_VERTEX_SHADER);
        GLuint fragment_shader = compile_shader(fragment_shader_src, GL_FRAGMENT_SHADER);

        GLuint shader_program = glCreateProgram();

        glBindAttribLocation(shader_program, 0, "a_pos");
        glBindAttribLocation(shader_program, 1, "a_color");
        glBindAttribLocation(shader_program, 2, "a_texcoord");

        glAttachShader(shader_program, vertex_shader);
        glAttachShader(shader_program, fragment_shader);
        glLinkProgram(shader_program);

        glUseProgram(shader_program);

        use_ortho_matrix(shader_program, 0.0f, width, height, 0.0f, -1.0f, 1.0f);
    }

    // Generate the index array
    {
        for (s32 i = 0, j = 0; i < MAX_INDICES; i += 6, j += 4) {
            indices[i + 0] = j + 0;
            indices[i + 1] = j + 1;
            indices[i + 2] = j + 2;
            indices[i + 3] = j + 3;
            indices[i + 4] = j + 0;
            indices[i + 5] = j + 2;
        }
    }

    // Create the vertex and index buffers
    {
        glGenBuffers(1, &vertex_buffer);
        glGenBuffers(1, &index_buffer);

        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), NULL, GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    }

    // Load the test image
    {
        s32 image_width;
        s32 image_height;
        u8 *data = stbi_load("game/test.png", &image_width, &image_height, NULL, 4);

        if (data) {
            GLuint texture;
            glGenTextures(1, &texture);

            glBindTexture(GL_TEXTURE_2D, texture);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

            stbi_image_free(data);
        }
        else {
            printf("Failed to load the test image!\n");
        }
    }
}

void graphics_begin_frame() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void graphics_end_frame() {
    flush_batch();
}

void graphics_draw_sprite(f32 x, f32 y, f32 width, f32 height) {
    if (num_sprites >= MAX_SPRITES) {
        flush_batch();
    }

    s32 index = num_sprites * 4 * 7;

    // top left
    vertices[index++] = x;
    vertices[index++] = y;
    vertices[index++] = 1.0f; // r
    vertices[index++] = 1.0f; // g
    vertices[index++] = 1.0f; // b
    vertices[index++] = 0.0f; // u
    vertices[index++] = 0.0f; // v

    // bottom left
    vertices[index++] = x;
    vertices[index++] = y + height;
    vertices[index++] = 1.0f; // r
    vertices[index++] = 1.0f; // g
    vertices[index++] = 1.0f; // b
    vertices[index++] = 0.0f; // u
    vertices[index++] = 1.0f; // v

    // bottom right
    vertices[index++] = x + width;
    vertices[index++] = y + height;
    vertices[index++] = 1.0f; // r
    vertices[index++] = 1.0f; // g
    vertices[index++] = 1.0f; // b
    vertices[index++] = 1.0f; // u
    vertices[index++] = 1.0f; // v

    // top right
    vertices[index++] = x + width;
    vertices[index++] = y;
    vertices[index++] = 1.0f; // r
    vertices[index++] = 1.0f; // g
    vertices[index++] = 1.0f; // b
    vertices[index++] = 1.0f; // u
    vertices[index++] = 0.0f; // v

    ++num_sprites;
}

void graphics_clear() {
    // TODO(zedzull): Remove this once the Lua function binding test that uses this isn't needed
}
