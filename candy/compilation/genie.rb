module Candy
    class GENie
        
        def compile(dependency, downloads_dir, toolchain, env)
            puts "Building #{dependency.name}..."
            file = File.join(downloads_dir, "genie")
            if (!File.exists?(file))
                URI.open(file, 'wb') { |f| f << open('https://github.com/bkaradzic/bx/raw/master/tools/bin/linux/genie').read }
            end
            dest = File.join(downloads_dir, "#{dependency.name}/build")
            Dir.chdir(dest) do
                success = system("#{downloads_dir}/genie #{dependency.flags.join(' ')}")
                raise "Failed to build #{dependency.name}" unless success
                Dir.chdir(File.join(dest, 'gmake')) do
                    success = system("make -f 'SoloudStatic.make' CC=#{env.cc.command} CXX=#{env.cxx.command}")
                end
                puts "#{dependency.name} was built!"
            end
        end
    end
end
