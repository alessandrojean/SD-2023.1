#!/usr/bin/python3

# inicializa o array (atencao: x00 encerra a string)
N = 12 # determina o tamanho do array (ALTERE pra um valor conveniente)
content = bytearray(0x90 for i in range(N))

# armazena uma string de 4 bytes a partir do offset 0 do array:
content[0:4] = ("SegD").encode('latin-1')

# armazena um inteiro de 4 bytes a partir do offset 4 do array:
number = 0xbabaca00
content[4:8] = (number).to_bytes(4, byteorder='little')

# grava o array content no arquivo badfile1
with open('badfile1', 'wb') as f:
  f.write(content)
