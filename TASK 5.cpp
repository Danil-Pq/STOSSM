Появились проблемы при установке Selenium. Код написал и оставил места где надо поменять данные. Скачаю Selenium в ближайшие время.

import unittest
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
import time

class LoginFormTest(unittest.TestCase):

    def setUp(self):
        # Инициализация драйвера
        self.driver = webdriver.Chrome()
        self.driver.get("https://example.com/login")  # Замените на URL вашей формы логина

    def test_successful_login(self):
        driver = self.driver
        # Находим поля ввода и кнопку входа
        username_field = driver.find_element(By.ID, "username")  # Замените на реальный ID поля username
        password_field = driver.find_element(By.ID, "password")  # Замените на реальный ID поля password
        login_button = driver.find_element(By.ID, "login-btn")   # Замените на реальный ID кнопки входа

        # Вводим корректные данные
        username_field.send_keys("correct_username")
        password_field.send_keys("correct_password")
        login_button.click()

        # Проверяем, что вход выполнен успешно
        time.sleep(2)  # Даем время для загрузки страницы
        self.assertIn("Dashboard", driver.title)  # Замените на ожидаемый заголовок страницы после входа

    def test_invalid_login(self):
        driver = self.driver
        # Находим поля ввода и кнопку входа
        username_field = driver.find_element(By.ID, "username")
        password_field = driver.find_element(By.ID, "password")
        login_button = driver.find_element(By.ID, "login-btn")

        # Вводим некорректные данные
        username_field.send_keys("wrong_username")
        password_field.send_keys("wrong_password")
        login_button.click()

        # Проверяем сообщение об ошибке
        time.sleep(2)
        error_message = driver.find_element(By.ID, "error-message")  # Замените на реальный ID элемента с сообщением об ошибке
        self.assertIn("Invalid username or password", error_message.text)

    def test_empty_fields(self):
        driver = self.driver
        # Находим кнопку входа
        login_button = driver.find_element(By.ID, "login-btn")

        # Пытаемся войти без ввода данных
        login_button.click()

        # Проверяем сообщение об ошибке
        time.sleep(2)
        error_message = driver.find_element(By.ID, "error-message")
        self.assertIn("Please fill out this field", error_message.text)

    def tearDown(self):
        # Закрываем браузер после каждого теста
        self.driver.quit()

if __name__ == "__main__":
    unittest.main()
