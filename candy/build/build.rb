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

        def add_dependency(name, format, source, includes, lib = nil, flags=[], tool="cmake")
            case format
            when 'git'
                dep = Candy::Git.new(name, source, lib, includes, flags, tool)
                dep.env = @env
                @dependencies.push(dep)
            else
                print "something went wrong"
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
                dependency.compile(@downloads_dir, toolchain)
            end
        end

        def join
            FileUtils.mkdir_p(@join_dir)
            @dependencies.each do |dependency|
                dependency.join(@join_dir)
            end
        end

        def flags
            ['-DZLIB_WINAPI']
        end

        def include_paths
            Dir.glob(File.join(@join_dir, "include", "**/"))
        end

        def library_paths
            [File.join(@join_dir, "lib")]
        end

        def libs
            ary = [] 
            ary << @dependencies.map{|dep| dep.name if dep.lib =~ /.*\.a$/}
            ary << libraries
            ary.flatten
        end

        def files
            src_dir = File.join(@join_dir, "src") 
            objs = Dir.each_child(src_dir).map do |f|
                @env.objfile(f.pathmap("#{src_dir}/%X"))
            end
        end

        def libraries
            []
        end
    end
end