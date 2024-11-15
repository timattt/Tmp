# Семинар 10

## Spring

* Spring = библиотека
* Как подключить:

```
    <dependency>
      <groupId>org.springframework</groupId>
      <artifactId>spring-core</artifactId>
      <version>${spring.version}</version>
    </dependency>
    <dependency>
      <groupId>org.springframework</groupId>
      <artifactId>spring-context</artifactId>
      <version>${spring.version}</version>
    </dependency>
    <dependency>
      <groupId>org.springframework</groupId>
      <artifactId>spring-beans</artifactId>
      <version>${spring.version}</version>
    </dependency>
```

```
<spring.version>6.2.0</spring.version>
```

* IoC = inversion of control = зависимости внедряются из вне.
* ApplicationContext - это IoC-контейнер, наследуется от BeanFactory, управляет бинами, ресурсами, событиями.
* Создание контекста:

```
ApplicationContext context = new AnnotationConfigApplicationContext(MyConfig.class);
```

* По-умолчанию название бина - это либо имя метода (если @Bean), либо имя класса в camel-style (если @Component и другие).
* Имя можно указать свое с помощью @Qualifier. Так как spring - это map, следовательно двух одинаковых имен быть не может.

### Полезные аннотации

* @Component(BEAN-NAME) - воздание бина из класса
* @Autowired - установить зависимость и произвести inject через конструктор, setter или прямо через поле
* @Qualifier(BEAN-NAME) - при наличии нескольких одинаковых бинов можно уточнить какой нужен
* @Value("ДОЛЛАР И СКОБКИ") - можно из файлов брать значение полей бинов
* @PostConstruct - помечаем метод, который вызовется после создания бина
* @PreDestroy - помечаем метод, который вызовется перед уничтожением бина
* @Configuration - класс, методы которого представляют из себя бины, помеченные аннотацией @Bean
* класс Environment - можно брать оттуда значения из внешних файлов .properties
* @ComponentsScan - можно указать в каких пакетах искать бины
* @Bean(BEAN-NAME) - метод становится бином. При внедрении зависимости singleton-метод не выполняется.
* Виды scope у бинов:
    * singleton - один бин на всю программу
    * prototype - новый объект при каждом новом вызове функции бина
    * request, session - один экзампляр на один http запрос
* Аннотация @Lazy дает команду IoC-контейнеру создать экземпляр бина при первом запросе, а не при запуске.

## Spring boot

* spring - библиотека
* spring boot - группа библиотек поверх spring с такими фичами:
    * Вместо зависимостей стартеры
    * Конфигурация автоматическая
    * Сервер находится внутри итогового jar-файла
* конфигурация через https://start.spring.io/
* Spring Boot всегда автоматически ищет файлы application.properties
* Можно создавать свою собственную автоконфигурацию. Для этого нужно, чтобы в jar был файл
META-INF/spring/org.springframework.boot.autoconfigure.AutoConfiguration.imports. В нем нужно пе-
речислить все классы конфигурации.
  

