# mruby-mrgss   [![Build Status](https://travis-ci.org/chronno/mruby-mrgss.svg?branch=dev)](https://travis-ci.org/chronno/mruby-mrgss)
 
 mruby-mrgss is a small framework to create cross platform 2d games in a simple way 

## install by mrbgems
- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

    # ... (snip) ...

    conf.gem :github => 'chronno/mruby-mrgss'
end
```
## example
```ruby
class Test < Game
    def initialize
        super
        screen.on_move = method(:on_change_position)
        screen.on_resize = method(:on_change_position)
        screen.on_focus = method(:on_change_focus)
        screen.on_close = method(:on_window_close)
    end

    def on_change_position(x, y)
        p "cambio! #{x} : #{y}"
    end

    def on_change_focus(focused)
        p "is focused #{focused}"
    end

    def on_window_close
        #return wheter or not you want the window to be closed
        true
    end

end
    game = Test.new
    game.start
```

## License
under the MIT License:
- see LICENSE file
