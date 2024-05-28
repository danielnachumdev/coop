import os, re
from danielutils import TemporaryFile


def cm(cmd):
    return os.system(cmd)


LINE_REGEX = re.compile("Name = (\w+) dir = (.+)")
ATTRS_REGEX = re.compile("(\w+\(.+?\))")
ATTR_TYPE_REGEX = re.compile("(\w+)")


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


def main() -> None:
    file_name = "./build_documentation.txt"
    with TemporaryFile(file_name) as f:
        cm(f"wsl.exe --distribution Ubuntu --exec /bin/bash -c \"cd /mnt/c/Users/danie/Desktop/Programming/VCS/C/coop/cmake-build-debug && /mnt/c/Users/danie/Desktop/Programming/VCS/C/coop/cmake-build-debug/create_documentation\" > {file_name}")
        lines = [l.strip() for l in f.read()]
    with open("Documentation.md", "w", encoding="utf8") as f:
        f.write("# COOP Documentation\n")
        f.write("## Implemented Classes\n")
        for line in lines:
            f.write(parse_line(line))


if __name__ == '__main__':
    main()
