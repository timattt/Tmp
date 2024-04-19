# Семинар 9

## Docker-compose

* Docker-compose - инструмент для запуска группы контейнеров
* Шаблон в формате yaml:

```
version: '3'

services:
  container1:
    build: ./some/dir/with/dockerfile/.
    # или
    image: myimage:latest
    environment:
      MY_ENV_VAR: "MY_VALUE"
      MY_ENV_VAR_FROM_ENV_FILE: ${MY_ENV_VAR_FROM_ENV_FILE}
    ports:
      - "8080:8080"
    healthcheck:
      test: [ "CMD", "healthcheck.sh", "--connect" ]
      timeout: 1s
      retries: 100
    depends_on:
      container2:
        condition: service_healthy
    volumes:
      - ./local/path/in/project:/some/path/in/container
    networks:
      - mynetwork
```
* Можно указать через ${} ссылку на переменную окружения из рядом лежащего файла .env

### Параметры для запуска контейнеров

* ```build``` - позволяет задать путь к файлу Dockerfile, который нужно использовать для создания образа
* ```image``` - позволяет указать название образа, из которого создавать контейнер
* ```environment``` - позволяет указать переменные окружения в контейнере
* ```ports``` - позволяет пробросить порты
* ```healthcheck``` - указание действия для проверки работоспособности контейнера
* ```depends_on``` - позволяет указать зависимый контейнер, текущий контейнер не запустится, пока не будет запущен указанный
* ```volumes``` - указывает тома
* ```networks``` - указывает используемые сети

### Сети

* Внизу файла можно указать директиву с сетями

```
networks:
  mynetwork:
    internal: true
```
