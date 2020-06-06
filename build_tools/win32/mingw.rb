module Builder
  module Win32
    class MinGW < Builder::Build
      def type
        'Windows using MinGW'
      end


      def libraries
        %w[ soloud glfw3 kazmath kernel32 user32 shell32 winmm gdi32 opengl32 ws2_32 ]
      end
      
      def soloud_cmake_flags
        [
          "-DCMAKE_TOOLCHAIN_FILE=#{toolchain}",
          '-DSOLOUD_BACKEND_SDL2=OFF',
          '-DSOLOUD_BACKEND_WINMM=ON',
          '-DSOLOUD_STATIC=ON'
  
        ]
      end

      def toolchain_name
        'mingw'
      end
    end
  end
end
