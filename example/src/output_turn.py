import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import MultipleLocator
from io import StringIO

# 🔹 Pega aquí tu CSV completo
raw_data = """
index,time_ms,yaw,left_rpm,right_rpm
0,2913,0.00,-4.27,-0.00
1,3013,0.01,-3.40,-0.00
2,3033,0.00,-3.20,-9.00
3,3053,0.01,57.80,-68.27
4,3073,-0.10,62.67,-75.93
5,3093,-0.64,70.47,-80.87
6,3113,-1.55,69.93,-77.93
7,3133,-2.75,72.47,-78.07
8,3153,-4.20,74.20,-84.87
9,3173,-5.80,69.13,-73.73
10,3193,-7.38,74.93,-79.73
11,3213,-9.20,78.60,-82.20
12,3233,-11.09,73.67,-83.53
13,3253,-13.06,78.40,-86.53
14,3273,-15.12,76.27,-81.07
15,3293,-17.08,75.73,-81.27
16,3313,-19.18,75.33,-83.53
17,3333,-21.35,76.33,-84.07
18,3353,-23.56,73.73,-87.67
19,3373,-24.65,77.87,-82.33
20,3393,-26.83,73.80,-84.20
21,3413,-29.02,75.13,-83.87
22,3433,-31.32,76.40,-86.73
23,3453,-33.63,76.13,-82.40
24,3473,-35.89,76.33,-84.53
25,3493,-38.19,74.53,-83.07
26,3513,-40.48,78.40,-84.13
27,3533,-42.76,73.60,-87.27
28,3553,-44.95,75.07,-85.00
29,3573,-47.13,75.00,-81.47
30,3593,-49.40,79.33,-84.73
31,3613,-51.63,76.27,-84.20
32,3633,-53.73,74.60,-86.20
33,3653,-55.89,69.93,-81.47
34,3673,-58.08,76.87,-84.13
35,3693,-60.38,77.00,-88.00
36,3713,-62.68,73.60,-87.80
37,3733,-64.79,73.67,-86.20
38,3753,-66.88,75.27,-85.93
39,3773,-68.98,73.67,-88.40
40,3793,-71.15,78.13,-83.73
41,3813,-73.29,73.80,-84.87
42,3833,-75.39,74.20,-78.60
43,3853,-77.51,79.13,-83.87
44,3873,-79.65,78.13,-84.93
45,3893,-81.81,78.00,-83.20
46,3913,-84.01,77.00,-88.20
47,3933,-86.18,75.27,-77.13
48,3953,-88.27,75.93,-82.20
49,3973,-90.47,75.67,-83.60

"""


# 🔹 DataFrame
df = pd.read_csv(StringIO(raw_data))

# 🔹 Tiempo en segundos
df["time_s"] = df["time_ms"] / 1000

# 🔥 USAR YAW DIRECTO COMO ÁNGULO
df["angle"] = df["yaw"]

# =========================
# 📊 GRÁFICA ÁNGULO
# =========================
plt.figure()
plt.plot(df["time_s"], df["angle"], label="Ángulo (real)")

ax = plt.gca()

# 🔥 CUADRÍCULA PRO
ax.yaxis.set_major_locator(MultipleLocator(3))
ax.yaxis.set_minor_locator(MultipleLocator(1))

plt.grid(which='major', linewidth=1)
plt.grid(which='minor', linestyle=':', alpha=0.5)

plt.title("Ángulo vs Tiempo (REAL)")
plt.xlabel("Tiempo (s)")
plt.ylabel("Ángulo (grados)")
plt.legend()

# =========================
# 📊 RPM
# =========================
plt.figure()
plt.plot(df["time_s"], df["left_rpm"], label="Left RPM")
plt.plot(df["time_s"], df["right_rpm"], label="Right RPM")

ax = plt.gca()
ax.yaxis.set_major_locator(MultipleLocator(10))
ax.yaxis.set_minor_locator(MultipleLocator(2))

plt.grid(which='major', linewidth=1)
plt.grid(which='minor', linestyle=':', alpha=0.5)

plt.title("RPM vs Tiempo")
plt.xlabel("Tiempo (s)")
plt.ylabel("RPM")
plt.legend()

plt.show()