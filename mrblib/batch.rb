module MRGSS
    class Batch

        def initialize
            @drawables = []
        end

        def add(object)
            @drawables.push(object);
        end

        def sort
            
        end

        def reset
            @drawables.clear
        end
    end
end




