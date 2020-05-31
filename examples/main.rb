include MRGSS
#
# los sprites no deberian auto registrarse para ser dibujados deberia poder elegir cuales van a ser dibujados
# resolver este problema implica tambien evitar la necesidad de mantener el contexto del juego en una gb
#
begin
    class Test < Game
        def start
            rect = Rect.new(0,5,10,15)
            print "Rect: #{rect}\nX:#{rect.x}\nY:#{rect.y}\nWidth:#{rect.width}\nHeight:#{rect.height}"

        end

       
        def update
          
        end

        def render(batch) 
          
        end
    end

    game = Test.new(1024, 1024, "a game")
    game.run
rescue Exception => e
    p e
    gets
end
