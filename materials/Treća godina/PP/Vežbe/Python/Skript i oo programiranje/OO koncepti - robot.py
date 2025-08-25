class Robot:
    # Dokumentacije klase
    """ Represents a robot with a name """
    
    # Statička promenljiva, zajednička za sve objekte
    population = 0
    
    def __init__(self, name):
        self.name = name
        Robot.population += 1
        print(f'{self.name} is created!')
        
    # Destruktor
    def __del__(self):
        Robot.population -= 1
        print(f'{self.name} is destroyed!')
        
    def say_hi(self):
        print(f'Hello, my name is {self.name}')
    
    # Klasna metoda, ako želimo statičku metodu koja ne koristi promenljive iz klase,
    # možemo koristiti @staticmethod i tada nemamo argument cls
    @classmethod
    def get_population(cls):
        return cls.population

print(Robot.get_population())
r1 = Robot("R2-D2")
r1.say_hi()
print(Robot.get_population())
r2 = Robot("David")
r2.say_hi()
print(Robot.get_population())
del r1
print(Robot.get_population())
del r2
print(Robot.get_population())