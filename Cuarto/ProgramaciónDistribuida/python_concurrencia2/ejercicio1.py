import threading
import random
import time

class Productor(threading.Thread):
    def __init__(self, buffer):
        super().__init__()
        self.buffer = buffer

    def run(self):
        while True:
            self.buffer.add()
            time.sleep(1)

class Consumidor(threading.Thread):
    def __init__(self, buffer, id):
        super().__init__()
        self.buffer = buffer
        self.id = id

    def run(self):
        while True:
            elem = self.buffer.remove()
            print(elem, " from ", self.id)
            time.sleep(2)

class Buffer():
    def __init__(self):
        self.buffer = []
        self.cond = threading.Condition()

    def add(self):
        self.cond.acquire()
        if len(self.buffer) == 10: self.cond.wait()

        self.buffer.append(random.randint(0,100))

        if (len(self.buffer) == 1): self.cond.notify()
        self.cond.release()
    
    def remove(self):
        self.cond.acquire()
        if len(self.buffer) == 0: self.cond.wait()

        elem = self.buffer.pop()

        if (len(self.buffer) == 9): self.cond.notify()
        self.cond.release()

        return elem

buffer = Buffer()
thread_productor = Productor(buffer)
thread_productor.start()

thread_consumidor1 = Consumidor(buffer, 1)
thread_consumidor2 = Consumidor(buffer, 2)

thread_consumidor1.start()
thread_consumidor2.start()
