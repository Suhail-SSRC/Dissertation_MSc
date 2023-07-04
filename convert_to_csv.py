import re

s = open("test.txt")

for line in s:
    print(re.sub("\s+", ",", line.strip()))