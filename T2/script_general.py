import os

dificulty = ["easy", "medium", "hard"]
tests = ["0","1","2","3","4"]
for dificult in dificulty:
    for test in tests:
        string = f"tests/hashing/{dificult}/test_{test}.txt"
        out = f"output/hashing/{dificult}/test_{test}.txt"
        carpet =  f"{dificult}"
        # print(f"\n{dificult}: {test}\n")
        os.system(f" ./pottermagic A {string} {out}")
        os.system(f"python3 check_hash.py {string} {out} {dificult} {test}")



back = ["easy/test_0.txt","easy/test_1.txt","easy/test_2.txt","easy/test_3.txt",
 "medium/test_0.txt","medium/test_1.txt","medium/test_2.txt",
  "hard/test_0.txt","hard/test_1.txt","hard/test_2.txt"]
output = ["easy/test_0.txt","easy/test_1.txt","easy/test_2.txt","easy/test_3.txt",
 "medium/test_0.txt","medium/test_1.txt","medium/test_2.txt",
  "hard/test_0.txt","hard/test_1.txt","hard/test_2.txt"]

for num in range(len(back)):
    test = back[num]
    out = output[num]
    print(f"\n{test}\n")
    os.system(f"time ./pottermagic B tests/backtracking/tests/{test} output/backtracking/{test}")
    os.system(f" python3 check_backtracking.py output/backtracking/{test}")
    # break

