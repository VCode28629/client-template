set_languages("c++17")
set_toolchains("clang")
add_rules("mode.debug", "mode.release")
add_cxflags("-fdeclspec")
add_cxxflags("-fdeclspec")

add_requires("nlohmann_json")

target("base")
    set_kind("shared")
    add_files("base/src/*.cpp")
    add_includedirs("base/include/")
    add_packages("nlohmann_json")

target("bridge")
    set_kind("shared")
    add_files("bridge/src/*.cpp")
    add_includedirs("bridge/include/")
    add_deps("base")
    add_includedirs("base/include/")
    add_packages("nlohmann_json")
    add_rpathdirs("$ORIGIN")

target("view")
    set_kind("binary")
    add_deps("bridge")
    on_build(function (target)
        local oldir = os.cd("./view")
        os.exec("pnpm install")
        os.exec("pnpm build")
        os.cd(oldir)
        oldir = os.cd("./tauri-bridge")
        if is_mode("debug") then
            os.exec("cargo tauri build --debug")
        end
        if is_mode("release") then
            os.exec("cargo tauri build")
        end
        os.cd(oldir)
    end)
    after_build(function (target) 
        local oldir = os.cd("./tauri-bridge")
        local build_dir = "$(buildir)/" .. (is_plat("windows") and "windows/x64/" or "linux/x86_64/")
        local mode = is_mode("debug") and "debug/" or "release/"
        if is_plat("windows") then
            os.mv("./target/" .. mode .. "view.exe", build_dir .. mode)
            os.mv("./target/" .. mode .. "view.pdb", build_dir .. mode)
        elseif is_plat("linux") then
            os.mv("./target/" .. mode .. "view", build_dir .. mode)
        end
        os.cd(oldir)
    end)