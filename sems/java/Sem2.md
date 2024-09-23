# Семинар 2

*ООП и классы*

## ООП

* Постулаты ООП:
  * инкапсуляция - сокрытие деталей реализации и предоставление в открытый доступ только публичного API
  * полиморфизм - вызывая переменную класса родителя со значением объекта класса потомка будет вызываться метод потомка
  * наследование - можно создать общий класс, который будет определять характеристики и поведение, свойственные какому-то другому классу
* один файл = один класс / интерфейс / перечисление / аннотация

## Классы

* класс определяется загрузчиком и полным именем
* модификаторы доступа:
  * public - видно отовсюду
  * package - видно только в пакете 
* final - определяет переменную, которая инициализируется ровно один раз. Или класс, от которого нельзя унаследоваться
* модификаторы доступа полей и методов-членов: public/package/private/protected
* static - определяет метод или поле, для доступа к которому не нужно обращаться к объекту класса (фактически глобальная переменная). Static поля инициализируются сверху-вниз.
* глобальную везде видимую константу можно создать так: ```public static final String myconst="biba";```
* abstract - можно сделать класс абстрактным, после чего в нем можно добавлять абстрактные (виртуальные) методы = методы, которые имеют тело только в классах наследниках
* в классе могут быть вложенные классы:
  * static member class - имеет доступ ко всем членам охватывающего класса
  * nonstatic member class - всегда имеет eclosing instance - охватывающий экземпляр. Для доступа можно использовать квалифицированное this
  * anonymous class
  * local class
* this - внутри функции-члена можно обратиться к исходному объекту
* enum = перечисления - это полноценные классы, где каждый элемент - это статический экземпляр.
* методы, которые есть у всех объектов:
  * equals
  * hashcode
  * toString
  * wait/notify
  * getClass
  * finalize (не использовать)
  * clone (не использовать)
* Выбор среди перегруженных методов статический (на этапе компиляции), а выбор среди перекрытых методов динамический (на этапе выполнения). Всегда выполняется наиболее конкретный метод.
* javadoc обязателен для контракта публичного API (в методах интерфейсов):
```
/**
* Description.
* 
* @param arg - my arg
* @throws MyException - why
* @returns myvalue
*/
int someMethod(int arg) {
  ...
}
```
 
### Полезные советы

* Вместо конструкторов можно использовать статические фабрики
* Для обеспечения неинстанцируемости служебных классов можно создать единстенный приватный конструктор
* Вместе с equals надо перекрывать и hashcode. Так как из эквивалентности по контракту hashcode следует равенство хешей.
* Для копирования объектов лучше предоставлять конструктор или фабрику вместо метода clone.
* Нельзя жертвовать инкапсуляцией для упрощения тестирования
* Лучше использовать композицию, а не наследование. Наследование надо либо запретить, либо задокументировать.
* Конструкторы класса не должны вызывать методы, которые можно перекрыть.
* Лучше использовать статические классы члены, чем не статические, чтобы избежать потенциальной утечки памяти
* Надо отделять API от реализации и скрывать все детали реализации.
* Надо делать класс или член как можно менее доступным.

## Интерфейсы

* модификаторов доступа для методов нет
* все методы абстрактные, кроме default
* полей нет
* используются для обозначения публичного API модуля
* Методы публичного API нужно документировать
* интерфейсы с одни методом = функциональные интерфейсы = лямбды
* В типе переменных нужно писать интерфейсы везде, где это возможно (пример со списком)
* mixin - интерфейс, который добавляет свойство:
  * Comparable
  * AutoCloseable
  * Clonable (не использовать)
* для лямбд есть вагон библиотечных интерфейсов: Function, Consumer...
* API = интерфейс, который стоит на входе в модуль - через него вызывается что-то внутри модуля
* SPI = интерфейс, который не реализован в модуле, а должен быть реализован в другом модуле (инверсия зависимостей)

## Аннотации

* просто маркер на поле/классе/методе
* сама аннотация не делает ничего. Делает только код, который анализирует на наличие аннотации

## Пример

*Накодить модуль по контракту:*

* модуль garden
* API-сервис GardenService:
  * growNewPlant(type) - возвращает новое растение
  * observeGarden - возвращает список всех растений
  * setNameGenerator(lambda)
* SPI-сервис PlantStorageService:
  * savePlant(plant) - сохраняет дерево куда-нибудь
  * listPlants - возврашает список всех деревьев в саду
* доменная область:
  * Plant (name, age, type): PineTree, Oak, Dandelion; Есть метод growUp() = age++;
  * PlantType: Tree, Flower;



 