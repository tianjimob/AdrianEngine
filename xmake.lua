add_rules("mode.debug", "mode.release", "mode.minsizerel")

set_project("AdrianEngine")
set_languages("c99", "c++20")
set_allowedarchs("x64")
add_requires("spdlog", "glfw")
add_packages("spdlog")

function set_intermediatedir (path) 
    set_objectdir(path)
    set_dependir(path)
end

local targetprefix = "bin/$(mode)-$(os)-$(arch)/"
local intermediateprefix = "bin-int/$(mode)-$(os)-$(arch)/"

target("AdrianEngine")
    set_kind("shared")
    add_files("AdrianEngine/src/**.cpp")
    add_packages("glfw")
    set_targetdir(targetprefix.."AdrianEngine")
    set_intermediatedir(intermediateprefix.."AdrianEngine")
    add_includedirs("AdrianEngine/src")
    set_pcxxheader("AdrianEngine/src/aepch.h")
    
    if is_os("windows") then
        add_defines("AE_PLATFORM_WINDOWS", "AE_BUILD_DLL")
    end

    if is_mode("release") then
        add_defines("AE_RELEASE")
    elseif is_mode("debug") then
        add_defines("AE_DEBUG")
        after_build(function (target) 
            os.cp(target:targetfile(), targetprefix.."SandboxApp")
        end)
    elseif is_mode("minsizerel") then
        add_defines("AE_MINSIZEREL")
    end 

target("SandboxApp")
    set_kind("binary")
    add_deps("AdrianEngine")
    add_files("Sandbox/src/*.cpp")
    set_targetdir(targetprefix.."SandboxApp")
    set_intermediatedir(intermediateprefix.."SandboxApp")
    add_includedirs("AdrianEngine/src")
    
    if is_os("windows") then
        add_defines("AE_PLATFORM_WINDOWS")
    end 
