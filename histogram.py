import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import csv
import numpy as np

x_list = []
y_list = []

bar_names = ["Const hash", "First ASCII hash", "Wordlen hash", "ASCII sum hash", 
             "ROL hash", "ROR hash", "PJW hash"]

with open('data/output.csv', 'r') as f:
    reader = csv.reader(f, delimiter='\t')
    x = []
    y = []
    for row in reader:
        if row == []:  
            x_list.append(x)
            y_list.append(y)
            x = []
            y = []
        else:
            x.append(float(row[0]))
            y.append(float(row[1]))

    x_list.append(x)
    y_list.append(y)

for i in range(7):
    std_dev = np.sqrt(np.var(y_list[i]))

    fig, ax = plt.subplots()
    
    if i == 0:
        x_list[i] = x_list[i][:500]
        y_list[i] = y_list[i][:500]
    
    if i == 2:
        x_list[i] = x_list[i][:100]
        y_list[i] = y_list[i][:100]
        ax.xaxis.set_major_locator(ticker.MultipleLocator(5))
    else:
        ax.xaxis.set_major_locator(ticker.MultipleLocator(100))

    ax.bar(x_list[i], y_list[i], color='red', linewidth=2, label=bar_names[i] + f' (Dispersion: {std_dev:.2f})')
    


    ax.set_xlabel('Номер списка')
    ax.set_ylabel('Количество элементов')
    ax.set_title(bar_names[i])
    ax.legend()
   
    fig.savefig('data/bar_chart_{}.png'.format(i+1))
    
    # Close the figure
    plt.close(fig)

