import math
import random
import time
import queue
import concurrent.futures as concurrent

class Productor ():
    def __init__ (self, cola, n, id):
        self.cola = cola
        self.n = n
        self.id = id
    
    def run (self):
        puntos_dentro = 0
        for _ in range(0, self.n):
            x = random.uniform(-1, 1)
            y = random.uniform(-1, 1)
            if x**2 + y**2 <= 1: puntos_dentro += 1
        
        self.cola.put((puntos_dentro, self.n))
        time.sleep(random.uniform(0.5, 2))
        print("Productor ", self.id, " ha terminado")
        return (4*(puntos_dentro/self.n), abs(math.pi - 4*(puntos_dentro/self.n)))

cola = queue.Queue()

executor = concurrent.ThreadPoolExecutor(10)
futures = []
for i in range(0,10):
   futures.append(executor.submit(Productor(cola, 100000, i).run))

for futuro in concurrent.as_completed(futures):
    print("Pi: ", futuro.result()[0], " Error: ", futuro.result()[1])