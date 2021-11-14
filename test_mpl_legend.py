import numpy as np 
import matplotlib.pyplot as plt 

x = np.array([1,2]) 
data = np.array([10,8]) 
err = np.array([2,1]) 

b1 = plt.bar(x-.2,2*err,0.4,color='b',bottom=data - err,alpha=0.3) 
plt.legend([b1[0]], ['nice legend graphic'],shadow=True,fancybox=True,numpoints=1) 
plt.axis([0,3,0,15]) 

plt.show()
