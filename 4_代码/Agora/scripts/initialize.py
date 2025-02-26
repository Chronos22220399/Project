from pathlib import Path 

class CmakeManager:
    project_name: str = "" 
    base_cmake_content = '''cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_SUPPRESS_REGENERATION FALSE)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_MODULE_PATH "${{CMAKE_CURRENT_LIST_DIR}}/cmake; ${{CMAKE_MODULE_PATH}}")
set(COMPILE_OPTIONS
    -O0 -g -Wall # 打开所有警告
    # -Wextra      # 打开额外的警告 -Werror # 将警告视为错误
    -pedantic # 启用严格的 C++ 标准
)

project(
    {}
LANGUAGES CXX
VERSION 1.0)
'''

    sub_project_cmake_content = '''file(GLOB_RECURSE srcs CONFIGURE_DEPENDES include/*.h include/*.hpp src/*.c src/*.cpp src/*.cc)

add_executable({} ${{srcs}})

target_include_directories(${{PROJECT_NAME}} PRIVATE ${{CMAKE_CURRENT_LIST_DIR}}/include)
'''
    
    def __init__(self, project_name: str):
        self.project_name = project_name
        
    def check_and_create_cmakefile(self, project_dir: Path, is_base_project_path: bool):
        # 配置根目录的 CMakeLists.txt
        if is_base_project_path:
            cmake_path = project_dir / "CMakeLists.txt"
            if not cmake_path.exists():
                print("CMakeLists.txt 不存在，开始初始化配置...")
                cmake_path.touch()
                
                # 开始初始化 CMakeLists.txt
                with open(cmake_path, mode="w") as cmakelists:
                    # 存在则检查 CMakeLists 内是否有内容，没有则直接写入基础配置
                    print(f"正在为 {self.project_name} 根路径的 CMakeLists.txt 写入配置...")
                    cmakelists.write(self.base_cmake_content.format(str(self.project_name)))         
                    
            else:
                print("CMakeLists.txt 已存在，不做处理")

            base_cmake_dir = project_dir / 'cmake'
            if not base_cmake_dir.exists():
                print("cmake 目录不存在，开始创建...")
                base_cmake_dir.mkdir()
        
        # 配置根目录下子项目的 CMakeLists.txt
        else:
            cmake_path = project_dir / "CMakeLists.txt"
            if not cmake_path.exists():
                print(f"子项目 {str(project_dir)} 的CMakeLists.txt 不存在，开始初始化配置...")
                cmake_path.touch()
                
                # 开始初始化 CMakeLists.txt
                with open(cmake_path, mode="w") as cmakelists:
                    # 存在则检查 CMakeLists 内是否有内容，没有则直接写入基础配置
                    print(f"正在为 {self.project_name} 根路径的 CMakeLists.txt 写入配置...")
                    cmakelists.write(self.sub_project_cmake_content.format(str(self.project_name)))         
                    
            else:
                print("CMakeLists.txt 已存在，不做处理")

            base_cmake_dir = project_dir / 'cmake'
            if not base_cmake_dir.exists():
                print("cmake 目录不存在，开始创建...")
                base_cmake_dir.mkdir()
            

def create_sub_project(base_project_path: Path, sub_project_name: str):
    main_file_content = '''#include <iostream>

int main() {
    return 0;
}
'''
    sub_project_path = base_project_path / sub_project_name
    include_path = sub_project_path / 'include'
    src_path = sub_project_path / 'src'
    main_file_path = src_path / 'main.cpp'
    
    if sub_project_path.exists():
        print(f"子项目 {sub_project_name} 已存在，不做处理")
        return
    sub_project_path.mkdir()
    include_path.mkdir()
    src_path.mkdir()

    # 事实上没有必要
    if not main_file_path.exists:
        print(f"{sub_project_name}/main.cpp 已存在，不做处理")
        return
    main_file_path.touch()
    
    with open(main_file_path, "w") as main_file:
        main_file.write(main_file_content)
        
    
    
def main():
    base_path = Path().cwd()
    project_name = input("请输入项目名称: ")
    cmake_manager = CmakeManager(project_name)
    cmake_manager.check_and_create_cmakefile(base_path, True)
    sub_projects: list[str] = []
    while True:
        sub_project = input("请输入子项目名称(暂停输入 exit()、exit、Exit、Exit()): ")
        if sub_project in ('exit()', 'exit', 'Exit', 'Exit()'):
            break
        
        sub_projects.append(sub_project)
        print("开始创建并配置子项目...")
        create_sub_project(base_path, sub_project)
        cmake_manager.check_and_create_cmakefile(Path(sub_project), False)
        
    for sub_project in sub_projects:
        # TODO: 在根项目中添加 add_subdirectories
        pass

if __name__ == "__main__":
    main()
