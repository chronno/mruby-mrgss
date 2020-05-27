include MRGSS
begin
    class Test < Game
        def start
            @sprites = []
            @frame = 0;
            @bmp = MRGSS::Bitmap.new("noblend.png")
        end

            
        def build(i)
            i.times do |f|
                spr = MRGSS::Sprite.new(@bmp)
                spr.x = (@bmp.width * @sprites.size) % 800
                spr.y = (@bmp.width * @sprites.size) / 800
                @sprites.push(spr)
            end
        end

        def update
            @frame +=1
            build(10000000) if @sprites.empty?
		    # if(@sprites.size < 1000) 
			#     build(1000)
		    # end
		    # p @frame
        end

        def render
            # for item in @sprites
            #     item.draw
            # end
            
        end
    end
    game = Test.new("a game", 800, 800, false)
    game.run
rescue Exception => e
    p e
    gets
end