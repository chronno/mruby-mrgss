module Candy
    class Git < Candy::Dependency
        
        def fetch(dest) 
            puts("Candy is fetching #{@name} from #{@src}")
            Dir.chdir(dest)
            if (!File.exists?(@name))
                ::Git.clone(@src, @name)
            else 
                puts("Candy already got this! ")
            end
        end

    end
end