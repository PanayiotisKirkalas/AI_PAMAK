import random

def read_cnf_from_file(file_path):
    with open(file_path, 'r') as file:
        cnf = [list(map(int, line.split())) for line in file.readlines()]
    return cnf

def write_solution_to_file(solution, file_path):
    with open(file_path, 'w') as file:
        if solution:
            file.write(" ".join(str(int(variable)) for variable in solution))
        else:
            file.write("No solution found.")

def walksat(cnf, max_flips, max_tries, probability):
    def satisfied(clause, assignment):
        for literal in clause:
            if literal > 0 and assignment[abs(literal)] or \
               literal < 0 and not assignment[abs(literal)]:
                return True
        return False

    for _ in range(max_tries):
        assignment = [False] + [random.choice([True, False]) for _ in range(len(cnf[0]))]

        for _ in range(max_flips):
            unsatisfied_clauses = [clause for clause in cnf if not satisfied(clause, assignment)]

            if not unsatisfied_clauses:
                return assignment[1:]

            random_clause = random.choice(unsatisfied_clauses)
            if random.random() < probability:
                flip_variable = random.choice(random_clause)
            else:
                flip_variable = max(set(random_clause), key=lambda x: sum(c.count(x) for c in unsatisfied_clauses))

            assignment[abs(flip_variable)] = not assignment[abs(flip_variable)]

    return None

# Παράδειγμα εκτέλεσης με αρχεία
input_file_path = "p10_1.txt"
output_file_path = "output1.txt"

cnf_formula = read_cnf_from_file(input_file_path)
result = walksat(cnf_formula, max_flips=1000, max_tries=100, probability=0.5)

write_solution_to_file(result, output_file_path)
