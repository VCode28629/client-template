// Prevents additional console window on Windows in release, DO NOT REMOVE!!
#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")]

use std::cell::OnceCell;
use std::ffi::{c_char, CStr, CString};
use tauri::{App, EventTarget, Manager};

static mut APP: OnceCell<*const App> = OnceCell::new();

mod bridge {
    use std::ffi::c_char;

    #[link(name = "bridge", kind = "raw-dylib")]
    extern "C" {
        pub fn invoke(func: *const c_char, args: *const c_char) -> *const c_char;
        pub fn initialize();
        pub fn free_str(s: *const c_char);
        pub fn emit_init(
            emit_func: extern "C" fn(*const c_char, *const c_char, *const c_char),
            emit_all_func: extern "C" fn(*const c_char, *const c_char),
        );
    }
}

extern "C" fn emit(window_name: *const c_char, event_name: *const c_char, args: *const c_char) {
    unsafe {
        if let Some(x) = APP.get_mut() {
            let app = *x as *mut App;
            let window_name = CStr::from_ptr(window_name).to_str().unwrap();
            let event_name = CStr::from_ptr(event_name).to_str().unwrap();
            let args = CStr::from_ptr(args).to_str().unwrap();
            (*app)
                .emit_to(EventTarget::webview_window(window_name), event_name, args)
                .unwrap();
        }
    }
}

extern "C" fn emit_all(event_name: *const c_char, args: *const c_char) {
    unsafe {
        if let Some(x) = APP.get_mut() {
            let app = *x as *mut App;
            let event_name = CStr::from_ptr(event_name).to_str().unwrap();
            let args = CStr::from_ptr(args).to_str().unwrap();
            (*app).emit(event_name, args).unwrap();
        }
    }
}

#[tauri::command]
fn invoke(func: &str, args: &str) -> String {
    let func_cstr = CString::new(func).expect("Invalid function name");
    let args_cstr = CString::new(args).expect("Invalid arguments");
    unsafe {
        let result = bridge::invoke(func_cstr.as_ptr(), args_cstr.as_ptr());
        let result_str = CStr::from_ptr(result).to_string_lossy().into_owned();
        bridge::free_str(result);
        result_str
    }
}

fn main() {
    unsafe {
        bridge::emit_init(emit, emit_all);
        bridge::initialize();
    }
    tauri::Builder::default()
        // .plugin(tauri_plugin_shell::init())
        .invoke_handler(tauri::generate_handler![invoke])
        .setup(|app| {
            unsafe {
                APP.get_or_init(|| app as *const App);
            }
            Ok(())
        })
        .run(tauri::generate_context!())
        .expect("error while running tauri application");
}
