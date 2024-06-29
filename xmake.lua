set_languages("c++23")
set_toolchains("clang")
add_rules("mode.debug", "mode.release")

add_requires("nlohmann_json")

target("bridge")
    set_kind("shared")
    add_files("bridge/src/*.cpp")
    add_packages("nlohmann_json")
    add_includedirs("bridge/include/")
    add_includedirs("base/include/")


target("view")
    set_kind("binary")
    add_deps("bridge")
    on_build(function (target)
        local oldir = os.cd("./view")
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
        if is_mode("debug") then
            os.mv("./target/debug/view.exe", "$(buildir)/windows/x64/debug/")
            os.mv("./target/debug/view.pdb", "$(buildir)/windows/x64/debug/")
        end
        if is_mode("release") then
            os.mv("./target/release/view.exe", "$(buildir)/windows/x64/release/")
            os.mv("./target/release/view.pdb", "$(buildir)/windows/x64/release/")
        end
        os.cd(oldir)
    end)