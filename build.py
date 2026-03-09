import os
import sys
import shutil
import subprocess

# directory where the build config should be created
BUILD_DIRECTORY = "build"
# build config generator, set it to None for default generator
BUILD_GENERATOR = "MinGW Makefiles"

def does_command_exists(cmd) -> bool:
    try:
        subprocess.run([cmd, "--version"], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        return True
    except FileNotFoundError:
        return False


def get_default_generator() -> str:
    if does_command_exists("ninja"):
        return "Ninja"
    elif os.name == "nt":
        return "MinGW Makefiles"
    else:
        return "Unix Makefiles"


def run(cmd) -> None:
    print("$ >>>", " ".join(cmd))
    subprocess.run(cmd, check=True)


def main() -> None:
    build_type = "Release"

    if not does_command_exists("cmake"):
        print("Cmake not installed...")
        sys.exit(1)

    if len(sys.argv) > 1:
        build_type = sys.argv[1].title()

    if len(sys.argv) > 2 and sys.argv[2] == "clean":
        if os.path.exists(BUILD_DIRECTORY):
            print("Cleaning build directory...")
            shutil.rmtree(BUILD_DIRECTORY)

    if BUILD_GENERATOR is not None:
        generator = BUILD_GENERATOR
    else:
        generator = get_default_generator()

    run([
        "cmake",
        "-S", ".",
        "-B", BUILD_DIRECTORY,
        "-G", generator,
        f"-DCMAKE_BUILD_TYPE={build_type}"
    ])

    run([
        "cmake",
        "--build", BUILD_DIRECTORY,
        "--parallel"
    ])


if __name__ == "__main__":
    main()
