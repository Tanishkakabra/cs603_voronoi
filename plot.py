import pandas as pd
import matplotlib.pyplot as plt

# Read data from the output.csv file (assuming it has columns: point1.x, point1.y, point2.x, point2.y)
df_output = pd.read_csv("output.csv")

bounds = pd.read_csv("bounding_values.csv", header=None)
xlimlow = bounds.iloc[0, 0]
ylimlow = bounds.iloc[0, 1]
xlimhigh = bounds.iloc[0, 2]
ylimhigh = bounds.iloc[0, 3]

# Extract values for xlimlow, ylimlow, xlimhigh, ylimhigh from the first row
# Create a scatter plot of point1
plt.scatter(df_output["point1.x"], df_output["point1.y"], label="Point 1", color="blue")

# Create a scatter plot of point2
plt.scatter(df_output["point2.x"], df_output["point2.y"], label="Point 2", color="red")

# Draw lines connecting each pair of points
for i in range(len(df_output)):
    plt.plot([df_output.loc[i, "point1.x"], df_output.loc[i, "point2.x"]],
             [df_output.loc[i, "point1.y"], df_output.loc[i, "point2.y"]],
             color="gray", linestyle="-")

# Read data from the input.csv file (assuming it has columns: x, y)
df_input = pd.read_csv("input.csv", header=None)  # No header row

# Extract x and y coordinates from the input data
x_input = df_input.iloc[:, 0]
y_input = df_input.iloc[:, 1]

# Create a scatter plot for input points
plt.scatter(x_input, y_input, label="Input Points", color="green", marker="o")

# Set equal aspect ratio for the plot
plt.axis("equal")

# Set xlim and ylim
plt.xlim(xlimlow, xlimhigh)
plt.ylim(ylimlow, ylimhigh)

# Add labels and title
plt.xlabel("X Coordinate")
plt.ylabel("Y Coordinate")
plt.title("Lines and Input Points")

# Show the plot
plt.legend()
plt.grid()
plt.show()
