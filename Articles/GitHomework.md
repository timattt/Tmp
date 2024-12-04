# Task 1

![image](https://github.com/user-attachments/assets/0a59b110-3a05-4dd1-8b36-1b924d1dbdba)

# Task 2

<img width="1199" alt="image" src="https://github.com/user-attachments/assets/6c82cb43-6417-4c06-8ad5-501ebba574f3">

# Task 3

![image](https://github.com/user-attachments/assets/6d5c86d9-1afe-46ae-aded-613b68dbf2f1)

# Task 4

## commit-on-wrong-branch

![image](https://github.com/user-attachments/assets/4cd4941a-2ea0-42bd-b9d2-cdb265dba9e5)

```
git checkout master
git branch remote 7958567
git rebase quickfix
git checkout remote
git merge quickfix
```

![image](https://github.com/user-attachments/assets/020e7698-43fd-4d85-9204-c86ab8df1aaa)

## commit-on-wrong-branch 2

![image](https://github.com/user-attachments/assets/3c57543a-cbf3-4179-92ad-48721a73b841)

```
git checkout new-feature
git cherry-pick e4c4dfe
git add .
git commit -m "fix merge conflict"
git checkout master
git reset --hard 414875a
```

![image](https://github.com/user-attachments/assets/2938e755-26b7-4a4c-a140-3becfa9a2272)

## reverted-merge

![image](https://github.com/user-attachments/assets/4d5e9bd1-4dbc-4e28-beff-ec0b3a29867e)

```
git add .
git commit -m "reverting"
git log --all --decorate --oneline --graph
git checkout integrate-library-1.2.4
git add .
git commit -m "lib fix"
git checkout master
git merge integrate-library-1.2.4
git add .
git commit -m "resolve merge"
```

![image](https://github.com/user-attachments/assets/2ffcaa0a-f5e7-44f8-bf12-b71671c450e4)

## Save my commit

![image](https://github.com/user-attachments/assets/3f1cb6c6-21d1-40a8-9739-803b4aef4162)

```
git reflog
git checkout c327d30
git checkout eebf7b3
git branch -D master
git checkout -b master
```

![image](https://github.com/user-attachments/assets/29eabc02-a84e-4c40-a938-8efe65f0155f)

## Detached head state

![image](https://github.com/user-attachments/assets/a58d77e2-cc3c-4d40-b3fd-6208ce4b11bd)

```
git checkout master
```

![image](https://github.com/user-attachments/assets/cd7b8604-60e8-4073-949a-ca97b742ddef)

# Task 5

## git-attributes 

Потестили смену концов строк в файле атрибутов

![image](https://github.com/user-attachments/assets/a3891b21-450f-4ce8-ba68-4275e3ae7b52)

Добавили настроки в файл конфига в репе и а файл атрибутов

![image](https://github.com/user-attachments/assets/15f76278-85b9-41ea-a3e3-8fcdb75a47b5)

Теперь виден диф для картинки

![image](https://github.com/user-attachments/assets/7f9ba6f3-741d-4cee-8c16-bf3afc62a10e)

## bisect

Используем бин поиск для нахождения плохого коммита

![image](https://github.com/user-attachments/assets/fd1138f5-3fc2-4214-9e3c-6a2172899fea)

Нашли

![image](https://github.com/user-attachments/assets/5d06004a-f4d3-4567-bd7f-54fd35fe3c49)

## bad commit

ищем коммит

![image](https://github.com/user-attachments/assets/8613f906-c6ed-4974-ab60-a48ea1efd79c)

нашли коммит и откатили - файл пропал

![image](https://github.com/user-attachments/assets/043c0074-bc82-4c23-b591-8e0e732e90ee)

## pre-push

Скрипт выполняется при каждом пуше в мастер. В другие ветки - ок, так как exitcode = 0

![image](https://github.com/user-attachments/assets/93f0fb62-504b-4f11-a78a-0049ea69b7a0)

## investigation

исследовали блобы в репозитории

![image](https://github.com/user-attachments/assets/e486534f-0727-430f-9322-180d2e7e4576)

## merge driver

Подключили драйвер

![image](https://github.com/user-attachments/assets/48453dbb-cf2c-4e92-81a5-9f3302f1c3af)

атрибуты настроили

![image](https://github.com/user-attachments/assets/5c0eeed3-2455-47d5-8aeb-a03c054200fa)

авто мердж

![image](https://github.com/user-attachments/assets/e2239d41-2678-40ab-a93c-23f1cbd8b3b5)

## Rebase Exec

ребейзим

![image](https://github.com/user-attachments/assets/78aee194-8280-4820-9f99-4a7fac017070)

![image](https://github.com/user-attachments/assets/87f18679-26a1-4152-aec8-ffb6cbd64a1d)

![image](https://github.com/user-attachments/assets/f572df22-d4b2-41f2-9510-27a8ca711e30)

![image](https://github.com/user-attachments/assets/82850c85-b71f-4f8a-b946-d36b206191eb)

![image](https://github.com/user-attachments/assets/6d010dec-ff6d-4be9-a201-844db28fc3f2)

