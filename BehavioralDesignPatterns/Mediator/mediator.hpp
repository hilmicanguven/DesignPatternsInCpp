/*

Mediator Design Pattern 

    | Mediator is a behavioral design pattern that lets you reduce chaotic dependencies between objects. 
    |    The pattern restricts direct communications between the objects and forces them to collaborate only via a mediator object.
                                                                                ...refactoring.guru

Birbirleri ile haberleşecek iki bileşeni doğrudan birbirleri ile haberleştirmek yerine,
"Mediator" sınıfı nesnesi ile haberleşmesi sağlanır. Bu durumda farklı sınıfların birbirlerine depend etmesi engellenir.
"Mediator" sınıfının diğer component'lerin override edeceği bir fonksiyon tanımı yapılır (genelde "notify" isimli) ve 
mediator nesnesini bir işlemin yapılacağı bildirilir. Mediator bu işlemin sonucundan etkilenecek diğer sınıflara gerekli bildirim ve işlemi yapar.
Component'ler birbirlerini bilmeden bu işlem yapılır.
Genellikle tüm Component'leri bilen bir "Concrete Mediator" nesnesi yapılır.

Gerçek hayatta buna örnek olarak,
    - uçakların pilotları birbirleri ile haberleşmek yerine "kule" ile haberleşerek dolaylı olarak birbirleri anlaşabilir.
    - chat room participants**
    - players in an MMORPG
    - event broker

Genellikle ChatRoom örneği çokça verilirmiş bu pattern incelenirken. İzlediğim kursta da açıklandığı için kod örneğini vereceğim.
basitçe örnek şu şekilde,
    - "Person class" ından oluşan kişiler birbirleri olan mesajlaşmasını bir "chatRoom class" aracılığı ile yapacak
    - hiçbir "Person" nesnesi birbirine referans vermeyecektir.
    - broadcast şeklinde herkese mesaj yayımlayabilir, ya da direct message şeklinde bir kişiye özel mesaj gönderebilir.
    - yeni birisi odaya girince bunun bilgisini alabilir.

*/

#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class ChatRoom;

class Person 
{

public:
    string name;
    ChatRoom* room{nullptr};
    vector<string> chat_log;

    Person(const string &name) : name(name) {}

    void say(const string& message) const;
    // {
    //     room->broadcast(name, message);
    // }
    
    void pm(const string& who, const string& message) const;
    // {
    //     room->message(name, who, message);
    // }

    void receive(const string& origin, const string& message)
    {
        string s{origin + ": \"" + message + "\""};
        std::cout << "[" << name << "'s chat session]" << s << "\n";
        chat_log.emplace_back(s);
    }

    bool operator==(const Person &rhs) const
    {
        return name == rhs.name;
    }

    bool operator!=(const Person &rhs) const
    {
        return !(rhs == *this);
    }
};


class ChatRoom
{

public:
    vector<Person*> people;

    void broadcast(const string& origin, const string& message)
    {
        for (auto p : people)
        {
            if (p->name != origin)
                p->receive(origin, message);
        }
    }

    void join(Person* p)
    {
        string join_msg = p->name + " joins the chat";
        broadcast("room", join_msg);
        p->room = this;
        people.push_back(p);
    }

    void message(const string& origin, const string& who, const string& message)
    {
        auto target = std::find_if(begin(people), end(people), [&](const Person *p) 
        {
            return p->name == who;
        });
        
        if (target != end(people))
        {
            (*target)->receive(origin, message);
        }
    }
};


void Person::say(const string& message) const
{
    room->broadcast(name, message);
}

void Person::pm(const string& who, const string& message) const
{
    room->message(name, who, message);
}