player = sprite_t("game/loveable_rogue.png")
player_idle = animation_t()
player_idle:add_frame(rect_t(96, 144, 16, 16), 0)
player:add_anim("idle", player_idle)
player:play_anim("idle")
player.x = 100
player.y = 100
player.scale = 2