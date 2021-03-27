from os import system, chdir
from sys import argv
import matplotlib.pyplot as plt


def building(path):
    system("mkdir build")
    chdir("build")

    #Delete this line
    system("cmake .. -DCMAKE_CXX_COMPILER=g++")

    system("cmake -G\"Unix Makefiles\" ..")
    system("make")
    system(f"./semester_project.exe ../images/{path} ../out.txt")


def reading():
    with open("out.txt", "r", encoding="utf-8") as f:
        result = f.readlines()
        for i in range(len(result)):
            result[i] = [int(x) for x in result[i].split()]
    #system("rm out.txt")
    return result[::100000]


def plotting(colors):
    hex_colors = ["#{:02x}{:02x}{:02x}".format(x[0], x[1], x[2])
                  for x in colors]
    sizes = [colors.count(x)/len(colors) for x in colors]
    fig, ax = plt.subplots()
    ax.pie(sizes, colors=hex_colors, radius=1.5)
    ax.axis('equal')
    plt.show()


if __name__ == "__main__":
    # if len(argv) != 2:
    #     print("Invalid arguments number")
    #     exit(1)
    # building(argv[1])
    result = sorted(reading(), key=lambda x: x[0]) #rgb
    plotting(result)
