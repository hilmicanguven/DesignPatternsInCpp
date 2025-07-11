/*

Descorator Design Pattern (aka Wrapper)

Mevcut bir nesnenin ekstra özellik/fonksiyonalite kazanmasını isteriz ancak mevcut kodları değiştirmemiz hem istenmez hem mümkün olmayabilir.
Bu durumda yeni özelliği ayrı tutmak isteriz. Bu durumda da mevcut yapı (decorated object) ile interaction olması gerekir. 

    | Facilitates the addition of behaviors to individual objects

İki opsiyon bulunur
- Aggregate the decorated object
- Inherit from the decorated object

// Dynamic Decorator
    - Keeps the reference to the decorated objects  -> ColoredShape{Square{}}

// Static Decorator
    - uses Mixin Inheritance via templates  -> ColoredShape<Square>
    - Mixin: Mixin, tek başına anlamlı olmayan ama başka sınıflara ek özellikler kazandırmak için kullanılan bir sınıftır.
                C++’ta mixin’ler genellikle template ve çoklu kalıtım ile birlikte kullanılır.

// Both
    - both method allows limitless composition  -> TransparentShape<ColoredShape<Square>>


    |   Decorator is a structural design pattern that lets you attach new behaviors to objects 
    |       by placing these objects inside special wrapper objects that contain the behaviors.
    |                                                                ...refactoring.guru


*/