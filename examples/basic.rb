include MRGSS
begin
    rect = Rect.new
    p rect
rescue Exception => e
    p e
end