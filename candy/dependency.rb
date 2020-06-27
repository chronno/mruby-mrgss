module Candy
    class Dependency

        attr_accessor :name
        attr_accessor :flags
        attr_accessor :env
        attr_accessor :lib

        def initialize(name, source, lib, includes, flags = [], tool="cmake")
            @name = name
            @src  = source
            @include_dir = includes
            @lib  = lib
            @flags = flags
            @tool = tool
            @env
        end

        def compile(downloads_dir, toolchain)
            case @tool
            when "cmake"
                puts "Candy will try to Compile #{name} with #{@tool}"
                Candy::CMake.new.compile(self, downloads_dir, toolchain)    
            else
                raise "unknown tool: #{@tool}"
            end
        end

        def join(join_dir)
            create_folders(join_dir)
            compilation_folder = File.join(join_dir, '..', 'downloads', "#{@name}")
            join_lib(join_dir, compilation_folder)
            join_include(join_dir, File.join(compilation_folder, "build"))
        end

        def join_include(join_dir, compilation_folder)
            includes_dir = File.join(compilation_folder, @include_dir)
            Dir.each_child(includes_dir).each do |entry|
                path = File.join(includes_dir, entry)
                FileUtils.cp_r(path, File.join(join_dir, "include")) if File.file?(path) && path =~ /.*\.h$/ || File.directory?(path)
            end
        end

        def join_lib(join_dir, compilation_folder)
            find_file(compilation_folder).each do |file|
                FileUtils.cp(file, File.join(join_dir, "lib")) if (file =~ /.*\.a$/)
                FileUtils.cp(file, File.join(join_dir, "src")) if (file =~ /.*\.c$/)
            end
        end

        def create_folders(join_dir)
            lib_dir = File.join(join_dir, "lib")
            src_dir = File.join(join_dir, "src")
            inc_dir = File.join(join_dir, "include")
            if (!File.exists?(lib_dir))
                FileUtils.mkdir(lib_dir)
            end
            if (!File.exists?(src_dir))
                FileUtils.mkdir(src_dir)
            end
            if (!File.exists?(inc_dir))
                FileUtils.mkdir(inc_dir)
            end
        end

        def find_file(compilation_folder)
            library_path = []
            return if @lib.nil?
            Find.find(compilation_folder) do |path|
                library_path << path if path =~ /#{@lib}/
            end
            library_path
        end

        def compiled?(join_dir)
            return false if !File.exists?(join_dir)
            !find_file(join_dir).empty?
        end
    end
end