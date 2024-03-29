# Эмбединги

## Без нейросетей

* смысл слова определеяется контекстом
* идем окном
* строим матрицу встречаемости слов, iое слово с jым
* можно понизить размерность
* еще можно сингулярно разложить. Тогда строки первой матрицы и строки последней - искомые эмбединги

## С нейросетями

* обучаем нейросеть - на вход onehot слово - на выходе тоже onehot слово. Фактически это задача классификации 

![image](https://github.com/timattt/Tmp/assets/25401699/3ed4276a-1107-4b4f-bcac-839f275cdd8d)

# seq2seq

## Encoder-decoder

![image](https://github.com/timattt/Tmp/assets/25401699/a1f2a5fc-8fbe-438a-8713-65aad2eedeff)

* контекст - эмбединг всего предложения, который передается от энкодера декодеру
* в конце последовательности энкодера - токен конца строки
* в начальном состоянии декодера на входе - токен начала строки
* обучение происзодит путем - teacher-forcing - в декодере подаем правильное значение вместо предсказанного

# BLEU

![image](https://github.com/timattt/Tmp/assets/25401699/7a182c6c-c7ed-4800-a321-b4601c0c6e95)

# attention

* энкодер-декобер забывает о начальных токенах
* аттеншн может быть любой функцией (напр, скалярным произведением)

![image](https://github.com/timattt/Tmp/assets/25401699/8bb9f4d2-365d-4d2b-941a-0729c6b2c2fb)

## self-attention

![image](https://github.com/timattt/Tmp/assets/25401699/1f49b084-3fb6-4ed6-a071-a090777fb928)

# Multi-head attention

* если аттентионов несколько - то каждый будет согласовывать свою информацию - род, число и тд
* три матрицы - query, key, value. $$Q = W_Q X$$, $$K = W_K X$$, $$V = W_V X$$

![image](https://github.com/timattt/Tmp/assets/25401699/44c30482-1b6e-41e3-9213-1fc674facdd8)

# positional encoding

![image](https://github.com/timattt/Tmp/assets/25401699/1d504e8c-d3cc-4d16-b39b-25b888bc4e87)

![image](https://github.com/timattt/Tmp/assets/25401699/9194640f-b3d3-40cd-9ab5-c0422ab1b77a)

* благодаря матрице поворота - можно легко получить линейное преобращование между этими векторами
* теперь на вход мы будем подавать сумму этих эмбедингов (позиции и слова)

# Batch normalization

* хотим избежать ковариационного сдвига
* сначала нормируемся так, чтобы матож ноль и дисперсия один
* потом делаем линейное преобразование, параметры которого есть параметры сети
* проблема - сложно использовать с последовательностями и маленькими данными
* паралелить сложно

# Layer normalization

* нормируем на одном слое - по одному предложению (батч размера 1)

# Mask

* чтобы декодер учитывал только те слова, которые он уже высрал - будем использовать маску в аттеншион

# Трансформер

![image](https://github.com/timattt/Tmp/assets/25401699/861807c6-b039-45e0-8e2b-14a948f8115b)

# BERT

* берем трансформер - выкидываем декодер
* вводим токен CLS, который собирает всю информацию, полезной при классификации
* используем маски
* будем предсказывать слово, которое пропущено
* можем отвечать на вопрос - идут ли два предложения друг за другом
