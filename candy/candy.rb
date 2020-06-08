begin
    require 'zip'
    require 'git'
    require 'open-uri'
    require 'find'
rescue LoadError
    puts 'Please, install the rubyzip and git gem, these are required to build'
    exit(1)
end

require_relative ('dependency')
require_relative ('dependencies/git')
require_relative ('compilation/cmake')
require_relative ('compilation/genie')
require_relative ('build/build')
require_relative ('build/linux')
require_relative ('build/mingw')

module Candy
    class Platform
        def detect(env)
            return detect_by_cross_build(env) if env.build.is_a?(MRuby::CrossBuild)
            detect_by_system(env)
        end

        def detect_by_cross_build(env)
        return windows_build(env) if /mingw/ =~ env.cc.command
        return emscripten_build(env) if /emcc/ =~ env.cc.command
        raise 'The only cross-build available for Builder is Windows with MingW.'
        end

        def detect_by_system(env)
        return osx_build(env) if /darwin/ =~ RUBY_PLATFORM
        return windows_build(env) if /mswin|mingw|win32/ =~ RUBY_PLATFORM
        linux_build(env)
        end

        def windows_build(env)
        return Mingw.new(env) if env.build.toolchains.include? 'gcc'
        raise 'Builder allows only MinGW builds for Windows for now.'
        end

        def linux_build(env)
            return Linux.new(env) if env.build.toolchains.include? 'gcc'
            raise 'Builder only allows GCC Builds on Linux for now.'
        end

        def emscripten_build
            raise "unimplemented build for Web" if env.build.toolchains.include? 'gcc'
            raise 'Builder only allows GCC Builds for Web for now.'
        end

        def osx_build(env)
            raise "unimplemented build for MacOS" if env.build.toolchains.include? 'clang'
            raise 'Builder allows only CLang builds on MacOS for now.'
        end
    end
end
