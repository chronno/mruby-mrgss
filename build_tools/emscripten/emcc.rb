module Carbuncle
  module WEB
    class Emscripten < Carbuncle::Build
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

      def linker_flags
        [
          '-s USE_GLFW=3',
          '-s ASYNCIFY',
          '--use-preload-plugins',
          '-03'
        ]
      end

      def all_dependencies
        []
      end
      
      def libraries
        []
      end

    end
  end
end
  