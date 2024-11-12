# Тз микросервиса для отрисовки matplotlib на питоне

## Требования

* Докер-образ с переменными окружения:
    * макс памяти
    * макс потоков-воркеров
* Внутри сервер на django/flask/fastApi
* swagger-документация

## RestApi

### ```GET /api/v1/func/graph/plot```

Рисует график через ```plt.plot``` и возвращает файл картинки.
После выполнения операции файл не должен оставаться в контейнере, чтобы потрбление памяти не увеличивалось со временем.

Параметры:

* список кривых с параметрами:
    * список точек
    * тип кривой (scatter, plot)
    * цвет
    * подпись к кривой
* imageWidth, imageHeight
* title
* xAxisName
* yAxisName
* useGrid

### ```GET /api/v1/func/graph/hist```

Рисует гистограмму через ```plt.hist``` и возвращает файл картинки.
После выполнения операции файл не должен оставаться в контейнере, чтобы потрбление памяти не увеличивалось со временем.

Параметры:

* список кривых с параметрами:
    * список точек
    * цвет
    * подпись к кривой
* imageWidth, imageHeight
* title
* xAxisName
* yAxisName

### ```GET /api/v1/version```

Возвращает текущую версию приложения.

### ```GET /api/v1/health```

Возвращает состояние здоровья по стандарту k8s (health check)