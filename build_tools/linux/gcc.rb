module Builder
  module Linux
    class GCC < Builder::Build
      def type
        'Linux using GCC'
      end

      def libraries
        %w[
          soloud glfw3 kazmath z m dl pthread X11 xcb GL Xext Xau Xdmcp 
        ]
      end

      def toolchain_name
        'gcc'
      end
      def soloud_cmake_flags
        [
          "-DCMAKE_TOOLCHAIN_FILE=#{toolchain}",
          '-DSOLOUD_BACKEND_SDL2=OFF',
          '-DSOLOUD_BACKEND_ALSA=ON'
        ]
      end
      def linker_flags
        [
        ]
      end
    end
  end
end
