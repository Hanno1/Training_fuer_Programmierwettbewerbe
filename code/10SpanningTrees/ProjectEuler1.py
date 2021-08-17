def euler_1(number):
    s = 0
    for i in range(1, number):
        if i % 3 == 0 or i % 5 == 0:
            s += i
    return s


print(euler_1(1000))
