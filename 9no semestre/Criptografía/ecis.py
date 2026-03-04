"""
Silverio Martínez Andrés
Materia: Criptografía
Ejemplo de uso de ECIES (Elliptic Curve Integrated Encryption Scheme)
"""

# Importar las librerías necesarias
import ecies
from eth_keys import keys
from coincurve.utils import get_valid_secret

def main():
    """
    Función principal que demuestra el ciclo completo de ECIES:
    1. Este geenera un par de llaves (pública y privada).
    2. Se define un mensaje secreto.
    3. Se cifra el mensaje con la llave pública.
    4. Se descifra el mensaje con la llave privada.
    5. Por último, se verifica que el mensaje original y el descifrado coincidan.
    """
    
    # 1. Generar un par de llaves ECC (estilo Ethereum, curva secp256k1)
    llave_privada = keys.PrivateKey(get_valid_secret())
    llave_privada_hex = llave_privada.to_hex()
    llave_publica_hex = llave_privada.public_key.to_hex()
    
    print(f"Llave Privada (hex): {llave_privada_hex}")
    print(f"Llave Pública (hex): {llave_publica_hex}\n")
    
    # 2. Definir el mensaje secreto que queremos compartir
    secreto_original = b'Este es un mensaje ultra secreto'
    print(f"Secreto Original: {secreto_original}\n")
    
    # 3. Se cifra el mensaje usando la llave punlica del destinatario
    mensaje_cifrado = ecies.encrypt(llave_publica_hex, secreto_original)
    print(f"Mensaje Cifrado: {mensaje_cifrado}\n")
    
    # 4. Se descifra el mensaje usando la llave privada correspondiente
    mensaje_descifrado = ecies.decrypt(llave_privada_hex, mensaje_cifrado)
    print(f"Mensaje Descifrado: {mensaje_descifrado}\n")
    
    # 5. Verificación final
    if secreto_original == mensaje_descifrado:
        print("¡Éxito! El mensaje descifrado coincide con el original.")
    else:
        print("Error: El mensaje descifrado no coincide.")

if __name__ == "__main__":
    main()