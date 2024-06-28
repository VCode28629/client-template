
* requirement
```
xmake
pnpm
tauri-cli@2.0.0-beta.20
```

* settings
```
./xmake.lua
./tauri-bridge/tauri.conf.json: 
    identifier
    app windows title
```


* 切换编译模式：
```
xmake f -m debug
xmake f -m release
```

* 编译：
```
xmake
```
