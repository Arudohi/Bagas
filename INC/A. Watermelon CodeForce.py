# Input with validation
while True:
    try:
        w = int(input())
        if 1 <= w <= 100:
            break
        else:
            print("Please enter a number between 1 and 100.")
    except ValueError:
        print("Invalid input. Please enter a valid number.")

# Check conditions
if w > 2 and w % 2 == 0:
    print("YES")
else:
    print("NO")