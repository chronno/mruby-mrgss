module MRGSS
    class Batch

        def initialize
            @drawables = []
        end

        def add(object)
            @drawables.push(object);
        end
    end
end