# -------------------------------- GENERATED BY C_BUILD --------------------------------
from c_build.source.Utilities import *
from c_build.source.Manager import *
# --------------------------------------------------------------------------------------
compiler_name = C_BUILD_COMPILER_NAME() if C_BUILD_IS_DEPENDENCY() else "cl"
compiler_std_version = "c11"
compiler_warning_level = ""
compiler_disable_specific_warnings = []
compiler_treat_warnings_as_errors = True
compiler_disable_warnings = False

project_name = "AOC_DAY8"
project_dependencies = ["ckit"]
project_rebuild_project_dependencies = False
project_debug_with_visual_studio = False
project_executable_procedures = ["AOC_day8.exe"]

if compiler_name == "cl":
    project_warning_level = "2"
    project_disable_specific_warnings = ["5105", "4668", "4820"]
elif compiler_name in ["gcc", "cc", "clang"]:
    project_warning_level = ""


libs = [f"../ckit/build_{compiler_name}/{C_BUILD_LIB('ckit', compiler_name)}"]
if IS_WINDOWS():
	windows_libs = ["User32.lib", "Gdi32.lib"] if compiler_name == "cl" else ["-lUser32", "-lGdi32"]
	libs += windows_libs

procedures_config = {
    "OpenGL_TechDemo": {
        "build_directory": f"./build_{compiler_name}",
        "output_name": f"AOC_day8.exe",
        "source_files": ["../Source/*.c"],
        "additional_libs": libs,
        "compile_time_defines": [],
        "compiler_inject_into_args": [],
        "include_paths": [
            "../ckit",
            "../include",
        ],
    },
}

compiler_config = {key: value for key, value in locals().items() if key.startswith('compiler_')}
project_config = {key: value for key, value in locals().items() if key.startswith('project_')}

manager: Manager = Manager(compiler_config, project_config, procedures_config)
manager.build_project()
# -------------------------------------------------------------------------------------
