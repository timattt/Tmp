# Семинар 9

## Thread pool

* Executors - класс, в котором есть статические методы-фабрики для создания пулов. Далее есть
методы execute и submit.
* Метод shutdown завершает работу всех потоков после выполнения задач.
* Есть вариант создавать Callable, который возвращает Future, через который можно подождать ре-
зультат выполнения потока.

### Виды пулов

![image](https://github.com/user-attachments/assets/5c239c61-b954-46d6-9270-8fb9d5030623)

* FixedThreadPool - количество потоков не меняется. Есть конкуретная очередь с задачами. Из
которой рабочие потоки забирают задачи.
* CachedThreadPool - Генерирует под каждую задачу новый поток или отдает ее свободному. При
этом если поток свободен, он 60 секунд ждет новую задачу, после чего уничтожается.
* ForkJoinPool - Применение принципа workStealing. Задача разбивается на подзадачи. Есть два
главных метода: fork и join. У каждого потока своя двусторонняя очередь. Но если очередь у
потока пуста, то он может украсть задачу у другого потока с заднего конца очереди - идиома
work-stealing.

![image](https://github.com/user-attachments/assets/4ec24a29-c219-47fc-8080-468a958e6370)

* Пример:

```
    @Test
    public void forkJoinTest() {
        int[] array = new int[] {
                0, 1, 2, 3, 4, 5, 6, 7
        };
        ForkJoinPool pool = new ForkJoinPool();
        System.out.println(pool.invoke(new SumTask(array, 0, array.length)));
    }

    @RequiredArgsConstructor
    static class SumTask extends RecursiveTask<Integer> {
        private final int[] array;
        private final int left;
        private final int right;

        @Override
        protected Integer compute() {
            if (Math.abs(left - right) <= 1) {
                int result = 0;
                for (int i = left; i < right; i++) {
                    result += array[i];
                }
                return result;
            }

            int middle = (left + right) / 2;
            var leftTask = new SumTask(array, left, middle);
            var rightTask = new SumTask(array, middle, right);

            leftTask.fork();
            rightTask.fork();

            return leftTask.join() + rightTask.join();
        }
    }
```

* ScheduledThreadPool - аналогичен ThreadPoolExecutor задачи выполняются отложено.
* Метод shutdown завершает работу всех потоков после выполнения задач.
* Метод shutdownNow - инициирует прерывание (InterruptedException) всех задач.
* Политика насыщения определяет, что делать с новой задачей, если очередь уже полна:
    * AbortPolicy (default) - кидает исключение
    * CallerRunsPolicy - выполняет в потоке, который вызвал execute
    * DiscardPolicy
    * DiscardOldestPolicy

## Многопоточные коллекции

### Set

* ConcurrentSkipListSet - аналогичен TreeSet, но для нескольких потоков.
* CopyOnWriteArraySet - лучше всего подходит для read-only коллекций, размер которых достаточ-
но мал, чтобы их скопировать, если произойдут некоторые изменяющие операции. Также разделяет
все основные свойства CopyOnWriteArrayList, так как с его помощью реализован

### List

* Vector - главное отличие от ArrayList в том, что Vector синхронизирован (с помощью synchronized),
также при нехватке места растет в два раза
* Stack - поскольку Stack унаследован от Vector, значит стек тоже синхронизирован
* CopyOnWriteArrayList - потокобезопасность без синхронизации. Когда мы используем любой из
методов модификации, таких как add() или remove(), все содержимое CopyOnWriteArrayList копи-
руется в новую внутреннюю копию. Можем безопасно перебирать список, даже когда происходит
одновременная модификация. Полезно в тех случаях, когда мы итерируемся чаще, чем изменяем.
Add, Remove, Contains за O(n), Get за O(1)

### Queue

Блокирующая очередь: Блокирующая операция take() - берет следующий элемент, если же очередь
пустая - блокирует выполнение до появления элемента (до момента, когда перестанет быть пустой) Блоки-
рующая операция put(E e) - помещает элемент в очередь, если очередь заполнена - блокирует выполнение
до освобождения места в очереди и успешного помещения в нее нового элемента.

* ConcurrentLinkedQueue - очередь рассчитанная на большое количество потоков.
* ConcurrentLinkedDeque - двусторонняя очередь рассчитанная на большое количество потоков.
* ArrayBlockingQueue - блокирующая очередь на основе массива
* PriorityBlockingQueue - отсортированная блокирующая очередь
* PriorityBlockingQueue - отсортированная блокирующая очередь
* LinkedBlockingQueue - блокирующая очередь на основе списка
* LinkedBlockingDeque - блокирующая обратная очередь на основе списка
* DelayQueue - когда потребитель хочет взять элемент из очереди, он может взять его только тогда,
когда истечет задержка для этого конкретного элемента
* SynchronousQueue - это специальный тип BlockingQueue, в котором каждая операция insert долж-
на ждать соответствующую команду remove в другой нити, и наоборот. В очереди в любой момент
времени может быть только один элемент.
* LinkedTransferQueue - похожа на BlockingQueue , но дает нам новую возможность реализовать
форму обратного давления. Это означает, что когда производитель отправляет сообщение потреби-
телю с помощью метода transfer() , производитель будет оставаться заблокированным до тех пор,
пока сообщение не будет использовано. Если 10 потоков положили по элементу - они будут ждать,
пока кто-то не заберет их.

### Map

* Hashtable - синхронизированная упорядоченная карта пар ключ-значение. Она не допускает пустых
значений и использует метод equals() для проверки на равенство.
* ConcurrentHashMap - многопоточный hash-map. Имеет сегменты, которые отдельно блокируются.
Таким образом, одновременно несколько потоков могут работать. Использует много замков - lock
stripping. Изменение во время итерирования не бросает исключение
* ConcurrentSkipListMap - многопоточность за логарифм.

## Тестирование

Статья про [mockito](https://habr.com/ru/articles/444982/)

* mock - прокси заглушка, которая по умолчанию возвращает нули у всех методов.
* spy - это специальные моки, которые в основном ведут себя как обычные объекты, но позволяют переопределять поведение отдельных методов.
* Установка заглушек: ```when(object.someMethod(eq(someArgValue))).thenReturn(someValue)``` или ```doReturn(someValue).when(object).someMethod(eq(someArg))```
