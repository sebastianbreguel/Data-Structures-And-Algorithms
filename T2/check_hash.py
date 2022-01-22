import sys

# Script que checkea si la solucion es correcta
def check_solve(test, obtained):
    map_dict = dict()
    if len(test) != len(obtained):
        return False
    for i in range(len(test)):
        a = obtained[i]
        b = test[i]
        if a in map_dict.keys():
            if map_dict[a] != b:
                return False
        else:
            map_dict[a] = b
    return True

# script to score solutions
def get_score(input_file, output_file, carpet, number):
    f_input = open(input_file, "r")
    f_output = open(output_file, "r")

    original_string = f_input.readline().strip().split(" ")[1]
    query_ammount = int(f_input.readline())

    passed = 0
    failed = []
    for query_id in range(query_ammount):
        # print(query_id)
        query = f_input.readline().strip().split(" ")[1]
        indices = f_output.readline().strip().split(" ")
        obtained_substring = original_string[int(indices[0]):int(indices[1])+1]
        result = check_solve(query, obtained_substring)
        if result:
            passed+=1
        else:
            failed.append(query_id+1)
    # print(f"Score: {passed}/{query_ammount} ==> {round(passed/query_ammount *100, 2)}%\n")
    # if(passed/query_ammount) != 1:
        # print(f"Lista Fallas (N° de linea en el output): {failed}")
    with open(f"reports/hash/{carpet}/report_{number}.txt", "w") as out:
        out.write(f"Score: {passed}/{query_ammount} ==> {round(passed/query_ammount *100, 2)}%\n")
        out.write(f"Lista Fallas (N° de linea en el output): {failed}")
    f_input.close()
    f_output.close()



if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Modo de uso python3 check_hash.py <archivo_consultas> <archivo_output>")
        sys.exit()
    input_file, output_file, carpet, number = sys.argv[1], sys.argv[2], sys.argv[3],  sys.argv[4]
    get_score(input_file, output_file, carpet, number)