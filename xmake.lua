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
        if is_plat("windows") then
            if is_mode("debug") then
                os.mv("./target/debug/view.exe", "$(buildir)/windows/x64/debug/")
                os.mv("./target/debug/view.pdb", "$(buildir)/windows/x64/debug/")
            elseif is_mode("release") then
                os.mv("./target/release/view.exe", "$(buildir)/windows/x64/release/")
                os.mv("./target/release/view.pdb", "$(buildir)/windows/x64/release/")
            end
        elseif is_plat("linux") then 
            if is_mode("debug") then
                os.mv("./target/debug/view.exe", "$(buildir)/windows/x64/debug/")
                os.mv("./target/debug/view.pdb", "$(buildir)/windows/x64/debug/")
            elseif is_mode("release") then
                os.mv("./target/release/view.exe", "$(buildir)/windows/x64/release/")
                os.mv("./target/release/view.pdb", "$(buildir)/windows/x64/release/")
            end
        end
        os.cd(oldir)
    end)