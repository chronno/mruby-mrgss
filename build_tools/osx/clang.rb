module Carbuncle
  module OSX
    class CLang < Carbuncle::Build
      def type
        'Mac OSX using CLang'
      end

      def flags
        []
      end

      def linker_flags
        [
          '-framework OpenGL',
          '-framework OpenAL',
          '-framework IOKit',
          '-framework CoreVideo',
          '-framework CoreAudio',
          '-framework AudioToolbox',
          '-framework Cocoa'
        ]
      end

      def toolchain_name
        'clang'
      end
    end
  end
end
