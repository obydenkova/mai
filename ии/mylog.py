mport numpy as np
from scipy.optimize import fmin_tnc

def sigmoid(x):
    return 1 / (1 + np.exp(-x))

def net_input(theta, x):
    return np.dot(x, theta)

def probability(theta, x):
    return sigmoid(net_input(theta, x))


def cost_function(theta, x, y):
    m = x.shape[0]
    total_cost = -(1 / m) * np.sum(
        y * np.log(probability(theta, x)) + (1 - y) * np.log(
            1 - probability(theta, x)))
    return total_cost

def gradient(theta, x, y):
    m = x.shape[0]
    return (1 / m) * np.dot(x.T, sigmoid(net_input(theta,   x)) - y)

def fit(x, y, theta):
    opt_weights = fmin_tnc(func=cost_function, x0=theta,
                  fprime=gradient,args=(x, y), messages=0)
    return opt_weights[0]

def prediction(x, param):
    theta = param[:, np.newaxis]
    return probability(theta, x)

def predict(res, probab_threshold=0.5):
    predicted_classes = []
    for pred in res:
        if pred >= probab_threshold:
            predicted_classes += [1]
        else:
            predicted_classes += [0]
    return predicted_classes

def accur(res, trueX):
	count = 0
	for i in range(len(trueX)):
		if ((res[i] >=0.5 and trueX[i] == 1) or
			(res[i] < 0.5 and trueX[i] == 0)):
			count+=1
	return count / len(trueX)

