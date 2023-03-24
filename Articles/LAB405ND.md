# Лаба

## ARINC

![image](https://user-images.githubusercontent.com/25401699/227460165-dadb466c-989a-42c6-b613-797be6c07ef8.png)

* st - импульс старта слова.
* JB2 - ce_tact - импульс на каждый бит слова.
* JC1 - en_tx - меандр, который покрывает все слово - нужен для синхронизации.
* JB8 - SDAT - данные 1 и 0.
* JB9 - QM - модулирующий сигнал для TXD1 и TXD0.
* JB1, JB7 - TXD1, TXD0 - сигналы для 1 и 0.
* T_adrdat - меандр для адреса и данных.
* JB3 - T_cp - меандр для контрольного бита.
* JB4 - FT_cp - триггер контроля четности - 0 или 1 в зависимости от четности кол единиц.

## Скорость

ARINC слово - 32 бита.
VEL - скорость передачи к кбит\сек.

## Схема

* BTN0 - сбрасывает принятые данные
* BTN3 - инвертирует один бит

### ADR_DAT_BL

Модуль источника скорости адреса и данных.
Здесь мы задаем данные, которые хотим отправить - как константы. И выходную скорость.
На вход кнопка - инвертирует один бит данных.

### AR_TXD

Основная часть схемы - на выходе сигнал ARINC.

### AR_MUX

Мульиплексор для данных дисплея.
Дисплей отображает данные, которые мы хотим отправить.

### AR_RXD

Приемник ARINC сигнала для тестирования

### BUF32

Модуль регистра записи принятых данных.

### Ответы на КВ

1. ```T = 1/VEL```.
2. Нельзя, так как нужно каждый такт проверять входные сигналы TXD1 и TXD0.
3. Чем больше скорость передачи, тем больше нужна тактовая частота.
4. да, ведь мы знаем сколько бит всего в одном слове.