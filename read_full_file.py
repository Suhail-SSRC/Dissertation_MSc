def copy_lines_with_phrase(input_file, output_file, phrase):
    with open(input_file, 'r') as file:
        lines = file.readlines()

    matching_lines = [line for line in lines if phrase in line]

    with open(output_file, 'a') as file:
        file.writelines(matching_lines)

# Usage example
input_file = 'finaltopnode.csv'  # Specify the input file path
output_file = 'output.txt'  # Specify the output file path
phrase = '2778'  # Specify the specific phrase to search for

copy_lines_with_phrase(input_file, output_file, phrase)
