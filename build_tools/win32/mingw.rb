module Builder
  module Win32
    class MinGW < Builder::Build
      def type
        'Windows using MinGW'
      end


      def libraries
        %w[
          glfw3 kazmath kernel32 user32 shell32 winmm gdi32 opengl32 ws2_32
        ]
      end

      def toolchain_name
        'mingw'
      end
    end
  end
end
