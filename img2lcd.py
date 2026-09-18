import sys
try:
    from PIL import Image, ImageEnhance
except ImportError:
    print("pip install Pillow")
    sys.exit(1)

def generate_headers(img_path):
    img = Image.open(img_path).convert('L')
    img = ImageEnhance.Contrast(img).enhance(1.8)
    img = img.resize((128, 64))
    img = img.convert('1', dither=Image.FLOYDSTEINBERG)
    pixels = img.load()

    oled_data = []
    for page in range(8):
        for x in range(128):
            byte = 0
            for bit in range(8):
                if pixels[x, page * 8 + bit] > 0:
                    byte |= (1 << bit)
            oled_data.append(byte)

    glcd_data = []
    for y in range(64):
        for x in range(0, 128, 8):
            byte = 0
            for bit in range(8):
                if pixels[x + bit, y] == 0: 
                    byte |= (1 << (7 - bit))
            glcd_data.append(byte)

    with open('custom_image.h', 'w') as f:
        f.write('#ifndef CUSTOM_IMAGE_H\n#define CUSTOM_IMAGE_H\n\n#include <stdint.h>\n\n')
        f.write('const uint8_t custom_oled[1024] = {\n' + ','.join(hex(b) for b in oled_data) + '\n};\n\n')
        f.write('const uint8_t custom_glcd[1024] = {\n' + ','.join(hex(b) for b in glcd_data) + '\n};\n\n')
        f.write('#endif\n')

if __name__ == '__main__':
    if len(sys.argv) < 2:
        sys.exit(1)
    generate_headers(sys.argv[1])
