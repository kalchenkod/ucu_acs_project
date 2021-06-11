from os import system, chdir, popen
from sys import argv
import matplotlib.pyplot as plt
import numpy as np
import colorsys


class VideoAnalyser:
    def __init__(self, video_path):
        self._video_path = video_path
        self._hex_colors = []
        self._sizes = []

    def building(self):
        system("mkdir build")
        chdir("build")
        system("cmake -G\"Unix Makefiles\" ..")
        system("make")
        popen(f"video.exe ../{self._video_path}").read()

    def analyze(self):
        colours = []
        sum_weights = 0
        with open("result.txt", "r", encoding="utf-8") as f:
            lines = f.readlines()[:1000]
            for line in lines:
                line = line.strip().split("-")
                colours.append((int(line[0]), float(line[1])))
                sum_weights += float(line[1])
                
        chdir("../")
        system("rm -r build")

        colours.sort(key=lambda x: x[0])
        rgb_colors = []
        for color in colours:
            rgb_colors.append(([int(x * 255) for x in colorsys.hsv_to_rgb(color[0] / 180, 1, 1)], color[1]))

        self._hex_colors = ["#{:02x}{:02x}{:02x}".format(x[0][0], x[0][1], x[0][2]) for x in rgb_colors]
        self._sizes = [x[1] / sum_weights for x in rgb_colors]

    def save(self):
        xmin, xmax = xlim = 0, len(self._sizes)
        ymin, ymax = ylim = 0, max(self._sizes)

        fig, ax = plt.subplots()
        ax.set(xlim=xlim, ylim=ylim, autoscale_on=False)

        x = np.arange(len(self._sizes))
        y = np.array(self._sizes)

        ax.bar(x, y, color=self._hex_colors, width=1)
        ax.set_facecolor('floralwhite')
        fig.set_facecolor('floralwhite')
        fig.set_figwidth(20)
        fig.set_figheight(6)

        #plt.show()
        self._video_path = self._video_path.replace(".mp4", ".png").replace(".avi", ".png").replace(".mov", ".png")
        fig.savefig(self._video_path)


if __name__ == "__main__":
    analyzer = VideoAnalyser(argv[1])
    analyzer.building()
    analyzer.analyze()
    analyzer.save()








