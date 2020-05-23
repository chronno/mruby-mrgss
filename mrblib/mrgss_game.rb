module MRGSS
    class Game
        def initialize(width, height)
            screen_rect = MRGSS::Rectangle.new(400,400,width, height)
            @screen = MRGSS::Screen.new(screen_rect, "Game");
        end

        def update
            
        end

        def render
            
        end
    end
end
