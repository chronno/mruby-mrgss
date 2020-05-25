module Builder
  class PlatformDetector
    attr_reader :env

    def initialize(env)
      @env = env
    end

    def detect
      return detect_by_cross_build if build.is_a?(MRuby::CrossBuild)
      detect_by_system
    end

    private

    def detect_by_cross_build
      return windows_build if /mingw/ =~ env.cc.command
      return emscripten_build if /emcc/ =~ env.cc.command
      raise 'The only cross-build available for Builder is Windows with MingW.'
    end

    def detect_by_system
      return osx_build if /darwin/ =~ RUBY_PLATFORM
      return windows_build if /mswin|mingw|win32/ =~ RUBY_PLATFORM

      linux_build
    end

    def osx_build
      return Builder::OSX::CLang.new(env) if toolchains.include? 'clang'

      raise 'Builder allows only CLang builds on MacOS for now.'
    end

    def windows_build
      return Builder::Win32::MinGW.new(env) if toolchains.include? 'gcc'

      raise 'Builder allows only MinGW builds for Windows for now.'
    end

    def linux_build
      return Builder::Linux::GCC.new(env) if toolchains.include? 'gcc'

      raise 'Builder only allows GCC Builds on Linux for now.'
    end

    def emscripten_build
      return Builder::WEB::Emscripten.new(env) if toolchains.include? 'gcc'

      raise 'Builder only allows GCC Builds for Web for now.'
    end

    def build
      env.build
    end

    def build_dir
      env.build_dir
    end

    def toolchains
      @toolchains ||= build.toolchains
    end
  end
end
