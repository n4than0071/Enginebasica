from PIL import Image
from pathlib import Path

pasta = Path(__file__).parent

imagem = Image.open(pasta / "fonte.png").convert("L")

if imagem.size != (100, 100):
    raise ValueError("A imagem precisa ter exatamente 100x100 pixels")

TAMANHO_SIMBOLO = 10
COLUNAS = 10
LINHAS = 10

arquivo = open("fonte.h", "w")

arquivo.write("#pragma once\n")
arquivo.write("#include <cstdint>\n\n")

arquivo.write("constexpr uint16_t fonte[100][10] = {\n\n")

for simboloY in range(LINHAS):

    for simboloX in range(COLUNAS):

        id = simboloY * 10 + simboloX

        arquivo.write(f"    // Simbolo {id}\n")
        arquivo.write("    {\n")

        for pixelY in range(TAMANHO_SIMBOLO):

            bits = ""

            for pixelX in range(TAMANHO_SIMBOLO):

                x = simboloX * 10 + pixelX
                y = simboloY * 10 + pixelY

                pixel = imagem.getpixel((x, y))

                if pixel < 128:
                    bits += "1"
                else:
                    bits += "0"

            arquivo.write(f"        0b{bits},\n")

        arquivo.write("    },\n\n")

arquivo.write("};\n")
arquivo.close()

print("fonte.h criado!")