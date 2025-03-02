from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
import time

# Настройка драйвера
driver = webdriver.Chrome()  # Убедитесь, что у вас установлен ChromeDriver

# Тест успешного входа
def test_successful_login():
    try:
        driver.get("https://example.com/login")  # Замените на URL вашей формы входа
        driver.find_element(By.ID, "username").send_keys("correct_username")
        driver.find_element(By.ID, "password").send_keys("correct_password")
        driver.find_element(By.ID, "login_button").click()
        time.sleep(2)  # Ожидание загрузки страницы
        assert "Главная страница" in driver.title  # Проверка успешного входа
        print("Тест успешного входа пройден")
    except Exception as e:
        print(f"Ошибка в тесте успешного входа: {e}")

# Тест входа с неверным паролем
def test_invalid_password():
    try:
        driver.get("https://example.com/login")
        driver.find_element(By.ID, "username").send_keys("correct_username")
        driver.find_element(By.ID, "password").send_keys("wrong_password")
        driver.find_element(By.ID, "login_button").click()
        time.sleep(2)
        error_message = driver.find_element(By.ID, "error_message").text
        assert "Неверный логин или пароль" in error_message
        print("Тест входа с неверным паролем пройден")
    except Exception as e:
        print(f"Ошибка в тесте входа с неверным паролем: {e}")

# Тест с пустыми полями
def test_empty_fields():
    try:
        driver.get("https://example.com/login")
        driver.find_element(By.ID, "login_button").click()
        time.sleep(2)
        error_message = driver.find_element(By.ID, "error_message").text
        assert "Заполните все поля" in error_message
        print("Тест с пустыми полями пройден")
    except Exception as e:
        print(f"Ошибка в тесте с пустыми полями: {e}")

# Запуск тестов
try:
    test_successful_login()
    test_invalid_password()
    test_empty_fields()
finally:
    driver.quit()  # Закрытие браузера
