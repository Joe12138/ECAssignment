import numpy as np
import os
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
from scipy import stats

sns.set_style('whitegrid')

# index = 0
for index in range(8):
    false_path = "./50_False/"+str(index)

    true_path = "./50_Neighborhood_True/"+str(index)

    false_list = os.listdir(false_path)

    true_list = os.listdir(true_path)

    false_array = np.zeros((21, 30))

    true_array = np.zeros((21, 30))


    for j in range(len(false_list)):
        file_name = false_list[j]
        with open(os.path.join(false_path, file_name), 'r') as f:
            data = f.readlines()
            data = data[1:]

            for i in range(len(data)):
                false_array[i][j] = float(data[i])

    for j in range(len(true_list)):
        file_name = true_list[j]
        with open(os.path.join(true_path, file_name), 'r') as f:
            data = f.readlines()
            data = data[1:]

            for i in range(len(data)):
                true_array[i][j] = float(data[i])

    eamls_avg = np.mean(false_array, axis=1)
    eamls_min = np.min(false_array, axis=1)
    eamls_std = np.std(false_array, axis=1)

    eamls_myinit_avg = np.mean(true_array, axis=1)
    eamls_myinit_min = np.min(true_array, axis=1)
    eamls_myinit_std = np.std(true_array, axis=1)

    """=========================== DATA PROCESSING ======================================="""
    iter = [i for i in range(0, 21)]
    color = [cm.gnuplot(1),cm.gist_earth(0.5),cm.Wistia(0.55),cm.gist_heat(0.5),cm.Blues(0.4)]
    f, ax = plt.subplots(1, 1)
    ax.plot(iter, eamls_min, color=color[0],marker='o',linestyle="-",label="EAMLS")
    # for i in range(len(iter)):
    #         plt.scatter(iter[i], ELS_avg[i],marker='o',color=color[0],s=20)

    ax.plot(iter, eamls_myinit_min, color=color[2], marker='v', linestyle="--", label="EAMLS+Adding NS")
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
    ax.set_xlabel(r'$\# Evaluation (\times 10^{3})$', fontsize=fs)
    ax.set_ylabel('Best Objective Value', fontsize=fs)
    plt.xticks(fontsize=fs)
    plt.yticks(fontsize=fs)
    ax.legend(fontsize=fs)

    # plt.show()
    f.savefig(os.path.join('E:\\2021_spring\\Evolutional Computing\\ReportFinal\\Conference-LaTeX-template_10-17-19\Assignment2\\50_neighbor_'+str(index)+'_best' + '.png'), dpi=800)