module Candy
    class Emscripten < Candy::Build

        def libraries
            %w[ ]
          end

        def toolchain_name
            'gcc'
        end

    end
end