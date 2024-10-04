# Семинар 5

## Паттерны

### Singleton

*пока реализации без многопоточки*

#### Static field

```java
public class Singleton {
	public static final Singleton INSTANCE = new Singleton();
}
```

#### Enum Singleton

```java
public enum Singleton {
	INSTANCE;
}
```

### Builder

* Используем аннотацию ```@Builder```

### Фабрики

* Классические абстрактные фабрики используют редко
* Но зато часто используют статические фабрики-методы. Их лучше использовать вместо конструкторов. В названии лучше придерживать семантики valueOf.

```java
class Integer {
  int integer;

  private Integer(int integer) {
    this.integer = integer;
  }

  public static Integer valueOf(int integer) {
    return new Integer(integer);
  } 
}
```

### Прототип

* Вместо этого паттерна есть миксин Cloneable

### Bridge

* Применение этого паттерна сводится к тому, что во всех типах полей нужно писать значение интерфейса. Тогда можно удобно подставлять различные реализации.

### Decorator & Proxy

Паттерны, которые позволяют добавить функционал отдельному объекту в иерархии. Фактически, происходит оборачивание нужного объекта в дополнительный функционал.

### Adapter

Паттерн, который позволяет стандратизировать API для разных реализаций. Сочетается с мостом. Привести пример с разными хранилищами (Postgres, Reddis)

### Iterator

Есть дефолтная реализация в библиотеке.



