module Carbuncle
  class Build
    attr_reader :env

    def initialize(env)
      @env = env
      Carbuncle::Console.header("Detecting Carbuncle build for #{type}.")
    end

    def build_dependencies
      all_dependencies.each(&:build)
    end
    
    def glfw
      @glfw ||= Carbuncle::Dependencies::GLFW.new(self)
    end

    def library_paths
      all_dependencies.map(&:lib_dir)
    end

    def libraries
      %w[glfw]
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

    def all_dependencies
      @all_dependencies ||= [glfw]
    end
  end
end
