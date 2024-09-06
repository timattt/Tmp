# Семинар 1

*Синтаксис java, строки, массивы, Object*

## Компиляция и запуск java

* A.java
```
class A {
	public static void main(String[] args) {
		System.out.println("biba");
	}
}
```
* компиляция: ```javac A.java```
* получаем A.class
* запуск: ```java A```
* собираем jar: ```jar cfe A.jar A A.class```
* получаем A.jar
* запускаем jar: ```java -jar A.jar```

## Создание и структура maven-проекта

* maven автоматически собирает исполняемые java-файлы
* все делается в файле pom.xml
* maven-артефакт определяется group-id, artifact-id, version
* артефакт = jar-файл
* у maven есть репозитории: удаленные и локальные (.m2)
* один артефакт может зависеть от других. Для этого секция dependencies
* создание maven-проекта в idea:

![image](https://github.com/user-attachments/assets/5e721a70-4719-4a20-9813-70beda78bc8a)
