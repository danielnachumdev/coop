import os
import sys


def cm(cmd: str) -> None:
    return os.system(cmd)


def get_all_files(directory):
    for root, dirs, files in os.walk(directory):
        for file in files:
            yield os.path.join(root, file)


COMPILATION_FLAGS: list[str] = []
VALGRIND_FLAGS: list[str] = ["--leak-check=full", "--show-leak-kinds=all", "-s"]


def main(args: list[str]) -> None:
    files: list[str] = list(get_all_files(os.path.join(os.getcwd(), "coop")))
    files = [f for f in files if f.endswith(".c") or f.endswith(".h")]
    sources = '"' + "\" \"".join(files) + '"'
    sources = sources.replace("\\", "/")
    sources = sources.replace("C:", "/mnt/c")
    flags = " ".join(COMPILATION_FLAGS)
    cmd = f"wsl gcc {flags} main.c _main.c _main.h {sources} -o main.out"
    print(cmd)
    if cm(cmd) == 0:
        valgrind = ""
        if len(args) == 1 and args[0] == "valgrind":
            valgrind = "valgrind " + " ".join(VALGRIND_FLAGS)
        cmd = f"wsl {valgrind} ./main.out"
        print(cmd)
        cm(cmd)


if __name__ == '__main__':
    main(sys.argv[1:])
