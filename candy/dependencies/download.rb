module Candy
    class Zipfile < Candy::Dependency
        
        def fetch(dest) 
            puts("downloading #{@name}...")
            Dir.chdir(dest)
            file = File.join(dest, "#{@name}.zip")
            if (!File.exists?(@name))
                URI.open(file, 'wb') { |f| f << open(@src).read }
            else 
                puts "Already downloaded"
            end
        end

    end
end