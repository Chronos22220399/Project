from pathlib import Path
import subprocess
import json

def build_by_cmake(libsrc_full_path: Path, build_dir: Path, options: dict):
    option_list: list[str] = [] 
    for key, value in options.items():
        pass
        command = '-D' + key + '=' + value
        option_list.append(command)
        
    build_command = ['cmake', str(libsrc_full_path), '-B', str(libsrc_full_path / 'build'), '-DCMAKE_INSTALL_PREFIX=' + str(build_dir)]
    build_command.extend(option_list)
    install_commad = ['cmake', "--build", str(libsrc_full_path/'build'), '--parallel', '8', '--target', 'install']
    print("Executing: ", " ".join(build_command))
    print("Executing: ", " ".join(install_commad))
    subprocess.run(build_command)
    subprocess.run(install_commad)

def check_and_download(library_name: str, url: str, download_dir: Path, build_dir: Path, build_tool: str, options: dict):
    # 检查库是否已经存在
    libsrc_full_path = download_dir / library_name # 例如: ~/.install/third_party_src/fmt
    libbuild_full_path = build_dir / library_name # 例如: ~/.install/
    if not Path.exists(libsrc_full_path):
        print(f"{library_name} not found. downloading to {libsrc_full_path} ...")
        # 拉取库并放入指定目录
        if (url.endswith('.git')):
            subprocess.run(['git', 'clone', url, '--depth=1', libsrc_full_path])
        elif url.endswith('.gz'):
            subprocess.run(['wget', url, '-P', libsrc_full_path])
        # ...

    # 编译库并存放到 .install 目录
    if not Path.exists(libbuild_full_path):
        print(f"Building {library_name}...")
        if build_tool == "cmake":
            build_by_cmake(libsrc_full_path=libsrc_full_path, build_dir=build_dir, options=options)
        elif build_tool == "bootstrap.sh":
            pass

def install_packages(libraries: dict):
    # 定义库及其信息
    base_path = Path.home() / '.install'
    if not base_path.exists():
        print(f"{base_path} 不存在，开始创建")
        base_path.mkdir(parents=True, exist_ok=True)
        
    download_dir = base_path / 'third_party_src'
    build_dir = base_path 
    # options 存放编译选项，没有就写个空的字典占位即可

    for lib_name, lib_info in libraries.items():
        check_and_download(lib_name, lib_info['url'], download_dir, build_dir, lib_info["build_tool"], lib_info['options'])
    
def config_by_libraries():
    libraries_json_file= Path.cwd() / 'libraries.json'
    if not libraries_json_file.exists():
        print(f"{libraries_json_file} 不存在，请检查其位置是否正确")
        return
    
    with open(libraries_json_file, "r", encoding='utf-8') as lib_json:
        lib_json_content = lib_json.read()
        libraries = json.loads(lib_json_content)
        install_packages(libraries=libraries)
    

def main():
    pass
            

if __name__ == "__main__":
    main()
