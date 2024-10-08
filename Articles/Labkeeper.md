# Labkeeper

<img width="103" alt="image" src="https://github.com/user-attachments/assets/27dbe708-ffca-4abc-9d03-bd78339a18bf">

## Общее описание

Веб-приложение для вычислений. Пишешь питоноподобный код слева - справа получаешь результат вычислений, с картинками, графиками и версткой markdown,
можно экспортировать в pdf. Фактически представляет собой упрощенную и более легковесную версию матлаба, со
спецификой, заточенной под конкретные лаборатории (ОИВТ РАН, биотех МФТИ, общефиз МФТИ) на физтехе. Кроме того,
удобно для использования любым человеком из интернета, имеющем необходимость что-то быстро и наглядно посчитать.
В частности имеет упор на вычисление погрешности и визуализацию, а также на простоту использования.

## Постановка проблемы

* На физтехе многие делают лабы по общефизу в экселе - проверено опросом студентов БМ (особенно актуально среди первокурсников)
* Во многих лабораториях тоже использую эксель - есть конкретные примеры
* С другой стороны, во многих лабораториях используют пиратский матлаб, что вообще-то опасно для сохранности данных (из-за пиратских вирусов) и нарушает авторские права
* Внятного и простого онлайн-калькулятора для вычисления **погрешности** правильным способом не существует на данный момент
* [Прототип этого приложения](https://github.com/timattt/laboratory-calculations-optimizator) успешно показал свою популярность среди первого курса ФРТК

### Востребованность в интернете

Кроме пользователей с физтеха, есть люди из интернета, которым нужен данный продукт. Вот некоторая статистика запросов в месяц по данной проблемной области в яндексе
(по всем запросам нет никакого внятного решения проблемы, поставленной в запросе):

* *калькулятор погрешности* ```~2000```
* *оформление лабораторных* ```~3000```
* *как оформить лабораторную работу* ```~1000```

## Монетизация

* брать деньги за каждую 100ую компиляцию. Первые N бесплатные в день
* встроенная реклама на сайте

## Пользовательские потребности

Человек хочет:

* Зайти на сайт и сразу увидеть место, куда можно написать выражение и мгновенно получить результат
* Загружать какие-то сторонние файлы, чтобы потом их использовать в сложных функциях
* Генерировать красивые графики, не хуже, чем в matplotlib
* Получать красивый вывод своих вычислений в формате pdf, чтобы потом сразу можно было как отчет по лабе использовать
* Генерировать файлы другого формата с данными
* Сохранять свой код и загруженные файлы в проект в своей учетной записи
* Получать детальный вывод о том, как считается погрешность
* Писать код на языке, близком к питону, но с функционалом для ввода погрешности и простым построением графиков
* Пользователь хочет иметь возможность выбрать режим округления в своих вычислениях

## Пользовательские сценарии

* Пользователь заходит первый раз, без логина. Вводит код, нажимает кнопку компиляции, справа получает результат. Таких компиляций доступно N в день. После истечения требуется залогиниться. В этом варианте недоступна загрузка и выгрузка файлов, в том числе итогового pdf.
* При первом входе пользователь видит краткую, но информативную подсказку.
* Пользователь был не залогинен, что-то написал, а потом резко залогинился. Теперь ему создается дефолтный проект, куда переезжает написанный код.
* Пользователь залогинился. Теперь он может выбрать проект и редактировать его. По умолчанию будет дефолтный проект.
* Пользователь прикрепляет файл в программу, теперь его можно использовать в функциях-вычислениях.
* При нажатии на кпопку pdf - результат компиляции упаковывается в pdf и скачивается локально пользователю на пк.
* При свежем запуске приложения залогиненным пользователем будет открываться последний редактируемый проект (изначально дефолтный).
* Если залогинен, пользователь может обозреть список своих проектов, а также создавать, удалять, редактировать свои существующие проекты.

## Возможности языка

### Сегменты

Весь проект делится на несколько сегментов: md-текста (куда автоматически подставляются значения и вычислительного кода) и python-подобного кода.
На каждом сегменте можно поставить галку - отображать результат сегмента в итоговом pdf.

### md-сегмент

Здесь располагается полноценный markdown текст. Через выражения ```${variable}``` можно вставлять туда значения, посчитанные
в других блоках.

### Вычислительный сегмент

#### Оператор погрешности

При указании численного значения, можно указать оператор ```#```, который по смыслу соответствует символу плюс-минус и указвает сигму в нормальном распределении величины.

#### Вычисления

В остальном, язык по синтаксису копирует python. Также добавляется оператор возведения в степень ```^``` и символ экспоненты ```e```. Больше подробностей по языку [тут](https://github.com/timattt/TypeThree/blob/master/manual.pdf).

#### Режимы округления

* Без округления, никакие знаки после запятой не отбрасываются
* Фиксированное кол. знаков, округление до нужного знака
* Погрешность округляется до первой значащей цифры, а величина до этого же порядка погрешности

#### Вставка картинок

Если в буфере обмена лежала картинка и пользователь залогинен, то после ctrl+v она вольется в файлы проекта и будет отображаться в результирующем pdf

## Системные операции для бэкенда

### v1

* ```POST /sync/compile``` компилирует код без входящих файлов. Возвращает список сегментов для вставки в итоговый документ (md-код, выражения и тд). Но без файлов. Аутентификация не предполагается. Но на один ip не более N запросов.

### v2

* ```POST /project/default``` создает дефолтный проект и перемещает туда код
* ```GET /project/default``` возвращает полную информацию о дефолтном проекте
* ```GET /project/{id}``` возвращает полную информацию о проекте
* ```POST /project/{id}/file``` загружает файл в проект
* ```POST /project/{id}/compile``` скомпилировать проект - возврат такой же как и в v1, но теперь есть возможность возвращать файлы для вставки или загрузки.
* ```POST /project/{id}``` модифицировать проект в базе
* ```DELETE /project/{id}``` удалить проект из базы
