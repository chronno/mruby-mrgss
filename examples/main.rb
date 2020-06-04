include MRGSS

begin
    class Test < Game
        def start
            @sprites = []
            @bitmap = Bitmap.new("resources/sheet.png")
            build_sprite(1)
        end

        def build_sprite(quants)
            quants.times do |new|
                sprite = Sprite.new(viewport)
                sprite.bitmap = @bitmap
                sprite.src_rect = Rect.new(0,96,144,96)
                sprite.origin_x = 72
                sprite.origin_y = 48
                sprite.x = (@sprites.size * 28) % 1036
                sprite.y = (@sprites.size * 28 / 1036).to_i * 48
                @sprites.push(sprite)
            end
        end

        def update
            if Mouse.click?(Mouse::BUTTON_LEFT)
                @sprites[0].x = Mouse.x - 72
                @sprites[0].y = Mouse.y - 48
            end
            print Mouse.press_time?(Mouse::BUTTON_LEFT)
        end
    end

    game = Test.new(1024, 768, "a game")
    game.run
rescue Exception => e
    p e
    gets
end
