import threading
import time
import queue

def fib(n):
    if n == 1 or n == 0:
        return n
    else:
        return fib(n-1) + fib(n-2)

class Productor(threading.Thread):
    def __init__(self, n, cola):
        super().__init__()
        self.cola = cola
        self.n = n
    
    def run(self):
        for i in range(0, self.n):
            time.sleep(0.5)
            self.cola.put(fib(i))

class Consumidor(threading.Thread):
    def __init__(self, cola):
        super().__init__()
        self.cola = cola
    
    def run(self):
        while True:
            time.sleep(1)
            print(self.cola.get())

cola = queue.Queue()
productor = Productor(10, cola)
consumidor = Consumidor(cola)

productor.start()
consumidor.start()

productor.join()
consumidor.join()

