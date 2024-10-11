# Семинар

*Рефлексия и аннотации*

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
