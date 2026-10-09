#!/usr/bin/env python3
import sys

def hex_to_text(hex_string: str) -> None:
    clean_str = hex_string.replace('{', '').replace('}', '').strip()
    try:
        hex_bytes = [int(x.strip(), 16) for x in clean_str.split(',') if x.strip()]
    except ValueError:
        sys.exit(1)

    print("[EDITED_ICON]")
    for b in hex_bytes:
        row = "".join(["#" if (b & (1 << i)) else "." for i in range(4, -1, -1)])
        print(row)

if __name__ == '__main__':
    if len(sys.argv) < 2:
        sys.exit(1)
    hex_to_text(sys.argv[1])
