import threading
import time

class myThread(threading.Thread):
    def __init__(self, id):
        threading.Thread.__init__(self)
        self.id = id
    
    def run(self):
        for _ in range(5):
            print("ID: ", self.id)
            time.sleep(1)
            print("La hebra sigue viva? ", self.is_alive())

thread1 = myThread(1)
thread1.start()
thread1.join(timeout=1)
if thread1.is_alive():
    print("La hebra sigue viva")