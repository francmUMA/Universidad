--Factorial
factorial :: Integer -> Integer
factorial 0 = 1
factorial n | n > 0 = n * factorial(n-1)
--main = print(factorial 5) 

--Nice
nice :: Integer -> Integer
nice n = n * n + 10 
--main = print (nice 5)

--Weird no se puede crear ya que es una funcion impura
weird :: Integer -> Integer
state = 0
weird n = state + 1 + n 

