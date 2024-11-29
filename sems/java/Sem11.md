# Spring boot

## spring boot starter

* spring boot starter - основной стартер с IoC контейнером

```
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter</artifactId>
        </dependency>
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-test</artifactId>
            <scope>test</scope>
        </dependency>
```

* CommandLineRunner - интерфейс, который объявляет точку входа в приложение из командной строки

## AOP starter

* Аспектно ориентированное программирование - добавляем общее поведение для разных объектов

```
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-aop</artifactId>
        </dependency>

```

* @Aspect - вешается на класс, определяет аспект. То есть общую функциональность для нескольких
классов.
* интерфейс JoinPoint - определяет точку входа логики аспекта в программу. Через этот интерфейс
можно получить название метода, аргументы и тд
* @PointCut (срез) - вешается на метод и определяет предикат, для Advice, то есть условие для вы-
полнения каких-то действий аспекта.
* Advice (совет) - включает в себя ряд аннотаций, вроде @Before, @After - определяет логику, которая
будет выполняться в аспекте.
* Прокси AOP - Объект, создаваемый АОП-фреймворком для реализации аспектных контрактов
* Связывание (weaving) - связывание аспектов с другими типами приложений или объектами для
создания снабженного советом объекта. Spring AOP, как и другие чистые АОП-фреймворки на Java,
осуществляет связывание во время выполнения программы
* Введение (introduction) - Объявление дополнительных методов или полей от имени типа. Например,
можно заставить бин унаследовать другой интерфейс с помощью аннотации @DeclareParents.
* Пример

```
@Aspect
@Component
public class TestAspect {
    @Pointcut("@annotation(TestAnnotation)")
    public void requiredAnnotation() {}

    @Around("@annotation(TestAnnotation)")
    public Object processAnnotation(ProceedingJoinPoint pjp) throws Throwable {
        pjp.proceed();
        return "biba";
    }
}
```

## Jdbc starter

* DataSource - настройка подключения к БД (бин)
* JDBCTemplate - запросы через query и update
* BeanPropertyRowMapper - маппинг строки БД в объект

```
        <dependency>
            <groupId>org.projectlombok</groupId>
            <artifactId>lombok</artifactId>
            <optional>true</optional>
        </dependency>
        <dependency>
            <groupId>com.h2database</groupId>
            <artifactId>h2</artifactId>
            <version>2.2.224</version>
        </dependency>
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-data-jpa</artifactId>
        </dependency>
```

* properties:

```
spring.datasource.url=jdbc:h2:mem:dcbapp
spring.datasource.driverClassName=org.h2.Driver
spring.datasource.username=sa
spring.datasource.password=password
spring.jpa.database-platform=org.hibernate.dialect.H2Dialect
```

## Jpa starter

* Сущности (@Entity) - ORM - маппим класс к таблице в Бд
* репозитории (@Reposiotry) - доступ к таблицам - отсюда можно получить классы сущностей
* @Transactional - создание методов-транзакций
