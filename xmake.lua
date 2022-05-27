add_rules("mode.debug", "mode.release")

set_project("AdrianEngine")
set_languages("c99", "c++20")
set_allowedarchs("x64")

function set_intermediatedir (path) 
    set_objectdir(path)
    set_dependir(path)
end

target("AdrianEngine")
    set_kind("shared")
    add_files("AdrianEngine/src/AdrianEngine/*.cpp")
    set_targetdir("bin/$(mode)-$(os)/AdrianEngine")
    set_intermediatedir("bin-int/$(mode)-$(os)/AdrianEngine")
    add_defines("AE_PLATFORM_WINDOWS", "AE_BUILD_DLL")

target("SandboxApp")
    set_kind("binary")
    add_files("Sandbox/src/*.cpp")
    set_targetdir("bin/$(mode)-$(os)/Sandbox")
    set_intermediatedir("bin-int/$(mode)-$(os)/Sandbox")
    add_includedirs("AdrianEngine/src")
    add_links("AdrianEngine")
    add_linkdirs("bin/$(mode)-$(os)/AdrianEngine")
    add_defines("AE_PLATFORM_WINDOWS")
