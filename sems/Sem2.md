# Семинар 2

Лучшая статья [тут](https://github.com/synthMoza/understanding_git_rus/wiki/%D0%92%D1%81%D1%82%D1%83%D0%BF%D0%BB%D0%B5%D0%BD%D0%B8%D0%B5)

## Зачем нужны VCS?

* сотрудничество
* откаты
* отслеживание прогресса
* организация

## Как работают СКВ

* Нарисовать картинку с файлом, изменениями, рассказать про понятие коммита.
* Коммит - это фиксированное изменение, то есть изменения строк. Представляется в виде вершины.

## Виды СКВ

<img width="332" alt="image" src="https://github.com/timattt/Tmp/assets/25401699/647550f3-8bb4-40f8-a091-995c28d806db">

* SVN (centralized)
* Git (distributed)
* Сейчас распреденные становятся все популярнее

## Хранилища репозиториев

* github
* gitlab (opensource)
* bitbucket

## Создание репо

* создать папку ```mkdir myrepo```
* команда ```git init```

## Указание кредов

* ```git config user.email "email"```
* ```git config user.name "name"```
* креды для разных репо могут отличаться, поэтому глобал плохо юзать (но я все равно юзаю))
* на атп-гитлабе нужно делать коммиты от имени атп-гитлаба, иначе печаль

## общий флоу работы

<img width="336" alt="image" src="https://github.com/timattt/Tmp/assets/25401699/57de75d4-0758-41f3-9d94-330101204fda">

## Создание коммита

* ```git status```
* ```git add FILE```
* ```git diff```
* ```git commit -m "message"```

## Просмотр состояния репо

* ```git status```
* ```git log --all --decorate --oneline --graph```
  
## Отправка изменений в удаленный репозиторий

* ```git remote add origin URL```
* ```git push origin BRANCH```

## Ветки

* Ветка - указатель на коммит
* ```git fetch origin``` - выкачает все ветки из удаленного репо
* ```git branch``` - узнать текущую ветку или статус можно юзать
* создание ветки на текущем коммите: ```git branch NAME```
* переключение на ветку: ```git checkout```

## Слияние

* ```git merge TARGET_BRANCH``` - вливает в текущую ветку другую ветку
* ```git pull origin BRANCH``` = fetch + merge
* конфликты надо решать отдельным коммитом

## .gitignore

* полезный файл, в котором лежит то, что не надо замечать

## rebase

![image](https://github.com/timattt/Tmp/assets/25401699/7d263fb6-2571-4b1f-bd64-53d9ba4b24e0)
