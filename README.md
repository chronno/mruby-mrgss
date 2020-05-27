# mruby-mrgss   [![Build Status](https://travis-ci.org/chronno/mruby-mrgss.svg?branch=dev)](https://travis-ci.org/chronno/mruby-mrgss)
MRGSS
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
p mrgss.hi
#=> "hi!!"
t = mrgss.new "hello"
p t.hello
#=> "hello"
p t.bye
#=> "hello bye"
```

## License
under the MIT License:
- see LICENSE file
