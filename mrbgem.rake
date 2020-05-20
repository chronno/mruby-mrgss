require 'open-uri'

begin
  require 'zip'
rescue LoadError
  puts 'Please, install the rubyzip gem `gem install rubyzip`, it is required to build'
  exit(1)
end

require_relative 'build_tools/platform_detector'
require_relative 'build_tools/console'


require_relative 'build_tools/build'
require_relative 'build_tools/linux/gcc'
require_relative 'build_tools/osx/clang'
require_relative 'build_tools/win32/mingw'

require_relative 'build_tools/dependency'
require_relative 'build_tools/dependencies/freetype'
require_relative 'build_tools/dependencies/raylib'
require_relative 'build_tools/dependencies/zlib'
require_relative 'build_tools/dependencies/libxml2'
require_relative 'build_tools/dependencies/tmx'
require_relative 'build_tools/dependencies/physfs'
require_relative 'build_tools/dependencies/soloud'
require_relative 'build_tools/dependencies/libwebsockets'
require_relative 'build_tools/dependencies/mbedtls'
require_relative 'build_tools/dependencies/glfw'

MRuby::Gem::Specification.new('mruby-mrgss') do |spec|
  spec.license = 'MIT'
  spec.authors = 'Manuel Quinteros'
  spec.version = 0.1
  
  #----------------------------------------------------------------------------
  # Game Lib Dependencies
  #----------------------------------------------------------------------------
  platform = Carbuncle::PlatformDetector.new(self).detect
  platform.build_dependencies

  #----------------------------------------------------------------------------
  # MRuby Dependencies
  #----------------------------------------------------------------------------
  spec.add_dependency('mruby-mtest', :github => 'iij/mruby-mtest')
  spec.add_dependency('mruby-errno', :github => 'iij/mruby-errno')
  
  #----------------------------------------------------------------------------
  # Compilation Flags
  #----------------------------------------------------------------------------
  spec.cc.flags          << platform.flags
  spec.build.cc.flags    << platform.flags
  spec.cc.include_paths  << platform.include_paths
  spec.cxx.include_paths << platform.include_paths

  include_dir = [File.join(dir, 'include')]
  spec.build.cc.include_paths  += platform.include_paths + include_dir
  spec.build.cxx.include_paths += platform.include_paths + include_dir

  spec.linker.library_paths += platform.library_paths
  spec.linker.libraries += platform.libraries
  spec.linker.flags += platform.linker_flags
  spec.build.linker.library_paths += platform.library_paths
  spec.build.linker.libraries += platform.libraries
  spec.build.linker.flags += platform.linker_flags
end
