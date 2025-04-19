import re
import sys

def parse_struct(struct_text):
    bitfield_pattern = re.compile(r'\breg_t\b\s+(\w+)?\s*:\s*(\d+)\s*;')
    fields = bitfield_pattern.findall(struct_text)
    total_bits = sum(int(bits) for _, bits in fields)
    return total_bits

def find_structs(source_code):
    struct_pattern = re.compile(r'typedef\s+volatile\s+struct\s*{([^}]+)}\s*(\w+)_t\s*;', re.DOTALL)
    return struct_pattern.findall(source_code)

def verify_structs(source_code):
    struct_failed = False
    structs = find_structs(source_code)
    for struct_body, struct_name in structs:
        total_bits = parse_struct(struct_body)
        if total_bits != 32 and total_bits != 0:
            print(f"[ERR] {struct_name} has {total_bits} bits!")
            struct_failed = True

    # Print the results and exit with appropriate status
    if struct_failed:
        print("[ERR] Some structs have invalid bit sizes.")
        sys.exit(1)
    else:
        print("[OK] All structs have valid bit sizes.")
        sys.exit(0)

# Get the file path from command line arguments
if len(sys.argv) != 2:
    print(f"Usage: {sys.argv[0]} <path_to_header_file>")
    sys.exit(1)

# Read the file and verify structs
filepath = sys.argv[1]
try:
    with open(filepath, "r") as f:
        source = f.read()
    verify_structs(source)
except FileNotFoundError:
    print(f"Error: File '{filepath}' not found.")
    sys.exit(1)
