# Семинар

## Рефлексия и аннотации

* Аннотации можно вешать на типы, методы, поля, параметры
* Параметры при создании аннотаций:
  * @Target - на что аннотацию надо вешать (метод, поле и тд)
  * @Retention - длительность жизни аннотации в коде
    * Source - аннотация запишется в байт-код вашего кода, но не должна сохраняться виртуальной машиной во время выполнения.
    * Runtime - аннотация будет доступна и во время выполнения, благодаря чему мы сможем её обработать, например получить все классы, которые имеют данную аннотацию.
    * Source - аннотация будет удалена компилятором (её не будет в байт-коде). Обычно это бывают аннотации, которые полезны только для компилятора. Например, lombok.
* ```Class.forName``` - позволяет получить объект класса класса, использую полное имя класса.
* Полное имя класса = имя пакета + имя класса
* Получение всех классов в пакете (из статьи на baeldung)

```java
    public Set<Class> findAllClassesUsingClassLoader(String packageName) {
        InputStream stream = ClassLoader.getSystemClassLoader()
          .getResourceAsStream(packageName.replaceAll("[.]", "/"));
        BufferedReader reader = new BufferedReader(new InputStreamReader(stream));
        return reader.lines()
          .filter(line -> line.endsWith(".class"))
          .map(line -> getClass(line, packageName))
          .collect(Collectors.toSet());
    }
 
    private Class getClass(String className, String packageName) {
        try {
            return Class.forName(packageName + "."
              + className.substring(0, className.lastIndexOf('.')));
        } catch (ClassNotFoundException e) {
            // handle the exception
        }
        return null;
    }
```
* Проблема работы со встроенной рефлексией в том, что для нее нужно **загружать** каждый класс. В больших проектах это может съесть много памяти. Альтернативное решение - читать байткод
* Популярная альтернатива: библиотека reflections

```
<dependency>
    <groupId>org.reflections</groupId>
    <artifactId>reflections</artifactId> 
    <version>0.9.12</version>
</dependency>
```

```java
public Set<Class> findAllClassesUsingReflectionsLibrary(String packageName) {
    Reflections reflections = new Reflections(packageName, new SubTypesScanner(false));
    return reflections.getSubTypesOf(Object.class)
      .stream()
      .collect(Collectors.toSet());
}
```

* Прокси. В java есть метод ```Proxy.newProxyInstance```, который позволяет конструировать прокси объекты, наследующие различные интерфейсы. Вызовы методов можно перехватывать.
* Однако, от классов наследоваться прокси не может. Тут нужно сторонняя библиотека, например:

```
<dependency>
    <groupId>org.javassist</groupId>
    <artifactId>javassist</artifactId>
    <version>3.28.0-GA</version>
</dependency>

```

```java
public static <T> T advancedCache(T target) {
    ProxyFactory factory = new ProxyFactory();
    factory.setSuperclass(target.getClass());
    Object result = factory.create(new Class<?>[0], new Object[0], new CachedObjectInvocationHandler<>(target));
    return (T) result;
}
```

## Io

* IO - устаревшая полностью блокирующая библиотека для работы с потоками ввода/вывода

## Nio

* Nio - ```new I/O``` современный стандарт java API для блокирующего/неблокирующего/ассинхронного ввода и вывода
* Buffer – это контейнер для данных примитивного типа. Фактически массив примитивов.
* Channel – открытое соединение с объектом, таким как аппаратное устройство, файл, сетевой сокет или программный компонент, который способен выполнять одну или несколько различных операций ввода-вывода, например чтение или запись. В unix это всегда будет файл (socket, pipe, fs ...) Иерархия каналов:

![image](https://github.com/user-attachments/assets/8ae6e1dd-0a1a-402a-8613-6354cce382c1)

красные – блокирующие каналы; пурпурные – асинхронные каналы; зеленые – неблокирующие каналы.

* Блокирующие каналы - реализовывают синхронное чтение. Поток ждет, пока не прочитает все. Есть класс ```Files``` - в нем есть все необходимое для работы. Пример использования:

```java
void nio_blocking_readFile() throws IOException, URISyntaxException {
    URL fileUrl = NioTest.class.getResource(testFilePath);
    var filepath = Path.of(fileUrl.toURI());
  
    try (ReadableByteChannel inputChannel = FileChannel.open(filepath)) {
        var buffer = ByteBuffer.allocate(300_000);
        int readByteCount = inputChannel.read(buffer);
      
        var resultBytes = new byte[readByteCount];
        //Записываем считанные данные в resultBytes
        //Если просто вызвать buffer.array(), то если массив больше считываемого файла,
        //в конце он будет заполнен нулями
        buffer.get(0, resultBytes);
        var fileString = new String(resultBytes, StandardCharsets.UTF_8);
      
        System.out.println(fileString);
    }
}
```

* Асинхронные каналы - позволяют получить объект future, либо использовать callback, когда операция завершится. Пример использования:

```java
void nio_async_readFile() throws URISyntaxException, IOException {
    URL fileUrl = NioTest.class.getResource(testFilePath);
    var path = Path.of(fileUrl.toURI());
  
    try (var inputChannel = AsynchronousFileChannel.open(path)) {
        var buffer = ByteBuffer.allocate(300_000);
        Future<Integer> futureResult = inputChannel.read(buffer, 0);
      
        while (!futureResult.isDone()) {
            System.out.println("Файл еще не загружен в буффер");
        }
      
        var fileString = new String(buffer.array(), StandardCharsets.UTF_8);
        System.out.println(fileString);
    }
}
```

* Неблокирующие каналы - могут переключаться между блокирующим и неблокирующим режимом. Работают с сокетами. Можно включить и выключить блокировку на IO операциях (будет пропуск операции, если данных еще нет).
* Selector – это объект, относящийся к группе каналов и определяющий, какой канал готов к записи/чтению/подключению и т.д. Под капотом syscall epoll из unix. Для использования с селектором можно использовать только неблокируемые каналы.

# Stream Api

* Stream - объект, который хранит и передает данные. Есть три вида операций:
  * операция создания - создает поток из какого-то кол элементов
  * промежуточная операция - изменеяет элементы в потоке (map)
  * терминальная операция - запускает выполнение всей цепочки (без этой операции ничего не будет работать) (sum, count, min, max, toList, collect)
* любые операции, выполняемые над потоком (например, фильтрация, маппинг, сортировка), не влияют на сам исходный набор данны
* Промежуточные операции являются ленивыми. Это означает, что они будут вызываться только в том случае, если это необходимо для выполнения терминальной операции.
* очень важно помнить, что потоки нельзя использовать повторно.
* промежуточные операции, которые уменьшают размер потока, должны быть размещены перед операциями, которые применяются к каждому элементу.
* Полезные методы:
  * ```Stream.of()```
  * ```collection.stream()```
  * ```Stream.generate(() -> "element").limit(10)```
  * ```Stream.iterate(40, n -> n + 2).limit(20)```
  * ```Files.lines(path)```
* reduce - позволяет объединять данные в потоке в одно

```java
IntStream.range(1, 4).reduce((a, b) -> a + b);
```
