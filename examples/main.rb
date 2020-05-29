include MRGSS
begin
    class Test < Game
        def start
            sprite = Sprite.new
            p sprite
            bitmap = Bitmap.new("resources/groot.png")
            p bitmap
            sprite.bitmap = bitmap
            p sprite.src_rect
        end

        def update

        end

        def render
         
        end
    end

    game = Test.new(1024, 1024, "a game")
    game.run
rescue Exception => e
    p e
    gets
end