import os
import psutil

# Пример использования
current_path = "C:\\Users\\UserName\\Documents\\"
current_path2 = "C:/"
if os.path.ismount(current_path):
    print("Текущая папка является корневой папкой (диском).")
else:
    print("Текущая папка НЕ является корневой папкой (диском).")