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
  platform.add_dependency("gl3w", 'git', "https://github.com/skaslev/gl3w.git", "include", "gl3w.c")
  platform.add_dependency("kazmath", 'git', "https://github.com/Kazade/kazmath.git", "../kazmath", "libkazmath.a", ['-DKAZMATH_BUILD_TESTS=OFF','-DKAZMATH_BUILD_JNI_WRAPPER=OFF','-DKAZMATH_BUILD_LUA_WRAPPER=OFF'])
  platform.add_dependency("soloud_static", 'git', "https://github.com/jarikomppa/soloud.git", "../include", "libsoloud_static.a", ["--with-miniaudio-only", "--with-tools", "gmake"], "genie")
  platform.fetch
  platform.compile
  platform.join
  #----------------------------------------------------------------------------
  # MRuby Dependencies
  #----------------------------------------------------------------------------
  #spec.add_dependency('mruby-mtest', :github => 'iij/mruby-mtest')
  #spec.add_dependency('mruby-errno', :github => 'iij/mruby-errno')
  
  #----------------------------------------------------------------------------
  # Compilation Flags
  #----------------------------------------------------------------------------
  spec.cc.flags          << platform.flags
  spec.build.cc.flags    << platform.flags
  spec.cc.include_paths  << platform.include_paths
  spec.cxx.include_paths << platform.include_paths
  # include_dir = [File.join(dir, 'include'), File.join(dir, 'include', "**", "*.h") ]
  # spec.build.cc.include_paths  += platform.include_paths + include_dir
  # spec.build.cxx.include_paths += platform.include_paths + include_dir
  
  spec.linker.library_paths += platform.library_paths
  spec.linker.libraries += platform.libs
  spec.build.linker.library_paths += platform.library_paths
  p platform.libs
  spec.build.linker.libraries += platform.libs
  #spec.build.libmruby << platform.files
end