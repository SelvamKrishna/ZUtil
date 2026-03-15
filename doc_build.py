from pathlib import Path

LIBRARY_SRC = Path("./zen")
OUTPUT_FILE = Path("DOCUMENTATION.md")

def write_namespace(namespace_text: str) -> None:
    with open(OUTPUT_FILE, "a") as file:
        file.write(f"## `zen::{namespace_text}`\n\n---\n\n")

def scan_file_docs(file_path: Path) -> list[str]:
    if not file_path.exists():
        raise FileNotFoundError(f"File: `{file_path.absolute()}` not found")

    output: list[str] = []

    with open(file_path, "r") as file:
        for raw_line in file.readlines():
            line = raw_line.strip()
            if line == "": continue
            output.append(line)

    return output

def write_file_docs(file_path: Path) -> None:
    with open(OUTPUT_FILE, "a") as file:
        file.write(f"### FILE: `{str(file_path.absolute()).strip("C:\\dev\\ZUtil\\")}`\n\n")

    print(f"[INFO] Scanning file: {file_path.absolute()}")

    for line in scan_file_docs(file_path):
        print(line)

def main() -> None:
    with open(OUTPUT_FILE, "w") as file:
        file.writelines("# Zen Utility Library Documentation\n\n---\n\n")

    write_namespace("core")
    write_file_docs(LIBRARY_SRC / "core" / "_ansi.hpp")
    # write_file_docs(LIBRARY_SRC / "core" / "_pro_string.hpp")
    print(f"[INFO] Documentation written to {OUTPUT_FILE.absolute()}")

if __name__ == "__main__":
    main()
