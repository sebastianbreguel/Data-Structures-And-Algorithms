import numpy as np
from PIL import Image, ImageOps
import sys
import json
# Open the image form working directory

def get_image_array(direction):
    color_image = Image.open(direction)

    img = np.array( ImageOps.grayscale(color_image))    # Se crea matriz de tonos grises

    photo = []

    # Extendemos matriz en un arreglo
    for i in img:
        photo += list(i)

    return np.array(photo)

"""
Recibe los arreglos de pixeles de la pauta y del alumno
Retorna el porcentaje (de 0 a 100) de error. 
    0.0   -> Todo bueno
    100.0 -> Todo malo
"""
def compare_photos(pauta, alumno):
    cont_pix = 0                            # Pixeles distintos de 0 que calzan con la pauta
    cont_total = 0                          # Cantidad de pixeles de la pauta distintos de cero

    for i in range(len(pauta)):
        try:
            if pauta[i] != 0:                   # Si el pixel de la pauta es distinto de cero, se cuenta
                cont_total += 1

                if pauta[i] == alumno[i]:       # Si el pixel de la pauta es igual al del alumno, se suma un punto
                    cont_pix += 1
            elif pauta[i] != alumno[i]:         # Si el pixel de la pauta es 0, y el alumno tiene un pixel distinto de 0, se suma el pixel al total (por estar incorrecto) 
                cont_total += 1
        except:
            cont_total +=1
    return (1 - cont_pix / cont_total) * 100


def grade(correctness, testname):
    with open("./data.json", "r") as f:
        data = json.load(f)
    for t in data:
        if t["name"] == testname:
            limits = t["limits"]
    
    min_difference = limits["min-difference"]
    max_difference = limits["max-difference"]

    second_quartile = (max_difference + min_difference)/2
    first_quartile = (min_difference + second_quartile)/2
    third_quartile = (max_difference + second_quartile)/2

    if correctness <= min_difference:
        return "CORRECT", 1
    if correctness <= first_quartile:
        return "PARTIAL CORRECT", 0.7
    if correctness <= second_quartile:
        return "PARTIAL CORRECT", 0.5
    if correctness <= third_quartile:
        return "PARTIAL CORRECT", 0.25
    if correctness < max_difference:
        return "PARTIAL CORRECT", 0.1
    return "WRONG OUPUT", 0

def compare_raw(ground_truth, student_output):
    alumno = get_image_array(student_output)
    pauta = get_image_array(ground_truth)
    return compare_photos(pauta, alumno)

if __name__ == '__main__':
    
    if len(sys.argv) < 4:
        print("Modo de Uso: python3 corrector.py testname output_esperado output_obtenido")
        print("test name ha de estar en minusculas, pueden revisar los nombres en data.json")

    testname = sys.argv[1]
    pauta = sys.argv[2]
    alumno = sys.argv[3]

    obtained = compare_raw(pauta, alumno)
    print(f"Tu porcentaje de diferencia es {obtained}%")
    result, score = grade(obtained, testname)
    print(f"Tu calificacion para este test es | {result} | {round(score, 2)} |")