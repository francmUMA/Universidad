import threading
import random
import math

class pithread (threading.Thread):
    def __init__(self, totalPoints):
        super().__init__()
        self.totalPoints = totalPoints
        self.pointsInside = 0
    
    def run(self):
        super().run()
        for _ in range(self.totalPoints):
            x = random.uniform(-1.00, 1.00)
            y = random.uniform(-1.00, 1.00)
            if (x*x + y*y <= 1):
                self.pointsInside += 1

totalPoints = 100000000
threads = 24
pointsInside = 0
threadsList = []

for _ in range(threads):
    thread = pithread(totalPoints//threads)
    threadsList.append(thread)
    thread.start()

for thread in threadsList:
    thread.join()
    pointsInside += thread.pointsInside

pi = 4.0 * pointsInside / totalPoints
error = math.pi - pi

print("Pi: ",pi)
print("Error: ",error)
        