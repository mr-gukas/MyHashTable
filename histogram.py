import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import csv

# Read the data from the CSV file
x_list = []
y_list = []

bar_names = ["Const hash", "First ASCII hash", "Wordlen hash", "ASCII sum hash", 
             "ROL hash", "ROR hash", "PJW hash"]

with open('data/output.csv', 'r') as f:
    reader = csv.reader(f, delimiter='\t')
    x = []
    y = []
    for row in reader:
        if row == []:  # empty line, start a new bar chart
            x_list.append(x)
            y_list.append(y)
            x = []
            y = []
        else:
            x.append(float(row[0]))
            y.append(float(row[1]))
    # append the last bar chart
    x_list.append(x)
    y_list.append(y)

# Create and save the bar charts
for i in range(7):
    # Create a new figure and axis for each bar chart
    fig, ax = plt.subplots()
    
    # Plot the bar chart
    ax.bar(x_list[i], y_list[i])
    
    # Set the x-axis step length to 50
    ax.xaxis.set_major_locator(ticker.MultipleLocator(50))
    
    # Add labels and title
    ax.set_xlabel('Номер списка')
    ax.set_ylabel('Количество элементов')
    ax.set_title(bar_names[i])
    
    # Save the figure as an image
    fig.savefig('data/bar_chart_{}.png'.format(i+1))

    # Close the figure
    plt.close(fig)

