import subprocess

BUILD_DIRECTORY = "build"
BUILD_GENERATOR = "MinGW Makefiles"
BUILD_MODE      = "Release"

BUILD_CONFIG_CMD = [
    "cmake",
    "-S", ".",
    "-B", BUILD_DIRECTORY,
    "-G", BUILD_GENERATOR,
    f"-DCMAKE_BUILD_TYPE={BUILD_MODE}"
]

BUILD_COMPILE_CMD = [
    "cmake",
    "--build", BUILD_DIRECTORY,
    "--parallel"
]

if __name__ == "__main__":
    subprocess.run(BUILD_CONFIG_CMD)
    print(" ".join(BUILD_CONFIG_CMD))
    subprocess.run(BUILD_COMPILE_CMD)
    print(" ".join(BUILD_COMPILE_CMD))
