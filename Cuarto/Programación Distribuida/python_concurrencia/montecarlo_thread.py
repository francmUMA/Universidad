import math
import random
import threading
import numpy as np


total_points = 100000
HEBRAS = 16
results_list = []
hebras_array = []
N_POINTS = total_points / HEBRAS

def montecarlo(puntos_totales, results):
  inside_points = 0
  x = 0.0
  y = 0.0

  for i in range(0, puntos_totales):
    x = random.uniform(-1.00, 1.00)
    y = random.uniform(-1.00, 1.00)
    if (x*x + y*y <= 1):
      inside_points += 1

  pi = (4.0 * inside_points / puntos_totales)
  error = math.pi - pi

  results = [pi, error]

for i in range(0, HEBRAS):
  results_list.insert(i, [0.0, 0.0])
  hebras_array.append(threading.Thread(target=montecarlo, args=(total_points,i,results_list[i])))
  hebras_array[i].start()

for i in range(0, HEBRAS):
  hebras_array[i].join()

pi = 0.0
for i in range(0, HEBRAS):
  pi += results_list[i][0]

print("Pi: ",pi)
pi = pi / HEBRAS

error = 0.0
for i in range(0, HEBRAS):
  error += results_list[i][1]

error = error / HEBRAS

print("Error: ",error,"\n" + "Pi: ",pi)

