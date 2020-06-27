require_relative 'candy/candy'

MRuby::Gem::Specification.new('mruby-mrgss') do |spec|
  spec.license = 'MIT'
  spec.authors = 'Manuel Quinteros'
  spec.version = 0.1
  #----------------------------------------------------------------------------
  # Game Lib Dependencies
  #----------------------------------------------------------------------------
  platform = Candy::Platform.new.detect(self)
  platform.add_dependency("glfw3", 'git', "https://github.com/glfw/glfw.git", "../include", "libglfw3.a")
  platform.add_dependency("gl3w", 'git', "https://github.com/skaslev/gl3w.git", "include", "gl3w.c")
  platform.prepare
  #----------------------------------------------------------------------------
  # MRuby Dependencies
  #----------------------------------------------------------------------------
  spec.add_dependency('mruby-method', :core => 'mruby-method')
  #spec.add_dependency('mruby-mtest', :github => 'iij/mruby-mtest')
  #spec.add_dependency('mruby-errno', :github => 'iij/mruby-errno')
  
  #----------------------------------------------------------------------------
  # Compilation Flags
  #----------------------------------------------------------------------------
  spec.bins                       = %w[mruby-mrgss]
  spec.cc.flags                   << platform.flags
  spec.cxx.flags                  << platform.flags
  spec.build.cc.flags             << platform.flags
  spec.build.cxx.flags            << platform.flags
  spec.cc.include_paths           << platform.include_paths
  spec.cxx.include_paths          << platform.include_paths
  spec.build.cc.include_paths     << platform.include_paths
  spec.build.cxx.include_paths    << platform.include_paths
  spec.linker.library_paths       += platform.library_paths
  spec.linker.libraries           += platform.libs
  spec.build.libmruby             << platform.files
  
end