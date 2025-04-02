set_project("openindev")

set_xmakever("2.6.0")

set_languages("c11")

target("template")
    set_kind("binary")  
    add_files("src/*.c")
    add_files("src/**/*.c") 
    add_includedirs("src") 
    add_defines("ENTRY_POINT=_main_")
    if is_os("windows") then
        add_linkdirs("lib/windows") 
        add_ldflags("lib/windows/example-commonRelease.lib", {force = true})
        add_links("bgfxRelease", "bimg_decodeRelease", "bimgRelease", "bxRelease", "example-commonRelease")
        add_syslinks("gdi32", "user32", "shell32") 
    else
        add_linkdirs("lib/linux") 
        --needs to be implemented, will do so later =) 
    end