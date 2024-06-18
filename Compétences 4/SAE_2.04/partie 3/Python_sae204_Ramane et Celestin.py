import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from sklearn.linear_model import LinearRegression
from spyder_kernels.utils.iofuncs import load_dictionary

fillesDF = pd.read_csv("./vue_pourcentage_filles.csv", delimiter=";")

fillesDF = fillesDF.dropna()
fillesAR = np.array(fillesDF)


def Centreduire(T):
    T = np.array(T, dtype=np.float64)
    (n, p) = T.shape
    Res = np.zeros((n, p))
    TMoy = np.mean(T, axis=0)
    TEcart = np.std(T, axis=0)
    for j in range(p):
        Res[:, j] = (T[:, j] - TMoy[j]) / TEcart[j]
    return Res


fillesAR0 = fillesAR[:, [2, 3, 4, 5, 6, 7]]
fillesAR0_CR = Centreduire(fillesAR0)


def DiagBatons(Colonne):
    Colonne = np.array(Colonne, dtype=np.float64)
    m = min(Colonne)  # m contient la valeur minimale de la colonne
    M = max(Colonne)  # M contient la valeur maximale de la colonne
    inter = []
    inter = np.linspace(
        m, M, 21
    )  # liste de 21 valeurs allant de m `a M. On peut utiliser la fonction np.linspace
    plt.figure()
    plt.hist(Colonne, inter, histtype='bar', align='left', rwidth=0.75)
    plt.title(f'Diagramme en bâtons pour la pourcentage des filles ')
    plt.xlabel('la pourcentage des filles')
    plt.show()
    
    # trace du diagramme pour les intervalles inter

#print(DiagBatons(fillesAR0_CR[:, 0]))

# Calcul de la matrice de covariance

MatriceCov = np.cov(fillesAR0_CR, rowvar=False)


#print("Matrice de covariance:")
#print(MatriceCov)

#la variable endogene
Y= fillesAR0_CR[:,5]
print("Variable endogène:")
print(Y)

#la variable explicative 
X= fillesAR0_CR[:,[0,2,3,4]]
print("Variable explicative:")
print(X)

linear_regression = LinearRegression()
linear_regression.fit(X, Y)
coefficients = linear_regression.coef_
print("a0")
print(coefficients)

# la regression linéaire multiple matricielle

def regression_lineaire_multiple(X, Y):
    n, p = X.shape
    X = np.hstack((np.ones((n, 1)), X))
    beta = np.linalg.inv(X.T @ X) @ X.T @ Y
    return beta

print("a1")
print(regression_lineaire_multiple(X, Y))


#coefficient de correlation

Ypred = np.array(coefficients[0]*X[:,0] + coefficients[1]*X[:,1] + coefficients[2]*X[:,2] + coefficients[3]*X[:,3])
print("Ypred")
print(Ypred)

def CorFilles (Y, Ypred):
    Y = np.array(Y, dtype=np.float64)
    Ypred = np.array(Ypred, dtype=np.float64)
    n = len(Y)
    Res = 0
    for i in range(n):
        Res += (Y[i] - Ypred[i]) ** 2
    return Res

print("Coefficient de correlation")
print(CorFilles(Y,Ypred))





