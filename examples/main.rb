include MRGSS
begin
    class Test < Game
        def start
            bitmap = Bitmap.new("groot.png")
            @sprite = Sprite.new(bitmap)
        end

        def update

        end

        def render
            @sprite.draw
        end
    end
    game = Test.new("a game", 640, 480, false)
    game.run
rescue Exception => e
    p e
end