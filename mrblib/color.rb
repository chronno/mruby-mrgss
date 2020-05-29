
#============================================================================
# ** ::MRGSS
#----------------------------------------------------------------------------
#  This module contains all MRGSS Modules.
#============================================================================
module MRGSS
    #------------------------------------------------------------------------
    # * Color
    #------------------------------------------------------------------------
    # This Class represents a RGBA Color
    #------------------------------------------------------------------------
    class Color
        #--------------------------------------------------------------------
        # Acessors
        #--------------------------------------------------------------------
        attr_accessor :red
        attr_accessor :green
        attr_accessor :blue
        attr_accessor :alpha
        #--------------------------------------------------------------------
        # Set
        #--------------------------------------------------------------------
        def set(arg, green = 0, blue = 0, alpha = 0)
            if (arg.is_a?(MRGSS::Color))
                @red = arg.red
                @green = arg.green
                @blue = arg.blue
                @alpha = arg.alpha
            elsif (args.each {|f|  f.is_a? Numeric })
                @red = arg
                @green = green
                @blue = blue
                @alpha = alpha
            else 
                raise "TypeError Numeric expected"
            end
            return (@red == other.red and @green == other.green and @blue = other.blue and @alpha = other.alpha)
        end
        #--------------------------------------------------------------------
        # Equals
        #--------------------------------------------------------------------
        def ==(other) 
            return false unless other.is_a? MRGSS::Color
            return (@red == other.red and @green == other.green and @blue = other.blue and @alpha = other.alpha)
        end
    end
end