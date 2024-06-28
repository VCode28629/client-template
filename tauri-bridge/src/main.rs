// Prevents additional console window on Windows in release, DO NOT REMOVE!!
#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")]

use std::ffi::{CStr, CString};

mod bridge {
    use std::ffi::c_char;

    #[link(name = "bridge", kind = "raw-dylib")]
    extern "C" {
        pub fn invoke(func: *const c_char, args: *const c_char) -> *const c_char;
        pub fn initialize();
        pub fn free_str(s: *const c_char);
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
        bridge::initialize();
    }
    tauri::Builder::default()
        // .plugin(tauri_plugin_shell::init())
        .invoke_handler(tauri::generate_handler![invoke])
        .run(tauri::generate_context!())
        .expect("error while running tauri application");
}
