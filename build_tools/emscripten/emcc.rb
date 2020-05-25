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

      def linker_flags
        [
          '-s USE_GLFW=3',
          '-s USE_WEBGL2=1',
          '-s ASYNCIFY',
          '--use-preload-plugins',
          '-0',
        ]
      end

      def all_dependencies
        @all_dependencies ||= []
      end
      
      def libraries
        %w[  ]
      end

    end
  end
end
  