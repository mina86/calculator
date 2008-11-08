#include "config.hpp"

#include <errno.h>
#include <math.h>

#include <iostream>

#include "functions.hpp"
#include "environment.hpp"
#include "file-lexer.hpp"
#include "math.hpp"




/** \mainpage Kalkulator
 *
 * <h2>Wymagania</h2>
 *
 * <h3>Wymagania funkcjonalne</h3>
 * <ol>
 *   <li>Kalkulator b�dzie wykonywa� obliczenia arytmetyczne na
 *     liczbach zmiennopozycyjnych.</li>
 *   <li> Kalkulator b�dzie akceptowa� wyra�enia w postaci wrostkowej
 *     (tj. np. 2 * 5) z uwzgl�dnieniem priorytet�w dzia�a� oraz
 *     nawiasowania.</li>
 *   <li>Kalkulator b�dzie posiada� operator negacji, dodawania,
 *     odejmowania, mno�enia, dzielenia, por�wnywania (r�wny, r�ny,
 *     mniejszy/wi�kszy (r�wny)), a tak�e operator warunkowy
 *     i p�tli.</li>
 *   <li>Kalkulator b�dzie posiada� zestaw wbudowanych funkcji
 *     matematycznych takich jak sinus, cosinus itp.</li>
 *   <li> Kalkulator b�dzie pozwala� na definiowanie zmiennych
 *     i sta�ych.</li>
 *   <li>Kalkulator b�dzie pozwala� na definiowanie funkcji
 *     u�ytkownika, takich �e:
 *     <ul>
 *       <li>ka�da funkcja b�dzie posiada�a w�asn� przestrze�
 *         zmiennych lokalnych,</li>
 *       <li>funkcje u�ytkownika b�d� mog�y wywo�ywa� inne funkcje
 *         w tym inne funkcje u�ytkownika,</li>
 *       <li>funkcje b�d� mog�y wo�a� si� rekurencyjnie (bezpo�rednio
 *         lub po�rednio).</li>
 *     </ul>
 *   </li>
 * </ol>
 *
 * <h3>Wymagania niefunkcjonalne</h3>
 * <ol>
 *   <li>Kalkulator b�dzie pozwala� na zdefiniowanie co najmniej
 *     tysi�ca funkcji.</li>
 *   <li>Kalkulator b�dzie umo�liwia� zdefiniowanie co najmniej
 *     tysi�ca zmiennych w ka�dej przestrzeni zmiennych lokalnych oraz
 *     zmiennych globalnych.</li>
 *   <li>Kalkulator b�dzie umo�liwia� zdefiniowanie co najmniej stu
 *     argument�w formalnych funkcji.</li>
 *   <li>Kalkulator b�dzie obs�ugiwa� stos wywo�a� funkcji
 *     o g��boko�ci co najmniej dziesi�ciu tysi�cy.</li>
 *   <li>Kalkulator b�dzie akceptowa� wyra�enia sk�adaj�ce si�
 *     z tysi�ca lub mniej operacji.</li>
 * </ol>
 *
 * <h2>Opis u�ycia</h2>
 *
 * <h3>Spos�b uruchomienia</h3>
 *
 * Program wczytuje wyra�enia ze standardowego wej�cia (rzecz jasna
 * strumie� wej�ciowy mo�na przekierowa� tak, aby program odczytywa�
 * dane z pliku) i&nbsp;wypisuje wyniki na standardowe wyj�cie.  Przy
 * domy�lnych opcjach milczy, a� do momentu, gdy dane wej�ciowe si�
 * zako�cz� i&nbsp;w�wczas wypisuje warto�ci wszystkich zmiennych
 * globalnych i&nbsp;ko�czy dzia�anie.
 *
 * Dodanie prze��cznika <tt>-v</tt> powoduje, i� kalkulator wypisuje
 * wynik ka�dej z instrukcji, o&nbsp;ile nie jest ona zako�czona
 * �rednikiem (o&nbsp;formacie danych wej�ciowych ni�ej).
 *
 * Dodanie prze��cznika <tt>-q</tt> powoduje, i� po zako�czeniu
 * program nie wypisze listy zmiennych zdefiniowanych
 * w&nbsp;programie.
 *
 * <p name="przelacznik_p" id="przelacznik_p">Prze��cznikami
 * <tt>-p</tt> i&nbsp;<tt>-P</tt> mo�na ustawi� dok�adno�� z jak�
 * operatory "niewyra�nego" (prze��cznik <tt>-p</tt>; domy�lnie
 * <tt>1e-9</tt>) lub zwyk�ego (prze��cznik <tt>-P</tt>; domy�lnie 0)
 * por�wnania b�d� por�wnywa� zmienne.  Prze��czniki te wp�ywa r�wnie�
 * na operatory relacji, ale nie wp�ywaj� na konwersje liczby na
 * warto�� logiczn�.</p>
 *
 * Informacje o&nbsp;opcjach oraz dzia�aniu aplikacji mo�na uzyska�
 * uruchamiaj�c go z&nbsp;opcj� <tt>-h</tt>.
 *
 * <h3>Dane wej�ciowe</h3>
 *
 * Kalkulator wczytuje instrukcje, z&nbsp;kt�rych ka�da zako�czona
 * jest �rednikiem lub znakiem przej�cia do nowej linii.  Wyj�tkiem
 * jest kombinacja backslash-przej�cie do nowej linii kt�ra traktowana
 * jest jak zwyk�a spacja oraz operator przecinek, kt�ry "zjada"
 * wszystkie bia�e znaki (wraz ze znakami przej�cia do nowej linii),
 * kt�re znajduj� si� za nim, dzi�ki czemu mo�na pisa� d�ugie, rozbite
 * na wiele linii sekwencjie wyra�en jako pojedyncza instrukcja.  To
 * w&nbsp;jaki spos�b instrukcja si� ko�czy (czy za pomoc� �rednika
 * czy znaku przej�cia do nowej linii) ma znaczenie, je�eli podana
 * zosta�a opcja <tt>-v</tt>.
 *
 * Instrukcj� mo�e by� albo wyra�enie, kt�re jest wyliczane
 * natychmiast po wczytaniu, albo definicja <a
 * href="#define_function">funkcji u�ytkownika</a>.
 *
 * Wyra�enia zapisywane s� w&nbsp;formacie infiksowym (tzn. naturalnym
 * zapisie z&nbsp;operatorem pomi�dzy operandami).
 *
 * B��dy w&nbsp;sk�adni w&nbsp;odczytywanych instrukcjach powoduj�
 * wypisanie odpowiedniego komunikatu b��du.  B��dy w&nbsp;trakcie
 * wykonywania wyra�enia (np. przypisanie warto�ci do istniej�cej
 * sta�ej, wo�anie nieistniej�cej funkcji) powoduj� wypisanie
 * komunikatu, ale r�wnie�, i� stan �rodowiska jest niezdefiniowany,
 * tzn. nie jest okre�lone, kt�re z&nbsp;wyra�e� zosta�y wykonane,
 * a&nbsp;kt�re nie (przyk�adowo, je�eli sta�a <var>foo</var> nie
 * zosta�a zdefiniowana, to po wywo�aniu instrukcji: <tt>\#foo = 1,
 * max(bar = 1, \#foo = 2)</tt> nie wiadomo czy zmienna <var>bar</var>
 * zosta�a zmodyfikowana czy nie).
 *
 * <h4>Gramatyka</h4>
 *
 * <pre>
 *input           ::= { instruction } ;
 *instruction     ::= [ define-instruction | expression ] ( ";" | "\n" ) ;
 *define-instruction::= "define" id formal-arguments "=" expression ;
 *formal-arguments::= "(" [ { id "," } id ] ")" ;
 *expression      ::= [ expression "," ] assignment-expr ;
 *assignment-expr ::= [ { variable assignment-op } ] repeat-expr ;
 *assignment-op   ::= "=" | "+=" | "-=" | "*=" | "/=" | "^=" ;
 *repeat-expr     ::= logic-or-expr [ rep-op expression ":" cond-expr ] ;
 *rep-op          ::= "?" | "@" | "#"
 *logic-or-expr   ::= [ logic-or-expr  "||" ] logic-xor-expr ;
 *logic-xor-expr  ::= [ logic-xor-expr "^^" ] logic-and-expr ;
 *logic-and-expr  ::= [ logic-and-expr "&&" ] cmp-expr ;
 *cmp-expr        ::= [ cmp-expr ( "==" | "!=" ) ] rel-expr ;
 *rel-expr        ::= [ rel-expr ( "<" | "<=" | ">" | ">=" ) ] additive-expr ;
 *additive-expr   ::= [ additive-expr ( "+" | "-" ) ] multiplicative-expr ;
 *multiplicative-expr::= [ multiplicative-expr mul-op ] power-expr ;
 *mul-op          ::= "*" | "/" | "%"
 *power-expr      ::= prefix-expr [ "^" power-expr ] ;
 *prefix-expr     ::= ( "+" | "-" | "!" ) prefix-expr | simple-expr ;
 *simple-expr     ::= number | "(" expr ")" | variable | id arguments | string ;
 *arguments       ::= "(" [ { assignment-expr "," } assignment-expr ] ")" ;
 *variable        ::= [ "$" | "#" ] id | "##" | "#!" ;
 *
 *number          ::= [ [ int ] "." ] int [ "e" [ "+" | "-" ] int ] ;
 *int             ::= { digit } ;
 *id              ::= ( letter | "_" ) { letter | "_" | digit }
 *digit           ::= ? any decimal digit ?
 *letter          ::= ? any lowercase or uppercase letter ? ;
 *string          ::= ? a sequence of characters souranded by " or ' ?
 * </pre>
 *
 * <h4>Operatory</h4>
 *
 * Kalkulator obs�uguje nast�puj�ce operatory (sortowane od
 * najwy�szego priorytetu; list� operator�w mo�na zawsze wy�wietli�
 * uruchamiaj�c program z opcj� <tt>-o</tt>):
 *
 * <table>
 *   <tr>
 *     <th>Nazwa</th>
 *     <th>Operatory</th>
 *     <th>Asocjacja</th>
 *    </tr>
 *   <tr>
 *     <td>Prefiksowe</td>
 *     <td><tt>+ - !</tt></td>
 *     <td>z prawej do lewej</td>
 *   </tr>
 *   <tr>
 *     <td>Pot�gowanie</td>
 *     <td><tt>^</tt></td>
 *     <td>z prawej do lewej</td>
 *   </tr>
 *   <tr>
 *     <td>Mno�enie/dzielenie</td>
 *     <td><tt>* / %</tt></td>
 *     <td>z lewej do prawej</td>
 *   </tr>
 *   <tr>
 *     <td>Dodawanie/odejmowanie</td>
 *     <td><tt>+ -</tt></td>
 *     <td>z lewej do prawej</td>
 *   </tr>
 *   <tr>
 *     <td>Relacji</td>
 *     <td><tt>&gt; &lt; &gt;= &lt;= ~&gt; ~&lt; &gt;~ &lt;~</tt></td>
 *     <td>z lewej do prawej</td>
 *   </tr>
 *   <tr>
 *     <td>Por�wnania</td>
 *     <td><tt>== != =~ !~</tt></td>
 *     <td>z lewej do prawej</td>
 *   </tr>
 *   <tr>
 *     <td>Iloczyn logiczny</td>
 *     <td><tt>&amp;&amp;</tt></td>
 *     <td>z lewej do prawej</td>
 *   </tr>
 *   <tr>
 *     <td>Logiczna alternatywa wykluczaj�ca</td>
 *     <td><tt>^^</tt></td>
 *     <td>z lewej do prawej</td>
 *   </tr>
 *   <tr>
 *     <td>Logiczna alternatywa</td>
 *     <td><tt>||</tt></td>
 *     <td>z lewej do prawej</td>
 *   </tr>
 *   <tr>
 *     <td>P�tle i operator warunkowy</td>
 *     <td><tt>#: @: ?:</tt></td>
 *     <td>z prawej do lewej</td>
 *   </tr>
 *   <tr>
 *     <td>Przypisanie</td>
 *     <td><tt>= += -= *= /= %= ^=</tt></td>
 *     <td>z prawej do lewej</td>
 *   </tr>
 *   <tr>
 *     <td>Przecinek</td>
 *     <td><tt>,</tt></td>
 *     <td>z lewej do prawej</td>
 *   </tr>
 * </table>
 *
 * Naturalnie obs�ugiwane jest r�wnie� nawiasowanie wyra�e�
 * w&nbsp;celu wymuszenia kolejno�ci wykonywania dzia�a�.
 *
 * Za wyj�tkiem operator�w <tt>^</tt>, <tt>^=</tt> oraz operator�w nie
 * wyst�puj�cych w&nbsp;j�zyku C&nbsp;wszystkie one maj� takie same
 * dzia�anie jak te znane z&nbsp;j�zyka C.
 *
 * Operator <tt>^</tt> oraz <tt>^=</tt> to operatory pot�gowe.
 *
 * Operatory <tt>=~</tt>, <tt>!~</tt>, <tt>~&gt;</tt>, <tt>~&lt;</tt>,
 * <tt>&gt;~</tt> oraz <tt>&lt;~</tt> s� "niewyra�nymi" (ang. fuzzy)
 * odpowiednikami operator�w odpowiednio <tt>==</tt>, <tt>!=</tt>,
 * <tt>&gt;</tt>, <tt>&lt;</tt>, <tt>&gt;=</tt> oraz <tt>&lt;=</tt>.
 * Wi�cej o&nbsp;tych operatorach przy okazji opisywania <a
 * href="#przelacznik_p">prze��cznika <tt>-p</tt></a>.
 *
 * Operator <tt>^^</tt> oznacza logiczny XOR i&nbsp;zasadniczo <tt>a
 * ^^ b</tt> jest r�wnowa�ne <tt>!a != !b</tt>.
 *
 * Operatory <tt>#:</tt> i <tt>@:</tt> s� operatorami
 * p�tli. <tt>@:</tt> odpowiada instrukcji <tt>while</tt> z innych
 * j�zyk�w programowania.  Dop�ki pierwsze wyra�enie daje warto��
 * prawdziw� wykonywane jest drugie.  Natomiast pierwszy argument
 * operatora <tt>#:</tt> odpowiada ile razy ma by� wykonane drugie
 * wyra�enie.  Rezultatem tych operator�w jest wynik trzeciego
 * wyra�enia.  W trakcie wyliczania warto�ci dost�pne s� dwie sta�e:
 * <tt>##</tt> okreslaj�ca numer iteracji (licz�c od zera) oraz
 * <tt>#!</tt> okre�laj�ca ostatni� wyliczon� warto�� wyra�enia cia�a
 * p�tli. (Aby uzyska� efekt p�tli do-while mo�na, pomijaj�c
 * rozwi�zanie oczywiste polegaj�ce na powt�rzeniu cia�a przed
 * instrukcj�, w warunku przyr�wna� sta�� <tt>##</tt> do zera, np.:
 * <tt>## == 0 || warunek @ cialo : wynik</tt>.)
 *
 * Nale�y zwr�ci� uwag� na operatory logiczne oraz operatory, kt�re
 * jako operandy przyjmuj� warto�ci logiczne.  W&nbsp;kalkulatorze
 * zmienna ma warto�� logiczn� fa�sz wtedy i&nbsp;tylko wtedy, gdy
 * jest r�wna zero.  Istotne jest, �e to co "wygl�da jak zero"
 * niekoniecznie "jest r�wne zero", zatem je�eli w&nbsp;wyniku
 * wykonania jakiej� operacji otrzymamy wynik "zero" mo�e si� on
 * okaza� liczb� o&nbsp;bardzo ma�ym (ale r�nym od zera) module
 * i&nbsp;w�wczas zostanie potraktowana jako warto�� logiczna prawda.
 * Z&nbsp;tego powodu, aby zamieni� wynik wyra�enia na warto��
 * logiczn� nale�y skorzysta� z "niewyra�nych" operator�w por�wnania.
 * Operatory logiczne zwracaj� 1.0 w&nbsp;przypadku prawdy i 0.0
 * w przypadku fa�szu.
 *
 * <h4>Zmienne i&nbsp;sta�e</h4>
 *
 * W&nbsp;kalkulatorze istniej� trzy rodzaje "zmiennych": zmienne
 * lokalne, zmienne globalne oraz sta�e.  Do zmiennych lokalnych
 * odwo�ujemy si� podaj�c ich nazw�, do zmiennych globalnych
 * poprzedzaj�c nazw� znakiem dolara, a&nbsp;do sta�ych poprzedzaj�c
 * nazw� znakiem hash.
 *
 * Zmiennym (i&nbsp;sta�ym) warto�ci przypisuje si� za pomoc� jednego
 * z&nbsp;operator�w przypisania.  Pr�ba przypisania warto�ci do
 * sta�ej powoduje b��d.  Odczyt z&nbsp;niezdefiniowanej zmiennej
 * zwraca warto�� zero.
 *
 * Podzia� na zmienne lokalne i&nbsp;globalne zaczynaj� mie� znaczenie
 * dopiero przy definiowaniu funkcji.  O&nbsp;zmiennych lokalnych
 * wi�cej w&nbsp;dziale po�wi�conym <a
 * href="#define_function">funkcjom u�ytkownika</a>.
 *
 * Warto zauwa�y�, i� przestrzenie nazw zmiennych i sta�ych s�
 * roz��czne.  Ponadto ka�de wywo�anie <a
 * href="#define_function">funkcji u�ytkownika</a> powoduje stworzenie
 * nowej przestrzeni nazw zmiennych lokalnych.  R�wnie� funkcje
 * posiadaj� osobn� przestrze� nazw.
 *
 * W&nbsp;programie zdefiniowane s� nast�puj�ce sta�e:
 *
 * <table>
 *     <tr>
 *       <th>Nazwa</th>
 *       <th>Opis</th>
 *     </tr>
 *     <tr>
 *       <td><tt>e</tt></td>
 *       <td>Baza logarytmu naturalnego, granica
 *         ci�gu <tt>(1+1/n)<sup>n</sup></tt>.</td>
 *     </tr>
 *     <tr>
 *       <td><tt>log2e</tt></td>
 *       <td>Logarytm o&nbsp;podstawie dwa z&nbsp;e.</td>
 *     </tr>
 *     <tr>
 *       <td><tt>log10e</tt></td>
 *       <td>Logarytm o&nbsp;podstawie dziesi�� z&nbsp;e.</td>
 *     </tr>
 *     <tr>
 *       <td><tt>ln2</tt></td>
 *       <td>Logarytm naturalny z&nbsp;dw�ch.</td>
 *     </tr>
 *     <tr>
 *       <td><tt>ln10</tt></td>
 *       <td>Logarytm naturalny z&nbsp;dzisi�ciu.</td>
 *     </tr>
 *     <tr>
 *       <td><tt>pi</tt></td>
 *       <td>Liczba Pi, stosunek obwodu okr�gu do jego �rednicy</td>
 *     </tr>
 *     <tr>
 *       <td><tt>pi_2</tt></td>
 *       <td>Po�owa warrto�ci liczby Pi.</td>
 *     </tr>
 *     <tr>
 *       <td><tt>pi_4</tt></td>
 *       <td>Czwarta cz�� warto�ci liczby Pi.</td>
 *     </tr>
 *     <tr>
 *       <td><tt>_1_pi</tt></td>
 *       <td>Odwrotno�� liczby Pi, stosunek �rednicy ork�gu do jego
 *         obwodu.</td>
 *     </tr>
 *     <tr>
 *       <td><tt>_2_pi</tt></td>
 *       <td>Dwie odwrotno�ci liczby Pi (odwrotno�� po�owy Pi).</td>
 *     </tr>
 *     <tr>
 *       <td><tt>_2_sqrtpi</tt></td>
 *       <td>Dwie odwrotno�ci pierwiastka z&nbsp;liczby Pi.</td>
 *     </tr>
 *     <tr>
 *       <td><tt>sqrt2</tt></td>
 *       <td>Pierwiastek kwadratowy z&nbsp;dw�ch.</td>
 *     </tr>
 *     <tr>
 *       <td><tt>sqrt1_2</tt></td>
 *       <td>Odwrotno�� pierwiastka kwadratowego z&nbsp;dw�ch.</td>
 *     </tr>
 *     <tr>
 *       <td><tt>#</tt></td>
 *       <td>Numer iteracji (licz�c od zera) p�tli.</td>
 *     </tr>
 *     <tr>
 *       <td><tt>!</tt></td>
 *       <td>Rezultat ostatnio wyliczonego wyra�nia cia�a p�tli.</td>
 *     </tr>
 * </table>
 *
 * W&nbsp;programie zdefiniowane s� nast�puj�ce funkcje wbudowane
 * (zale�nie od �rodowiska z&nbsp;jakim kalkulator by� kompilowane
 * niekt�re mog� nie wyst�powa�; aby pozna� list� funkcji nale�y
 * skorzysta� z&nbsp;prze��cznika <tt>-f</tt>):
 *
 * <table>
 *     <tr>
 *       <th>Nazwa(argumenty)</th>
 *       <th>Opis</th>
 *     </tr>
 *     <tr>
 *       <td><tt>sqrt(x)</tt></td>
 *       <td>Zwraca pierwiastek kwadratowy argumenty.</td>
 *     </tr>
 *     <tr>
 *       <td><tt>cbrt(x)</tt></td>
 *       <td>Zwraca pierwiastek sze�cienny argumentu.</td>
 *     </tr>
 *     <tr>
 *       <td><tt>e(x)</tt></td>
 *       <td>Synonim <tt>exp(x)</tt>.</td>
 *     </tr>
 *     <tr>
 *       <td><tt>exp(x)</tt></td>
 *       <td>Zwraca liczb� <tt>e</tt> podniesion� do pot�gi <tt>x</tt>
 *         (<tt>e<sup>x</sup></tt>).</td>
 *     </tr>
 *     <tr>
 *       <td><tt>log(x)</tt></td>
 *       <td>Zwraca logarytm naturalny z&nbsp;argumentu.</td>
 *     </tr>
 *     <tr>
 *       <td><tt>log(x,y)</tt></td>
 *       <td>Zwraca logarytm o&nbsp;podstawie <tt>y</tt>
 *         z&nbsp;<tt>x</tt>.</td>
 *     </tr>
 *     <tr>
 *       <td><tt>ln(x)</tt></td>
 *       <td>Synonim <tt>ln(x)</tt>.</td>
 *     </tr>
 *     <tr>
 *       <td><tt>log10(x)</tt></td>
 *       <td>Zwraca logarytm o&nbsp;podstawie dziesi�c
 *         z&nbsp;argumentu.</td>
 *     </tr>
 *     <tr>
 *       <td><tt>log2(x)</tt></td>
 *       <td>Zwraca logarytm o&nbsp;podstawie dwa z&nbsp;argumentu.</td>
 *     </tr>
 *     <tr>
 *       <td><tt>cos(x)</tt></td>
 *       <td>Zwraca cosinus argumentu (podanego w&nbsp;radianach).</td>
 *     </tr>
 *     <tr>
 *       <td><tt>sin(x)</tt></td>
 *       <td>Zwraca inus argumentu (podanego w&nbsp;radianach).</td>
 *     </tr>
 *     <tr>
 *       <td><tt>tan(x)</tt></td>
 *       <td>Zwraca tangens argumentu (podanego w&nbsp;radianach).</td>
 *     </tr>
 *     <tr>
 *       <td><tt>acos(x)</tt></td>
 *       <td>Zwraca arcus cosinus (podany w&nbsp;radianach) argumentu.</td>
 *     </tr>
 *     <tr>
 *       <td><tt>asin(x)</tt></td>
 *       <td>Zwraca arcus sinus (podany w&nbsp;radianach) argumentu.</td>
 *     </tr>
 *     <tr>
 *       <td><tt>atan(x)</tt></td>
 *       <td>Zwraca arcus tangens (podany w&nbsp;radianach) argumentu.</td>
 *     </tr>
 *     <tr>
 *       <td><tt>atan(x,y)</tt></td>
 *       <td>Zwraca arcus tangens (podany w&nbsp;radianach) ilorazu
 *         argument�w bior�c pod uwag� ich znaki dzi�ki czemu mo�e
 *         zwr�ci� warto�� z&nbsp;ca�ej dziedziny funkcji tangens.</td>
 *     </tr>
 *     <tr>
 *       <td><tt>cosh(x)</tt></td>
 *       <td>Zwraca cosinus hiperboliczny argumentu (<tt>(e<sup>x</sup> +
 *           e<sup>-x</sup>)/2</tt>).</td>
 *     </tr>
 *     <tr>
 *       <td><tt>sinh(x)</tt></td>
 *       <td>Zwraca sinus hiperboliczny argumentu (<tt>(e<sup>x</sup> -
 *           e<sup>-x</sup>)/2</tt>).</td>
 *     </tr>
 *     <tr>
 *       <td><tt>tanh(x)</tt></td>
 *       <td>Zwraca tangens hiperboliczny argumentu (<tt>(e<sup>x</sup> -
 *           e<sup>-x</sup>)/(e<sup>x</sup> + e<sup>-x</sup>)</tt>).</td>
 *     </tr>
 *     <tr>
 *       <td><tt>acosh(x)</tt></td>
 *       <td>Odwrotno�� <tt>cosh</tt>.</td>
 *     </tr>
 *     <tr>
 *       <td><tt>asinh(x)</tt></td>
 *       <td>Odwrotno�� <tt>sinh</tt>.</td>
 *     </tr>
 *     <tr>
 *       <td><tt>atanh(x)</tt></td>
 *       <td>Odwrotno�� <tt>tanh</tt>.</td>
 *     </tr>
 *     <tr>
 *       <td><tt>min(...)</tt></td>
 *       <td>Zwraca najmniejszy z&nbsp;argument�w.</td>
 *     </tr>
 *     <tr>
 *       <td><tt>max(...)</tt></td>
 *       <td>Zwraca najwi�kszy z&nbsp;argument�w.</td>
 *     </tr>
 *     <tr>
 *       <td><tt>avg(...)</tt></td>
 *       <td>Zwraca �redni� arytmtyczn� z&nbsp;argument�w.</td>
 *     </tr>
 *     <tr>
 *       <td><tt>braek(x) break(x, n)</tt></td>
 *       <td>Ucieka z <tt>n</tt> (domy�lnie jeden) poziom�w instrukcji
 *         p�tli jako wynik instrukcji daj�c <tt>x</tt>.  Je�eli
 *         n jest mniejsze od jednej czwartej po prostu zwraca
 *         <tt>x</tt>.</td>
 *     </tr>
 *     <tr>
 *       <td><tt>return(x) return(x, n)</tt></td>
 *       <td>Ucieka z <tt>n</tt> (domy�lnie jeden) poziom�w wywo�a�
 *         funkcji u�ytkownika daj�c <tt>x</tt>.  Je�eli n jest
 *         mniejsze od jednej czwartej po prostu zwraca
 *         <tt>x</tt>.</td>
 *     </tr>
 *     <tr>
 *       <td><tt>print(x) p(x)</tt></td>
 *       <td>Wypisuje na standardowe wyj�cie warto�� <tt>x</tt>
 *         i&nbsp;zwraca j�.  Warto�� jest wypisana bez jakichkolwiek
 *         bia�ych znak�w wok� niej.</td>
 *     </tr>
 * </table>
 *
 * <h4>Wywo�ywanie funkcji</h4>
 *
 * Aby wywo�a� funkcj� nale�y po jej nazwie wypisa� w&nbsp;nawiasach
 * okr�g�ych jej argumenty.  Je�eli funkcja nie przyjmuje argument�w
 * nale�y wypisa� puste nawiasy.
 *
 * Wywo�anie niezdefiniowanej funkcji lub wywo�anie funkcji
 * z nieprawid�ow� liczb� argument�w spowoduje b��d.
 *
 * <h4 id="define_function">Funkcje u�ytkownika</h4>
 *
 * Funkcje definiuje si� za pomoc� konstrukcji <tt>define
 * nazwa(argumenty) = wyra�enie</tt>, gdzie <tt>argumenty</tt> to
 * lista (mo�e by� pusta) nazw argument�w funkcji oddzielonych
 * przecinkami, a&nbsp;wyra�enie, to operacje jakie maj� si� wykona�
 * w&nbsp;momencie wywo�ania funkcji, np.:
 *
 * <pre>define add1(x) = x + 1
 *add1(10)
 *<i>11</i></pre>
 *
 * Backslash na ko�cu linii powoduje "sklejenie" linii z&nbsp;nast�pn�
 * dzi�ki czemu definicje d�ugich funkcji mo�na dzieli� na cz�ci.
 * Ponadto, operator przecinek powoduje "zjadanie" bia�ych znak�w
 * znajduj�cych si� za nim, np.:
 *
 * <pre>define sqsump1(x, y) = z = x + y,
 *z^2 \
 *+ 1
 *sqsump1(1,2)
 *<i>10</i></pre>
 *
 * Przy ka�dym wywo�aniu funkcji tworzona jest nowa przestrze�
 * zmiennych lokalnych dzi�ki czemu funkcje mog� stosowa� przer�ne
 * zmienne bez obaw, i� spowoduje to b��dne dzia�anie innych funkcji,
 * np.:
 *
 * <pre>x = 10;
 *define foo() = x = 20, x + 1
 *define bar() = x = 20, x + $x
 *x
 *<i>10</i>
 *foo()
 *<i>21</i>
 *bar()
 *<i>30</i></pre>
 *
 * Dzi�ki obecno�ci operatora warunkowego mo�na definiowa� funkcje
 * rekurencyjne, np.:
 *
 * <pre>define fib(x) = x &gt;= 2 ? fib(x-1) + fib(x-2) : x
 *fib(10)
 *<i>55</i></pre>
 *
 * Definicja ju� istniej�cej funkcji (r�wnie� wbudowanej) powoduje
 * zamazanie dotychczasowej definicji na rzecz nowej.  Pozwala to
 * poprawia� b��dy bez konieczno�ci restartu �rodowiska ani wymy�lania
 * za ka�dym razem nowych nazw.
 *
 * <h2>Implementacja</h2>
 *
 * <h3>�rodowisko</h3>
 *
 * �rodowisko (ang. \link calc::Environment Environment\endlink)
 * przechowuje zdefiniowane zmienne, sta�e i funkcje oraz nadzoruje
 * wykonywanie wyra�e� (tzn. obs�uguje ewentualne wyj�tki, kt�re
 * wyra�enie mo�e rzuci� oraz udost�pnia wyra�eniom metody dost�pu do
 * zmiennych, sta�ych i funkcji).  Klasa ta odpowiada r�wnie� za
 * tworzenie nowych przestrzeni zmiennych lokalnych.
 *
 * <h3>Wyra�enia</h3>
 *
 * Wszystkie wyra�enia dziedzicz� po abstrakcyjnej klasie \link
 * calc::Expression Expression\endlink i udost�pniaj� metod� \link
 * calc::Expression::execute() execute()\endlink, kt�ra wykonuje ona
 * dane wyra�enie w kontek�cie danego �rodowiska.  Zasadniczo ka�dy
 * operator posiada odpowiadaj�c� mu klas� \link calc::Expression
 * Expression\endlink.
 *
 * <h3>Funkcje</h3>
 *
 * Funkcje dziedzicz� po klasie \link calc::Function Function\endlink,
 * kt�ra udost�pnia metod� \link calc::Function::execute()
 * execute()\endlink s�u��c� do wykonania funkcji w kontek�cie danego
 * �rodowiska z danymi argumentami.  Funkcje wbudowane nie wprowadzaj�
 * nowej przestrzeni nazw, gdy� wykonywane s� w kodzie C++, jednak
 * funkcje u�ytkownika (dziedzicz�ce po klasie \link
 * calc::UserFunction UserFunction\endlink) tworz�, gdy� sprowadzaj�
 * si� do zwyk�ego wywo�ania wyra�enie w nowym kontek�cie.
 *
 * <h3>Lekser</h3>
 *
 * Konkretna instancja leksera dziedziczy po abstrakcyjnej klasie
 * \link calc::Lexer Lexer\endlink (idea jest taka, �e w ten spos�b
 * mo�na definiowa� r�ne leksery pobieraj�ce dane z r�nych �r�de�).
 * W programie zdefiniowany jest tylko jedna taka klasa: \link
 * calc::FILELexer FILELexer\endlink.  Czyta ona dane z pliku (lub
 * standardowego wej�cia).
 *
 * Metod�, kt�ra zwraca kolejne tokeny jest \link
 * calc::Lexer::nextToken() nextToken()\endlink.  Dla token�w
 * jednoznakowych zwraca kod ASCII danego znaku, a dla bardziej
 * z�o�onych jedn� z warto�ci definiowanych w typie \link
 * yy::Parser::token::yytokentype Parser::token::yytokentype\endlink.
 *
 * Informacje towarzysz�ce tokenom takim jak \link
 * yy::Parser::token::ID ID\endlink (identyfikator), \link
 * yy::Parser::token::STRING STRING\endlink (ci�g znak�w), \link
 * yy::Parser::token::NUMBER NUMBER\endlink (liczba), a tak�e \link
 * yy::Parser::token::SET_OP SET_OP\endlink (operatory przypisania),
 * \link yy::Parser::token::REL_OP REL_OP\endlink (operatory relacji)
 * i \link yy::Parser::token::CMP_OP CMP_OP\endlink (operatory
 * przyr�wnania) przekazywane s� poprzez uni� \link
 * yy::Parser::semantic_type Parser::semantic_type\endlink.
 *
 * Dodatkowo, lekser zapisuje w strukturze typu \link yy::location
 * location\endlink po�o�enie w strumieniu wej�ciowym, gdzie dany
 * token zosta� napotkany, co jest przydatne g��wnie przy wypisywaniu
 * komunikat�w b��d�w.
 *
 * Przyk�adowo, gdyby lekser napotka� ci�g <tt>define seven() = 1 + 2
 * * 3</tt> wygenerowa�by nast�puj�ce tokeny: \link
 * yy::Parser::token::DEFINE DEFINE\endlink, \link
 * yy::Parser::token::ID ID\endlink z warto�ci� <tt>seven</tt>, '(',
 * ')', '=', \link yy::Parser::token::NUMBER NUMBER\endlink
 * z warto�ci� <tt>1</tt>, '+', \link yy::Parser::token::NUMBER
 * NUMBER\endlink z warto�ci� <tt>2</tt>, '*' oraz \link
 * yy::Parser::token::NUMBER NUMBER\endlink z warto�ci� <tt>3</tt>.
 *
 * <h3>Parser</h3>
 *
 * Parser budowany jest za pomoc� programu <tt>bison</tt>.  W trakcie
 * odczytywania wyra�enia tworzy on odpowiednie obiekty klas
 * z hierarchii rozpoczynaj�cej si� od klasy \link calc::Expression
 * Expression\endlink.  Gdy wyra�enie takie ma zosta� wykonane
 * wywo�ywana jest metoda \link calc::Environment::execute()
 * Environment::execute()\endlink, kt�ra wo�a metod� \link
 * calc::Expression::execute() Expression::execute()\endlink,
 * obs�uguje rzucone wyj�tki itp.
 *
 * Je�eli parser napotka na definicj� funkcji u�ytkownika, wywo�uje
 * metod� \link calc::Environment::addUserFunction()
 * Environment::addUserFunction()\endlink, kt�ra dodaje odpowiedni
 * wpis w mapie funkcji zdefiniowanych w �rodowisku.
 *
 * Przyk�adowo, je�eli parser napotka na ci�g <tt>1 + 2 * 3</tt>,
 * w kolejnych krokach b�d� budowane nast�puj�ce obiekty:
 *
 * <ul>
 *   <li><tt>_1 = new \link calc::NumberExpression NumberExpression\endlink(1)</tt></li>
 *   <li><tt>_2 = new \link calc::NumberExpression NumberExpression\endlink(2)</tt></li>
 *   <li><tt>_3 = new \link calc::NumberExpression NumberExpression\endlink(3)</tt></li>
 *   <li><tt>_m = new \link calc::MulExpression MulExpression\endlink(_2, _3)</tt></li>
 *   <li><tt>_a = new \link calc::AddExpression AddExpression\endlink(_1, _m)</tt></li>
 * </ul>
 *
 * Gdyby takie wyra�enie mia�o zosta� wykonane (tzn. po tym nast�pi�by
 * znak przej�cia do nowej linii lub �rednik) parser wywo�a�by metod�
 * \link calc::Environment::execute() Environment::execute()\endlink
 * z podanym jako argumentem wyra�eniem <tt>_a</tt>.
 *
 * Gdyby jednak tekst ten by� poprzedzony ci�giem <tt>define seven()
 * =</tt> zosta�aby zdefiniowana funkcja u�ytkownika poprzez wywo�anie
 * <tt>\link calc::Environment::addUserFunction
 * Environment::addUserFunction\endlink("seven", _argument_names,
 * _a)</tt> (gdzie <tt>_arguments</tt> by�oby pustym wektorem (funkcja
 * nie posiada argument�w)).
 *
 */




/**
 * A "Verbose" environment which prints result of each
 * instruction.
 */
struct VerboseEnvironment : public calc::Environment {
	/** \copydoc calc::Environment::Environment(real,real) */
	explicit VerboseEnvironment(calc::real p, calc::real fp)
		: Environment(p, fp) { }

	void instruction(calc::real value) {
		std::cout << value << '\n';
	}
};


/** Prints help. */
static void help();
/** Prints syntax help. */
static void helpSyntax();
/** Printsss list of built-in functions. */
static void listFunc();
/** Prints list of built-in constants. */
static void listConst();
/** Prints list of operators. */
static void listOp();


static calc::real parsePrecision(int argc, char **argv, int &i, char *&ch) {
	if (*++ch) {
		/* nothing */
	} else if (++i < argc) {
		ch = argv[i];
	} else {
		std::cerr << "precision expected\n";
		return 1;
	}

	char *end;
	errno = 0;
	calc::real precision = calc::m::ator(ch, &end);
	if (precision < 0 || errno || *end) {
		std::cerr << ch << ": invalid precision\n";
		return 1;
	}
	ch = end - 1;

	return precision;
}


int main(int argc, char **argv) {
	bool verbose = false, quiet = false, finish = false;
	calc::real precision = 0, fprecision = 1e-9;
	char *filename = 0;

	int i = 1;
	for (; i < argc && argv[i][0] == '-' && argv[i][1]; ++i) {
		if (argv[i][1] == '-' && argv[i][2] == 0) {
			++i;
			break;
		}

		for (char *ch = argv[i]; *++ch; ) {
			switch (*ch) {
			case 'v': verbose = true;               break;
			case 'q': quiet   = true;               break;
			case 'h': finish  = true; help();       break;
			case 's': finish  = true; helpSyntax(); break;
			case 'f': finish  = true; listFunc();   break;
			case 'c': finish  = true; listConst();  break;
			case 'o': finish  = true; listOp();     break;
			case 'p': fprecision = parsePrecision(argc, argv, i, ch); break;
			case 'P':  precision = parsePrecision(argc, argv, i, ch); break;
			default:
				std::cerr << "invalid option: " << *ch << '\n';
				return 1;
			}
		}
	}

	switch (argc - i) {
	case 1: filename = argv[i];
	case 0: break;
	default:
		std::cerr << "unexpected argument: " << argv[i+1] << '\n';
		return 1;
	}

	if (finish) {
		return 0;
	}


	/* Create environment. */
	calc::Environment *env = verbose
		? new VerboseEnvironment(precision, fprecision)
		: new calc::Environment(precision, fprecision);
	/* So we won't have to bother freeing */
	std::auto_ptr<calc::Environment> _env(env);


	/* Register constants */
	{
		calc::Environment::Variables &consts = env->constants();
		consts["e"]         = 2.7182818284590452353602874713526625l;
		consts["log2e"]     = 1.4426950408889634073599246810018921l;
		consts["log10e"]    = 0.4342944819032518276511289189166051l;
		consts["ln2"]       = 0.6931471805599453094172321214581766l;
		consts["ln10"]      = 2.3025850929940456840179914546843642l;
		consts["pi"]        = 3.1415926535897932384626433832795029l;
		consts["pi_2"]      = 1.5707963267948966192313216916397514l;
		consts["pi_4"]      = 0.7853981633974483096156608458198757l;
		consts["_1_pi"]     = 0.3183098861837906715377675267450287l;
		consts["_2_pi"]     = 0.6366197723675813430755350534900574l;
		consts["_2_sqrtpi"] = 1.1283791670955125738961589031215452l;
		consts["sqrt2"]     = 1.4142135623730950488016887242096981l;
		consts["sqrt1_2"]   = 0.7071067811865475244008443621048490l;
	}


	/* Register functions */
	{
		calc::Environment::Functions &funcs = env->functions();
		funcs["sqrt"  ] = calc::builtin::sqrt::get();
		funcs["cbrt"  ] = calc::builtin::cbrt::get();
		funcs["e"     ] = calc::builtin::exp::get();
		funcs["exp"   ] = calc::builtin::exp::get();
		funcs["log"   ] = calc::builtin::log::get();
		funcs["ln"    ] = calc::builtin::log::get();
		funcs["log10" ] = calc::builtin::log10::get();
		funcs["log2"  ] = calc::builtin::log2::get();
		funcs["cos"   ] = calc::builtin::cos::get();
		funcs["sin"   ] = calc::builtin::sin::get();
		funcs["tan"   ] = calc::builtin::tan::get();
		funcs["acos"  ] = calc::builtin::acos::get();
		funcs["asin"  ] = calc::builtin::asin::get();
		funcs["atan"  ] = calc::builtin::atan::get();
		funcs["cosh"  ] = calc::builtin::cosh::get();
		funcs["sinh"  ] = calc::builtin::sinh::get();
		funcs["tanh"  ] = calc::builtin::tanh::get();
		funcs["acosh" ] = calc::builtin::acosh::get();
		funcs["asinh" ] = calc::builtin::asinh::get();
		funcs["atanh" ] = calc::builtin::atanh::get();
		funcs["min"   ] = calc::builtin::min::get();
		funcs["max"   ] = calc::builtin::max::get();
		funcs["avg"   ] = calc::builtin::avg::get();
		funcs["break" ] = calc::builtin::Break::get();
		funcs["return"] = calc::builtin::Return::get();
		funcs["print" ] = calc::builtin::print::get();
		funcs["p"     ] = calc::builtin::print::get();
		funcs["read"  ] = calc::builtin::read::get();
		funcs["r"     ] = calc::builtin::read::get();
	}


	/* Run */
	calc::FILELexer lexer(filename);
	env->setReadLexer(filename ? new calc::FILELexer() : &lexer);
	yy::Parser parser(lexer, *env);
	parser.parse();

	if (env->getReadLexer() != &lexer) {
		delete env->getReadLexer();
	}
	env->setReadLexer(0);


	/* Print variables */
	if (!quiet) {
		calc::Environment::Variables::const_iterator
			it = env->global().begin(), end = env->global().end();
		for (; it != end; ++it) {
			if (it->first[0] != '_') {
				std::cout << it->first << " = " << it->second << '\n';
			}
		}
	}


	/* Finish */
	return 0;
}



static void help() {
	std::cout <<
		"usage: ./calc [-vqhsofc] [filename]\n"
		"  -v     print result of each instruction terminated with a new line\n"
		"  -q     do not print values of all global variables at the end\n"
		"  -p<p>  set fuzzy comparison precision to <p>; default 1e-9\n"
		"  -P<p>  set arithemtic comparison precision to <p>; default 0\n"
		"  -h     print this help screen and exit\n"
		"  -s     print syntax\n"
		"  -o     print list of oeprators and exit\n"
		"  -f     print list of built-in functions and exit\n"
		"  -c     print list of built-in constants and exit\n";
}


static void helpSyntax() {
	std::cout <<
"Calculator reads in-fix expressions (similar to C) from standard\n"
"input.  Expressions may end with a semicolon or a new line.  In the\n"
"later case if a -v switch was given expression's result will be\n"
"printed.\n"
"\n"
"To access a variable simply state its name.  It will refer to local\n"
"variable (see functions below).  To refer to global variable prefix it\n"
"with a dolar sign ('$') and to refer to a constant prefix it with\n"
"a hash ('#').\n"
"\n"
"To call a function simply put it name followd by a comma-separated\n"
"list of arguments in parens.  If function takes no arguments you must\n"
"still put empty parens.\n"
"\n"
"To define a user function use the 'define' keyword, as follows:\n"
"  define name(arg1, arg2, arg3) = expression\n"
"\n"
"When user function is called expression that defines it is called in\n"
"a separate scope with it's own local variables.\n"
"\n"
"If you end a line by a single slash the new line character is ignored\n"
"and the next line is treated as continuation of the current one.  Also\n"
"all white space (including new lines) after a comma are ignored.\n"
"\n"
"If you call a non-existant function or assign value to already defined\n"
"constant an error is triggered and the state of the enviroment is\n"
"undefined (ie. parts of the expressions may have been executed).\n"
"\n"
"You can put a string surrounded by quotes or apostrophes.  Such\n"
"a string is printed and evaluates to one.\n";
}


static void listFunc() {
	std::cout << "Available funxtions:\n"
		"  sqrt(x)     returns square root of x\n"
		"  cbrt(x)     returns cube root of x\n"
		"  e(x)        synonym of exp(x)\n"
		"  exp(x)      returns e raised to the power of x\n"
		"  log(x)      returns the natural logarithm of x\n"
		"  log(x,y)    returns base y logarithm of x\n"
		"  ln(x)       synonym of log(x)\n"
		"  log10(x)    returns base 10 logarithm of x\n"
		"  log2(x)     returns base 2 logarithm of x\n"
		"  cos(x)      returns cosine of x (given in radians)\n"
		"  sin(x)      returns sine of x (given in radians)\n"
		"  tan(x)      returns tangent of x (given in radians)\n"
		"  acos(x)     returns arc cosine of x (given in radians)\n"
		"  asin(x)     returns arc sine of x (given in radians)\n"
		"  atan(x)     returns arc tangent of x (given in radians)\n"
		"  atan(x,y)   returns arc tangent of y/x (given in radians)\n"
		"  cosh(x)     returns hyperbolic cosine of x\n"
		"  sinh(x)     returns hyperbolic sine of x\n"
		"  tanh(x)     returns hyperbolic tangent od x\n"
		"  acosh(x)    an inverse of cosh\n"
		"  asinh(x)    an inverse of sinh\n"
		"  atanh(x)    an inverse of tanh\n"
		"  min(...)    returns smallest argument\n"
		"  max(...)    returns biggest argument\n"
		"  avg(...)    returns average of arguments\n"
		"  break(x)    breaks from a loop with x as expression's value\n"
		"  break(x,n)  breaks from n loops with x as expression's value\n"
		"  return(x)   breaks from a function with x as return value\n"
		"  return(x,n) breaks from n functions with x as return value\n"
		"  print(x)    prints x\n"
		"  p(x)        synonym od print(x)\n"
		"  read()      reads a number from standard input (experimental)\n"
		"  r()         synonym of read()\n";
}


static void listConst() {
	std::cout << "Available constants:\n"
		"  e         base of a natural logarithm\n"
		"  log2e     a base 2 logarithm of e\n"
		"  log10e    a base 10 logarithm of e\n"
		"  ln2       a natural logarithm of 2\n"
		"  ln10      a natural logarithm of 10\n"
		"  pi        Pi\n"
		"  pi_2      Pi/2\n"
		"  pi_4      Pi/4\n"
		"  _1_pi     1/Pi\n"
		"  _2_pi     2/Pi\n"
		"  _2_sqrtpi 2/sqrt(Pi)\n"
		"  sqrt2     square root of 2\n"
		"  sqrt1_2   1/sqrt(2)\n"
		;
}


static void listOp() {
	std::cout << "Available operators (from highest priority):\n"
		"  Prefix          + - !              right-to-left\n"
		"  Power           ^                  right-to-left\n"
		"  Multiplicative  * / %              left-to-right\n"
		"  Additive        + -                left-to-right\n"
		"  Relation        > < >= <= >~ <~    left-to-right\n"
		"  Compare         == != =~ !~        left-to-right\n"
		"  Logic and       &&                 left-to-right\n"
		"  Logic xor       ^^                 left-to-right\n"
		"  Logic or        ||                 left-to-right\n"
		"  Ternary         ?: @: #:           right-to-left\n"
		"  Assigment       = += -= *= /= ^=   right-to-left\n"
		"  Comma           ,                  left-to-right\n";
}
