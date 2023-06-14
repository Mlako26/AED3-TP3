import pathlib
import subprocess
import os
import random
import shutil
import time
import matplotlib.pyplot as plt
import math

# Cambiar directorio 
parent_dir = pathlib.Path(__file__).parent
os.chdir(parent_dir)


# Compilar C++ code
subprocess.run(["g++", "-o", "ej3", "../src/ej3.cpp"])
subprocess.run(["g++", "-o", "ej3c", "../src/ej3counting.cpp"])


# Variables
MIN_N = 100
MAX_N = 2000 + MIN_N

REPS = 100
STEP = 100

# crear carpeta para ubicar los tests
if not os.path.exists(os.path.join(parent_dir, "in")) : 
    os.mkdir(os.path.join(parent_dir, "in")) 

# crear archivo donde meter los tiempos
open("tiempos.txt", "w").close()

# generar test aleatorio para un n especifico
def random_test(n):
    test = ""
    U = random.randint(1, 10)
    V = random.randint(1, 10)
    R = random.randint(1, int(1e4))
    W = random.randint(1, n-1)
    test += str(n) + " " + str(R) + " " + str(W) + " " + str(min(U, V)) + " " + str(max(U, V)) + "\n"
    
    x = random.sample(range(-10000, 10000), n)
    y = random.sample(range(-10000, 10000), n)
    
    for i in range(0, n):
        test += str(x[i]) + " " + str(y[i]) + "\n"

    return test

def create_tests():
    T = (MAX_N - MIN_N) // STEP
    for n in range(MIN_N, MAX_N, STEP):
        with open(f"in/test_{n}", 'w') as f:
            f.write(f"{REPS}\n")
            for _ in range(REPS):
                f.write(random_test(n))


# compilar el codigo y correr los tests aleatorios
def run():
    for n in range(MIN_N, MAX_N, STEP):
        with open(f"in/test_{n}", 'r') as f:
            input_data = f.read()

        # Run C++ program with input
        start_time = time.time()
        subprocess.run(["./ej3"], input=input_data, stdout=subprocess.PIPE, text=True)
        end_time = time.time()
        t1 = (end_time - start_time)
        start_time = time.time()
        subprocess.run(["./ej3c"], input=input_data, stdout=subprocess.PIPE, text=True)
        end_time = time.time()
        t2 = (end_time - start_time)

        # guardar tiempo promedio con 5 decimales
        with open("tiempos.txt", 'a') as f:
            f.write(f"{n} {t1/REPS:.5f} {t2/REPS:.5f}\n")


create_tests()
run()
shutil.rmtree("in") # borra los tests aleatorios 

# Leer los datos del archivo
n = []
t1 = []
t2 = []
with open('tiempos.txt') as f:
    for line in f:
        n_val, t1_val, t2_val = line.strip().split()
        n.append(int(n_val))
        t1.append(float(t1_val))
        t2.append(float(t2_val))

# Crear el gráfico
plt.plot(n, t1, label="QuickSort", color='red')
plt.scatter(n, t1, color='red')
plt.plot(n, t2, label="BucketSort", color='blue')
plt.scatter(n, t2, color='blue')
plt.title('Tiempo de Ejecución en Función de la Cantidad de Oficinas')
plt.xlabel('Cantidad de Oficinas')
plt.ylabel('Tiempo de Ejecución Promedio (s)')
plt.legend()
plt.grid(True)

# Guardar el gráfico en un archivo
plt.savefig('grafico.png')