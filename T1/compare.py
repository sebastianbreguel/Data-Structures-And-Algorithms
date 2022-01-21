import os
__author__ = 'sebastianbreguel'


tests = ["easy/outEyeLeash.png","easy/outplant.png ","easy/sans.png ","easy/outriver.png","medium/outBrain.png","medium/outCamera.png","medium/outMona.png","hard/outNachito.png","hard/campus.png","hard/outCara.png"]
tests_name = ["eyeleash","plant","sans","rio","brain","camera","mona","nachito","campus","cara"]
test_gen = [
"time ./potterphoto tests/easy/eyeLeash.png  output/easy/outEyeLeash.png  markers/easy/MarkerEyeLeash.png 0.3  1",
"time ./potterphoto tests/easy/plant.png  output/easy/outplant.png  markers/easy/MarkerPlant.png  0.2",
"time ./potterphoto tests/easy/sans.png  output/easy/sans.png  markers/easy/sans_marker.png  0.3",
"time ./potterphoto tests/easy/river.png output/easy/outriver.png  markers/easy/MarkerRiver.png  0.4",
"time ./potterphoto tests/medium/brain.png  output/medium/outBrain.png  markers/medium/MarkerBrain.png 0.18",
"time ./potterphoto tests/medium/camera.png  output/medium/outCamera.png  markers/medium/markerCamera.png 0.37  1",
"time ./potterphoto tests/medium/mona_lisa.png  output/medium/outMona.png  markers/medium/MarkerMonaLisa.png 0.3",
"time ./potterphoto tests/hard/nachito.PNG  output/hard/outNachito.png  markers/hard/MarkerNachitoV2.PNG  0.2" ,
"time ./potterphoto tests/hard/campus.png  output/hard/campus.png  markers/hard/campus_marker.png 0.9",
"time ./potterphoto tests/hard/cara.png  output/hard/outCara.png  markers/hard/markercara.png  0.45",]

for number in range(len(tests_name)):
    test_name = tests_name[number]
    test_file = tests[number]
    gen_test = test_gen[number]
    print(test_name, test_file)
    print("\n")
    os.system(f"{gen_test}")
    print("\n")
    os.system(f"python3 corrector.py {test_name} solutions/{test_file} output/{test_file}")
    print("\n")