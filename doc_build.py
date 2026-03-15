from pathlib import Path

LIBRARY_SRC = Path("./zen")
OUTPUT_FILE = Path("DOCUMENTATION.md")

def init_doc_file() -> None:
    with open(OUTPUT_FILE, "w") as file:
        file.writelines("# Zen Utility Library Documentation\n\n---\n\n")

def write_file_name(file_path: Path) -> None:
    with open(OUTPUT_FILE, "a") as file:
        file.write(f"## FILE: `{str(file_path.absolute()).strip("C:\\dev\\ZUtil\\")}`\n")

def scan_file_docs(file_path: Path) -> list[str]:
    if not file_path.exists():
        raise FileNotFoundError(f"File: `{file_path.absolute()}` not found")

    output: list[str] = []

    with open(file_path, "r") as file:
        for line in file.readlines():
            output.append(line)

    return output

def generate_docs(file_path: Path) -> None:
    write_file_name(file_path)
    for line in scan_file_docs(file_path):
        print(line)

def main() -> None:
    init_doc_file()
    generate_docs(Path("zen/container/double_buffer.hpp"))
    print(f"[INFO] Documentation written to {OUTPUT_FILE.absolute()}")

if __name__ == "__main__":
    main()
