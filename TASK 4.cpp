import os
import time
import unittest
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC

class HomeworkDownloadTest(unittest.TestCase):

    def setUp(self):
        # Инициализация драйвера
        self.driver = webdriver.Chrome()  # Убедитесь, что ChromeDriver установлен и добавлен в PATH
        self.driver.get("https://journal.top-academy.ru")  # Переход на учебную платформу
        self.download_dir = os.path.join(os.getcwd(), "downloads")  # Папка для скачивания файлов
        if not os.path.exists(self.download_dir):
            os.makedirs(self.download_dir)

        # Настройка Chrome для скачивания файлов в указанную папку
        chrome_options = webdriver.ChromeOptions()
        prefs = {"download.default_directory": self.download_dir}
        chrome_options.add_experimental_option("prefs", prefs)
        self.driver = webdriver.Chrome(options=chrome_options)

    def test_download_homework(self):
        driver = self.driver

        # Авторизация на платформе
        try:
            # Находим поля для ввода логина и пароля
            username_field = driver.find_element(By.ID, "username")  # Замените на реальный ID поля логина
            password_field = driver.find_element(By.ID, "password")  # Замените на реальный ID поля пароля
            login_button = driver.find_element(By.ID, "login-btn")   # Замените на реальный ID кнопки входа

            # Вводим учетные данные
            username_field.send_keys("your_username")  # Замените на ваш логин
            password_field.send_keys("your_password")  # Замените на ваш пароль
            login_button.click()

            # Ожидаем загрузки страницы после авторизации
            WebDriverWait(driver, 10).until(
                EC.presence_of_element_located((By.ID, "homework-section"))  # Замените на реальный ID раздела с заданиями
            )
        except Exception as e:
            self.fail(f"Ошибка авторизации: {e}")

        # Переход к разделу с домашними заданиями
        try:
            homework_section = driver.find_element(By.ID, "homework-section")
            homework_section.click()
        except Exception as e:
            self.fail(f"Ошибка при переходе в раздел заданий: {e}")

        # Поиск последнего задания
        try:
            assignments = driver.find_elements(By.CLASS_NAME, "assignment-item")  # Замените на реальный класс задания
            if not assignments:
                self.fail("Нет доступных заданий для скачивания")

            last_assignment = assignments[-1]  # Берем последнее задание
            download_button = last_assignment.find_element(By.CLASS_NAME, "download-btn")  # Замените на реальный класс кнопки скачивания
            download_button.click()

            # Ожидаем завершения скачивания
            time.sleep(5)  # Даем время для скачивания файла
        except Exception as e:
            self.fail(f"Ошибка при скачивании задания: {e}")

        # Проверка, что файл скачан
        downloaded_files = os.listdir(self.download_dir)
        if not downloaded_files:
            self.fail("Файл не был скачан")
        else:
            print(f"Скачанные файлы: {downloaded_files}")

    def tearDown(self):
        # Закрываем браузер после завершения теста
        self.driver.quit()

        # Очистка папки с загрузками
        for file in os.listdir(self.download_dir):
            file_path = os.path.join(self.download_dir, file)
            os.remove(file_path)
        os.rmdir(self.download_dir)

if __name__ == "__main__":
    unittest.main()
