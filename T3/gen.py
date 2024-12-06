import os

__author__ = "Sebastian Breguel"
__email__ = "sebabreguel@uc.cl"

tests = ["easy", "normal", "hard"]
indices = ["0", "1", "2", "3"]

for i in range(3):
    for j in range(4):
        test = f"{tests[i]}_{indices[j]}"
        print(f"\n{test}\n")
        os.system(f"time ./pottergreedy A tests/{test}.txt output/P1/{test}.txt")

# ./pottergreedy A tests/easy_0.txt output/P1/easy_0.txt
# indices = ["0","1","2","3","4","5"]

# for indice in indices:
#     test = f"tests/P2/test_{indice}"
#     print(f"\n{test}\n")
#     os.system(f"time ./pottergreedy B {test}.txt output/{test}.txt")
