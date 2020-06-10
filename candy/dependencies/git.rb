module Candy
    class Git < Candy::Dependency
        
        def fetch(dest) 
            puts("cloning #{@name}...")
            Dir.chdir(dest)
            if (!File.exists?(@name))
                ::Git.clone(@src, @name)
            else 
                puts "Already cloned"
            end
        end

    end
end