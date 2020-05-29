 module Builder
  module WEB
    class Emscripten < Builder::Build
      def type
        'Web build using emscripten'
      end

      def toolchain_name
        'emcc'
      end

      def flags
        [
          
        ]
      end

      def raylib_cmake_flags
        [
          '-DPLATFORM=Web',
          '-DSTATIC=ON',
          '-DBUILD_EXAMPLES=OFF',
          '-DBUILD_GAMES=OFF',
          "-DCMAKE_TOOLCHAIN_FILE=#{toolchain}",
          '-DSUPPORT_FILEFORMAT_BMP=ON',
          '-DSUPPORT_FILEFORMAT_JPG=ON',
        ]
      end

      def linker_flags
        [
        
        ]
      end

      def all_dependencies
        @all_dependencies ||= [kazmath]
      end
      
      def libraries
        %w[kazmath]
      end

    end
  end
end
  