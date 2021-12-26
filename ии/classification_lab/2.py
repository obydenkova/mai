import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import random as rd
import math
import myLog
import myTree
import myRandomTree as myRD

from sklearn.linear_model import LogisticRegression
from sklearn.metrics import classification_report, confusion_matrix
from sklearn.ensemble import RandomForestClassifier
from sklearn import tree
from sklearn.metrics import classification_report


def dataPreparing(dataset, split):
    X1 = dataset[0:71]['Vehicle_theft'].values
    Y1 = dataset[0:71]['Drugs'].values
    X2 = dataset[132:205]['Vehicle_theft'].values
    Y2 = dataset[132:205]['Drugs'].values

    req_data = []
    for i in range(len(X1)):
        req_data.append([[X1[i], Y1[i]],0])

    for i in range(len(X2)):
        req_data.append([[X2[i], Y2[i]],1])

    trainData =[]
    testData = []
    for i in range (len(req_data)):
        if rd.random() < split:
            trainData.append(req_data[i])
        else:
            testData.append(req_data[i])

    testX = []
    testY = []
    trainX = []
    trainY = []

    for i in range(len(trainData)):
        trainX.append(trainData[i][0])
        trainY.append(trainData[i][1])

    for i in range(len(testData)):
        testX.append(testData[i][0])
        testY.append(testData[i][1])

    trainX = np.array(trainX)
    trainY = np.array(trainY)
    testX = np.array(testX)

    return trainX, trainY, testX, testY

if __name__ == '__main__':
    dataset = pd.read_csv('../crime.csv')
    trainX, trainY, testX, testY = dataPreparing(dataset, 0.85)
    model = LogisticRegression(solver='liblinear', random_state=0).fit(trainX, trainY)
    pred = model.predict(testX)
    test_report = classification_report(pred, testY)
    print('sklearn log: \n', pred)
    print('accur: ',model.score(testX,testY))
    print(test_report)

    trainLog = np.c_[np.ones(len(trainX)), trainX]
    testLog = np.c_[np.ones(len(testX)), testX]
    theta = np.zeros((trainLog.shape[1], 1))
    param = myLog.fit(trainLog, trainY, theta)
    res = myLog.prediction(testLog, param)
    pred_class = myLog.predict(res)
    test_report = classification_report(pred_class, testY)
    print('my log:\n', pred_class)
    print('my accur: ', myLog.accur(res, testY))
    print(test_report)

    res = myLog.prediction(trainLog, param)
    pred_class = myLog.predict(res)
    print('LR train:', myLog.accur(pred_class, trainY))

##############################
    model=tree.DecisionTreeClassifier()
    model.fit(trainX,trainY)
    pred = model.predict(testX)
    print('sklearn Dtree: \n')
    print(pred)
    print('accur: ')
    print(model.score(testX,testY))
    test_report = classification_report(pred, testY)
    print(test_report)

    model = myTree.DecisionTreeClassifier(max_depth=5)
    model.fit(trainX, trainY)
    pred = model.predict(testX)
    print('my Dtree: \n')
    print(pred)
    print('my accur: ', myLog.accur(pred, testY))
    test_report = classification_report(pred, testY)
    print(test_report)

    pred_class = model.predict(trainX)
    print('DT train:', myLog.accur(pred_class, trainY))
################################

    model = RandomForestClassifier(n_estimators=10)
    model.fit(trainX, trainY)
    pred = model.predict(testX)
    print('sklearn RF: \n')
    print(pred)
    print('accur: ')
    print(model.score(testX,testY))
    test_report = classification_report(pred, testY)
    print(test_report)

    model = myRD.RandomTreeClassifier(5)
    model.fit(trainX, trainY)
    pred = model.predict(testX)
    print('my RF: \n')
    print(pred.astype(int))
    print('my accur: ', myLog.accur(pred, testY))
    test_report = classification_report(pred, testY)
    print(test_report)

    pred_class = model.predict(trainX)
    print('RF train:', myLog.accur(pred_class, trainY))
