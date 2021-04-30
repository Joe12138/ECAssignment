from matplotlib import pyplot as plt

from matplotlib.font_manager import FontProperties

zhang_value_10 = [
4336.67,
3893.81,
2815.76,
4075.56,
3282.98,
2270.43,
2865.86,
2120.92
]

lan_value_10 = {
4232.91,
3280.49,
2815.76,
4075.56,
3199.81,
2270.43,
2865.86,
1808.56
}

zhang_value_50 = [
12872.6,
10149.2,
12334.1,
14925.8,
10811.4,
12173.4,
11671.6,
8117.11
]

lan_value_50 = {
9635.66,
10745.7,
10951.1,
9903.54,
10811.4,
10510.5,
11862.5,
9025.69
}

zhang_value_100 = [
21904.9,
22594.6,
21748.1,
19538.4,
13582.6,
17073,
17730.4,
18962.2
]

lan_value_100 = {
18130.8,
19941.9,
18445.9,
17652.7,
14507.6,
17073,
17555.3,
16904.4
}

zhang_value_600 = [
123346,
120116,
130431,
134407
]

lan_value_600 = {
104916,
107088,
106921,
102246
}

bar_width = 0.35

index = [i for i in range(4)]

index2 = [i+bar_width for i in index]

plt.bar(index, zhang_value_600, bar_width, label='RS In [1]')

plt.bar(index2, lan_value_600,bar_width, label='My RS')

def add_labels(rects):
    for rect in rects:
        height = rect.get_height()
        plt.text(rect.get_x() + rect.get_width() / 2, height, height, ha='center', va='bottom')


plt.legend()

plt.xlabel('Instance No.')
plt.ylabel('Best Objective Value')


# plt.show()
plt.savefig('./repair_1_600.png', dpi=800)