import threading
import math
import random
import time
import queue

class Consumidor (threading.Thread):
    def __init__ (self, cola):
        super().__init__()
        self.cola = cola
        self.puntos_dentro = 0
        self.puntos_totales = 0
    
    def run (self):
        while True:
            data = self.cola.get()
            self.puntos_dentro += data[0]
            self.puntos_totales += data[1]
            print("Puntos dentro del circulo: ", self.puntos_dentro, "Puntos totales: ", self.puntos_totales)
            print("Pi: ", (self.puntos_dentro/self.puntos_totales)*4, 
                  " Error: ", abs(math.pi - (self.puntos_dentro/self.puntos_totales)*4))

class Productor (threading.Thread):
    def __init__ (self, cola, n):
        super().__init__()
        self.cola = cola
        self.n = n
    
    def run (self):
        while True:
            puntos_dentro = 0
            for i in range(0, self.n):
                x = random.uniform(-1, 1)
                y = random.uniform(-1, 1)
                if x**2 + y**2 <= 1: puntos_dentro += 1
            
            self.cola.put((puntos_dentro, self.n))
            time.sleep(1)

cola = queue.Queue()
consumidor = Consumidor(cola)
for _ in range(0,10):
    productor = Productor(cola, 100000)
    productor.start()

consumidor.start()