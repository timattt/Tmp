# Семинар 3

## Исключения

* исключение = объект, который пролетает через стек вызовов, возможно, заворачиваясь в другие объекты
* иерархия исключений

![image](https://github.com/user-attachments/assets/c1550e94-1e36-47b3-9266-1d4706220582)

* Исключения, который наследуются от RuntimeException - не проверяемые. Они не требуют ставить throws или оборачивать код в catch. Любые другие исключения требуют.
* Error - ошибки, которые терминируют выполнение программы.
* try-finally - блок finally выполняется всегда.
* Ресурсы: try (res = new...) - после такого блока будет вызван метод close.
* Exception chaining - ошибки разных слоев вкладываются друг в друга.
* Рекомендация: Вызов метода, который завершился исключением должен оставлять объект в состоянии до вызова.

## Однопоточные коллекции

### Ассимптотика

![image](https://github.com/user-attachments/assets/13592f9a-3328-4775-af72-cfce99618640)

### Иерархия коллекций

![image](https://github.com/user-attachments/assets/d0e46f82-b749-4a47-982f-ccbebe4e24ba)

### Иерархия словарей

![image](https://github.com/user-attachments/assets/a8e96485-7072-48fb-aad4-e95ea2bb2b8e)

### Множества

*Интерфейс Set*

* **LinkedHashSet** - класс поддерживает связный список элементов набора в том порядке, в котором они вставлялись. Это позволяет организовать упорядоченную итерацию вставки в набор.
* **TreeSet** - все операции с элементами за логарифм. В основе лежит красно-черное дерево. Есть операции поиска потолка и пола.
* **EnumSet** - множество, которое просто хранит элементы перечисления. Фактически, просто битовая карта для перечисления.
* **HashSet** - множество на основе хеширования.

### Списки

*Интерфейс List*

* **LinkedList** - связный список. Можно удобно работать с началом и концом.
* **ArrayList** - System.arrayCopy() используется для копирования, она быстрая. При нехватке места растет на 50 процентов от исходного.

### Очереди

*Интерфейс Queue*

* **PriorityQueue** - Элементы в PriorityQueue автоматически упорядочиваются по своему естественному порядку или по компаратору. В основе лежит куча, поэтому все операции за O(nlog(n)). Элементы итерируются по возрастанию. Можно брать максимум.
* **ArrayDequeue** - под капотом там массив, который увеличивается в два раза при переполнении. фактически там происходит работа с двумя указателями.

### Карты

*Интерфейс Map*

* **HashMap** - несинхронизированная неупорядоченная карта пар ключ-значение (key-value). Она допускает пустые значения и использует хэш-код в качестве проверки на равенство.
* **LinkedHashMap** - отличие от HashMap состоит в том, что при сравнении элементов используется сравнение ссылок, а не значений.
* **WeakHashMap** - слабые ссылки. (WeakReference) Можно использовать для эффективного кеша в памяти.
* **TreeMap** - красно-черное дерево. Все операции за O(log(n)).
* **EnumMap** - карта по перечислениям. Все операции за константу, так как перечисление конечно.
