# Read number of test cases
t = int(input())

# Process each test case
results = []
for _ in range(t):
    n = int(input())
    results.append((n // 2) + (n % 2))

# Print results
print('\n'.join(map(str, results)))