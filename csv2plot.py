from scipy import *
from scipy import  stats
from scipy import  optimize
from numpy import *


import matplotlib.pyplot as plt
import matplotlib.font_manager
import networkx as nx

prop =  matplotlib.font_manager.FontProperties(fname='C:\Windows\Fonts\meiryo.ttc', size=20)


filename = ["eil51", "pr76", "rat99", "kroA100", "ch130"]
for i in range(5):

    name = filename[i] + ".csv"
    data = loadtxt(name,delimiter=",")
    print("mean:", average(data))
    print("variance:", std(data))
    plt.figure(i);
    plt.title("AS " + filename[i] , fontproperties=prop)
    plt.plot(data);


plt.show()
