require 'git'
module Builder
    module Dependencies
        class Kazmath < Builder::Dependency
            def name
            'kazmath'
            end

            def download
                puts("Downloading #{name}...")
                FileUtils.mkdir_p(vendor_dir)
                Dir.chdir(vendor_dir)
                Git.clone('https://github.com/Kazade/kazmath.git', name)
            end

            def build
                return already_built if library_exists?
                download unless zip_exists?
                build_dependency
            end
            
            def lib_dir
                @lib_dir ||= File.join(build_dir, 'kazmath')
            end

            def library_exists?
                File.directory?(build_dir)
            end

            def subdir
                'kazmath'
            end

            def include_paths
                [base_dir, File.join(base_dir, 'kazmath')]
            end
        end
    end
end