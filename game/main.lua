-- The screen size isn't communicated between Lua and C yet
SCREEN_WIDTH = 640
SCREEN_HEIGHT = 480
NUM_ENTITIES = 150

entities = {}

function create_entity()
    local entity = {}

    entity.x = math.random(0, SCREEN_WIDTH - 32)
    entity.y = math.random(0, SCREEN_HEIGHT - 32)

    if math.random(100) <= 50 then
        entity.vel_x = 0.0333
        entity.vel_y = 0.0333
    else
        entity.vel_x = -0.0333
        entity.vel_y = -0.0333
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

function zull.update()
    for i = 1, NUM_ENTITIES do
        entities[i].x = entities[i].x + entities[i].vel_x
        entities[i].y = entities[i].y + entities[i].vel_y

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
        zull.graphics.draw_sprite(entities[i].x, entities[i].y, 32.0, 32.0)
    end
end
