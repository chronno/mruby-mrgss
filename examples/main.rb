include MRGSS

begin
    class Test < Game
        def on_change_position(x, y)
            p "cambio! #{x} : #{y}"
        end

        def on_change_focus(focused)
            p "is focused #{focused}"
        end

        def on_window_close
            true
        end

        def start 
            screen.on_move = method(:on_change_position)
            screen.on_resize = method(:on_change_position)
            screen.on_focus = method(:on_change_focus)
            screen.on_close = method(:on_window_close)
            bitmap = Bitmap.new("resources/groot.png")
            screen.icon = bitmap
            sprite = Sprite.new
        end

        def update
        end

    end
    game = Test.new
    game.run
rescue Exception => e
    p e
end



