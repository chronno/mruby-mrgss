require 'git'
module Builder
    module Dependencies
        class GL3W < Builder::Dependency
            def name
            'GL3W'
            end

            def download
                puts("Downloading #{name}...")
                FileUtils.mkdir_p(vendor_dir)
                Dir.chdir(vendor_dir)
                Git.clone('https://github.com/skaslev/gl3w.git', name)
            end

            def build
                return already_built if library_exists?
                download unless zip_exists?
                build_dependency
            end

            def build_dependency
                puts "Building #{name}..."
                FileUtils.mkdir_p(build_dir)
                Dir.chdir(build_dir) do
                success = system("cmake #{cmake_flags.join(' ')} #{cmake_dir}") && system('cmake --build .') && system('make')
                raise "Failed to build #{name}" unless success
                puts "#{name} was built!"
                end
            end
            
            def library_exists?
                File.directory?(build_dir)
            end

            def subdir
                'GL3W'
            end

            def lib_dir
                @lib_dir ||= File.join(build_dir, 'src')
            end

            def include_paths
                [base_dir, File.join(build_dir, 'include'), build_dir, File.join(build_dir, 'include/GL'),]
            end

            def add_to_build
                Dir.glob("#{build_dir}/src/*.{c,cpp,cxx,cc,m,asm,s,S}")
            end
        end
    end
end
