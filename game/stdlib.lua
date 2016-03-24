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
    local temp = {img=img, animations={}, x=0, y=0, cur_anim="", scale=1}
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
            zull.graphics.draw_sprite_ex(self.img, self.x, self.y, self:get_anim().cur_rect.w * self.scale, self:get_anim().cur_rect.h * self.scale,
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
            x = x + (self.characters[c].w * self.scale)
        end
    end
    return temp
end