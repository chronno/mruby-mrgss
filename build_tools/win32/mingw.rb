module Carbuncle
  module Win32
    class MinGW < Carbuncle::Build
      def type
        'Windows using MinGW'
      end

      def libraries
        %w[
          raylib_static freetype physfs tmx soloud
          mbedtls mbedcrypto mbedx509
          xml2 zlibstatic kernel32 user32 shell32 winmm gdi32 opengl32 ws2_32
        ]
      end

      def toolchain_name
        'mingw'
      end

      def raylib_library
        'libraylib_static.a'
      end

      def soloud_cmake_flags
        [
          "-DCMAKE_TOOLCHAIN_FILE=#{toolchain}",
          '-DSOLOUD_BACKEND_SDL2=OFF',
          '-DSOLOUD_BACKEND_WINMM=ON'
        ]
      end
    end
  end
end
