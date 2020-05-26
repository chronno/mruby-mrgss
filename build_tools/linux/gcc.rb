module Builder
  module Linux
    class GCC < Builder::Build
      def type
        'Linux using GCC'
      end

      def libraries
        %w[
          raylib z m dl pthread X11 xcb GL Xext Xau Xdmcp
        ]
      end

      def toolchain_name
        'gcc'
      end

      def linker_flags
        [
          '-no-pie'
        ]
      end
    end
  end
end
