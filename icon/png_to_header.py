#example: python3 _to_header.py aovkhoi. aovcheat aovcheat.h

import sys
import os

def _to_c_header(_path, var_name=None, output_path=None):
    """Convert a local  file to C header (.h) with unsigned char array"""
    
    if not os.path.exists(_path):
        print(f"Error: File '{_path}' not found!")
        return
    
    # Tự động tạo tên biến từ tên file nếu không truyền vào
    if var_name is None:
        var_name = os.path.splitext(os.path.basename(_path))[0]
        # Thay ký tự không hợp lệ cho C variable name
        var_name = var_name.replace('-', '_').replace(' ', '_').replace('.', '_')
    
    # Tự động tạo output path nếu không truyền vào
    if output_path is None:
        output_path = os.path.splitext(_path)[0] + '.h'
    
    # Đọc file binary
    with open(_path, 'rb') as f:
        binary_data = f.read()
    
    file_size = len(binary_data)
    print(f"Input:  {_path} ({file_size:,} bytes)")
    print(f"Output: {output_path}")
    print(f"Var:    {var_name}")
    
    # Format as C array (12 bytes per line)
    lines = []
    for i in range(0, len(binary_data), 12):
        chunk = binary_data[i:i+12]
        hex_str = ', '.join(f'0x{byte:02X}' for byte in chunk)
        lines.append(f'    {hex_str}')
    
    array_content = ',\n'.join(lines)
    
    # Tạo header guard
    guard_name = var_name.upper() + '_H'
    
    # Ghi file .h
    with open(output_path, 'w') as f:
        f.write(f'// Auto-generated from {os.path.basename(_path)}\n')
        f.write(f'// Size: {file_size:,} bytes\n\n')
        f.write(f'#ifndef {guard_name}\n')
        f.write(f'#define {guard_name}\n\n')
        f.write(f'static const unsigned char {var_name}_data[] = {{\n{array_content}\n}};\n')
        f.write(f'static const unsigned int {var_name}_data_len = sizeof({var_name}_data);\n\n')
        f.write(f'#endif // {guard_name}\n')
    
    print(f"\n✓ Done! Saved to {output_path}")


if __name__ == '__main__':
    if len(sys.argv) < 2:
        # Mặc định convert anhvu.
        script_dir = os.path.dirname(os.path.abspath(__file__))
        default_ = os.path.join(script_dir, 'anhvu.')
        print(f"No argument, using default: anhvu.\n")
        _to_c_header(default_, var_name='aovcheat')
    else:
        _path = sys.argv[1]
        var_name = sys.argv[2] if len(sys.argv) > 2 else None
        output_path = sys.argv[3] if len(sys.argv) > 3 else None
        _to_c_header(_path, var_name, output_path)
