# Семинар 8

## Заголовки объектов

Написано на базе [статьи](https://habr.com/ru/articles/447848/)

* В 32-битной системе заголовок весит 8 байт = 4 байта markword (параметры) + 4 байта classword (указатель на класс)
* Markword может иметь одно из 5 состояний:
  * Обычное. В таком состоянии в параметре хранятся следуcющие вещи:
    * identity hash code - который генерирует System.hashCode - это рандомный hash код. Генерируется один раз для каждого объекта, а потом хранится в заголовке. Важно, что в разных JVM это не всегда так, например в Hotspot хешкод генерируется иначе.
    * age - возраст объекта в gc
    * биты идентифицирующие состояние
  * biased-lock - объект был свободен, потом им завладел один поток и пока больше никто на объект не претендует.
    * thread - идентификатор потока-владельца
    * epoch - параметр, который описывает эпоху блокирования
    * age - возраст объекта в gc
    * биты идентифицирующие состояние
  * lightweight-lock - блокировка с помощью атомика и спин лока.
    * ptr-to-lock-record - указатель на атомик
    * биты идентифицирующие состояние - уменьшены
  * heavyweight lock - полноценный замок с помощью mutex
    * ptr-to-heavyweight-konitor - указатель на mutex
    * биты идентифицирующие состояние - уменьшены
   
## Механизмы синхронизации

### synchronized

* Синхронизированные блоки могут выполняться только одним методом в один момент времени -
остальные ждут.

```java
Object monitorLock = new Object();

Runnable task = () -> {
    System.out.println("I am before sync: " + Thread.currentThread().getName());
    synchronized (monitorLock) {
        try {
            Thread.sleep(5000);
            System.out.println("I am inside: " + Thread.currentThread().getName());
        } catch (InterruptedException ignored) {
        }
    }
    System.out.println("I am after sync: " + Thread.currentThread().getName());
};

Thread thread1 = new Thread(task);
Thread thread2 = new Thread(task);

thread1.start();
thread2.start();

try {
    thread1.join();
    thread2.join();
} catch (InterruptedException ignored) {
}
```

* Для синхронизации всегда нужен объект. Потому что при синхронизации используется монитор. Монитор = элемент, который обеспечивает эксклюзивное владение объектом в случае блокировки.
* Когда synchronized висит на методе-члене, синхронизация происходит по this. На статическом методе
синхронизация происходит по самому классу.

```java
class SyncClass {
    synchronized void foo() {
        try {
            Thread.sleep(5000);
            System.out.println("I am inside: " + Thread.currentThread().getName());
        } catch (InterruptedException ignored) {
        }
    }
}

SyncClass sync = new SyncClass();

Runnable task = () -> {
    System.out.println("I am before sync: " + Thread.currentThread().getName());
    sync.foo();
    System.out.println("I am after sync: " + Thread.currentThread().getName());
};

Thread thread1 = new Thread(task);
Thread thread2 = new Thread(task);

thread1.start();
thread2.start();

try {
    thread1.join();
    thread2.join();
} catch (InterruptedException ignored) {
}
```

```java
class SyncClass {
    static synchronized void foo() {
        try {
            Thread.sleep(5000);
            System.out.println("I am inside: " + Thread.currentThread().getName());
        } catch (InterruptedException ignored) {
        }
    }
}

Runnable task = () -> {
    System.out.println("I am before sync: " + Thread.currentThread().getName());
    SyncClass.foo();
    System.out.println("I am after sync: " + Thread.currentThread().getName());
};

Thread thread1 = new Thread(task);
Thread thread2 = new Thread(task);

thread1.start();
thread2.start();

try {
    thread1.join();
    thread2.join();
} catch (InterruptedException ignored) {
}
```

* Синхронизированный статически метод может быть вызван только одним потоком за раз и только
так.

### wait & notify

* Метод wait вызывается только внутри блока synchronized и только на объекте, по которому синхро-
низируемся. В этот момент происходит выход из синхронизации до тех пор, пока не будет вызван
метод notify.
* Notify пробуждает только один ждущий поток, notifyAll пробуждает все ждущие потоки. Причем
пробужбение произойдет только если монитор становится свободен.

```java
Object lock = new Object();

Thread thread1 = new Thread(() -> {
    try {
        synchronized (lock) {
            System.out.println("1");
            lock.wait();
            System.out.println("4");
        }
    } catch (InterruptedException ignored) {
    }
});
Thread thread2 = new Thread(() -> {
    try {
        synchronized (lock) {
            Thread.sleep(4000);
            System.out.println("2");
            lock.notify();
            Thread.sleep(4000);
            System.out.println("3");
        }
    } catch (InterruptedException ignored) {
    }
});

thread1.start();
thread2.start();

try {
    thread1.join();
    thread2.join();
} catch (InterruptedException ignored) {
}
```

### Locks

![image](https://github.com/user-attachments/assets/7d0e9a9b-4a10-42a6-a9e6-ecba8e9b2a95)

* Метод lock захватывает замок. После этого другие вызывающие метод lock ждут пока замок не
осободится.
* Метод unlock отпускает замок.
* Использовать надо в блоке try-finally.
* Еще есть метод tryLock - пытается взять замок, если получилось - возвращает true. При помощи этого метода можно забирать несколько замков в разном порядке.
* Виды замков:
  * ReentrantLock - базовый замок.
  * ReadWriteReentrantLock - замок с двумя мониторами на чтение и на запись. Чтение блокиру-
ется, когда происходит запись. Несколько потоков могут держать readLock.

```java
class SmartSyncContainer {
    private int x;

    private final ReadWriteLock lock = new ReentrantReadWriteLock();

    public void setX(int x) {
        lock.writeLock().lock();
        try {
            this.x = x;
        } finally {
            lock.writeLock().unlock();
        }
    }

    public int getX() {
        lock.readLock().lock();
        try {
            return x;
        } finally {
            lock.readLock().unlock();
        }
    }
}
```

* Есть два варианты справедливости:
  * справедливый - потоки приобретают справедливый замок в том порядке, в котором его запра-
шивали.
  * несправедливый - может произойти проталкивание, при наличии в данный замка в свободном
состоянии.

## volatile

* Гарантирует совпадение значения переменной в кэшах разных потоков.
* Фактически отключает кэширование для переменной.
* Гарантирует атомарность одной операции (read / write), но при многоэтапных операциях - при ин-
кременте, например, уже надо использовать Atomic.
* 32-битные примитивы имеют атомарные чтение и запись изначально, однако volatile для них будет
гарантроовать мгновенную видимость (visibility) изменений в других потоках.
* Для 64-битных чисел (long, double) использование volatile необходимо для атомарности чтения и
записи, иначе операции могут быть двухэтапными. Фактически, кроме всего прочего, volatile избав-
ляется от двухэтапности и гарантирует атомарность.
* Кроме того операции над volatile переменной не будут переупорядочены с другими операциями в
памяти. (hb)
* Для атомарного CAS использовать AtomicFieldUpdater.
* Многопоточная инициализация. Объявление переменной volatile гарантирует, что другие потоки не
получат доступ к неинициализированной переменной. Это следует из hb.

## 5 вариантов реализации синглтона

Взято из [статьи](https://habr.com/ru/articles/129494/) 

### 1 Static field

```java
public class Singleton {
	public static final Singleton INSTANCE = new Singleton();
}
```

### 2 Enum Singleton

```java
public enum Singleton {
	INSTANCE;
}
```

### 3 Synchronized Accessor (ленивый)

```java
public class Singleton {
	private static Singleton instance;
	
	public static synchronized Singleton getInstance() {
		if (instance == null) {
			instance = new Singleton();
		}
		return instance;
	}
}
```

### 4 Double Checked Locking & volatile

```java
public class Singleton {
  private static volatile Singleton instance;
	
  public static Singleton getInstance() {
		  Singleton localInstance = instance;
    if (localInstance == null) {
			    synchronized (Singleton.class) {
				   localInstance = instance;
				   if (localInstance == null) {
         instance = localInstance = new Singleton();
       }
     }
   }
		 return localInstance;
	 }
}
```

### 5 On Demand Holder idiom

```java
public class Singleton {
		
	public static class SingletonHolder {
		public static final Singleton HOLDER_INSTANCE = new Singleton();
	}
		
	public static Singleton getInstance() {
		return SingletonHolder.HOLDER_INSTANCE;
	}
}
```
