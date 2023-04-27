import subprocess
import re
import statistics

command = "./optimize"

num_runs = 100

execution_times = []

for i in range(num_runs):
    output = subprocess.check_output(command, shell=True)
    execution_time = float(re.findall(r"Execution time: (\d+\.\d+) seconds", output.decode())[0])
    execution_times.append(execution_time)

avg_time = statistics.mean(execution_times)
variance = statistics.variance(execution_times)
std_dev  = statistics.stdev(execution_times)
min_time = min(execution_times)
max_time = max(execution_times)

print("Математическое ожидание: {:.6f}".format(avg_time))
print("Мин значение {:.6f}".format(min_time))
print("Макс значение {:.6f}".format(max_time))
print("Погрешность: {:.6f}%".format(std_dev / avg_time * 100))

