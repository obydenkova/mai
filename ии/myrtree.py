import numpy as np
import random
import myTree

class RandomTreeClassifier:
    def __init__(self, tree_num=10):
        self.tree_num = tree_num
        self.trees = []

    def get_sub_x(self, X,y):
        x_size = len(X)
        sample = []
        new_y = []
        while len(sample) < x_size:
            ind = random.randrange(x_size)
            sample.append(X[ind])
            new_y.append(y[ind])
        sample = np.array(sample)
        new_y = np.array(new_y)
        return sample, new_y

    def fit(self, X, y):
        for i in range(self.tree_num):
            tree = myTree.DecisionTreeClassifier()
            X1, Y1 = self.get_sub_x(X, y)
            tree.fit(X1,Y1, 1)
            self.trees.append(tree)

    def predict(self, X):
        res = np.zeros(len(X))
        for i in range(self.tree_num):
            res += self.trees[i].predict(X)

        for i in range(len(res)):
            if (res[i] / self.tree_num < 0.5):
                res[i] = 0
            else:
                res[i] = 1
        return res
