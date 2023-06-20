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

MAX_N = int(2e3)
n_list = []
step = 200
nnn = 200
while(nnn <= MAX_N) : 
    n_list.append(nnn)
    # if(nnn == 10 * step): step *= 10
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


FILE_NAME = "tiempos.txt"

def random_test(n):
    test = ""
    M = (n * (n-1)) // 10
    K = random.randint(0, 299)
    ST = random.sample(range(1, n+1), 2)
    test += str(n) + " " + str(M) + " " + str(K) + " " + str(ST[0]) + " " + str(ST[1]) + "\n"

    # no toques esto que corre a las chapas
    test_cases = [f"{v} {w} {l}" for v, w, l in zip(random.choices(range(1, n+1), k=M+K), random.choices(range(1, n+1), k=M+K), random.choices(range(1, 1001), k=M+K))]
    test += "\n".join(test_cases) + '\n'

    return test

def create_tests_linear():
    # crear carpeta para ubicar los tests
    if not os.path.exists(os.path.join(parent_dir, "in")) : 
        os.mkdir(os.path.join(parent_dir, "in")) 

    for n in n_list:
        with open(f"in/test_{n}", 'w') as f:
            f.write(f"{REPS}\n") # Hace 100 test cases por n diferente
            for i in range(REPS):
                f.write(random_test(n))
                print(f"\t-> Listo el test {n}: {i+1}")
        print(f"Listo el test {n}!")

# compilar el codigo y correr los tests aleatorios
def run_linear():

    for imp in implementaciones:
        subprocess.run(["g++", "-o", imp.exe, imp.path])

    # crear archivo donde meter los tiempos
    open(FILE_NAME, "w").close()

    for n in n_list:
        with open(f"in/test_{n}", 'r') as f:
            input_data = f.read()

        tiempos = []
        for imp in implementaciones:
            start_time = time.time()
            subprocess.run(["./" + imp.exe], input=input_data, stdout=subprocess.PIPE, text=True)
            end_time = time.time()
            tiempos.append(end_time - start_time)
            imp.t.append((end_time - start_time)/REPS)

        # guardar tiempo promedio con 5 decimales
        with open(FILE_NAME, 'a') as f:
            f.write(f"{n} ") 
            for t in tiempos:
                f.write(f"{t/REPS:.5f} ")
            f.write("\n") 

        print(f"Ya corrio el test {n}")

    for imp in implementaciones:
        os.remove(imp.exe)

    shutil.rmtree("in") # borra los tests aleatorios 
    
        

def graph_linear(b):
    # Crear el gráfico

    if(b) :     
        with open(FILE_NAME) as f:
            for line in f:
                _, *t_vals = line.strip().split()
                i = 0
                for imp in implementaciones:
                    imp.t.append(float(t_vals[i]))
                    i += 1 

    for imp in implementaciones: 
        plt.plot(n_list, imp.t, label=imp.nombre, color=imp.color)
        plt.scatter(n_list, imp.t, color=imp.color)


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

n_list = [(kkk * (kkk-1)) // 1000 for kkk in n_list]

print("Creando grafico:...")
graph_linear(False)
print("Listo!\n")
