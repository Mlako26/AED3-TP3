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


# Variables
REPS = 10

MAX_N = int(5e3) + 1
n_list = []
step = 10
nnn = 10
while(nnn < MAX_N) : 
    n_list.append(nnn)
    if(nnn == 10 * step): step *= 10
    nnn += step


class Implementacion:
    def __init__(self, nombre, color, exe, path):
        self.nombre = nombre
        self.color = color
        self.exe = exe
        self.path = path
        self.t = []


implementaciones = []
implementaciones.append(Implementacion("Heap", "red", "ej1", "../src/ej1.cpp"))
# implementaciones.append(Implementacion("FibonacciHeap", "blue", "ej1_fibonacci", "../src/ej1_fibonacci.cpp"))
implementaciones.append(Implementacion("Dense", "green", "ej1_dense", "../src/ej1_dense.cpp"))

for imp in implementaciones:
    subprocess.run(["g++", "-o", imp.exe, imp.path])


FILE_NAME = "tiempos.txt"
# crear carpeta para ubicar los tests
if not os.path.exists(os.path.join(parent_dir, "in")) : 
    os.mkdir(os.path.join(parent_dir, "in")) 

# crear archivo donde meter los tiempos
open(FILE_NAME, "w").close()

def random_test(n):
    test = ""
    M = (n * (n-1)) // 2
    K = random.randint(0, 299)
    ST = random.sample(range(1, n+1), 2)
    test += str(n) + " " + str(M) + " " + str(K) + " " + str(ST[0]) + " " + str(ST[1]) + "\n"

    # no toques esto que corre a las chapas
    test_cases = [f"{v} {w} {l}" for v, w, l in zip(random.choices(range(1, n+1), k=M+K), random.choices(range(1, n+1), k=M+K), random.choices(range(1, 1001), k=M+K))]
    test += "\n".join(test_cases) + '\n'

    return test

def create_tests_linear():
    for n in n_list:
        with open(f"in/test_{n}", 'w') as f:
            f.write(f"{REPS}\n") # Hace 100 test cases por n diferente
            for _ in range(REPS):
                f.write(random_test(n))
        print(f"Listo el test {n}")

# compilar el codigo y correr los tests aleatorios
def run_linear():
    for n in n_list:
        with open(f"in/test_{n}", 'r') as f:
            input_data = f.read()

        tiempos = []
        for imp in implementaciones:
            start_time = time.time()
            subprocess.run(["./" + imp.exe], input=input_data, stdout=subprocess.PIPE, text=True)
            end_time = time.time()
            tiempos.append(end_time - start_time)


        # guardar tiempo promedio con 5 decimales
        with open(FILE_NAME, 'a') as f:
            f.write(f"{n} ") 
            for t in tiempos:
                f.write(f"{t/REPS:.5f} ")
            f.write("\n") 

        print(f"Ya corrio el test {n}")
        

def graph_linear():
    # Leer los datos del archivo
    n = []

    with open(FILE_NAME) as f:
        for line in f:
            n_val, *t_vals = line.strip().split()
            n.append(int(n_val))
            i = 0
            for imp in implementaciones:
                imp.t.append(float(t_vals[i]))
                i += 1 


    # Crear el gráfico
    for imp in implementaciones: 
        plt.plot(n, imp.t, label=imp.nombre, color=imp.color)
        # plt.scatter(n, imp.t, color=imp.color)


    plt.title('Tiempo de Ejecución en Función de la Cantidad de Puntos')
    plt.xlabel('Cantidad de Puntos')
    plt.ylabel('Tiempo de Ejecución Promedio (s)')
    plt.legend()
    plt.grid(True)

    # Guardar el gráfico en un archivo
    plt.savefig('grafico.png')

print("Creando tests:...")
create_tests_linear()
print("Listo!\n")

print("Ejecutando algoritmos:...")
run_linear()
print("Listo!\n")

print("Eliminando tests:...")
shutil.rmtree("in") # borra los tests aleatorios 
for imp in implementaciones:
    os.remove(imp.exe)
print("Listo!\n")

print("Creando grafico:...")
graph_linear()
print("Listo!\n")
