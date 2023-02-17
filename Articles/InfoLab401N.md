# Лаба 401 по инфокому

## 5.1

(VCB4RE 2)

У нас тут счетчик.
Входы:

* clk - часы, каждый такт что-то происходит
* ce - само значение счетчика
* R - сброс регистра

Выходы:
* Q - само число
* TC - переполнение
* CEO - необходимость переноса

### Тест

Подадим 10 тактов единичек на ce.
Потом подождем. Теперь подадим сигнал сброса.
Таким образом счетчик дошел до значения 9, остановился и потом сбросился.

![VCB4RE](https://user-images.githubusercontent.com/25401699/218034190-987d6db6-802a-42e4-83e9-e2097b129ad7.PNG)

## 5.2

(VCD4RE 3)

Тут все аналогично предыдущему варианту, но сброс автоматически происходит при необходимости переноса (причем на значении 9).
Так что будем подавать 10 тактов единичек и увидим, что счетчик вырос до 9, а потом упал до 0.

![VCD4RE](https://user-images.githubusercontent.com/25401699/218034240-b6925674-58aa-4ece-87a8-8f6cd9dd0d69.PNG)

## 5.3

(VCBDmSE)

Входы:

* clk - часы, каждый такт что-то происходит
* ce - само значение счетчика
* S - установка регистра в макс значение

### Тест

У нас счетчик стартует с макс значения и уменьшается. Если он доходит до нуля, то возвращается обратно в макс.
Если подать s, то он будет все время макс.

![image](https://user-images.githubusercontent.com/25401699/218038882-47c0dda9-db73-4500-b261-d916ce5a7dbf.png)

## 5.4

(VCBmCLED 1)

Число можно подать на вход, используя пин L.
Это счетчик, который умеет прибавлять единицу или вычитать ее к числу, которое подается на вход или которое было до этого.
Если происходит переполнение или ноль, то он подаст сигнал.

### Тест

Мы стартуем с нуля, увеличиваем число. Потом в какой-то момент начинаем считать вниз. Видим, что происходит переполнение и сброс.

![image](https://user-images.githubusercontent.com/25401699/218042657-90911aca-5157-4456-b1dd-c2c4f3eedef1.png)

## 5.5

(VCJmRE 4)

Это какой-то странный счетчик.
Смысл сводится к тому, что он прибавляет или убавляет степени двойки.

![image](https://user-images.githubusercontent.com/25401699/218045191-544a21b3-2c63-4740-b8ba-2eba0a6e71de.png)

## 5.6

(VCGrey4RE)

Этот счетчик выдает [коды грея](http://e-maxx.ru/algo/gray_code).

![image](https://user-images.githubusercontent.com/25401699/218048150-1e0a856e-d2fb-4e64-bdd3-27d421567838.png)

# Контрольные вопросы

## 7.1

T-триггер — это счетный триггер. У данного триггера имеется только один вход. Принцип работы T-триггера заключается в следующем. После поступления на вход T импульса, состояние триггера меняется на прямо противоположное.

* CB2CE: 2 Т-триггера FTCE 
* VCBmCLED: 2 т-триггера FTCLEX 
* VCB4RE: 4 триггера CB2CE
* VCD4RE: 4 триггера CB2CE
* VCJ4RE: 4 D-триггера

## 7.2

Частота синхронизации: 1/Tclk = 50 МГц

## 7.3

$$F_{max} = \frac{1}{(m-1) * T_{1}+T_{2}}$$
где m — число разрядов; Т1 — задержка переключения одного триггера; Т2 — время срабатывания внешнего элемента или считывающей схемы.

## 7.4

Нужно добавить обратную связь. 10=8+2=0010+1000
То есть из второго и последнего счетчика надо вывести провода в элемент И и подвести ко входу очистки.

## 7.5

Нужно добавить конденсатор.

![image](https://user-images.githubusercontent.com/25401699/219596942-9aee80f5-f98f-4667-ab64-71010ff0f5f3.png)

![image](https://user-images.githubusercontent.com/25401699/219596998-32913284-6f94-4386-b9b5-fd3af51235bc.png)

## 7.6

![image](https://user-images.githubusercontent.com/25401699/219599403-853f229c-664a-4d33-9d2d-3d96aff05f2d.png)