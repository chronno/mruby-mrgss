require_relative 'candy/candy'

MRuby::Gem::Specification.new('mruby-mrgss') do |spec|
  spec.license = 'MIT'
  spec.authors = 'Manuel Quinteros'
  spec.version = 0.1
  spec.bins = %w[mruby-mrgss]
  #----------------------------------------------------------------------------
  # Game Lib Dependencies
  #----------------------------------------------------------------------------
  platform = Candy::Platform.new.detect(self)
  platform.add_dependency("glfw3", 'git', "https://github.com/glfw/glfw.git", "../include", "libglfw3.a")
  platform.add_dependency("kazmath", 'git', "https://github.com/Kazade/kazmath.git", "../kazmath", "libkazmath.a", ['-DKAZMATH_BUILD_TESTS=OFF','-DKAZMATH_BUILD_JNI_WRAPPER=OFF','-DKAZMATH_BUILD_LUA_WRAPPER=OFF'])
  platform.prepare
  #----------------------------------------------------------------------------
  # MRuby Dependencies
  #----------------------------------------------------------------------------
  #spec.add_dependency('mruby-mtest', :github => 'iij/mruby-mtest')
  #spec.add_dependency('mruby-errno', :github => 'iij/mruby-errno')
  
  #----------------------------------------------------------------------------
  # Compilation Flags
  #----------------------------------------------------------------------------
  spec.cc.flags             << platform.flags
  spec.cxx.flags            << platform.flags
  spec.cc.include_paths     << platform.include_paths
  spec.cxx.include_paths    << platform.include_paths
  spec.linker.library_paths += platform.library_paths
  spec.linker.libraries     += platform.libs
end