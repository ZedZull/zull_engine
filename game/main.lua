-- The screen size isn't communicated between Lua and C yet
SCREEN_WIDTH = 640
SCREEN_HEIGHT = 480
NUM_ENTITIES = 2048

function rect_t(x, y, w, h)
    local temp = {x=x, y=y, w=w, h=h,__type="__RECT__"}
    return temp
end

function animation_t(name)
    local temp = {delays={}, rects={}, image="", 
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

test_image = zull.graphics.load_texture("game/test.png")
test_animation = animation_t()
test_animation:add_frame(rect_t(0, 0, 16, 16), 2)
test_animation:add_frame(rect_t(16, 16, 16, 16), 2)
test_animation:add_frame(rect_t(0, 0, 32, 32), 2)
entities = {}

function create_entity()
    local entity = {}

    entity.x = math.random(0, SCREEN_WIDTH - 32)
    entity.y = math.random(0, SCREEN_HEIGHT - 32)

    if math.random(100) <= 50 then
        entity.vel_x = 50.0
    else
        entity.vel_x = -50.0
    end

    if math.random(100) <= 50 then
        entity.vel_y = 50.0
    else
        entity.vel_y = -50.0
    end

    return entity
end

function zull.init()
   math.randomseed(os.time())

    for i = 1, NUM_ENTITIES do
        entities[i] = create_entity()
    end
end

function zull.shutdown()

end

function zull.update(delta_time)
    test_animation:update(delta_time)
   for i = 1, NUM_ENTITIES do
        entities[i].x = entities[i].x + entities[i].vel_x * delta_time
        entities[i].y = entities[i].y + entities[i].vel_y * delta_time

        if entities[i].x <= 0.0 or entities[i].x + 32.0 >= SCREEN_WIDTH then
            entities[i].vel_x = -entities[i].vel_x
        end

        if entities[i].y <= 0.0 or entities[i].y + 32.0 >= SCREEN_HEIGHT then
            entities[i].vel_y = -entities[i].vel_y
        end
    end
end

function zull.draw()
    for i = 1, NUM_ENTITIES do
        zull.graphics.draw_sprite_ex(test_image, entities[i].x, entities[i].y, 32, 32,
            test_animation.cur_rect.x, test_animation.cur_rect.y, test_animation.cur_rect.w, test_animation.cur_rect.h)
    end
end
