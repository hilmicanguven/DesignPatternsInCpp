/*

Template Design Pattern

öncelikle, "c++ templates" ile alakası bulunmuyor.
daha önce algoritmaların common ve specific kısımlarından bahsetmiştik.
stratgy design paterninde bunu composiiton/inheritance ile yapmıştık
    hatırlamak gerekirse,
        Asıl logic'i içeren sınıf, farklı işlemler için stratgy'leri içeren class'ları elemanı olarak tutuyordu
        ve farklılaşan bu specific işlemler için sınıflar ana bir base sınıftan türüyordu. (inheritance)
burada ise ana iskelet kısmını oluşturup concrete implementation'lar sub-classeslar içerisinde oluyor.
yani oluşturulan sub-class base class'ın ana algoritmasında belirtilen arayüzleri override ediyor.

Örnek senaryo,
    Ana sınıf = Game
        Ana algoritma
            	void run()
                {
                    start();
                    while (!have_winner())
                        take_turn();
                    cout << "Player " << get_winner() << " wins.\n";
                }

    Sub-Class = Şogi (Japon Satrancı)
        override edeceği arayüzler ise
            start
            have_winner
            take_turn
            get_winner
        

*/
