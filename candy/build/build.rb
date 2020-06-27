module Candy
    class Build
        def initialize(env)
            @env = env
            @downloads_dir = File.join(@env.build.build_dir, 'downloads')
            @join_dir = File.join(@env.build.build_dir, 'build')
            @dependencies = []
        end

        def toolchain
            File.join(@env.dir, 'candy', 'toolchains', "#{toolchain_name}.cmake")
        end

        def add_dependency(name, fetchformat, source, includes, lib = nil, flags=[], tool="cmake")
            case fetchformat
            when 'git'
                dep = Candy::Git.new(name, source, lib, includes, flags, tool)
                dep.env = @env
                @dependencies.push(dep)
            else
                print "unknown fetch format"
            end
        end

        def fetch
            FileUtils.mkdir_p(@downloads_dir)
            @dependencies.each do |dependency|
                dependency.fetch(@downloads_dir)
            end
        end

        def compile
            @dependencies.each do |dependency|
                dependency.compile(@downloads_dir, toolchain) unless dependency.compiled?(@join_dir)
            end
        end

        def join
            FileUtils.mkdir_p(@join_dir)
            @dependencies.each do |dependency|
                dependency.join(@join_dir)
            end
        end

        def flags
            ['-DZLIB_WINAPI', '-DUSESTB', '-std=c99']
        end

        def include_paths
          Dir.glob(File.join(@join_dir, "include", "**/")) + Dir.glob(File.join(@env.dir, 'include', "**/"))
        end

        def library_paths
            [File.join(@join_dir, "lib")]
        end

        def libs
            ary = [] 
            ary << @dependencies.filter_map {|dep| dep.name if dep.lib =~ /.*\.a$/}
            ary << libraries
            ary.flatten
        end

        def files
            src_dir = File.join(@join_dir, "src") 
            ary = []
            ary += Dir.glob("#{src_dir}/*/*").map {|file| @env.objfile(file.pathmap("%X"))}
            ary += Dir.glob("#{src_dir}/*").filter_map {|file| @env.objfile(file.pathmap("%X")) unless File.directory?(file) }
            ary
        end

        def libraries
            []
        end

        def prepare
            fetch
            compile
            join
            find_extra_src(File.join(@env.dir, 'src'))
        end

        def find_extra_src(src_folder)
            extra = Dir.entries(src_folder).select {|entry| File.directory? File.join(src_folder ,entry) and !(entry =='.' || entry == '..') }
            Dir.each_child(src_folder).each do |entry|
                path = File.join(src_folder, entry)
                FileUtils.cp_r(path, File.join(@join_dir, "src")) if File.directory?(path) && !(entry =='.' || entry == '..')
            end
        end
    end
end