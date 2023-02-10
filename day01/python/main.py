input_file = "../input.txt"
# input_file = "../test.txt"

# Open the file
with open(input_file, "r") as file:
    all_numbers = []
    numbers = []
    # Loop through each line in the file
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

print(all_numbers)

all_sums = []
for numbers in all_numbers:
    sum_of_numbers = sum(numbers)
    all_sums.append(sum_of_numbers)

print("Max number: ", max(all_sums))

