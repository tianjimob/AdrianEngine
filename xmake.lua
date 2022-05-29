add_rules("mode.debug", "mode.release", "mode.minsizerel", "mode.releasedbg")

set_project("AdrianEngine")
set_languages("c99", "c++20")
set_allowedarchs("x64")
add_requires("spdlog", "glfw", "imgui")

if is_os("windows") then
    add_defines("AE_PLATFORM_WINDOWS")
end 

function set_intermediatedir (path) 
    set_objectdir(path)
    set_dependir(path)
end

local targetprefix = "bin/$(mode)-$(os)-$(arch)/"
local intermediateprefix = "bin-int/$(mode)-$(os)-$(arch)/"

target("glad")
    set_kind("static")
    add_files("AdrianEngine/vendor/GLAD/src/glad.c")
    add_includedirs("AdrianEngine/vendor/GLAD/include")

target("AdrianEngine")
    set_kind("shared")
    add_deps("glad")
    add_files("AdrianEngine/src/**.cpp")
    add_packages("glfw", "spdlog", "imgui")
    set_targetdir(targetprefix.."AdrianEngine")
    set_intermediatedir(intermediateprefix.."AdrianEngine")
    add_includedirs("AdrianEngine/src", "AdrianEngine/vendor/GLAD/include")
    set_pcxxheader("AdrianEngine/src/aepch.h")
    add_defines("AE_BUILD_DLL")

    if is_mode("release") then
        add_defines("AE_RELEASE")
    elseif is_mode("releasedbg") then
        add_defines("AE_DEBUG")
    elseif is_mode("debug") then
        add_defines("AE_DEBUG")
    elseif is_mode("minsizerel") then
        add_defines("AE_MINSIZEREL")
    end 

    after_build(function (target) 
            os.cp(target:targetfile(), targetprefix.."SandboxApp")
        end)

target("SandboxApp")
    set_kind("binary")
    add_deps("AdrianEngine")
    add_files("Sandbox/src/*.cpp")
    add_packages("spdlog")
    set_targetdir(targetprefix.."SandboxApp")
    set_intermediatedir(intermediateprefix.."SandboxApp")
    add_includedirs("AdrianEngine/src")
    
    
