# cd /Users/anhvu99er/Desktop/Project_HackGame/Aovcheat1.0/hocvienlienquan && python3 png_to_header.py autott.png
import re
import requests
import base64
from bs4 import BeautifulSoup
from PIL import Image, ImageDraw
from io import BytesIO

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
    result.save(output, format="PNG", optimize=True)
    return output.getvalue()

headers = {
    'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/131.0.0.0 Safari/537.36',
    'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8',
    'Accept-Language': 'vi-VN,vi;q=0.9,en-US;q=0.8,en;q=0.7',
    'Referer': 'https://lienquan.garena.vn/'
}

try:
    req = requests.get("https://lienquan.garena.vn/hoc-vien/tuong-skin/", headers=headers, timeout=10)
    req.raise_for_status()
    soup = BeautifulSoup(req.text, "html.parser")
    heroes = soup.select('.st-heroes__item')
except requests.RequestException as e:
    print(f"Error fetching main page: {e}")
    heroes = []

hero_images = {}
filter_heroes = ["Dyadia"]  # Bỏ dấu nháy, dùng contains
found_count = 0

for hero in heroes:
    name = hero.select_one('.st-heroes__item--name').get_text(strip=True)
    
    # Kiểm tra nếu tên chứa bất kỳ keyword nào trong filter
    if not any(keyword in name for keyword in filter_heroes):
        continue
    
    found_count += 1
    
    href = hero.get('href')
    if name and href:
        try:
            print(f"Processing {name}...")
            req = requests.get(href, headers=headers, timeout=10)
            req.raise_for_status()
            soup = BeautifulSoup(req.text, "html.parser")
            skin = soup.select_one('.hero__skins--list a[href="#heroSkin-1"] img')
            if skin and 'src' in skin.attrs:
                hero_images[name] = skin['src']
                print(f"Found icon for {name}")
                
                # Tải và xử lý ngay
                try:
                    response = requests.get(skin['src'], headers=headers, timeout=10)
                    response.raise_for_status()
                    processed_img = process_image(response.content)
                    base64_str = base64.b64encode(processed_img).decode('utf-8')
                    
                    print(f"\n{'='*80}")
                    print(f"Hero: {name}")
                    print(f"{'='*80}\n")
                    
                    # Convert sang C array và lưu vào file .h
                    c_array_str = base64_to_c_array(base64_str, name)
                    with open(f"{name}_icon.h", "w") as f:
                        f.write(c_array_str)
                    print(f"✓ Saved C array to {name}_icon.h\n")
                    
                except Exception as e:
                    print(f"Error processing {name}: {e}")
            else:
                print(f"No icon found for {name}")
        except requests.RequestException as e:
            print(f"Error fetching detail page for {name}: {e}")

print(f"\n✓ Processed {found_count}/{len(filter_heroes)} heroes")
print("\nDone!")