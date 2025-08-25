import sys

# Argumenti komandne linije (prvi argument je ime programa)
if len(sys.argv) > 1:
    for arg in sys.argv:
        print(arg)
        
import os

# Trenutni, roditeljski direktorijum i separator
print(os.curdir)
print(os.pardir)
print(os.sep)

# Vraća listu fajlova i direktorijuma u prosleđenom direktorijumu
print(os.listdir(os.curdir))

# Prolazi kroz sve poddirektorijume prosleđenog i vraća putanju, poddirektorijume i fajlove
for (dirpath, dirs, files) in os.walk(os.pardir):
    print(dirpath)
    print(dirs)
    print(files)

# Ispisujemo apsolutne putanje svih fajlova u trenutnom direktorijumu
for f in os.listdir(os.curdir):
    if os.path.isfile(os.path.join(os.curdir, f)):
        print(os.path.abspath(os.path.join(os.curdir, f)))