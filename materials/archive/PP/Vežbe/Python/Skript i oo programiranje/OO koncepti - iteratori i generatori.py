class MyIterator:
    
    def __init__(self, limit):
        self.limit = limit
    
    # Poziva se pre iteracije, vraća objekat koji ima metod __next__
    def __iter__(self):
        self.position = 0
        return self
    
    # Poziva se kada treba preći na sledeći element
    def __next__(self):
        if self.position >= self.limit:
            raise StopIteration
        self.position += 1
        return self.position - 1
    
#for i in MyIterator(10):
#    print(i)

# Generatori su funkcije koje imaju ključnu reč yield, oni se prebacuju u iteratore
# yield vraća neku vrednost, ali nastavlja dalje sa izvršavanjem i pamti gde je stao
def MyGenerator():
    yield [] 
    for i in range(10):
        yield i
    yield 15
      
#for value in MyGenerator():
#    print(value)
    
# npr. Fibonačijevi brojevi
def Fibonacci():
    a = 0
    b = 1
    while True:
        yield a
        a, b = b, a + b  

for n in Fibonacci():
    print(n)