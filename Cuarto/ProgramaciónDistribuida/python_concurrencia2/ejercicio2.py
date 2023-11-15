import threading
import random

class Jugador(threading.Thread):
    def __init__(self, id, dado1, dado2):
        super().__init__()
        self.id = id
        self.dado1 = dado1
        self.dado2 = dado2
        self.puntos = 0
    
    def run(self):
        print(f"Jugador {self.id} ha lanzado los dados")
        dado1.lanzar()
        dado2.lanzar()
        self.puntos = dado1.valor + dado2.valor
        print(f"Jugador {self.id} ha sacado {self.puntos} puntos, con los dados {dado1.valor} y {dado2.valor}")
        dado1.liberar()
        dado2.liberar()
    
    def get_resultado(self):
        return self.puntos

class Dado():
    def __init__(self):
        self.disponible = True
        self.valor = 0
        self.cond = threading.Condition()
    
    def lanzar(self):
        self.cond.acquire()
        if (not self.disponible): self.cond.wait()
        self.disponible = False
        self.valor = random.randint(1,6)
        self.cond.release()
    
    def liberar(self):
        self.cond.acquire()
        self.disponible = True
        self.cond.notify()
        self.cond.release()
    
    def get_valor(self):
        return self.valor

dado1 = Dado()
dado2 = Dado()

thread_p1 = Jugador(1, dado1, dado2)
thread_p2 = Jugador(2, dado1, dado2)

thread_p1.start()
thread_p2.start()

thread_p1.join()
thread_p2.join()

if (thread_p1.get_resultado() > thread_p2.get_resultado()):
    print(f"Jugador 1 ha ganado con {thread_p1.get_resultado()} puntos")
elif (thread_p1.get_resultado() < thread_p2.get_resultado()):
    print(f"Jugador 2 ha ganado con {thread_p2.get_resultado()} puntos")
else:
    print(f"Empate con {thread_p1.get_resultado()} puntos")