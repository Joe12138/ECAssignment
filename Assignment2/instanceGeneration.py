# -*- coding: UTF-8 -*-
import numpy as np
import pickle


class Instances:
    def __init__(self, fp_listParameters):
        '''
        @parameters: 0:iSitesNum, 1:iScenNum, 2:iDemandLB, 3:iDemandUB, 4:iFixedCostLB, 5:iFixedCostUP, 6:iCoordinateLB, 7:iCoordinateUB, 8:fFaciFailProb
        '''
        self.iSitesNum = fp_listParameters[0]
        self.iScenNum = fp_listParameters[1]
        self.iDemandLB = fp_listParameters[2]
        self.iDemandUB = fp_listParameters[3]
        self.iFixedCostLB = fp_listParameters[4]
        self.iFixedCostUB = fp_listParameters[5]
        self.iCoordinateLB = fp_listParameters[6]
        self.iCoordinateUB = fp_listParameters[7]
        self.fFaciFailProb = fp_listParameters[8]

        self.a_2d_SitesCoordi = np.zeros((self.iSitesNum, 2))
        self.aiDemands = np.zeros(self.iSitesNum, dtype=np.int)
        self.aiFixedCost = np.zeros(self.iSitesNum, dtype=np.int)
        self.af_2d_TransCost = np.zeros((self.iSitesNum, self.iSitesNum))

    def funGenerateInstances(self):
        # generate the x and y coordinates of candidate sites
        self.a_2d_SitesCoordi = self.iCoordinateLB + (
            self.iCoordinateUB - self.iCoordinateLB) * np.random.rand(
                self.iSitesNum, 2)
        self.aiDemands = np.random.randint(self.iDemandLB,
                                           self.iDemandUB,
                                           size=self.iSitesNum)
        self.aiFixedCost = np.random.randint(self.iFixedCostLB,
                                             self.iFixedCostUB,
                                             size=self.iSitesNum)
        for i in range(self.iSitesNum):
            for j in range(i + 1, self.iSitesNum):
                temCost = np.linalg.norm(self.a_2d_SitesCoordi[i] -
                                         self.a_2d_SitesCoordi[j])
                self.af_2d_TransCost[i][j] = self.af_2d_TransCost[j][
                    i] = temCost


if __name__ == '__main__':
    '''
    Test the code.
    listPara:
    0:iSitesNum, 1:iScenNum, 2:iDemandLB, 3:iDemandUB, 4:iFixedCostLB, 5:iFixedCostUP, 6:iCoordinateLB, 7:iCoordinateUB, 8:fFaciFailProb
    '''
    iInsNum = 8
    iSitesNum = 30
    iScenNum = 1
    iDemandLB = 0
    iDemandUB = 1000
    iFixedCostLB = 500
    iFixedCostUB = 1500
    iCoordinateLB = 0
    iCoordinateUB = 1
    fFaciFailProb = 0.05
    listPara = [iSitesNum, iScenNum, iDemandLB, iDemandUB, iFixedCostLB, iFixedCostUB, iCoordinateLB, iCoordinateUB, fFaciFailProb]
    # f = open('600-nodeInstances', 'wb', encoding='UTF-8')
    for k in range(iInsNum):
        file_name = './FLP/Instance/{}_{}.txt'.format(iSitesNum, k)
        with open(file_name, 'w', encoding='UTF-8') as f:
            generateInstances = Instances(listPara)
            generateInstances.funGenerateInstances()

            f.write('siteNum={}\n'.format(str(generateInstances.iSitesNum)))
            f.write('demandLowerBound={}\n'.format(str(generateInstances.iDemandLB)))
            f.write('demandUpperBound={}\n'.format(str(generateInstances.iDemandUB)))
            f.write('fixedCostLowerBound={}\n'.format(str(generateInstances.iFixedCostLB)))
            f.write('fixedCostUpperBound={}\n'.format(str(generateInstances.iFixedCostUB)))
            f.write('coordinateLowerBound={}\n'.format(str(generateInstances.iCoordinateLB)))
            f.write('coordinateUpperBound={}\n'.format(str(generateInstances.iCoordinateUB)))
            f.write('facilityFailProbility={}\n'.format(str(generateInstances.fFaciFailProb)))

            f.write('Coordinate: index, x, y\n')
            for i in range(generateInstances.iSitesNum):
                f.write("{},{},{}\n".format(str(i), str(generateInstances.a_2d_SitesCoordi[i][0]), str(generateInstances.a_2d_SitesCoordi[i][1])))
            
            f.write("Demand:index, demand\n")
            for i in range(generateInstances.iSitesNum):
                f.write("{},{}\n".format(str(i), str(generateInstances.aiDemands[i])))

            f.write("Fixcost:index, fixedCost\n")
            for i in range(generateInstances.iSitesNum):
                f.write("{},{}\n".format(str(i), str(generateInstances.aiFixedCost[i])))

            f.write('TransCost:start_index, end_index, transCost\n')
            for i in range(generateInstances.iSitesNum):
                for j in range(generateInstances.iSitesNum):
                    if i!=j:
                        f.write("{},{},{}\n".format(str(i), str(j), str(generateInstances.af_2d_TransCost[i][j])))





