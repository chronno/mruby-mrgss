module Candy
    class Emscripten < Candy::Build

        def emcc_included
            ["glfw3"]
        end

        def libs
            ary = [] 
            ary << @dependencies.filter_map {|dep| dep.name if dep.lib =~ /.*\.a$/ && !emcc_included.include?(dep.name)}
            ary << libraries
            ary.flatten
        end

        def libraries
            %w[ ]
          end

        def toolchain_name
            'gcc'
        end

    end
end