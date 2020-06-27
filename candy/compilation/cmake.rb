module Candy

    class CMake
        def compile(dependency, downloads_dir, toolchain)
            puts "Candy is now building #{dependency.name}..."
            build_flags(dependency, toolchain)
            dest = File.join(downloads_dir, "#{dependency.name}/build")
            FileUtils.mkdir_p(dest)
            execute_compile(dependency, dest)
        end

        def build_flags(dependency, toolchain)
            dependency.flags << "-DCMAKE_TOOLCHAIN_FILE=#{toolchain}"
        end

        def execute_compile(dependency, dest)
            cmake_dir = '..'
            Dir.chdir(dest) do
                success = system("cmake #{dependency.flags.join(' ')} #{cmake_dir}") && system('cmake --build .')
                raise "Candy failed to build #{dependency.name}" unless success
                puts "Candy finished building #{dependency.name}"
            end
        end
    end

end