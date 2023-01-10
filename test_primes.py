def is_prime(n):
    for i in range(2, n//2+1):
        if not (n%i):
            return 0
    return 1

nn=0
for i in range(2, 2500001):
    nn+=is_prime(i)

print(str(nn))
   
