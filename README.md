# Projekt- Kalkulator w Allegro ![image100](https://github.com/forgeine/projekt_kalkulator/assets/135221458/165d9486-103e-45ae-b65b-3fee39fbbc29)


Kalkulator oparty jest o biblioteki Allegro. Główna zasada działania opiera się o strukturę [Calculator] oraz funkcje void, które są inicjalizowane poprzez wykrycie, w którym miejscu myszka została kliknięta [x i y]. Bazowy stan kalkulatora to zawsze 0.

![image](https://github.com/forgeine/projekt_kalkulator/assets/135221458/0d39b6e2-832e-4500-baa9-1a341bbec688)

Gdy kliknięta zostaje cyfra to jest ona dopisywana do tablicy i wyświetlana na wyświetlaczu, jako część [liczby_1]. Jak na zdjęciu poniżej. 

![image](https://github.com/forgeine/projekt_kalkulator/assets/135221458/298dc84d-b68f-446a-a677-c40b606ae6ae) 
![image](https://github.com/forgeine/projekt_kalkulator/assets/135221458/8976a365-6d1c-47d0-8149-b6872f6fa721)

Po kliknięciu myszką na klawisz funkcyjny liczba z tablicy zostaje zapisana i rozpoczyna się wpisywanie następnej [liczby_2]. W przypadku korekcji liczby można kliknąć na [<-] (backspace) i zmienić ją liczba po liczbie.

![image](https://github.com/forgeine/projekt_kalkulator/assets/135221458/21f04d03-d53c-4ca9-bb51-0f323f033af0) 
![image](https://github.com/forgeine/projekt_kalkulator/assets/135221458/558ab09a-675d-424b-a2e9-64256fcb7987)

Niżej przykładowa funkcja, tutaj [^].

![image](https://github.com/forgeine/projekt_kalkulator/assets/135221458/6605c652-aae6-4841-9e85-1eab44f220d0)

Kolejkę kończy wybranie przycisku równa się [=], który przydziela wynik działania do [liczby_1] i ją wyświetla. Niżej przykładowe działanie po kliknięciu [=], tutaj dla [+].

![image](https://github.com/forgeine/projekt_kalkulator/assets/135221458/ed42e5cf-dac5-4799-a816-a87f9fba16eb)
![image](https://github.com/forgeine/projekt_kalkulator/assets/135221458/335556da-a753-41f6-b59a-7128edc9af42)

Można wtedy przystąpić do kolejnego wpisywania [liczby_2] bądź do wyczyszczenia pamięci i rozpoczęcia obliczeń od nowa. Rysowanie elementów kalkulatora odbywa się w pętli istnienia okna [display], osobno rysowany jest wyświetlacz i jego zawartość, osobno w jednej pętli:  kafelki, znaki na kafelkach oraz efekt hover, po najechaniu na kafelek. 

![image](https://github.com/forgeine/projekt_kalkulator/assets/135221458/b184ae80-8138-44e2-8238-97b703987f8a)
