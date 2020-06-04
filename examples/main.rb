include MRGSS

begin
    class Test < Game
        def start
            @sprites = []
            @bitmap = Bitmap.new("resources/sheet.png")
            @count = 0
            @first_time = true
        end

        def build_sprite(quants)
            return if @sprites.size >= 100000
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
            print "#{@sprites.size}\n"
        end

        def update
            
            @count += 1
            if (@count % 20 == 0)
                build_sprite(100)
                @count = 0
                if(@sprites.size == 100000)
                    @sprites.each do |sprite|
                        sprite.angle += 1
                        rect = sprite.src_rect
                        rect.x += 144
                        rect.x %= 576
                        sprite.src_rect = rect
                    end
                end
            end
        end
    end

    game = Test.new(1024, 768, "a game")
    game.run
rescue Exception => e
    p e
    gets
end
