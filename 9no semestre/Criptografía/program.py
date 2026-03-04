"""
Lab 1 - Stream Cipher (formato de entrada/salida solicitado)
Lee 4 líneas desde stdin:
  seed
  nonce
  message 1
  message 2

Salida (exacta, sin etiquetas):
  linea1 -> hex(C1 ⊕ C2)
  linea2 -> hex(P1 ⊕ P2)
"""

import hashlib
import sys

def keystream(seed, nbytes, nonce, counter0=0):
    if isinstance(seed, str):
        seed = seed.encode('utf-8')
    if isinstance(nonce, str):
        nonce = nonce.encode('utf-8')

    keystream_bytes = b''
    counter = counter0

    while len(keystream_bytes) < nbytes:
        counter_bytes = counter.to_bytes(8, byteorder='big')
        hash_input = seed + nonce + counter_bytes
        hash_output = hashlib.sha256(hash_input).digest()
        keystream_bytes += hash_output
        counter += 1

    return keystream_bytes[:nbytes]

def sxor(a: bytes, b: bytes) -> bytes:
    n = min(len(a), len(b))
    return bytes(x ^ y for x, y in zip(a[:n], b[:n]))

def encrypt_stream(plaintext, seed, nonce, counter0=0):
    if isinstance(plaintext, str):
        plaintext = plaintext.encode('utf-8')
    key_stream = keystream(seed, len(plaintext), nonce, counter0)
    ciphertext = sxor(plaintext, key_stream)
    return ciphertext

def decrypt_stream(ciphertext, seed, nonce, counter0=0):
    key_stream = keystream(seed, len(ciphertext), nonce, counter0)
    plaintext = sxor(ciphertext, key_stream)
    return plaintext

def main():
    lines = []
    for _ in range(4):
        line = sys.stdin.readline()
        if not line:
            line = ""
        lines.append(line.rstrip("\n"))

    seed = lines[0]
    nonce = lines[1]
    plaintext1 = lines[2]
    plaintext2 = lines[3]

    p1_bytes = plaintext1.encode('utf-8')
    p2_bytes = plaintext2.encode('utf-8')

    c1 = encrypt_stream(p1_bytes, seed, nonce)
    c2 = encrypt_stream(p2_bytes, seed, nonce)

    c_xor = sxor(c1, c2)
    p_xor = sxor(p1_bytes, p2_bytes)

    sys.stdout.write(c_xor.hex() + "\n")
    sys.stdout.write(p_xor.hex() + "\n")

if __name__ == "__main__":
    main()
