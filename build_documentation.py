import os, re
import sys
from typing import IO, List

from danielutils import TemporaryFile


def cm(cmd):
    return os.system(cmd)


LINE_REGEX = re.compile("Name = (\\w+) dir = (.+)")
ATTRS_REGEX = re.compile("(\\w+\\(.+?\\))")
ATTR_TYPE_REGEX = re.compile("(\\w+)")


def parse_attr(attr: str) -> str:
    attr_type = ATTR_TYPE_REGEX.match(attr).group(1)
    res = f"\n\t\t* Type = `{attr_type}`"
    return res


def parse_line(line: str) -> str:
    m = LINE_REGEX.match(line)
    name = m.group(1)
    dir = m.group(2)
    attrs = ATTRS_REGEX.findall(dir)
    res = f"* Type name: `{name}`\n\t* Attributes: "
    res += "".join(map(parse_attr, attrs))
    return res + "\n"


def parse_lines(output: IO[str], lines: List[str]) -> None:
    joined = "\n".join(lines)
    OBJ_REGEX: re.Pattern = re.compile(r"Name = (\w+)\n([\s\S]+?Attributes: \[[\s\S]+?\]\n\))")
    ATTRS_REGEX: re.Pattern = re.compile(r"Attributes: \[.*?\n([\s\S]+?)\n\]")
    ATTR_REGEX: re.Pattern = re.compile(r"\"(\w+)\" ?: (.+)")
    objs = OBJ_REGEX.findall(joined)
    for name, obj in objs:
        output.write(f"# Type name: `{name}`\n")
        attrs = ATTR_REGEX.findall(ATTRS_REGEX.findall(obj)[0])
        for attr_name, attr_value in attrs:
            output.write(f"* `{attr_name}`: {attr_value}\n")


def main(target_system: str) -> None:
    file_name = "./build_documentation.txt"
    cwd = os.getcwd()
    cmd = f"powershell.exe -c \"cd {cwd}/cmake-build-debug; {cwd}/cmake-build-debug/build_documentation.exe\" > {file_name}"
    if target_system == "wsl":
        cwd = cwd.replace("\\", "/").replace("C:", "/mnt/c")
        cmd = f"wsl.exe --distribution Ubuntu --exec /bin/bash -c \"cd {cwd}/cmake-build-debug && {cwd}/cmake-build-debug/build_documentation\" > {file_name}"
    with TemporaryFile(file_name) as f:
        cm(cmd)
        lines = [l.strip() for l in f.read()]
    with open("Documentation.md", "w", encoding="utf8") as f:
        f.write("# COOP Documentation\n")
        f.write("## Implemented Classes\n")
        parse_lines(f, lines)


if __name__ == '__main__':
    if not (len(sys.argv[1:]) == 1):
        print("Expecting an argument: Literal[wsl, windows]")
    else:
        main(sys.argv[1])
