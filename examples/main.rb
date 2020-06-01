include MRGSS
#
# los sprites no deberian auto registrarse para ser dibujados deberia poder elegir cuales van a ser dibujados
# resolver este problema implica tambien evitar la necesidad de mantener el contexto del juego en una gb
#
begin
    class Test < Game
        def start
            @sprites = []
            @bitmap = Bitmap.new("resources/sheet.png")
            @count = 0
            build_sprite(104)
        end

        def build_sprite(quants)
            quants.times do |new|
                sprite = Sprite.new
                sprite.bitmap = @bitmap
                sprite.src_rect = Rect.new(0,96,144,96)
                sprite.origin_x = 72
                sprite.origin_y = 48
                sprite.x = (@sprites.size * 72) % 936
                sprite.y = ((@sprites.size * 72) / 936).to_i * 96
                @sprites.push(sprite)
            end
        end
        def update
            @count += 1
            if (@count % 100 == 0)
                @sprites.each do |sprite|
                    sprite.angle += 1
                    rect = sprite.src_rect
                    rect.x += 144
                    rect.x %= 576
                    sprite.src_rect = rect
                end
            end
        end

        def render(batch) 
            @sprites.each do |sprite|
                batch.add(sprite)
            end
        end
    end

    game = Test.new(1024, 800, "a game")
    game.run
rescue Exception => e
    p e
    gets
end
