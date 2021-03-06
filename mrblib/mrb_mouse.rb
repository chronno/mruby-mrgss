#============================================================================
# ** ::MRGSS
#----------------------------------------------------------------------------
#  This module contains all MRGSS Modules.
#============================================================================
module MRGSS
    #------------------------------------------------------------------------
    # * Mouse 
    #------------------------------------------------------------------------
    # This Class represents the mouse input
    #------------------------------------------------------------------------
    module Mouse
      #----------------------------------------------------------------------
      # Buttons status buffer
      #----------------------------------------------------------------------
      @trigger = Array.new(8).fill(false)
      @release = Array.new(8).fill(false)
      @press = Array.new(8).fill(false)
      @repeat = Array.new(8).fill(false)
      @time = Array.new(8).fill(0)
      #----------------------------------------------------------------------
      # Buttons constants
      #----------------------------------------------------------------------
      BUTTON_LEFT     = 0
      BUTTON_RIGHT    = 1
      BUTTON_MIDDLE   = 2
      BUTTON_4        = 3
      BUTTON_5        = 4
      BUTTON_6        = 5
      BUTTON_7        = 6
      BUTTON_8        = 7
      #----------------------------------------------------------------------
      # X Attribute Accessor
      #----------------------------------------------------------------------
      def self.x 
        @x
      end
      #----------------------------------------------------------------------
      # Y Attribute Accessor
      #----------------------------------------------------------------------
      def self.y
        @y
      end
      #----------------------------------------------------------------------
      # update the mouse position whenever the mose moves
      #----------------------------------------------------------------------
      def self.update_position(x, y)
        @x = x
        @y = y
      end
      #----------------------------------------------------------------------
      # update the mouse buttons whenever something change
      #----------------------------------------------------------------------
      def self.update_buttons(button, action)
        @trigger[button] = action == 1 && @time[button] == 0
        @release[button] = action == 0 
        @time[button] = action == 1 ? @time[button] + 1 : 0
        @press[button] = action != 0 && @time[button] > 1
      end
      #----------------------------------------------------------------------
      # click?
      #----------------------------------------------------------------------
      def self.click?(button)
        @trigger[button]
      end
      #----------------------------------------------------------------------
      # pressed?
      #----------------------------------------------------------------------
      def self.press?(key)
        return @press[key] 
      end
      #----------------------------------------------------------------------
      # released?
      #----------------------------------------------------------------------
      def self.release?(key)
        return @release[key] 
      end
      #----------------------------------------------------------------------
      # Time pressed
      #----------------------------------------------------------------------
      def self.press_time?(key)
        return @time[key] 
      end
    end
  end