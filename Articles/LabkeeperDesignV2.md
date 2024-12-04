# Техническое задание по дизайну Labkeeper v2

## Нововведения

### Возможность двигать сегменты с кодом

На каждом сегменте появляются что-то, за что можно потянуть и сегмент подвинется

### Локализация

Где-то в хедере сверху нужны кнопки, которые будут менять язык (русский и английский)

### Выделение ошибок

Если на строке обраховалась ошибка, то строку надо как-то подсветить красным

### Файловый менеджер

Слева должен появиться файловый менеджер. Через него можно добавлять файлы и картинки к проекту.
Важно, что менеджер отображается только залогиненным пользователям.
Референс такой:

![image](https://github.com/user-attachments/assets/824b244e-ad13-4519-a6a8-16146fbf1167)

И такой:

![image](https://github.com/user-attachments/assets/3aebed3f-44be-41e1-aad7-bf8cb9271573)

Нужны такие возможности:

* Возможность свернуть менеджер
* кнопка загрузить файл
* Папки не предусмотрены - просто список файлов
* рядом с каждым файлом кнопка удалить и переименовать
* Кнопка обновить список файлов
* Также некоторые файлы могут быть автосгенерированными - их нужно как-то особенным образом выделить
* Если пользователь перетягивает файл с рабочего стола - нужно, чтобы зона, где файл надо отпустить (то есть сам менеджер) обозначался как-нибудь. Что-то такое:

![image](https://github.com/user-attachments/assets/c3c7c0e3-c02c-4b09-8ae7-2fc16f2a1a8d)