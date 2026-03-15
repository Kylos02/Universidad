
-- Declaración de la entidad llamada "practica2"
-- Define las entradas y salidas del circuito
entity Practica2_vhd is 
 port (
   a0, b0, c0 : in bit;  -- Entradas: dos operandos (a0, b0) y un acarreo de entrada (c0)
   c1, s0     : out bit  -- Salidas: suma (s0) y acarreo de salida (c1)
 );
end Practica2_vhd;

-- Descripción de la arquitectura "suma" para la entidad "practica2"
architecture suma of Practica2_vhd is
begin
  -- Asignación concurrente para la salida de la suma
  -- s0 representa el bit de la suma resultante
  -- La operación XOR permite calcular la suma de los bits de entrada con el acarreo
  s0 <= a0 xor b0 xor c0;

  -- Asignación concurrente para la salida del acarreo
  -- c1 se activa cuando al menos dos de las entradas son '1'
  -- Esta es la expresión booleana clásica del acarreo en un sumador completo
  c1 <= (a0 and b0) or (a0 and c0) or (b0 and c0);
end suma;

