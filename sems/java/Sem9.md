# Семинар 9

## Thread pool

* Executors - класс, в котором есть статические методы-фабрики для создания пулов. Далее есть
методы execute и submit.
* Метод shutdown завершает работу всех потоков после выполнения задач.
* Есть вариант создавать Callable, который возвращает Future, через который можно подождать ре-
зультат выполнения потока.

### Виды пулов

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
