def read_file_contents(file_path):
    number_arrays = []
    numbers = []
    try:
        with open(file_path, "r") as file:
            for line in file:
                if line.strip() == "":
                    number_arrays.append(numbers)
                    numbers = []
                else:
                    number = int(line.strip())
                    numbers.append(number)
            if numbers:
                number_arrays.append(numbers)
        return number_arrays
    except FileNotFoundError:
        print(f"File not found: {file_path}")
        return None
    except ValueError as e:
        print(f"Error parsing the file contents: {e}")
        return None

def find_sum_of_numbers(number_arrays):
    if not number_arrays:
        return None
    sum_of_number_arrays = []
    for numbers in number_arrays:
        sum_of_numbers = sum(numbers)
        sum_of_number_arrays.append(sum_of_numbers)
    return sum_of_number_arrays

def find_maximum_number(sum_of_number_arrays):
    if not sum_of_number_arrays:
        return None
    if not all(isinstance(i, int) for i in sum_of_number_arrays):
        raise ValueError("Input must be an array of integers.")
    return max(sum_of_number_arrays)

if __name__ == "__main__":
    input_file = "../input.txt"
    # input_file = "../test.txt"
    number_arrays = read_file_contents(input_file)
    if number_arrays is None:
        exit()
    sum_of_number_arrays = find_sum_of_numbers(number_arrays)
    if sum_of_number_arrays is None:
        exit()
    max_number = find_maximum_number(sum_of_number_arrays)
    if max_number is None:
        exit()
    print("Max number: ", max_number)

