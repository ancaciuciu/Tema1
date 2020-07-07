***Anca-Maria CIUCIU***
***313 AB***
***Tema 1 SDA***

Pentru executarea cerintelor: 

- s-a folosit un vector care pastreaza valorile din fisierul cerinte.in
- 1 - se executa cerinta respectiva si se afiseaza output-ul 
- 0 - nu se executa si se afiseaza output-ul pana la acea cerinta
---
==CERINTA 1== 

*Scop: construirea listei dublu inlantuite, circulare, cu santinela;*

- au fost adaugate in structura informatiile din fisierul date.in
- cu ajutorul unui buffer s-a alocat memorie pentru campurile de tip sir de caractere
- aceasta structura s-a adaugat in lista circulara cu santinela cu ajutorul functiei **addCountry()** 
		
> aspectul listei: *head->prev ---> newNode --->  head*, HEAD este SANTINELA

- noul nod se va adauga de fiecare data la final

---
==CERINTA 2== 

*Scop: eliminarea unor tari din lista;*

- s-a folosit functia **removeNodes()**
	- se foloseste de un algoritm clasic de aflare a minimului
	- scorul initial s-a calculat cu ajutorul functiei **initialScore()** -medie aritmetica
	- eliminarea efectiva a tarii s-a realizat cu functia **removeCountry()**
- removeNodes() va fi apelata de un numar de ori egal cu numarul total de tari
din care se scade cea mai mare putere a lui 2 posibila calculata cu **closestPow2()**:

---
==CERINTA 3== 

*Scop: simularea jocului de tenis propriu-zis;*

- numarul de etape al jocului este egal cu logaritm in baza 2 din numarul de tari
- principala functie folosita pentru aceasta cerinta este **task3()**:
	- functia returneaza stiva WINNER
- se vor pune jucatorii din tara1 si tara2 intr-o coada, alternat
 - cei 2 jucatori extrasi din coada se vor confrunta cu ajutorul functiei **playGame()**:
 	- functia returneaza:
        	- 1  daca castiga primul jucator
        	- 2  daca castiga al doilea jucator 
        	- 0  daca e remiza
- in urma valorii returnate de playGame(), se vor actualiza punctajele
- in cazul in care cele 2 tari au acelasi scor local, se va folosi functia **bestPersonalScore()**:
	- returneaza cel mai mare scor personal dintr-o tara 
- la fiecare iteratie se va sterge stiva de tari complet pentru ca se doreste continuarea jocului cu tarile castigatoare
- prin urmare se vor adauga de fiecare data in stiva de tari, elementele (tarile) din stiva WINNER
- de asemenea, si stiva WINNER se va sterge la fiecare iteratie si va primi
valoarea NULL tot din acelasi motiv

---
==CERINTA 4==

*Scop: Clasament;*

- s-a facut o copie a stack-ului de la cerinta anterioara
- s-a facut update la scorurile personale ale jucatorilor deoarece copia s-a realizat in momentul in care scorurile nu erau finalizate
- BST-ul se va afisa descrescator cu *right -> root -> left* cu functia de tip void **printBST()** 

---
==CERINTA 5== 

 *Scop: Numararea jucatorilor ce se afla intre 2 jucatori dupa scor;*

- se vor interschimba cei doi jucatori in cazul in care primul are scorul mai mare decat al doilea tocmai pentru a respecta structura unui interval (x,y) cu x < y
- in cazul existentei ambilor jucatori in BST, se va aplica functia **task5()**:
	-  se foloseste de un algoritm asemanator cu cel de LCA, ce include si cazul in care scorul din radacina se afla intre cele de 2 scoruri


    	


