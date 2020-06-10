module Candy
    class Mingw < Candy::Build

        def libraries
            %w[ kernel32 user32 shell32 winmm gdi32 opengl32 ws2_32 ]
        end

        def toolchain_name
            'mingw'
        end

    end
end