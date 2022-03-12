#!/usr/bin/env python3
import os.path
import sys
import pywavefront
import struct
import numpy
from pathlib import Path

if len(sys.argv) != 4:
    print("usage: ./model3d_compiler.py OBJ_FILE CAFE_FILE T3S_DIR")
    exit(1)

cafe_file = open(sys.argv[2], "wb")
cafe_stem = Path(sys.argv[2]).stem
obj_file = pywavefront.Wavefront(sys.argv[1])

texture_counter = 0

# write file header
cafe_file.write(struct.pack("<HH", 0xCAFE, len(obj_file.materials)))

for name, material in obj_file.materials.items():
    assert material.vertex_format in ('T2F_N3F_V3F', 'T2F_V3F')

    # build material properties struct
    material_properties = bytes()
    material_properties += struct.pack("<ffff", *material.ambient[0:3], 1)
    material_properties += struct.pack("<ffff", *material.diffuse[0:3], 1)
    material_properties += struct.pack("<ffff", *material.specular[0:3], 1)
    material_properties += struct.pack("<ffff", *material.emissive[0:3], 1)

    # write material properties length and struct
    cafe_file.write(struct.pack("<H", len(material_properties)))
    cafe_file.write(material_properties)

    # generate .t3s file
    if material.texture:
        t3s_directory = Path(sys.argv[3])
        t3s_stem = str(t3s_directory / (f"cafe_{cafe_stem}_tex{texture_counter}"))
        assert t3s_stem.isascii()
        texture_counter += 1

        try:
            with open(f"{t3s_stem}.t3s", "w") as f:
                abs_path = os.path.abspath(material.texture.path)
                assert ' ' not in abs_path
                f.writelines([
                    "-f auto-etc1 -z auto\n",
                    abs_path
                ])
        except IOError as error:
            print(f"warning: could not open texture file: {error}")

        # write texture path length and characters
        texture_path = f"romfs:/{t3s_stem}.t3x"
        texture_path_length = len(texture_path)
        cafe_file.write(struct.pack(f"<H{texture_path_length}s", texture_path_length, bytes(texture_path.encode("ascii"))))
    else:
        cafe_file.write(struct.pack("<H", 0))

    vbo = bytes()

    if material.vertex_format == 'T2F_N3F_V3F':
        for tx, ty, nx, ny, nz, vx, vy, vz in zip(*(iter(material.vertices),) * 8):
            vbo += struct.pack("<fff", vx, vy, vz)
            vbo += struct.pack("<ff", tx, ty)
            vbo += struct.pack("<fff", nx, ny, nz)
    elif material.vertex_format == 'T2F_V3F':
        for tx, ty, vx, vy, vz in zip(*(iter(material.vertices),) * 5):
            # TODO: compute normals
            nx, ny, nz = 0, 0, 0
            vbo += struct.pack("<fff", vx, vy, vz)
            vbo += struct.pack("<ff", tx, ty)
            vbo += struct.pack("<fff", nx, ny, nz)

    # write VBO length and VBO data
    cafe_file.write(struct.pack(f"<H", len(vbo)))
    cafe_file.write(vbo)
