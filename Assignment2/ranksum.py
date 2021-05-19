from scipy.stats import wilcoxon
import csv
import numpy as np
import os 

path = "G:\\EvolutionaryAlgorithm\\ECAssignment\\Assignment2\\FLP\\Result\\Total"

# file_list = ['10_init_pop_F_T.csv', '10_MY_HU.csv', '50_init_pop_F_T.csv', '50_MY_HU.csv', '50_MYINIT_HU.csv']
path = "E:\\2021_spring\\Evolutional Computing\\ECAssignment\\Assignment2\\Compare Result"
file_list = ['50_neighborhood.csv']

for file2 in file_list:
    print(file2)
    data_array = np.zeros((16, 30))
    row_num = 0
    with open(os.path.join(path, file2)) as f:
        f_csv = csv.reader(f)

        for row in f_csv:
            if "Instance" not in row[0]:
                continue
            else:
                for i in range(1, 31):
                    data_array[row_num][i-1] = float(row[i])
                row_num += 1

    # print(data_array)

    for i in range(8):
        # print("instance {}".format(i))
        x = data_array[i][:]
        y = data_array[8+i][:]
        # print(x)
        # print(y)
        zhang_avg = np.mean(x)
        zhang_std = np.std(x)
        zhang_min = np.min(x)

        lan_avg = np.mean(y)
        lan_std = np.std(y)
        lan_min = np.min(y)

        print("\midrule")
        content = str(i) + " & "

        try:
            a, pvalue=wilcoxon(x, y, zero_method="wilcox")
        except ValueError:
            pvalue=1000

        zhang_avg_min = 0
        if pvalue < 0.05 and zhang_avg < lan_avg:
            zhang_avg_min = 1
        elif pvalue < 0.05 and zhang_avg > lan_avg:
            zhang_avg_min = 2
        else:
            if zhang_avg < lan_avg:
                zhang_avg_min = 3
            else:
                zhang_avg_min = 4

        

        if zhang_avg_min==1:
            content += str(round(zhang_avg,2)) + "*&" + str(round(zhang_std, 2)) + "&" + str(round(zhang_min,2)) + " & \\underline{"+str(round(lan_avg,2)) + "}&" + str(round(lan_std, 2)) + "&" + str(round(lan_min, 2)) + "\\\\"
        elif zhang_avg_min==2:
            content += str(round(zhang_avg,2)) + "&" + str(round(zhang_std, 2)) + "&" + str(round(zhang_min,2)) + "& \\textbf{"+str(round(lan_avg,2)) + "}*&" + str(round(lan_std, 2)) + "&" + str(round(lan_min, 2)) + "\\\\"
        elif zhang_avg_min==3:
            content += str(round(zhang_avg,2)) + "*&" + str(round(zhang_std, 2)) + "&" + str(round(zhang_min,2)) + " &" + str(round(lan_avg,2)) + "&" + str(round(lan_std, 2)) + "&" + str(round(lan_min, 2)) + "\\\\"
        else:
            content += str(round(zhang_avg,2)) + "&" + str(round(zhang_std, 2)) + "&" + str(round(zhang_min,2)) +"&" + str(round(lan_avg,2)) + "*&" + str(round(lan_std, 2)) + "&" + str(round(lan_min, 2)) + "\\\\"

        print(content)
        

    # x=[7333.814421,7473.255694,7637.868117,7021.584956,7365.981412,7087.187331,7489.080446,6992.483011,7332.964995,7177.53417,7260.701963,6914.274959,6857.79762,7075.181093,7133.152989,7471.0654,7430.247236,7391.853947,6991.153065,7397.907349,7190.123682,7555.403087,7340.340955,7109.782215,7030.680622,7682.881593,7098.233316,7458.434613,7441.659056,7543.628152]
    # y=[6956.724227,6992.483011,6991.153065,6967.070941,6975.912169,6992.483011,7105.188939,6975.912169,6914.274959,6974.728147,6814.141677,6925.071118,6814.141677,7056.338886,6914.274959,7022.707717,7144.381028,6992.483011,6814.141677,6814.141677,6857.79762,6814.141677,7114.054073,7219.407355,6953.885286,7336.001469,6914.274959,6950.860949,6953.885286,6950.860949]
        
    
    print("*******************************")