begin
    rect_a = MRGSS::Rectangle.new(0, 0, 10, 10)
    rect_b = MRGSS::Rectangle.new(1, 1,  8,  8)
    
    print rect_b.contained_by?(rect_a)
    puts "\n"
    print rect_a.containing(rect_b)
rescue
    print "falló"
end


