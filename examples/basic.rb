include MRGSS
begin
    screen = Screen.new(Rectangle.new(40,40,640,480), "Hello World")
    
rescue Exception => e
    p e
end


