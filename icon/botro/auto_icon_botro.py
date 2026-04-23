import re
import os
import unicodedata
import requests
import base64
from bs4 import BeautifulSoup
from PIL import Image, ImageDraw
from io import BytesIO

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))

def to_camel_no_accent(text):
    """Convert Vietnamese text to CamelCase without diacritics. E.g. 'LÁ CHẮN SINH MỆNH' → 'LaChanSinhMenh'"""
    # Normalize and strip diacritics
    nfkd = unicodedata.normalize('NFKD', text)
    ascii_str = ''.join(c for c in nfkd if not unicodedata.combining(c))
    # Handle special Vietnamese chars not caught by NFKD
    replacements = {'đ': 'd', 'Đ': 'D'}
    for src, dst in replacements.items():
        ascii_str = ascii_str.replace(src, dst)
    # CamelCase each word
    words = re.findall(r'[A-Za-z0-9]+', ascii_str)
    return ''.join(w.capitalize() for w in words)

def base64_to_c_array(base64_str, var_name):
    """Convert base64 string to C array format"""
    # Decode base64 to binary
    binary_data = base64.b64decode(base64_str)
    
    # Format as C array
    lines = []
    for i in range(0, len(binary_data), 12):
        chunk = binary_data[i:i+12]
        hex_str = ', '.join(f'0x{byte:02X}' for byte in chunk)
        lines.append(f'    {hex_str}')
    
    # Join lines with comma at end except last line
    array_content = ',\n'.join(lines)
    
    c_array = f'unsigned char _{var_name}_data[] = {{\n{array_content}\n}};\n'
    c_array += f'unsigned int _{var_name}_data_len = sizeof(_{var_name}_data);\n'
    
    return c_array

def process_image(img_data):
    img = Image.open(BytesIO(img_data)).convert("RGBA")
    size = 64
    mask = Image.new("L", (size, size), 0)
    draw = ImageDraw.Draw(mask)
    draw.ellipse((0, 0, size, size), fill=255)
    img = img.resize((size, size), Image.LANCZOS)
    result = Image.new("RGBA", (size, size), (0, 0, 0, 0))
    result.paste(img, (0, 0), mask)
    # Bỏ viền đỏ - chỉ lấy ảnh tròn gốc
    output = BytesIO()
    result.save(output, format="", optimize=True)
    return output.getvalue()

headers = {
    'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/131.0.0.0 Safari/537.36',
    'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8',
    'Accept-Language': 'vi-VN,vi;q=0.9,en-US;q=0.8,en;q=0.7',
    'Referer': 'https://lienquan.garena.vn/'
}

try:
    req = requests.get("https://lienquan.garena.vn/hoc-vien/phu-tro/", headers=headers, timeout=10)
    req.raise_for_status()
    soup = BeautifulSoup(req.text, "html.parser")
    heroes = soup.select('.st-extra-skills__item')
    print(f"Found {len(heroes)} items on page")
except requests.RequestException as e:
    print(f"Error fetching main page: {e}")
    heroes = []

hero_images = {}
filter_heroes = []  # Rỗng = lấy tất cả
found_count = 0

for hero in heroes:
    name_el = hero.select_one('.st-extra-skills__item--name')
    img_el  = hero.select_one('.st-extra-skills__item--img img')
    if not name_el:
        continue
    name = name_el.get_text(strip=True)
    # Nếu filter rỗng thì lấy tất cả, ngược lại chỉ lấy tên chứa keyword
    if filter_heroes and not any(keyword in name for keyword in filter_heroes):
        continue

    found_count += 1
    img_src = img_el['src'] if img_el and 'src' in img_el.attrs else None
    if not img_src:
        print(f"No image for {name}")
        continue

    # Tên biến C: CamelCase không dấu
    var_name = to_camel_no_accent(name)

    print(f"Processing {name}...")
    try:
        response = requests.get(img_src, headers=headers, timeout=10)
        response.raise_for_status()
        processed_img = process_image(response.content)
        base64_str = base64.b64encode(processed_img).decode('utf-8')

        # Convert sang C array và lưu vào file .h trong folder botro
        c_array_str = base64_to_c_array(base64_str, var_name)
        out_path = os.path.join(SCRIPT_DIR, f"{var_name}_icon.h")
        with open(out_path, "w") as f:
            f.write(c_array_str)
        print(f"✓ Saved {out_path}")
    except Exception as e:
        print(f"Error processing {name}: {e}")

print(f"\n✓ Processed {found_count} items")
print("Done!")