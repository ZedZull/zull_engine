-- The screen size isn't communicated between Lua and C yet
SCREEN_WIDTH = 640
SCREEN_HEIGHT = 480
NUM_ENTITIES = 2048

function rect_t(x, y, w, h)
    local temp = {x=x, y=y, w=w, h=h,__type="__RECT__"}
    return temp
end

function animation_t()
    local temp = {delays={}, rects={}, 
    cur_frame=1,cur_delay=0,cur_rect=nil,
    __type="__ANIMATION__"}
    function temp:add_frame(rect, delay)
        table.insert(self.rects, rect)
        table.insert(self.delays, delay)
        if self.cur_rect == nil then self.cur_rect = self.rects[1] end
    end
    function temp:remove_frame(i)
        table.remove(self.rects, i)
        table.remove(self.delays, i)
    end
    function temp:update(delta)
        self.cur_delay = self.cur_delay + delta
        if self.cur_delay >= self.delays[self.cur_frame] then
            self.cur_delay = 0
            self.cur_frame = self.cur_frame + 1
            -- TODO: Add support for animation play types
            if self.cur_frame > #self.rects then self.cur_frame = 1 end
            self.cur_rect = self.rects[self.cur_frame]
        end
    end
    return temp
end

function sprite_t(img)
    if type(img) == "string" then img = zull.graphics.load_texture(img) end
    local temp = {img=img, animations={}, x=0, y=0, cur_anim=""}
    function temp:add_anim(name, anim)
        self.animations[name] = anim
    end
    function temp:play_anim(name)
        self.cur_anim = name
    end
    function temp:stop_anim()
        self.cur_anim = ""
    end
    function temp:get_anim() 
        if self.cur_anim == "" then return nil end
        return self.animations[self.cur_anim]
    end
    function temp:update(delta, fn)
        if self.cur_anim ~= "" then self.animations[self.cur_anim]:update(delta) end
        if fn ~= nil then fn(delta) end
    end
    function temp:draw()
        if self.cur_anim == "" then
            zull.graphics.draw_sprite(self.img, self.x, self.y)
        else
            zull.graphics.draw_sprite_ex(self.img, self.x, self.y, self:get_anim().cur_rect.w, self:get_anim().cur_rect.h,
                self:get_anim().cur_rect.x, self:get_anim().cur_rect.y, 
                self:get_anim().cur_rect.w, self:get_anim().cur_rect.h)
        end
    end
    return temp
end

function font_t(img)
    if type(img) == "string" then img = zull.graphics.load_texture(img) end
    local temp = {img=img, characters={}, scale=1}   
    function temp:add_char(c, rect)
        self.characters[c] = rect
    end
    function temp:draw_text(text, x, y)
        local x = x
        local y = y
        for i=1, #text do
            local c = text:sub(i, i)
            zull.graphics.draw_sprite_ex(self.img, x, y, self.characters[c].w * self.scale, self.characters[c].h * self.scale,
                                        self.characters[c].x, self.characters[c].y, self.characters[c].w, self.characters[c].h)
            x = x + self.characters[c].w
        end
    end
    return temp
end

test_font = font_t("game/loveable_rogue.png")
test_font:add_char('a', rect_t(0, 0, 8, 8))
test_font:add_char('b', rect_t(8, 0, 8, 8))
test_font:add_char('c', rect_t(16, 0, 8, 8))
test_font:add_char('d', rect_t(24, 0, 8, 8))
test_font:add_char('e', rect_t(32, 0, 8, 8))
test_font:add_char('f', rect_t(40, 0, 8, 8))
test_font:add_char('g', rect_t(48, 0, 8, 8))
test_font:add_char('h', rect_t(56, 0, 8, 8))
test_font:add_char('i', rect_t(64, 0, 8, 8))
test_font:add_char('j', rect_t(72, 0, 8, 8))
test_font:add_char('k', rect_t(80, 0, 8, 8))
test_font:add_char('l', rect_t(88, 0, 8, 8))
test_font:add_char('m', rect_t(96, 0, 8, 8))
test_font:add_char('n', rect_t(104, 0, 8, 8))
test_font:add_char('o', rect_t(112, 0, 8, 8))
test_font:add_char('p', rect_t(120, 0, 8, 8))
test_font:add_char('q', rect_t(128, 0, 8, 8))
test_font:add_char('r', rect_t(136, 0, 8, 8))
test_font:add_char('s', rect_t(144, 0, 8, 8))
test_font:add_char('t', rect_t(152, 0, 8, 8))
test_font:add_char('u', rect_t(160, 0, 8, 8))
test_font:add_char('v', rect_t(168, 0, 8, 8))
test_font:add_char('w', rect_t(176, 0, 8, 8))
test_font:add_char('x', rect_t(184, 0, 8, 8))
test_font:add_char('y', rect_t(192, 0, 8, 8))
test_font:add_char('z', rect_t(200, 0, 8, 8))
test_font:add_char(' ', rect_t(208, 0, 8, 8))
test_font:add_char('0', rect_t(0, 16, 8, 8))
test_font:add_char('1', rect_t(8, 16, 8, 8))
test_font:add_char('2', rect_t(16, 16, 8, 8))
test_font:add_char('3', rect_t(24, 16, 8, 8))
test_font:add_char('4', rect_t(32, 16, 8, 8))
test_font:add_char('5', rect_t(40, 16, 8, 8))
test_font:add_char('6', rect_t(48, 16, 8, 8))
test_font:add_char('7', rect_t(56, 16, 8, 8))
test_font:add_char('8', rect_t(64, 16, 8, 8))
test_font:add_char('9', rect_t(72, 16, 8, 8))
test_font:add_char(':', rect_t(80, 16, 8, 8))
test_font:add_char('/', rect_t(104, 16, 8, 8))



function zull.init()
end

function zull.shutdown()
end

function zull.input(event)
end

function zull.update(delta_time)
end

function zull.draw()
    test_font:draw_text('hp: 10/10', 0, 0)
end
