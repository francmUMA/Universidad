import threading

lock = threading.Condition()

class writer_thread(threading.Thread):
    def __init__(self, message):
        super().__init__()
        self.message = message

    
    def run(self):
        super().run()
        for i in range(5):
            lock.acquire()
            print(self.message, end="")
            lock.notify()
            if i < 4: lock.wait()
            lock.release()
        
t1 = writer_thread("Hola")
t2 = writer_thread(" Mundo\n")
t1.start()
t2.start()
t1.join()
t2.join()

            

