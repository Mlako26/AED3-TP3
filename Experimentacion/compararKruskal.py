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
subprocess.run(["g++", "-o", "ej3dense", "../src/ej3dense.cpp"])
subprocess.run(["g++", "-o", "ej3gooddsu", "../src/ej3gooddsu.cpp"])
subprocess.run(["g++", "-o", "ej3baddsu", "../src/ej3baddsu.cpp"])


# Variables
MIN_N = 100
MAX_N = int(1e3) + MIN_N
stress = [500, 600, 700, 800, 900]

REPS = 100
STRESS_REPS = 1000
STEP = 100

# crear carpeta para ubicar los tests
if not os.path.exists(os.path.join(parent_dir, "in")) : 
    os.mkdir(os.path.join(parent_dir, "in")) 

# crear archivo donde meter los tiempos
open("tiemposK.txt", "w").close()

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

def create_tests_linear():
    for n in range(MIN_N, MAX_N, STEP):
        with open(f"in/test_{n}", 'w') as f:
            f.write(f"{REPS}\n") # Hace 100 test cases por n diferente
            for _ in range(REPS):
                f.write(random_test(n))

def create_tests_stress():
    for n in stress:
        with open(f"in/test_{n}", 'w') as f:
            f.write(f"{STRESS_REPS}\n") # Hace 100 test cases por n diferente
            for _ in range(STRESS_REPS):
                f.write(random_test(n))


# compilar el codigo y correr los tests aleatorios
def run_linear():
    for n in range(MIN_N, MAX_N, STEP):
        with open(f"in/test_{n}", 'r') as f:
            input_data = f.read()

        # Run C++ program with input
        start_time = time.time()
        subprocess.run(["./ej3baddsu"], input=input_data, stdout=subprocess.PIPE, text=True)
        end_time = time.time()
        t1 = (end_time - start_time)

        start_time = time.time()
        subprocess.run(["./ej3gooddsu"], input=input_data, stdout=subprocess.PIPE, text=True)
        end_time = time.time()
        t2 = (end_time - start_time)

        start_time = time.time()
        subprocess.run(["./ej3dense"], input=input_data, stdout=subprocess.PIPE, text=True)
        end_time = time.time()
        t3 = (end_time - start_time)

        # guardar tiempo promedio con 5 decimales
        with open("tiemposK.txt", 'a') as f:
            f.write(f"{n} {t1/REPS:.5f} {t2/REPS:.5f} {t3/REPS:.5f}\n")

def run_stress():
    for n in stress:
        with open(f"in/test_{n}", 'r') as f:
            input_data = f.read()

        # Run C++ program with input
        start_time = time.time()
        subprocess.run(["./ej3baddsu"], input=input_data, stdout=subprocess.PIPE, text=True)
        end_time = time.time()
        t1 = (end_time - start_time)

        start_time = time.time()
        subprocess.run(["./ej3gooddsu"], input=input_data, stdout=subprocess.PIPE, text=True)
        end_time = time.time()
        t2 = (end_time - start_time)

        # guardar tiempo promedio con 5 decimales
        with open("tiemposK.txt", 'a') as f:
            f.write(f"{n} {t1/STRESS_REPS:.5f} {t2/STRESS_REPS:.5f}\n")

def graph_linear():
    # Leer los datos del archivo
    n = []
    t1 = []
    t2 = []
    t3 = []
    with open('tiemposK.txt') as f:
        for line in f:
            n_val, t1_val, t2_val, t3_val = line.strip().split()
            n.append(int(n_val))
            t1.append(float(t1_val))
            t2.append(float(t2_val))
            t3.append(float(t3_val))

    # Crear el gráfico
    plt.plot(n, t1, label="DSU", color='red')
    plt.scatter(n, t1, color='red')
    plt.plot(n, t2, label="DSU optimizado", color='blue')
    plt.scatter(n, t2, color='blue')
    plt.plot(n, t3, label="KruskalDense",color='green')
    plt.scatter(n, t3, color='green')
    plt.title('Tiempo de Ejecución en Función de la Cantidad de Oficinas')
    plt.xlabel('Cantidad de Oficinas')
    plt.ylabel('Tiempo de Ejecución Promedio (s)')
    plt.legend()
    plt.grid(True)

    # Guardar el gráfico en un archivo
    plt.savefig('graficoKlinear.png')

def graph_stress():
    # Leer los datos del archivo
    n = []
    t1 = []
    t2 = []
    with open('tiemposK.txt') as f:
        for line in f:
            n_val, t1_val, t2_val = line.strip().split()
            n.append(int(n_val))
            t1.append(float(t1_val))
            t2.append(float(t2_val))

    # Crear el gráfico
    plt.plot(n, t1, label="DSU", color='red')
    plt.scatter(n, t1, color='red')
    plt.plot(n, t2, label="DSU optimizado", color='blue')
    plt.scatter(n, t2, color='blue')
    plt.title('Tiempo de Ejecución en Función de la Cantidad de Oficinas')
    plt.xlabel('Cantidad de Oficinas')
    plt.ylabel('Tiempo de Ejecución Promedio (s)')
    plt.legend()
    plt.grid(True)

    # Guardar el gráfico en un archivo
    plt.savefig('graficoKstress.png')

print("Creando tests:...")
#create_tests_linear()
create_tests_stress()
print("Listo!\n")

print("Ejecutando algoritmos:...")
#run_linear()
run_stress()
print("Listo!\n")

print("Eliminando tests:...")
shutil.rmtree("in") # borra los tests aleatorios 
print("Listo!\n")

print("Creando grafico:...")
#graph_linear()
graph_stress()
print("Listo!\n")
