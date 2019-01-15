# Range

## Часть первая
Мы уже умеем писать `range-base` цикл `for`

```cpp
    vector<int> v = {1, 2, 3, 4, 5, 6};
    for(int i : v)
    {
        cout << i << " ";
    }
```
Вывод:
```sh
1 2 3 4 5 6 
```

И это действительно очень удобно. Но что если я хочу вывести только 3 первых элемента?

Тогда мне придется писать обычный цикл `for`
```cpp
    for(int i = 0; i < 3; i++)
    {
        cout << v[i] << " ";
    }
```
Очень хотелось бы делать как-то так:
```cpp
    vector<int> v = {1, 2, 3, 4, 5, 6};
    for(int i : Range(v, 3))
    {
        cout << i << " ";
    }
```
И соответственно вывод:
```sh
1 2 3 
```

Давайте попробуем реализовать шаблонную функцию `Range`, которая будет принимать итератор на начало последовательности и количество элементов:
```cpp
template <typename T>
vector<T> Range(vector<T> const &v, size_t top)
{
    auto start = v.begin();
    auto end = v.begin() + std::min(top, v.size());
    vector<T> tmp{start, end};
    return tmp;
}
```

Любопытная строка `std::min(top, v.size())` - это защита от обращения за границы последовательности. Что если значение `top` будет превышать размер последовательности?

Т.е. в случае если `top` меньше размера последовательности, то итератор `end` будет указывать на элемент с индексом `top`, в случае если `top` превышает размер последовательности, то `end` будет указывать на конец последовательности.

Подумав немного над кодом можно вспомнить что `std::vector` имеет конструктор принимающий два итератора, на начало и конец последовательности, то есть можно написать так:
```cpp
template <typename T>
vector<T> Range(vector<T> const &v, size_t top)
{
    vector<T> tmp{v.begin(), next(v.begin(), min(top, v.size()))};-->
    return tmp;
}
```

Думаем еще раз и сокращаем код до одной строки:
```cpp
template <typename T>
vector<T> Range(vector<T> const &v, size_t top)
{
    return {v.begin(), next(v.begin(), min(top, v.size()))};
}
```

Отлично теперь мы можем сделать, так как хотели в начале.

Код полностью:
```cpp
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
vector<T> Range(vector<T> const &v, size_t top)
{
    return {v.begin(), next(v.begin(), min(top, v.size()))};
}

int main()
{
    vector<int> v = {1, 2, 3, 4, 5, 6};
    for(int i : Range(v, 3))
    {
        cout << i << " ";
    }
}
```

Запускаем, проверяем:
```sh
1 2 3 
```

## Часть вторая

Я немного изменю код в `main`
```cpp
    vector<int> v = {1, 2, 3, 4, 5, 6};
    for(int& i : Range(v, 3))
    {
        i++;
    }

    for (auto x : v)
    {
        cout << x << " ";
    }

```    

Теперь я хочу изменить значения первых трех элементов в контейнере. Обратите внимание, теперь я обращаюсь к элементу по ссылке `for(int& i : Range(v, 3))`, добавился `&` после `int`. 
Давайте посмотрим вывод:
```cpp
1 2 3 4 5 6 
```
Ничего не изменилось, так как в `Range` мы создали копию нашего оригинального контейнера, а это значит:
* мы потратили впустую кучу ресурсов
* мы не можем изменить с помощью `Range` нашу последовательность

Что нам должна возвращать функция `Range` чтобы мы не копировали вектор и имели возможность получить доступ к элементам последовательности? 

Правильно! Пару итераторов на начало и на конец последовательности.
Реализуем шаблонный класс `Iterator`:
```cpp
template <typename I>
class IteratorRange
{
public:
    I first, last;
};
```
Все просто, класс, который содержит в себе итератор на начало и конец.
Теперь в функции `Range` заменим возвращаемое значение на `IteratorRange`:
```cpp
template <typename T>
IteratorRange<typename vector<T>::iterator> Range(vector<T> const &v, size_t top)
{
    return {v.begin(), next(v.begin(), min(top, v.size()))};
}
```
Возникла проблема, наш код перестал собираться, компилятор ругает на отсутствие каких-то функций begin и end...

![](https://hownot2code.files.wordpress.com/2017/07/screenshot_15.png?w=676)


Хорошо, а что если попробовать их реализовать?
```cpp
template <typename I>
class IteratorRange
{
public:

    I begin() const
    { return first;}

    I end() const
    { return last;}
    
    I first, last;
};
```

И весь код полностью:
```cpp
#include <iostream>
#include <vector>

using namespace std;

template <typename I>
class IteratorRange
{
public:

    I begin() const
    { return first;}
    
    I end() const
    { return last;}
    
    I first, last;
};

template <typename T>
IteratorRange<typename vector<T>::iterator> Range(vector<T> &v, size_t top)
{
    return {v.begin(), next(v.begin(), min(top, v.size()))};
}

int main()
{
    vector<int> v = {1, 2, 3, 4, 5, 6};
    for(int& i : Range(v, 3))
    {
        i++;
    }
    
    for (auto x : v)
    {
        cout << x << " ";
    }
}
```

Вывод:
```sh
2 3 4 4 5 6
```
Успех!

