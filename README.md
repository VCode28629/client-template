
* requirement
```
xmake
pnpm
tauri-cli@2.0.0-beta.20
```


* build

* settings
```
./xmake.lua
./tauri-bridge/tauri.conf.json: 
    identifier
    app windows title
```


* 分步编译

cd view
pnpm build
cd ..
cd tauri-bridge
cargo tauri build
cd ..

