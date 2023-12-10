import matplotlib.pyplot as plt
plot_fname = "700mb_execute.png"

# Sample data
categories = ['Serial', 'P=1', 'P=4', 'P=8', 'P=16', 'P=32', 'P=64']
values = [941, 944, 542, 482, 456, 439, 437]

# Colors for each bar
colors = ['red', 'green', 'blue', 'orange', 'purple', 'brown', 'pink']

# Creating the bar chart with different colors
bars = plt.bar(categories, values, color=colors)

# Adding the value as text on top of each bar
for bar in bars:
    yval = bar.get_height()
    plt.text(bar.get_x() + bar.get_width()/2, yval, int(yval), ha='center', va='bottom')

# Adding title and labels
plt.title('KMS execution time of 700MB file')
plt.xlabel('methods')
plt.ylabel('time (ms)')
plt.savefig(plot_fname, dpi=300)

# Display the chart
plt.show()
