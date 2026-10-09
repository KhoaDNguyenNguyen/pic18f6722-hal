#!/usr/bin/env python3
import sys
import os

def parse_bdf_for_lcd(bdf_path: str, text: str) -> None:
    if not os.path.exists(bdf_path):
        print(f"Error: Missing BDF file at {bdf_path}", file=sys.stderr)
        sys.exit(1)

    with open(bdf_path, 'r') as f:
        bdf_content = f.readlines()

    for char in text:
        ascii_val = ord(char)
        bitmap_hex = []
        preview_lines = []
        in_char = False
        in_bitmap = False
        
        for line in bdf_content:
            line = line.strip()
            
            if line == f"ENCODING {ascii_val}":
                in_char = True
            elif in_char and line == "BITMAP":
                in_bitmap = True
            elif in_bitmap:
                if line == "ENDCHAR":
                    break
                
                # Convert BDF to LCD standard (Shift Right 3)
                val_bdf = int(line, 16)
                val_lcd = val_bdf >> 3
                bitmap_hex.append(f"0x{val_lcd:02X}")
                
                # Generate ASCII preview (Bitmask from MSB to LSB of 5-bit)
                row_str = "".join(["██" if (val_lcd & (1 << i)) else ".." for i in range(4, -1, -1)])
                preview_lines.append(row_str)

        if len(bitmap_hex) == 8:
            print(f"/* --- Preview: '{char}' (ASCII: {ascii_val}) --- */")
            for row in preview_lines:
                print(f"// {row}")
            print(f"const uint8_t lcd_char_{ascii_val}[8] = {{{', '.join(bitmap_hex)}}};\n")
        else:
            print(f"/* Error: Character '{char}' not found in BDF */\n")

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} <string>")
        sys.exit(1)
        
    bdf_file = os.path.expanduser("~/5x8.bdf")
    parse_bdf_for_lcd(bdf_file, sys.argv[1])