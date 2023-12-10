import pandas as pd
import matplotlib.pyplot as plt

plot_fname = "omp_execute.png"

fname = "speedup.csv"
df = pd.read_csv(fname, comment="#")
var_names = list(df.columns)

# split the df into individual vars
# assumption: column order - 0=problem size, 1=blas time, 2=basic time

problem_sizes = df[var_names[0]].values.tolist()
code1_time = df[var_names[1]].values.tolist()
code2_time = df[var_names[2]].values.tolist()
code3_time = df[var_names[3]].values.tolist()
code4_time = df[var_names[4]].values.tolist()
code5_time = df[var_names[5]].values.tolist()
code6_time = df[var_names[6]].values.tolist()
code7_time = df[var_names[7]].values.tolist()


plt.figure()

plt.title("Execute Time(ms) of KMS Serial and OMP at various Threads")

xlocs = [i for i in range(len(problem_sizes))]

plt.xticks(xlocs, problem_sizes)

plt.plot(code1_time, "k-<",label = var_names[1])
plt.plot(code2_time, "b-x",label = var_names[2])
plt.plot(code3_time, "g-+",label = var_names[3])
plt.plot(code4_time, "m-*",label = var_names[4])
plt.plot(code5_time, "c-^",label = var_names[5])
plt.plot(code6_time, "y-D",label = var_names[6])
plt.plot(code7_time, "r-o",label = var_names[7])


#plt.xscale("log")
#plt.yscale("log")

plt.xlabel("Problem Sizes")
plt.ylabel("Speedup")

plt.legend(loc="best")

plt.grid(axis='both')
plt.ylim(0, 30) 


# save the figure before trying to show the plot
plt.savefig(plot_fname, dpi=300)


plt.show()

# EOF
