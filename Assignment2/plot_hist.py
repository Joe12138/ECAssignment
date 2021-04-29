from matplotlib import pyplot as plt

eamls_average = [
    19673.72982,
20464.72672,
20093.79769,
19554.68671,
21921.81548,
20332.5684,
18170.51014,
19700.02205
]

myinit_avg = [
    10158.37061,
10715.52706,
10424.86849,
10356.89923,
11300.78193,
10907.38999,
10361.82205,
9548.387283

]

eamls_best = [
    15732.85533,
16586.81313,
17287.32078,
17685.48094,
18006.63756,
14313.52,
15888.07594,
16432.33933

]

myinit_best = [
    7704.960748,
8734.930623,
8950.986174,
9027.602454,
9653.770612,
9091.78406,
9114.029666,
8510.211451

]

from matplotlib.font_manager import FontProperties

bar_width = 0.35

index = [i for i in range(8)]

index2 = [i+bar_width for i in index]

plt.bar(index, eamls_average, bar_width, label='Init Method In [1]')

plt.bar(index2, myinit_avg,bar_width, label='My Init Method')

def add_labels(rects):
    for rect in rects:
        height = rect.get_height()
        plt.text(rect.get_x() + rect.get_width() / 2, height, height, ha='center', va='bottom')


plt.legend()

plt.xlabel('Instance No.')
plt.ylabel('Average Objective Value')


# plt.show()
plt.savefig('./init_data_avg.png', dpi=800)