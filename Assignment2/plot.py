import pandas as pd
import re
import seaborn as sns
import matplotlib.pyplot as plt
import matplotlib.cm as cm
from matplotlib.pyplot import MultipleLocator
from mpl_toolkits.axes_grid1.inset_locator import mark_inset
from mpl_toolkits.axes_grid1.inset_locator import inset_axes
import shutil
import sys
import os
from scipy import stats

sns.set_style('whitegrid')

# Make it all show up
pd.set_option('display.max_columns', None)
pd.set_option('display.max_rows', None)
pd.set_option('max_colwidth', 100)

"""=================================== LOAD DATA ELS compare  ===================================="""
eamls_avg = [20171.65667,
18243.75333,
15514.21667,
13281.17333,
11700.79167,
10826.286,
10274.02467,
9630.789667,
9051.019,
8797.920333,
8562.684667,
8329.433667,
8139.116667,
8014.993667,
7812.037,
7704.454667,
7624.071333,
7530.406,
7412.668,
7347.310667,
7281.431667
]

eamls_myinit_avg = [
    10188.962,
8821.330333,
8256.487333,
8140.858,
8006.062667,
7924.864667,
7771.245333,
7698.630333,
7555.380333,
7453.928,
7391.607,
7352.248333,
7310.695,
7265.055667,
7201.794333,
7160.884667,
7109.157,
7070.274,
7058.299333,
7030.646667,
7003.779
]

eamls_std = [
    2235.604928,
1753.363178,
1774.665438,
1386.002028,
1222.462998,
1259.761947,
1155.746439,
850.1869312,
548.562607,
692.3860579,
658.2572509,
565.5472925,
547.1063852,
500.3618784,
412.3908805,
344.5821003,
326.8675185,
340.4932406,
298.8950914,
306.9278957,
295.2548117

]

eamls_myinit_std = [
857.4267731,
535.6393339,
515.2096369,
465.9710046,
361.8949964,
343.6942141,
319.7443964,
344.1867283,
336.8751581,
284.7115229,
274.6345946,
271.6551572,
244.5468138,
234.1129062,
213.712598,
181.48386,
190.8274724,
149.0081095,
148.3375021,
143.8900683,
129.8359482

]

eamls_best = [
    16138.4,
14874.1,
11654.9,
11040.6,
8437.42,
8437.42,
8437.42,
7920.57,
7840.68,
7795.05,
7193.23,
7193.23,
7193.23,
7193.23,
6956.72,
6956.72,
6956.72,
6857.8,
6857.8,
6857.8,
6857.8
]

eamls_myinit_best = [
    8871.57,
7538.29,
7444.69,
7444.69,
7444.69,
7444.69,
7020.83,
6975.91,
6953.89,
6953.89,
6953.89,
6953.89,
6953.89,
6857.8,
6857.8,
6857.8,
6857.8,
6857.8,
6857.8,
6814.14,
6814.14
]


"""=========================== DATA PROCESSING ======================================="""
iter = [i for i in range(0, 21)]
color = [cm.gnuplot(1),cm.gist_earth(0.5),cm.Wistia(0.55),cm.gist_heat(0.5),cm.Blues(0.4)]
f, ax = plt.subplots(1, 1)
ax.plot(iter, eamls_best, color=color[0],marker='o',linestyle="-",label="EAMLS")
# for i in range(len(iter)):
#         plt.scatter(iter[i], ELS_avg[i],marker='o',color=color[0],s=20)

ax.plot(iter, eamls_myinit_best, color=color[2], marker='v', linestyle="--", label="EAMLS+My Init")
# for i in range(len(iter)):
#         plt.scatter(iter[i], MAELS_H_avg[i],marker='v',color=color[2],s=20)

# r1 = list(map(lambda x: x[0] - x[1], zip(eamls_avg, eamls_std)))
# r2 = list(map(lambda x: x[0] + x[1], zip(eamls_avg, eamls_std)))
# r5 = list(map(lambda x: x[0] - x[1], zip(eamls_myinit_avg, eamls_myinit_std)))
# r6 = list(map(lambda x: x[0] + x[1], zip(eamls_myinit_avg, eamls_myinit_std)))
# ax.fill_between(iter, r1, r2, color=color[0], alpha=0.1)
# ax.fill_between(iter, r5, r6, color=color[2], alpha=0.1)


"""=================================   attribute of   ==============================="""
# 设置刻度
x_major_locator=MultipleLocator(4)
# y_major_locator=MultipleLocator(100)
# plt.xlim(-10,730)
ax.xaxis.set_major_locator(x_major_locator)
# ax.yaxis.set_major_locator(y_major_locator)
ax.grid(False)
handles, labels = ax.get_legend_handles_labels()
ax.legend(handles, labels)
fs=9
ax.set_xlabel('Generation', fontsize=fs)
ax.set_ylabel('Best Objective Value', fontsize=fs)
plt.xticks(fontsize=fs)
plt.yticks(fontsize=fs)
ax.legend(fontsize=fs)

plt.show()
f.savefig(os.path.join('True_False_best' + '.png'), dpi=600)
