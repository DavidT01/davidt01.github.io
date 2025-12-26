import math

class Shape:
    
    # Podrazumevane vrednosti
    def __init__(self, color = 'black', filled = False):
        # Sa _ označavamo da želimo da promenljiva bude protected, a sa __ private
        self.__color = color
        self.__filled = filled
        
    def get_color(self):
        return self.__color
    
    def get_filled(self):
        return self.__filled
    
    def set_filled(self, filled):
        self.__filled = filled

# Za podklasu zadajemo listu klasa koje nasleđuje
class Rectangle(Shape):
    
    def __init__(self, length, breadth):
        # super() poziva nadklasu
        super().__init__()
        self.__length = length
        self.__breadth = breadth
        
    def get_area(self):
        return self.__length * self.__breadth
    
    def get_perimeter(self):
        return 2 * (self.__length + self.__breadth)
    
class Circle(Shape):
    
    def __init__(self, radius):
        super().__init__(color = 'blue')
        self.__radius = radius
        
    def get_area(self):
        return math.pi * self.__radius**2
    
    def get_perimeter(self):
        return 2 * math.pi * self.__radius
    
r1 = Rectangle(10, 50)
print(r1.get_color())
print(r1.get_filled())
print(r1.get_area())
print(r1.get_perimeter())
r1.set_filled(True)
print(r1.get_filled())

r2 = Circle(1)
print(r2.get_color())
print(r2.get_filled())
print(r2.get_area())
print(r2.get_perimeter())
r2.set_filled(True)
print(r2.get_filled())