include MRGSS
begin
    class Example < Game
        def initialize
            super(640,480)
            @rect = Rectangle.new(0,0,200,100);
            @color = Color.new(0,0,0,255)
            @size = 5
        end

        def update            
            if @font.nil?
                @font = Font.new
            end
            @rect.x += 1
            @rect.x %= 680
            @size += 1
            @size %= 100
            @color.r +=1
            @color.r %=255 
        end

        def render
            @font.draw_text("un texto", @rect, @size, 1, true, @color)
        end
    end
    game = Example.new
    game.run
rescue Exception => e
    p e
end