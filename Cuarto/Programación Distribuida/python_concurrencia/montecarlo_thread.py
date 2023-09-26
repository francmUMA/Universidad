import math
import random
import threading

total_points = 100000
pi = 0.0
error = 0.0

def montecarlo(puntos_totales):
  inside_points = 0
  x = 0.0
  y = 0.0

  for i in range(0, puntos_totales):
    x = random.uniform(-1.00, 1.00)
    y = random.uniform(-1.00, 1.00)
    if (x*x + y*y <= 1):
      inside_points += 1

  pi = 4.0 * inside_points / puntos_totales
  error = math.pi - pi

class PiThread(threading.Thread):
    def __init__(self, group=None, target=None, name=None,
                 args=(), kwargs={}, Verbose=None):
        threading.Thread.__init__(self, group=group, target=target, name=name,
                 args=args, kwargs=kwargs)
        self.value = (0.0, 0.0)

  


print("Error: ",error,"\n" + "Pi: ",pi)