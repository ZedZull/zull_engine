require "game/stdlib"
SCREEN_WIDTH = 640
SCREEN_HEIGHT = 480
NUM_ENTITIES = 2048

main_font = font_t("game/loveable_rogue.png")
main_font:add_char('a', rect_t(0, 0, 8, 8))
main_font:add_char('b', rect_t(8, 0, 8, 8))
main_font:add_char('c', rect_t(16, 0, 8, 8))
main_font:add_char('d', rect_t(24, 0, 8, 8))
main_font:add_char('e', rect_t(32, 0, 8, 8))
main_font:add_char('f', rect_t(40, 0, 8, 8))
main_font:add_char('g', rect_t(48, 0, 8, 8))
main_font:add_char('h', rect_t(56, 0, 8, 8))
main_font:add_char('i', rect_t(64, 0, 8, 8))
main_font:add_char('j', rect_t(72, 0, 8, 8))
main_font:add_char('k', rect_t(80, 0, 8, 8))
main_font:add_char('l', rect_t(88, 0, 8, 8))
main_font:add_char('m', rect_t(96, 0, 8, 8))
main_font:add_char('n', rect_t(104, 0, 8, 8))
main_font:add_char('o', rect_t(112, 0, 8, 8))
main_font:add_char('p', rect_t(120, 0, 8, 8))
main_font:add_char('q', rect_t(128, 0, 8, 8))
main_font:add_char('r', rect_t(136, 0, 8, 8))
main_font:add_char('s', rect_t(144, 0, 8, 8))
main_font:add_char('t', rect_t(152, 0, 8, 8))
main_font:add_char('u', rect_t(160, 0, 8, 8))
main_font:add_char('v', rect_t(168, 0, 8, 8))
main_font:add_char('w', rect_t(176, 0, 8, 8))
main_font:add_char('x', rect_t(184, 0, 8, 8))
main_font:add_char('y', rect_t(192, 0, 8, 8))
main_font:add_char('z', rect_t(200, 0, 8, 8))
main_font:add_char(' ', rect_t(208, 0, 8, 8))
main_font:add_char('0', rect_t(0, 16, 8, 8))
main_font:add_char('1', rect_t(8, 16, 8, 8))
main_font:add_char('2', rect_t(16, 16, 8, 8))
main_font:add_char('3', rect_t(24, 16, 8, 8))
main_font:add_char('4', rect_t(32, 16, 8, 8))
main_font:add_char('5', rect_t(40, 16, 8, 8))
main_font:add_char('6', rect_t(48, 16, 8, 8))
main_font:add_char('7', rect_t(56, 16, 8, 8))
main_font:add_char('8', rect_t(64, 16, 8, 8))
main_font:add_char('9', rect_t(72, 16, 8, 8))
main_font:add_char(':', rect_t(80, 16, 8, 8))
main_font:add_char('/', rect_t(104, 16, 8, 8))



function zull.init()
end

function zull.shutdown()
end

function zull.input(event)
end

function zull.update(delta_time)
end

zull.graphics.clear_color(0, 0, 0)
function zull.draw()
    main_font.scale = 1.5
    main_font:draw_text('darithorn is awesome', 0, 0)
end
