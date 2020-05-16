module MRGSS
    class Rectangle
        def inside(other)
            starts_inside = self.x > other.x && self.y > other.y
            ends_inside = (self.width + self.x < other.width + other.x) && (self.height + self.y < other.height + other.y)
            return  starts_inside && ends_inside
        end
    end
end