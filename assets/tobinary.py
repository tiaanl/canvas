import sys
import os

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print('USAGE: {} <binary-file-to-encode>'.format(sys.argv[0]))
    
    filename = sys.argv[1]
    
    file_size = os.path.getsize(filename)

    with open(filename, 'rb') as file:
        buf = file.read(file_size)
        chars = ['{0:#04x}'.format(ch) for ch in buf]

    print('U8 binaryData[] = {')
    print(', '.join(chars))
    print('};')
