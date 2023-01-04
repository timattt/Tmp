# Space plunder

### Идея игры
Идея такая: мы находимся в двумерном космосе, размер космических кораблей сопоставим с размерами планет, живем в условиях классической задачи об N тел.   
Корабли двигаются по Мещерскому. К некой галактике есть торговые пути, фарпосты и т.д. Вот это все надо грабить. Есть ракеты, лазерные пушки и т.д.
### Столкновения объектов
Про математику в столкновениях можно почитать на [википедии](https://ru.wikipedia.org/wiki/%D0%A3%D0%B4%D0%B0%D1%80)

1. Берем направление текущей скорости. В этом направлении ищем ближайший объект. Находим.
2. Двигаемся до него.
3. Обрабатыем столкновение. Имеем новое направление скорости.
4. Повторяем предыдущие действия. Проходим так все, что можем пройти за данное dt.   

Замечание:   
1. Если ближайший объект находится на расстоянии 0. Пусть таких объектов несколько.
2. Виртуально сталкиваемся с каждым их них. Получаем n направлений.
3. Теперь перестаем их учитывать. По старой схеме находим для каждого направления конечную точку.
4. Для каждой точки считаем проникновение в исходные n объектов. Берем ту точку, для которой проникновение меньше.

Замечание:   
В упрощенной модели с шарами можно просто двигаться в направлении от шара в случае нахождения внутри шара.
 