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
 * <h2>Tre�� zadania</h2>
 *
 * Napisa� program kalkulatora dla liczb rzeczywistych.  Dzia�ania:
 * dodawanie, odejmowanie, mno�enie, dzielenie, podnoszenie do pot�gi,
 * funkcje trygonometryczne, funkcje logarytmiczne.  Priorytety
 * operacji naturalne (tzn. mno�enie przed dodawaniem). Istnieje
 * mo�liwo�� u�ycia nawias�w do zmiany priorytet�w.  Mo�liwo��
 * deklarowania i&nbsp;u�ywania zmiennych oraz definiowania funkcji.
 * Dane czytane ze strumienia wej�ciowego.  Wynikiem jest warto��
 * u�ytych zmiennych.
 *
 * <h2>Opis u�ycia</h2>
 *
 * <h3>Spos�b uruchomienia</h3>
 *
 * Program wczytuje wyra�enia ze standardowego wej�cia i&nbsp;wypisuje
 * wyniki na standardowe wyj�cie.  Przy domy�lnych opcjach milczy, a�
 * do momentu, gdy dane wej�ciowe si� zako�cz� i&nbsp;w�wczas wypisuje
 * warto�ci wszystkich zmiennych i&nbsp;ko�czy dzia�anie.
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
 * b�d� por�wnywa� zmienne.  Domy�lnie dok�adno�ci� jest zero,
 * tzn. dwie warto�ci "s� sobie r�wne" je�eli "s� sobie r�wne".
 * Prze��czniki te wp�ywa r�wnie� na operatory relacji, ale nie
 * wp�ywaj� na konwersje liczby na warto�� logiczn�.</p>
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
 * kt�re znajduj� si� za nim.  To w&nbsp;jaki spos�b instrukcja si�
 * ko�czy ma znaczenie, je�eli podana zosta�a opcja <tt>-v</tt>.
 *
 * Instrukcj� mo�e by� albo wyra�enie, kt�re jest wyliczane
 * natychmiast po wczytaniu, albo <a href="#define_function">funkcj�
 * u�ytkownika</a>.
 *
 * Wyra�enia zapisywane s� w&nbsp;formacie infiksowej (tzn. naturalnym
 * zapisie z&nbsp;operatorem pomi�dzy operandami).
 *
 * B��dy w&nbsp;sk�adni w&nbsp;odczytywanych instrukcjach powoduj�
 * wypisanie odpowiedniego komunikatu b��du.  B��dy w&nbsp;trakcie
 * wykonywania wyra�enia (np. przypisanie warto�ci do istniej�cej
 * sta�ej, wo�anie nieistniej�cej funkcji) powoduj� wypisanie
 * komunikatu, ale r�wnie� i� stan �rodowiska jest niezdefiniowany,
 * tzn. nie jest okre�lone, kt�re z&nbsp;wyra�e� zosta�y wykonane,
 * a&nbsp;kt�re nie.
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
 *     <td><tt>* /</tt></td>
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
 *     <td><tt>== != ~~ =~ !~</tt></td>
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
 *     <td>Operator warunkowy</td>
 *     <td><tt>?:</tt></td>
 *     <td>z prawej do lewej</td>
 *   </tr>
 *   <tr>
 *     <td>Przypisanie</td>
 *     <td><tt>= += -= *= /= ^=</tt></td>
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
 * Operator <tt>^</tt> oraz <tt>^=</tt> s� to operatory pot�gowe.
 *
 * Operatory <tt>~~</tt>, <tt>=~</tt>, <tt>!~</tt>, <tt>~&gt;</tt>,
 * <tt>~&lt;</tt>, <tt>&gt;~</tt> oraz <tt>&lt;~</tt> s�
 * "niewyra�nymi" (ang. fuzzy) odpowiednikami operator�w odpowiednio
 * <tt>==</tt>, <tt>==</tt>, <tt>!=</tt>, <tt>&gt;</tt>,
 * <tt>&lt;</tt>, <tt>&gt;=</tt> oraz <tt>&lt;=</tt>.  Wi�cej
 * o&nbsp;tych operatorach przy okazji opisywania <a
 * href="#przelacznik_p">prze��cznika <tt>-p</tt></a>.
 *
 * Operator <tt>^^</tt> oznacza logiczny XOR i&nbsp;zasadniczo <tt>a
 * ^^ b</tt> jest r�wnowa�ne <tt>!a != !b</tt>.
 *
 * Nale�y zwr�ci� uwag� na operatory logiczne oraz operatory, kt�re
 * jako operandy przyjmuj� warto�ci logiczne.  W&nbsp;kalkulatorze
 * zmienna ma warto�� logiczn� fa�sz wtedy i&nbsp;tylko wtedy, gdy
 * jest r�wna zero.  Trzeba zwr�ci� uwag�, �e to co "wygl�da jak zero"
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
 * Zmienne lokalne i&nbsp;globalne zaczynaj� mie� znaczenie dopiero
 * przy definiowaniu funkcji, je�eli wpisujemy wyra�enia bezpo�rednio
 * s� one uto�samiane.  O&nbsp;zmiennych lokalnych wi�cej
 * w&nbsp;dziale po�wi�conym <a href="#define_function">funkcjom
 * u�ytkownika</a>.
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
 * lista (mo�e by� p�sta) nazw argument�w funkcji oddzielonych
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
 * Kalkulator korzysta z programu <tt>bison</tt> do wygenerowania, na
 * podstawie stworzonego pliku z&nbsp;opisem gramatyki, parsera wyra�e�.
 * Korzysta on z&nbsp;klasy FILELexer s�u��cej do dzielenia wczytywanych
 * danych na tokeny (klasa ta dziedziczy po klasie Lexer dzi�ki czemu
 * stosunkowo prosto mo�na napisa� inne leksery).
 *
 * W&nbsp;trakcie odczytu danych budowane jest drzewo dzia�a�, kt�rego
 * ka�dy w�ze� jest obiektem klasy dziedzicz�cej po klasie Expression.
 * Klasa ta deiniuje (mi�dzy innymi) abstrakcyjn� metod� wirtualn�
 * Expression::execute(), kt�ra implementowana przez konkretne klasy
 * wykonuje odpowiednie operacje na operandach.
 *
 * Operacje wykonywane s� wewn�trz �rodowiska definiowanego przez klas�
 * Environment.  Klasa ta przechowuje list� sta�ych
 * (Environment::_constants), funkcji (Environment::_functions) oraz
 * przestrzeni nazw zmiennych (Environment::_stack).  Taka klasa
 * umo�liwia, aby w&nbsp;jednym programie istnia�o kilka �rodowisk
 * i&nbsp;�eby to samo wyra�enie mog�o by� wykonywane w&nbsp;kilku
 * r�nych �rodowiskach.
 *
 * Klasa Environment definiuje kilka metod wirtualnych dzi�ki czemu
 * u�ytkownik mo�e napisa� w�asne metody formatuj�ce wypisywane dane.
 * W&nbsp;ten w�a�nie spos�b zosta� zaimplementowany
 * prze��cznik <tt>-v</tt> (zale�nie czy jest on obecny czy nie tworzony
 * jest obiekt jednej z&nbsp;dw�ch klas).
 *
 * Funkcje kalkulatora s� obiektami klasy pochodnej od klasy Function,
 * kt�ra definiuje (mi�dzy innymi) abstrakcyjn� metod� wirtualn�
 * Funcion::execute(Environment &env, const Arguments &args), kt�ra
 * powoduje wyliczenie jej warto�ci.  Funkcje wbudowana dziedzicz� po
 * klasie BuiltInFunction, a&nbsp;funkcje u�ytkownika s� obiektami klasy
 * UserFunction.
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

	if (i < argc) {
		std::cerr << "unexpected argument: " << argv[i] << '\n';
		return 1;
	}

	if (finish) {
		return 0;
	}


	/** Create environment. */
	calc::Environment *env = verbose
		? new VerboseEnvironment(precision, fprecision)
		: new calc::Environment(precision, fprecision);


	/* Register constants */
	{
		calc::Environment::Variables &consts = env->constants();
#if HAVE_LONG_DOUBLE
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
#else
		consts["e"]         = 2.7182818284590452354;
		consts["log2e"]     = 1.4426950408889634074;
		consts["log10e"]    = 0.4342944819032518276;
		consts["ln2"]       = 0.6931471805599453094;
		consts["ln10"]      = 2.3025850929940456840;
		consts["pi"]        = 3.1415926535897932384;
		consts["pi_2"]      = 1.5707963267948966192;
		consts["pi_4"]      = 0.7853981633974483096;
		consts["_1_pi"]     = 0.3183098861837906715;
		consts["_2_pi"]     = 0.6366197723675813430;
		consts["_2_sqrtpi"] = 1.1283791670955125739;
		consts["sqrt2"]     = 1.4142135623730950488;
		consts["sqrt1_2"]   = 0.7071067811865475244;
#endif
	}


	/* Register functions */
	{
		calc::Environment::Functions &funcs = env->functions();
		funcs["sqrt" ] = calc::Func_sqrt::get();
		funcs["cbrt" ] = calc::Func_cbrt::get();
		funcs["e"    ] = calc::Func_exp::get();
		funcs["exp"  ] = calc::Func_exp::get();
		funcs["log"  ] = calc::Func_log::get();
		funcs["ln"   ] = calc::Func_log::get();
		funcs["log10"] = calc::Func_log10::get();
		funcs["log2" ] = calc::Func_log2::get();
		funcs["cos"  ] = calc::Func_cos::get();
		funcs["sin"  ] = calc::Func_sin::get();
		funcs["tan"  ] = calc::Func_tan::get();
		funcs["acos" ] = calc::Func_acos::get();
		funcs["asin" ] = calc::Func_asin::get();
		funcs["atan" ] = calc::Func_atan::get();
		funcs["cosh" ] = calc::Func_cosh::get();
		funcs["sinh" ] = calc::Func_sinh::get();
		funcs["tanh" ] = calc::Func_tanh::get();
		funcs["acosh"] = calc::Func_acosh::get();
		funcs["asinh"] = calc::Func_asinh::get();
		funcs["atanh"] = calc::Func_atanh::get();
		funcs["min"  ] = calc::Func_min::get();
		funcs["max"  ] = calc::Func_max::get();
		funcs["avg"  ] = calc::Func_avg::get();
	}


	/* Run */
	calc::FILELexer lexer;
	yy::Parser parser(lexer, *env);
	parser.parse();


	/* Print variables */
	if (!quiet) {
		calc::Environment::Variables::const_iterator
			it = env->global().begin(), end = env->global().end();
		for (; it != end; ++it) {
			std::cout << it->first << " = " << it->second << '\n';
		}
	}


	/* Finish */
	delete env;
	return 0;
}



static void help() {
	std::cout <<
		"usage: ./calc [-vqhsofc]\n"
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
"undefined (ie. parts of the expressions may have been executed).\n";
}


static void listFunc() {
	std::cout << "Available funxtions:\n"
		"  sqrt(x)   returns square root of x\n"
		"  cbrt(x)   returns cube root of x\n"
		"  e(x)      synonym of exp(x)\n"
		"  exp(x)    returns e raised to the power of x\n"
		"  log(x)    returns the natural logarithm of x\n"
		"  log(x,y)  returns base y logarithm of x\n"
		"  ln(x)     synonym of log(x)\n"
		"  log10(x)  returns base 10 logarithm of x\n"
		"  log2(x)   returns base 2 logarithm of x\n"
		"  cos(x)    returns cosine of x (given in radians)\n"
		"  sin(x)    returns sine of x (given in radians)\n"
		"  tan(x)    returns tangent of x (given in radians)\n"
		"  acos(x)   returns arc cosine of x (given in radians)\n"
		"  asin(x)   returns arc sine of x (given in radians)\n"
		"  atan(x)   returns arc tangent of x (given in radians)\n"
		"  atan(x,y) returns arc tangent of y/x (given in radians)\n"
		"  cosh(x)   returns hyperbolic cosine of x\n"
		"  sinh(x)   returns hyperbolic sine of x\n"
		"  tanh(x)   returns hyperbolic tangent od x\n"
		"  acosh(x)  is an inverse of cosh\n"
		"  asinh(x)  is an inverse of sinh\n"
		"  atanh(x)  is an inverse of tanh\n"
		"  min(...)  returns smallest argument\n"
		"  max(...)  returns biggest argument\n"
		"  avg(...)  returns average of arguments\n";
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
		"  Prefix          + - !             right-to-left\n"
		"  Power           ^                 right-to-left\n"
		"  Multiplicative  * /               left-to-right\n"
		"  Additive        + -               left-to-right\n"
		"  Relation        > < >= <=         left-to-right\n"
		"  Compare         == !=             left-to-right\n"
		"  Logic and       &&                left-to-right\n"
		"  Logic xor       ^^                left-to-right\n"
		"  Logic or        ||                left-to-right\n"
		"  Ternary         ?:                right-to-left\n"
		"  Assigment       = += -= *= /= ^=  right-to-left\n"
		"  Comma           ,                 left-to-right\n";
}
