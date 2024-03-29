# Семинар 3

## Rebase

* С помощью команды rebase вы можете взять все коммиты из одной ветки и в том же порядке применить их к другой ветке.
* Команда ```git rebase master``` возьмет коммиты текущей ветки и прицепит их поверх коммитов вертки master
* ВАЖНО! Не перемещайте коммиты, уже отправленные в публичный репозиторий. Потому что это изменяет коммиты веток, которые могут использовать другие пользователи.

## Cherry pick

* Можно вытащить любой коммит и добавить поверх своей ветки ```git cherry-pick COMMIT_ID```

## Squash

* Коммиты можно сживать в один: ```git rebase -i HEAD~6```. Здесь i означает интерактивный режим.

## Полезные команды

### diff

Позволяет сравнивать построчно два файла

## Процессы

### ps или htop

Показывает список активных процессов. Отсюда можно узнать pid процесса.

### kill

Убивает процесс. Принимает на вход пид процесса.

### time

Позволяет замерять время работы процесса. В аргументе достаточно указать команду, время которой будет замеряться.

## Пользователи

### useradd 

Добавляет нового пользователя

## Сеть

### ip, ipconfig

Позволяет увидеть основные настройки сети. Ip адрес, например

### ping

Пингует что-нибудь

# Паттерны

* порождающие
* структурные
* поведенческие

## Singleton

* Класс, который имеет ровно один свой объект
* Есть статиский глобальный метод instance()
* Есть статическое поле объекта
* Есть публичных конструкторов нет
* Нужен для глобальной точки доступа к чему-нибудь. Например, менеджер ресурсов в геймдеве
* Минус в многопоточности и god-object

## Factory method

<img width="433" alt="image" src="https://github.com/timattt/Tmp/assets/25401699/6cfad7ab-7a97-4f8f-a1fd-d8027d2abce1">
<img width="779" alt="image" src="https://github.com/timattt/Tmp/assets/25401699/d95478b0-f4fc-4d07-b2d5-f965bcd4aebb">

## Abstract factory

<img width="864" alt="image" src="https://github.com/timattt/Tmp/assets/25401699/8b48f4f6-a553-4d52-88f2-d11faf784725">
<img width="771" alt="image" src="https://github.com/timattt/Tmp/assets/25401699/ec75c45b-4ecc-4db7-9218-65b1f09a796b">

## Builder

<img width="832" alt="image" src="https://github.com/timattt/Tmp/assets/25401699/5f73f377-aae6-4004-92c6-eeb8260c8dbc">


