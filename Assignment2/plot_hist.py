from matplotlib import pyplot as plt

eamls_average = [
27224.66795,
26952.62241,
25299.17459,
24867.76599,
27893.683,
26515.84881,
24053.98711,
25535.90531


]

myinit_avg = [
24164.80025,
23950.89367,
22418.88754,
22371.04807,
24943.67661,
23826.18138,
22247.11623,
22514.79949

]

eamls_best = [
20908.21658,
21086.47411,
19524.1847,
19420.10882,
21804.96697,
20196.98053,
18096.78863,
19402.33389


]

myinit_best = [
10392.69481,
10294.65323,
9725.532135,
10424.27541,
11227.51768,
10900.12428,
11518.87344,
9446.761963


]

from matplotlib.font_manager import FontProperties

bar_width = 0.35

index = [i for i in range(8)]

index2 = [i+bar_width for i in index]

plt.bar(index, eamls_best, bar_width, label='Init Method In [1]')

plt.bar(index2, myinit_best,bar_width, label='My Init Method')

def add_labels(rects):
    for rect in rects:
        height = rect.get_height()
        plt.text(rect.get_x() + rect.get_width() / 2, height, height, ha='center', va='bottom')


plt.legend()

plt.xlabel('Instance No.')
plt.ylabel('Best Objective Value')


# plt.show()
plt.savefig('./init_data_best.png', dpi=800)