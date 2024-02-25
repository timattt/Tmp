# Семинар 4

## Паттерн прототип

* Прототип - порождающий паттерн проектирования, который позволяет копировать объекты, не вдаваясь в их реализацию
* Фактически имеется метод Clonable с функцией clone внутри
* Прототип не опирается на наследование, но ему нужна сложная операция инициализации. Фабричный метод, наоборот, построен на наследовании, но не требует сложной инициализации.

## Система сборки maven

### Лайфхак по установке пиратской версии idea

### Как мы можем запускать программы на java

* Вот есть JVM, там есть **javac**, **java**
* Имеем файл **A.java**
```
public class A {
    public static void main(String[] args) {
        System.out.println("Hello World!");
    }
}
```
* Сначала компилируем в байткод ```javac A.java```
* Теперь запускаем ```java A```

### Системы сборки автоматизируют этот процесс

* Есть сборочный файл pom.xml - он описывает конфигурации сборки каждого модуля
* артефакт — это любая библиотека, хранящаяся в репозитории
* Зависимости — это те библиотеки, которые непосредственно используются в вашем проекте для компиляции кода или его тестирования
* Плагины же используются самим Maven'ом при сборке проекта или для каких-то других целей
* Архетип — это некая стандартная компоновка файлов и каталогов в проектах различного рода (веб, swing-проекты и прочие), например в Spring Boot:

<img width="311" alt="image" src="https://github.com/timattt/Tmp/assets/25401699/435ffbb1-e9af-43e1-9276-54fa874a3d35">

* m2 - локальный репозиторий с зависимостями, скачанными на ПК
* Полезные переменные окружения: ```M2_HOME```, ```JAVA_HOME```
* есть три lifecycle:
  * clean - очистка проектных файлов
  * default - обычная сборка
  * site - подготовка документации
* каждый lifecycle состоит из фаз:
  * validate: check if all information necessary for the build is available
  * compile: compile the source code
  * test-compile: compile the test source code
  * test: run unit tests
  * package: package compiled source code into the distributable format (jar, war, …)
  * integration-test: process and deploy the package if needed to run integration tests
  * install: install the package to a local repository
  * deploy: copy the package to the remote repository
  * site: generate documentation
* минимальный файл pom.xml:
```
<project>
  <modelVersion>4.0.0</modelVersion>

  <groupId>com.mycompany.app</groupId>
  <artifactId>my-app</artifactId>
  <version>1</version>
</project>
```
* зависимости:
```
<dependencies>
    <dependency>
        <groupId/>
        <artifactId/>
    </dependency>
</dependencies>
```
* проперти:
```
<properties>
<myproperty>myvalue</myproperty>
</properties>
```
* объявление подмодулей:
```
<modules>
    <module>mymodule</module>
</modules>
```
