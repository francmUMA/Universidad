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
            x = random.uniform(-1, 1)
            y = random.uniform(-1, 1)
            if (x*x + y*y <= 1):
                self.pointsInside += 1
    
    def getPointsInside(self):
        return self.pointsInside

totalPoints = 10000000
pointsInside = 0

thread = pithread(totalPoints)
thread.start()


thread.join()
pointsInside = thread.getPointsInside()

pi = 4.0 * pointsInside / totalPoints
error = math.pi - pi

print("Pi: ",pi)
print("Error: ",error)
        

