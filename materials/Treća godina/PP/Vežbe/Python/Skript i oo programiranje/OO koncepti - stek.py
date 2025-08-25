class Stack:
    
    # Konstruktor
    def __init__(self):
        # Promenljiva koju će imati svaki objekat klase
        self.items = []
    
    def push(self, el):
        self.items.append(el)
        
    def peek(self):
        try:
            return self.items[-1]
        except IndexError:
            print('Stack is empty!')
            return None
    
    def pop(self):
        try:
            return self.items.pop()
        except IndexError:
            print('Stack is empty!')
            return None

s = Stack()
s.push(1)
s.push(3)
s.push(4)
s.push(2)
print(s.peek())
print(s.pop())
print(s.peek())
print(s.pop())
print(s.pop())
print(s.pop())
print(s.peek())
print(s.pop())