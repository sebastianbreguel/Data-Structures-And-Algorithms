import os

__author__ = "Sebastian Breguel"
__email__ = "sebabreguel@uc.cl"

tests = ["easy", "normal", "hard"]
indices = ["0", "1", "2", "3"]

for i in range(3):
    for j in range(4):
        test = f"{tests[i]}_{indices[j]}"
        print(f"\n{test}\n")
        os.system(f"python3 checkSteinerMST.py tests/{test}.txt output/P1/{test}.txt")

# indices = ["0","1","2","3","4","5"]

# for indice in indices:
#     test = f"P2/test_{indice}"
#     print(f"\n{test}\n")
#     os.system(f"python3 lightsCheck.py {test}.txt output/{test}.txt")
