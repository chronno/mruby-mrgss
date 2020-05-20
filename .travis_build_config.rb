MRuby::Build.new do |conf|
  
  toolchain :gcc
  
  conf.gembox 'default'
  conf.gem File.expand_path(File.dirname(__FILE__))
  
  if ENV['DEBUG'] == 'true'
    conf.enable_debug
    conf.cc.defines = %w(MRB_ENABLE_DEBUG_HOOK)
    conf.gem core: 'mruby-bin-debugger'
  end
end

MRuby::CrossBuild.new('win32') do |conf|
  toolchain :gcc

  conf.gembox 'default'
  conf.gem File.expand_path(File.dirname(__FILE__))
  
  conf.cc.command = 'x86_64-w64-mingw32-gcc'
  conf.cxx.command = 'x86_64-w64-mingw32-g++'
  conf.linker.command = 'x86_64-w64-mingw32-gcc'
  conf.archiver.command = 'x86_64-w64-mingw32-ar'

  conf.linker.libraries += %w[wsock32 ws2_32]
  conf.linker.flags += %w[-static-libgcc -static-libstdc++]
  
  conf.exts.executable = '.exe'

  conf.cc.flags << '-DPCRE_STATIC'
  
  if ENV['DEBUG'] == 'true'
    conf.enable_debug
    conf.cc.defines = %w(MRB_ENABLE_DEBUG_HOOK)
    conf.gem core: 'mruby-bin-debugger'
  end
end

MRuby::CrossBuild.new('emscipten') do |conf|
  toolchain :clang
  conf.gembox 'default'
  conf.cc.command = 'emcc'
  conf.cc.flags = %W(-Os)
  conf.linker.command = 'emcc'
  conf.archiver.command = 'emar'
  
  if ENV['DEBUG'] == 'true'
    conf.enable_debug
    conf.cc.defines = %w(MRB_ENABLE_DEBUG_HOOK)
    conf.gem core: 'mruby-bin-debugger'
  end
end

