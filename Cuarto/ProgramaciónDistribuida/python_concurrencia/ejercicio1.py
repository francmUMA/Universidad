import threading

class myThread(threading.Thread):
    def __init__(self, id):
        threading.Thread.__init__(self)
        self.id = id
    
    def run(self):
        print("ID: ", self.id)

thread1 = myThread(1)
thread1.start()
thread1.join()