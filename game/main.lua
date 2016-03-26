require "game/stdlib"
require "game/font"
require "game/player"
SCREEN_WIDTH = 640
SCREEN_HEIGHT = 480
NUM_ENTITIES = 2048


function zull.init()
    zull.graphics.clear_color(0, 0, 0)
end

function zull.shutdown()
end

function zull.input(event)
end

function zull.update(delta_time)
end

function zull.draw()
    player:draw()
end
