module Builder
  class Build
    attr_reader :env

    def initialize(env)
      @env = env
      Builder::Console.header("Detecting Builder build for #{type}.")
    end

    def build_dependencies
      all_dependencies.each(&:build)
    end
    
    def glfw
      @glfw ||= Builder::Dependencies::GLFW.new(self)
    end

    def gl3w
      @gl3w ||= Builder::Dependencies::GL3W.new(self)
    end

    def raylib
      @raylib ||= Builder::Dependencies::Raylib.new(self)
    end

    def library_paths
      all_dependencies.map(&:lib_dir)
    end

    def libraries
      %w[raylib]
    end

    def glfw_cmake_flags
      [
        '-DPLATFORM=Desktop',
        '-DSTATIC=ON',
        '-DBUILD_EXAMPLES=OFF',
        '-DBUILD_GAMES=OFF',
        "-DCMAKE_TOOLCHAIN_FILE=#{toolchain}",
        '-DSUPPORT_FILEFORMAT_BMP=ON',
        '-DSUPPORT_FILEFORMAT_JPG=ON',
      ]
    end

    def raylib_cmake_flags
      [
        '-DPLATFORM=Desktop',
        '-DSTATIC=ON',
        '-DBUILD_EXAMPLES=OFF',
        '-DBUILD_GAMES=OFF',
        "-DCMAKE_TOOLCHAIN_FILE=#{toolchain}",
        '-DSUPPORT_FILEFORMAT_BMP=ON',
        '-DSUPPORT_FILEFORMAT_JPG=ON',
      ]
    end

    def gl3w_cmake_flags
      [
        # "-G\"MSYS Makefiles\"",
        "-DCMAKE_TOOLCHAIN_FILE=#{toolchain}"
      ]
    end
 
    def include_paths
      all_dependencies.map(&:include_paths).flatten
    end

    def toolchain
      @toolchain ||= File.join(env.dir, 'build_tools', 'toolchains', "#{toolchain_name}.cmake")
    end

    def flags
      ['-DZLIB_WINAPI']
    end

    def linker_flags
      []
    end

    def library_extension
      'a'
    end

    def glfw_library
      'libglfw3.a'
    end

    def raylib_library
      'libraylib.a'
    end

    def gl3w_library
      
    end

    def all_dependencies
      @all_dependencies ||= [raylib]
    end

    def files
      all_dependencies.map(&:add_to_build).flatten
    end
  end
end
