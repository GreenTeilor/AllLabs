from collections import Counter

import matplotlib.pyplot as plt
from scipy.integrate import simps
import serial.tools.list_ports
import seaborn as sns

ports = serial.tools.list_ports.comports()
available_ports = [port.device for port in ports]

print("Доступные порты:", available_ports)

# Настройка соединения
ser = serial.Serial('COM9', 115200, timeout=1)

# Массив для сохранения чисел
numbers = []

try:
    while True:
        if ser.in_waiting > 0:
            readData = ser.readline().decode('utf-8').strip()
            data = ord(readData)

            if 1 <= data <= 6:
                numbers.append(data)
                print(f"Получено: {data}, Текущий массив: {numbers}")

                if len(numbers) > 1:
                    ax = sns.kdeplot(numbers, fill=True)
                    plt.xlabel('Значения')
                    plt.ylabel('Плотность вероятности')
                    plt.title('График плотности вероятности распределения')
                    plt.show()
except KeyboardInterrupt:
    print("\nПрограмма завершена.")
finally:
    ser.close()
    plt.ioff()
