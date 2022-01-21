import os
__author__ = 'Juampisaez'
"""
Este archivo es para generar los 18 outputs de la T1-2021-1 de EDD.
Instrucciones:
Dentro de la carpeta de la T1-2021-1 deben estar este archivo python junto a la carpeta 'tests', 
la cúal contiene a las carpetas easy, medium y hard con los respectivos .png de inputs.
El test mas largo demora 3 segundos en mi pc.
"""

if not os.path.exists(f"output/easy/"):
		os.makedirs(f"output/easy/")
if not os.path.exists(f"output/medium/"):
		os.makedirs(f"output/medium/")
if not os.path.exists(f"output/hard/"):
		os.makedirs(f"output/hard/")
os.system(f"time ./potterphoto tests/easy/river.png output/easy/outriver.png  markers/easy/MarkerRiver.png  0.4")
os.system(f"time ./potterphoto tests/easy/plant.png  output/easy/outplant.png  markers/easy/MarkerPlant.png  0.2")
os.system(f"time ./potterphoto tests/easy/sans.png  output/easy/sans.png  markers/easy/sans_marker.png  0.3")
os.system(f"time ./potterphoto tests/easy/eyeLeash.png  output/easy/outEyeLeash.png  markers/easy/MarkerEyeLeash.png 0.3  1")



os.system(f"time ./potterphoto tests/medium/mona_lisa.png  output/medium/outMona.png  markers/medium/MarkerMonaLisa.png 0.3")
os.system(f"time ./potterphoto tests/medium/brain.png  output/medium/outBrain.png  markers/medium/MarkerBrain.png 0.18")
os.system(f"time ./potterphoto tests/medium/camera.png  output/medium/outCamera.png  markers/medium/markerCamera.png 0.37  1")

os.system(f"time ./potterphoto tests/hard/campus.png  output/hard/campus.png  markers/hard/campus_marker.png 0.9")
os.system(f"time ./potterphoto tests/hard/cara.png  output/hard/outCara.png  markers/hard/markercara.png  0.45")
os.system(f"time ./potterphoto tests/hard/nachito.PNG  output/hard/outNachito.png  markers/hard/MarkerNachitoV2.PNG  0.2")