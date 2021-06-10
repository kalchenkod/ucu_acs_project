import colorsys

import matplotlib.pyplot as plt
import numpy as np

dct = dict()
with open("result.txt", "r", encoding="utf-8") as f:
    lines = f.readlines()[:1000]
    for line in lines:
        line = line.strip().split("-")
        dct[int(line[0])] = float(line[1])


# genres = tuple(hex_colors)
# x = range(len(genres))
# ax = plt.gca()
# ax.bar(x, dct.values(), color= hex_colors)
# ax.set_xticks(x)
# ax.set_xticklabels(genres)
# plt.show()

result = [x*255 for x in colorsys.hls_to_rgb(0, 0.5, 0.5)]
print(result)


with open("init_matrix.txt", 'w', encoding="utf-8") as f:
    for i in range(100):
        for j in range(100):
            if j == 0:
                f.write(str(100) + " ")
            elif j == 99:
                f.write(str(-100) + " ")
            else:
                f.write(str(0) + " ")
        f.write("\n")