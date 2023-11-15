import threading

semaphore = threading.Semaphore(1)
data = {'a':0, 'e':0, 'i':0, 'o':0, 'u':0}

class AnalizerThread(threading.Thread):
    def __init__(self, frase, inicio, fin):
        super().__init__()
        self.frase = frase
        self.inicio = inicio
        self.fin = fin
    
    def run(self):
        super().run()
        for i in range(self.inicio, self.fin):
            semaphore.acquire()
            if  data.get(self.frase[i]) != None:
                data.update({self.frase[i]:data.get(self.frase[i]) + 1})
            semaphore.release()

frase = "Esto es una frase de prueba"
frase = frase.lower()
numThreads = 5
size = len(frase) // numThreads
threads = []

for i in range(numThreads):
    if i == numThreads - 1: threads.append(AnalizerThread(frase, i * size, len(frase)))
    threads.append(AnalizerThread(frase, i * size, (i * size) + size))
    threads[i].start()

for i in range(numThreads):
    threads[i].join()

print(data)