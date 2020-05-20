module Carbuncle
    module WEB
      class Emscripten < Carbuncle::Build
        def type
          'Web build using emscripten'
        end
  
        def flags
          []
        end
  
        def linker_flags
          [
          ]
        end
  
        def toolchain_name
          'clang'
        end
  
        def soloud_cmake_flags
          [
            "-DCMAKE_TOOLCHAIN_FILE=#{toolchain}",
            '-DSOLOUD_BACKEND_SDL2=OFF',
            '-DSOLOUD_BACKEND_MINIAUDIO=ON'
          ]
        end
      end
    end
  end
  