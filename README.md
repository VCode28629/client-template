
* Requirements
```
xmake
cargo(install by rustup is recommended)
tauri-cli(version "^2.0.0-beta")
clang
pnpm
unzip or 7zip(need by xmake)
nodejs(need by pnpm, >=14 or tsc will be error)
```

If you wanna use gcc or other C/C++ compiler instead of clang, check the `xmake.lua`

* To switch compile mode
```
xmake f -m debug
xmake f -m release
```

* To compile
```
xmake
```

* Settings: Remember to change these when you start a new project

```
./xmake.lua
./tauri-bridge/tauri.conf.json
./tauri-bridge/capabilities/
./tauri-bridge/Cargo.toml
./view/package.json
./view/tsconfig.json
./view/tsconfig.node.json
./view/vite.config.ts
```

If you don't want to use `vite`, `react`, `typescript` or `pnpm`, clean the `view` folder, then check `tauri.conf.json`, `xmake.lua` and `package.json`.
