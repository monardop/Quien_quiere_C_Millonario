from random import randint

with open("config.txt", "w") as f:
    f.write(f"Rounds: {randint(4, 7)}\n")
    f.write(f"Tiempo: {randint(5, 30)}\n")
