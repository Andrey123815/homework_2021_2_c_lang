## Follow me
  
[![Youtube](https://img.shields.io/badge/-Youtube-090909?style=for-the-badge&logo=youtube&logoColor=ff0000)](https://youtube.com/channel/UCBT7kqu7CPeJ5XI0AKoebPw)
[![Telegram](https://img.shields.io/badge/-Telegram-090909?style=for-the-badge&logo=telegram&logoColor=27A0D9)](https://t.me/And_Dayk)
[![Instagram](https://img.shields.io/badge/-Instagram-090909?style=for-the-badge&logo=instagram&logoColor=B4068E)](https://www.instagram.com/diakonov_041)
[![Vk](https://img.shields.io/badge/-Vk-090909?style=for-the-badge&logo=vk&logoColor=4F7DB3)](https://vk.com/iddiakonov_041)
[![Twitter](https://img.shields.io/badge/-Twitter-090909?style=for-the-badge&logo=twitter&logoColor=27A0D9)](https://twitter.com/ivredomon?t=Y_vpcIiqIlrzdM4LcE3urw&s=09)
[![Gitlab](https://img.shields.io/badge/-Gitlab-090909?style=for-the-badge&logo=gitlab&logoColor=1195F5)](https://gitlab.com/Andrey123815)
[![Stepik](https://img.shields.io/static/v1?style=for-the-badge&message=Stepik&color=000000&logo=Simkl&logoColor=FFFFFF&label=)](https://stepik.org/users/296520383?auth=login)
<br>
  <br>


<div  align="left">
 
## About Repostitory
  
Study of the basics and principles of single- and multithreaded programming, creation of static and dynamic libraries, implementation of libraries operating in single-threaded and multithreaded mode
  
  
  
## Languages 
![C](https://img.shields.io/badge/-C-090909?style=for-the-badge&logo=C&logoColor=6296CC)
<br>
  <br>


## Task
В вашем распоряжении — прямоугольная матрица из 10 000 x 5000 вещественных чисел двойной точности. 
Составьте наивный алгоритм транспонирования матрицы, а затем реализуйте параллельный алгоритм с использованием
нескольких потоков решения этой задачи с учетом оптимизации работы с кэш-памятью.

На что необходимо обратить внимание:
- основная информация описана в https://park.mail.ru/blog/topic/view/14270/
- параллельная реализация не должна быть осуществлена с помощью процессов, когда требуется реализация
        с помощью потоков (и наоборот);
- компиляция должна происходить с флагами -Wall -Werror -Wpedantic, то есть необработанных ворнингов быть не должно;
- количество потоков/процессов должно быть не захардкожено, а определяться в зависимости от возможностей
        системы(например, в зависимости от количества ядер процессора);
- при разработке обеих библиотек стоит делать общий интерфейс, не раскрывая особенностей реализации;
- библиотеки должны быть взаимозаменяемыми - конкретная реализация (последовательная/параллельная) -
        использоваться в зависимости от конфигурации сборки;
- юнит-тесты должны быть реализованы для обеих реализаций (последовательной/параллельной).
        Покрытие тестами должно быть максимально возможным;
- должны присутствовать стресс-тесты. Они могут быть реализованы внешним образом, запуская две разные программы -
        одну со статической библиотекой с последовательной реализацией, вторую - с динамической библиотекой с
        параллельной реализацией, и сравнивая их выводы друг с другом.
- для организации ввода/вывода больших данных полезно работать с файлами, а в программе - предусмотреть работу
        с универсальными потоками входных/выходных данных (или хотя бы перенаправлять ввод/вывод на уровне их запуска)
- если в задании сказано, что программа должна обрабатывать файлы объёмом 100 Мб – это лишь ориентир,
        на которых программа точно должна работать, и на котором имеет смысл делать замеры производительности и
        эффективности алгоритмов. Поэтому тесты на такой объём должны быть. Однако сама программа должна уметь работать
        с произвольными размерами входных данных
- измерение времени должно осуществляться внешним образом, а не внутри кода библиотек.
        При этом необходимо делать несколько замеров и усреднять. Стоит помнить о том, что clock()
        в многопоточных приложениях работает не так, как ожидается.
