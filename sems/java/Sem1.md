# Семинар 1

*Синтаксис java, строки, массивы, Object*

## Система оценивания

* 4 дз
* 2 кр

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
* артефакт = jar-файл = модуль
* у maven есть репозитории: удаленные и локальные (.m2)
* один артефакт может зависеть от других. Для этого секция dependencies
* создание maven-проекта в idea:

![image](https://github.com/user-attachments/assets/5e721a70-4719-4a20-9813-70beda78bc8a)

* структура модуля:

![image](https://github.com/user-attachments/assets/08e31a2b-921e-4473-907e-2b117ccdb5f3)

* команды для сборки в maven: ```mvn clean package```
* очистка: ```mvn clean```
* установить артефакт в локальный репозиторий: ```mvn install```
* Самая полезная зависимость:

```
    <dependency>
      <groupId>org.projectlombok</groupId>
      <artifactId>lombok</artifactId>
      <version>1.18.34</version>
      <scope>provided</scope>
    </dependency>
```

## Методы

* методы класса - их можно вызывать только от объекта данного класса ```obj.meth()```
* статические методы - их можно вызывать без объекта, а просто указав название класса, где они лежат: ```Obj.meth()```. Фактически - глобальные методы
* модификаторы доступа
* * public - доступно везде
  * package - доступно только в пакете
  * protected - доступно в лкассе и в его потомках
  * private - доступно только в классе
 
## Объекты

* все объект, кроме примитивных типов
* примитивы в стеке
* объекты в куче
* любой класс наследуется от класса Object
* есть boxing, int - Integer
* Integer немутабелен
* сравнение с Nan всегда false

## Массивы и списки

* можно определить массив: ```A[] a = new A[10];```
* длинна массива: ```a.length```
* если выйти за границу массива будет IndexOutOfBoundsException
* многомерные массивы: ```A[][] a = new A[10][20];```. Последующие измерения можно не инициализировать
* Списки:
* * ```List<Integer> list = new LinkedList<>();``` (связный)
  * ```List<Integer> list = new Array<>();``` (вектор)
* есть операции: add, remove, get
 
## Строки

* класс String иммутабелен - при каждой конкатенации создается новая строка
* строки хранят в себе char[]
* для быстрого создания строк: StringBuffer и StringBuilder
* StringBuilder - непотокобезопасен, более быстрый. Есть метод append.
* StringBuffer - синхронихирован, более старый

## Lombok

* @Getter
* @setter
* @Data
* @AllArgsConstructor
* @NoArgsConstructor
* @NonNull
* @Log
* @Builder
* @ToString
* @EqualsAndHashCode
* @Cleanup
