include MRGSS
begin
    game = Game.new("a game", Rect.new(0,0,640,480), false)
    game.start
rescue Exception => e
    p e
end