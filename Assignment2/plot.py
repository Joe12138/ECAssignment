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
eamls_avg = [
    20560.38667,
18314.88667,
15420.87667,
13223.49667,
11500.87133,
10216.17867,
9197.559333,
8441.194667,
7941.003667,
7575.669,
7350.42,
7161.684667,
7039.519667,
6981.854333,
6928.636667,
6893.802667,
6855.842333,
6830.107333,
6815.595333,
6814.14,
6814.14

]

eamls_myinit_avg = [
    10170.78733,
8830.450333,
7993.040667,
7539.024667,
7240.124667,
7007.209333,
6864.974,
6839.826333,
6831.681,
6820.348,
6815.595333,
6815.595333,
6814.14,
6814.14,
6814.14,
6814.14,
6814.14,
6814.14,
6814.14,
6814.14,
6814.14

]

eamls_std = [
1779.587514,
1555.016992,
1672.24656,
1485.451573,
1227.749801,
1030.44786,
860.7277846,
643.6245662,
525.0956415,
451.1331546,
366.2232555,
279.2266595,
207.1993583,
154.8386411,
102.1850324,
89.32000735,
64.41330492,
35.44830555,
7.837209849,
4.54747E-12,
4.54747E-12


]

eamls_myinit_std = [
854.2370752,
555.9339212,
411.9873509,
328.9073594,
253.8976266,
179.9887686,
71.85169047,
60.70824499,
45.50087203,
26.5072783,
7.837209849,
7.837209849,
4.54747E-12,
4.54747E-12,
4.54747E-12,
4.54747E-12,
4.54747E-12,
4.54747E-12,
4.54747E-12,
4.54747E-12,
4.54747E-12


]

eamls_best = [
    17560.9,
16061.3,
11767.1,
10343.6,
8532.87,
8103.96,
7680.45,
7492.41,
7273.53,
7020.83,
6925.07,
6814.14,
6814.14,
6814.14,
6814.14,
6814.14,
6814.14,
6814.14,
6814.14,
6814.14,
6814.14

]

eamls_myinit_best = [
    8049.86,
7603.24,
7021.58,
6857.8,
6814.14,
6814.14,
6814.14,
6814.14,
6814.14,
6814.14,
6814.14,
6814.14,
6814.14,
6814.14,
6814.14,
6814.14,
6814.14,
6814.14,
6814.14,
6814.14,
6814.14

]


"""=========================== DATA PROCESSING ======================================="""
iter = [i for i in range(0, 21)]
color = [cm.gnuplot(1),cm.gist_earth(0.5),cm.Wistia(0.55),cm.gist_heat(0.5),cm.Blues(0.4)]
f, ax = plt.subplots(1, 1)
ax.plot(iter, eamls_avg, color=color[0],marker='o',linestyle="-",label="EAMLS")
# for i in range(len(iter)):
#         plt.scatter(iter[i], ELS_avg[i],marker='o',color=color[0],s=20)

ax.plot(iter, eamls_myinit_avg, color=color[2], marker='v', linestyle="--", label="EAMLS+My Init")
# for i in range(len(iter)):
#         plt.scatter(iter[i], MAELS_H_avg[i],marker='v',color=color[2],s=20)

r1 = list(map(lambda x: x[0] - x[1], zip(eamls_avg, eamls_std)))
r2 = list(map(lambda x: x[0] + x[1], zip(eamls_avg, eamls_std)))
r5 = list(map(lambda x: x[0] - x[1], zip(eamls_myinit_avg, eamls_myinit_std)))
r6 = list(map(lambda x: x[0] + x[1], zip(eamls_myinit_avg, eamls_myinit_std)))
ax.fill_between(iter, r1, r2, color=color[0], alpha=0.1)
ax.fill_between(iter, r5, r6, color=color[2], alpha=0.1)


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
ax.set_ylabel('Average Objective Value', fontsize=fs)
plt.xticks(fontsize=fs)
plt.yticks(fontsize=fs)
ax.legend(fontsize=fs)

plt.show()
f.savefig(os.path.join('True_False_avg' + '.png'), dpi=600)
