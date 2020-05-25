module Builder
    module Dependencies
      class GLFW < Builder::Dependency
        def name
          'GLFW'
        end
  
        def url
          'https://github.com/glfw/glfw/releases/download/3.3.2/glfw-3.3.2.zip'
        end
  
        def subdir
          'glfw-3.3.2'
        end
  
        def lib_dir
          @lib_dir ||= File.join(build_dir, 'src')
        end
  
        def include_paths
          [base_dir, File.join(base_dir, 'include'), build_dir, File.join(build_dir, 'include/GLFW'),]
        end
      end
    end
  end
  