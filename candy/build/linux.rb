module Candy
    class Linux < Candy::Build

        def libraries
            %w[ z m dl pthread X11 xcb GL Xext Xau Xdmcp ]
          end

        def toolchain_name
            'gcc'
        end

    end
end