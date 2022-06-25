import sys
import matplotlib.pyplot as plt
from matplotlib import dates
import numpy as np

def readfile(filename):
    f = open(filename, "r")
    pricearr = np.array(())
    datearr = np.array(())
    for string in f:
        price_string = ""
        date_string = ""
        for element in range(0, len(string)):
            if string[element] == " ":
                price_string = string[:element]
                date_string = string[element + 1:len(string) - 1]
                break
        price = float(price_string)
        pricearr = np.append(pricearr, price)
        datearr = np.append(datearr, date_string)

    fig, ax=plt.subplots(1, 1)
    ax.xaxis.set_major_locator(dates.MonthLocator(bymonthday=1))
    plt.plot_date(datearr,pricearr,"")
    plt.gcf().autofmt_xdate()
    plt.savefig(sys.argv[2])

    f.close()


if __name__ == '__main__':
    readfile(sys.argv[1])
    #"src/Python/prices.txt"

