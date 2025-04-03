add_rules("mode.release", "mode.debug")

set_languages("c11")
set_arch("x86_64")

toolchain("gcc_build")
    set_kind("standalone")
    set_toolset("cc", "gcc")
    set_toolset("cxx", "g++")
    set_toolset("ld", "g++")
    set_toolset("ar", "ar")
    set_toolset("strip", "strip")


target("openindev")
    set_toolchains("gcc_build")
    set_kind("binary")
    add_files("src/*.c", "src/**/*.c", "src/externincludes/glad.c")
    add_includedirs("src/externincludes")
    
    set_optimize("fastest")
    if is_os("windows") then
        add_defines("_WIN32_WINNT=0x0600", "WINVER=0x0600", "PSAPI_VERSION=1")
        add_ldflags("-lpsapi")
        add_linkdirs("lib/windows") 
        add_links("SDL2", "SDL2.dll", "psapi")
        add_syslinks("gdi32", "winmm") 
    else
        add_linkdirs("lib/linux") 
        add_links("SDL2")
    end
    
    