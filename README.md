#Rozwiązywacz labiryntów (labsolver)

---
Mini-Projekt 3 na PINF gr. 1 

Autor: Grzegorz Jewusiak (319046)

##Szczegóły implementacyjne
Dostępna w dołączonym pliku PDF.

##Historia zmian i kod źródłowy
Dostępne w repozytorium na Githubie. Proszę o informację w razie potrzeby udostępnienia historii zmian.

##Sposób użycia
Kod należy zbudować poleceniem `make run`.
W celu wejścia w "tryb debugowania", należy wpisać `make debug`.

Tryb debugowania:
- Wypisuje wczytane krawędzie, macierze sąsiedztwa i incydencji, wszystkie ścieżki które prowadzą do końca labiryntu.

###Wymagane pliki
Należy zdefiniować labirynt w formacie:
<pre>
#P#####
#     #
# # # #
#   # #
# # ###
#     #
#####K#
</pre>

Gdzie `#` to ściana, `P` to wejście do labiryntu, zaś `K` to wyjście.
Maksymalny rozmiar labiryntu to 10x10, czyli 21 znaków (#, P, K lub spacja) i 21 linii.
<b>Należy dopilnować, by na końcach linii nie było spacji, tabulatorów.</b>

###Wywołanie

`labsolver <ścieżka>`

`<ścieżka>` - argument obowiązkowy - ścieżka do pliku z definicją labiryntu/sgrafu

###Wynik

Wynik prezentowany jest w postaci dostępnych ścieżek, wraz z ich długościami i adnotacją która jest najkrótsza.

###Kody błędów (exit codes)

- 0 - powodzenie - znaleziono >=1 ścieżek
- 1 - nie znaleziono ścieżek / brak punktu końcowego `K`
- 2 - niepowodzenie czytania labiryntu z pliku
- 3 - brak pozycji początkowej (wejścia `P`) w labiryncie
- 4 - błąd otwarcia pliku

##W jaki sposób oznaczane są pozycje w labiryncie?
Każda kolumna ma przypisany numer od 0 do 9, zaś każdy wiersz ma przypisany numer {0, 10, 20, ..., 90}.
Aby otrzymać ID pozycji w labiryncie, nalezy je zsumować, tj. dla pozycji w drugiej (czyli indeks [1]) kolumnie, 3 wierszu (czyli indeks [2]) jest to pozycja o ID=20+1=21. Została wyróżniona poniżej za pomocą <b><u>0</u></b>.

###Wizualizacja labiryntu:

Pozycje oznaczone zostały `o`, zaś przejścia `|` lub `-`. 

Znaki `o | -` nie mogą znajdować się w pliku z labiryntem!

<pre>
    0 1 2   
   #P#####
0  #o-o-o#
   #|#|#|#
10 #o-o#o#
   #|#|###
20 #o-<b><u>0</u></b>-o#
   #####K#
</pre>
