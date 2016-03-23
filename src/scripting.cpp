static int clear_stack(lua_State *lua) {
    lua_pop(lua, lua_gettop(lua));
    return 0;
}

internal s32 lua_graphics_load_texture(lua_State *lua) {
    char *filename = (char *)lua_tostring(lua, 1);

    Texture texture = graphics_load_texture(filename);
    // Can't just push the texture as userdata because it gets
    // deleted after scope finishes
    lua_newtable(lua);
    lua_pushnumber(lua, texture.width);
    lua_setfield(lua, -2, "width");
    lua_pushnumber(lua, texture.height);
    lua_setfield(lua, -2, "height");
    lua_pushnumber(lua, texture.gl_handle);
    lua_setfield(lua, -2, "handle");
    // This should be used to determine if the proper type
    // is being passed into C functions from Lua
    lua_pushstring(lua, "__TEXTURE__");
    lua_setfield(lua, -2, "__type");
    return 1;
}

internal s32 lua_graphics_draw_sprite(lua_State *lua) {
    // TODO(zedzull): This is using hacked together texture loading (see below) until there's proper bindings
    // TODO(zedzull): This should probably check for the correct arguments
	luaL_checktype(lua, 1, LUA_TTABLE);
    lua_getfield(lua, 1, "__type");
    const char *type = luaL_checkstring(lua, -1);
    // Check if type == "__TEXTURE__"
    lua_getfield(lua, 1, "width");
    lua_getfield(lua, 1, "height");
    lua_getfield(lua, 1, "handle");
    int width = luaL_checknumber(lua, -3);
    int height = luaL_checknumber(lua, -2);
    GLuint handle = (GLuint)luaL_checknumber(lua, -1);
    Texture texture = { width, height, handle };
    f32 x = lua_tonumber(lua, 2);
    f32 y = lua_tonumber(lua, 3);

    graphics_draw_sprite(texture, x, y);
    clear_stack(lua);
    return 0;
}

internal s32 lua_runtime_error(lua_State *lua) {
    luaL_traceback(lua, lua, lua_tostring(lua, lua_gettop(lua)), 1);
    printf("%s\n", lua_tolstring(lua, lua_gettop(lua), NULL));

    exit(1);

    return 0;
}

internal s32 safe_lua_call(lua_State *lua, s32 num_args, s32 num_returns) {
    s32 error_handler_pos = lua_gettop(lua) - num_args;

    lua_pushcfunction(lua, lua_runtime_error);
    lua_insert(lua, error_handler_pos);

    s32 result = lua_pcall(lua, num_args, num_returns, error_handler_pos);

    lua_remove(lua, error_handler_pos);

    return result;
}

internal lua_State *lua;

bool script_init() {
    // TODO(zedzull): Texture loading is hacked on right here until there's proper bindings
    // Texture texture = graphics_load_texture("game/test.png");

    lua = luaL_newstate();
    luaL_openlibs(lua);

    lua_newtable(lua);

    // Bind graphics functions
    {
        lua_newtable(lua);

        lua_pushcfunction(lua, lua_graphics_load_texture);
        lua_setfield(lua, lua_gettop(lua) - 1, "load_texture");

        lua_pushcfunction(lua, lua_graphics_draw_sprite);
        lua_setfield(lua, lua_gettop(lua) - 1, "draw_sprite");

        lua_setfield(lua, lua_gettop(lua) - 1, "graphics");
    }

    lua_setglobal(lua, "zull");

    // TODO(zedzull): Loading the main script file should be more flexible (from a different directory, name, etc.)
    s32 status = luaL_loadfile(lua, "game/main.lua");

    if (status == LUA_ERRFILE) {
        printf("Could not load 'game/main.lua'!\n");
        return false;
    }

    if (status == LUA_ERRSYNTAX) {
        printf("%s\n", lua_tolstring(lua, lua_gettop(lua), NULL));
        return false;
    }

    safe_lua_call(lua, 0, 0);

    lua_getglobal(lua, "zull");
    lua_getfield(lua, lua_gettop(lua), "init");

    safe_lua_call(lua, 0, 0);

    return true;
}

// TODO(zedzull): If any of these built-in "callback" functions aren't present in the script, it generates a runtime error.
void script_update(f64 delta_time) {
    lua_getglobal(lua, "zull");
    lua_getfield(lua, lua_gettop(lua), "update");
    lua_pushnumber(lua, delta_time);

    safe_lua_call(lua, 1, 0);
}

void script_draw() {
    lua_getglobal(lua, "zull");
    lua_getfield(lua, lua_gettop(lua), "draw");

    safe_lua_call(lua, 0, 0);
}

void script_shutdown() {
    lua_getglobal(lua, "zull");
    lua_getfield(lua, lua_gettop(lua), "shutdown");

    safe_lua_call(lua, 0, 0);

    lua_close(lua);
}
