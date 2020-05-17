include MRGSS
begin
    game = MRGSS::Game.new(640, 480)
    game.run
rescue Exception => e
    p e
end


