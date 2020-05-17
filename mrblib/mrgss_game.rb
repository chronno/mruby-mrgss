module MRGSS
    class Game
        def initialize(width, height)
            screen_rect = MRGSS::Rectangle.new(400,400,width, height)
            @screen = MRGSS::Screen.new(screen_rect, "Game");
        end

        def update
            @screen.update
        end

        def run
            @screen.show
            while !@screen.disposed?
                update
                @screen.update
            end
        end
    end
end
