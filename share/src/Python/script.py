import sys
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib import dates
import numpy as np

plt.rcParams["figure.figsize"] = [7.50, 3.50]
plt.rcParams["figure.autolayout"] = True

headers = ['Date', 'close']

df = pd.read_csv(sys.argv[1])

np_arr = df.values
datearr = np_arr[:,0]
pricearr = np_arr[:,4]

fig, ax=plt.subplots(1, 1)
ax.xaxis.set_major_locator(dates.MonthLocator(bymonthday=1))
plt.plot_date(datearr,pricearr,"")
plt.gcf().autofmt_xdate()
plt.savefig(sys.argv[2])