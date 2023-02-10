def read_file_contents(file_path):
    all_numbers = []
    numbers = []
    # Loop through each line in the file
    with open(file_path, "r") as file:
        for line in file:
            # Check if the line is empty
            if line.strip() == "":
                all_numbers.append(numbers)
                numbers = []
            else:
                number = int(line.strip())
                numbers.append(number)

    # Append the last array of numbers to the list of arrays, if there is any
    if numbers:
        all_numbers.append(numbers)
    return all_numbers

def find_sum_of_numbers(all_numbers):
    all_sums = []
    for numbers in all_numbers:
        sum_of_numbers = sum(numbers)
        all_sums.append(sum_of_numbers)
    return all_sums

def find_maximum_number(all_sums):
    return max(all_sums)

if __name__ == "__main__":
    input_file = "../input.txt"
    # input_file = "../test.txt"
    all_numbers = read_file_contents(input_file)
    all_sums = find_sum_of_numbers(all_numbers)
    max_number = find_maximum_number(all_sums)
    print("Max number: ", max_number)

