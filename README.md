# Bat-Computer

**Bat-Computer** is a C++ console application inspired by the Batman universe.  
The program functions as an intelligence management system used by Batman to monitor criminals, coordinate the Bat-Family, and evaluate the status of his equipment.

---

# Tema 0

- [x] Nume proiect (poate fi schimbat ulterior)
- [x] Scurtă descriere a temei alese, ce v-ați propus să implementați

---

# Tema 1

## Cerințe

- [x] definirea a minim **3-4 clase** folosind compunere cu clasele definite de voi; moștenirile nu se iau în considerare aici  
- [x] constructori de inițializare cu parametri pentru fiecare clasă  
- [x] pentru o aceeași (singură) clasă: constructor de copiere, `operator=` de copiere, destructor  
- [x] `operator<<` pentru **toate** clasele pentru afișare (`std::ostream`) folosind compunere de apeluri cu `operator<<`  
- [x] cât mai multe `const` (unde este cazul) și funcții `private`  
- [x] implementarea a minim 3 funcții membru publice pentru funcționalități netriviale specifice temei alese, dintre care cel puțin 1-2 funcții mai complexe  
  - nu doar citiri/afișări sau adăugat/șters elemente într-un/dintr-un vector  
- [x] scenariu de utilizare **cu sens** a claselor definite:  
  - crearea de obiecte și apelarea tuturor funcțiilor membru publice în `main`  
  - vor fi adăugate în fișierul `tastatura.txt` DOAR exemple de date de intrare de la tastatură (dacă există); dacă aveți nevoie de date din fișiere, creați alte fișiere separat  
- [ ] minim 50-55% din codul propriu să fie C++, `.gitattributes` configurat corect  
- [x] tag de `git`: de exemplu `v0.1`  
- [x] serviciu de integrare continuă (CI) cu **toate bifele**; exemplu: GitHub Ac

---

# Tema 2

## Cerințe

- [x] separarea codului din clase în .h (sau .hpp) și .cpp
- [x] moșteniri:
  - minim o clasă de bază și 3 clase derivate din aceeași ierarhie; cele 3 derivate moștenesc aceeași clasă de bază
  - ierarhia trebuie să fie cu bază proprie, nu derivată dintr-o clasă predefinită
  - [x] funcții virtuale (pure) apelate prin pointeri de bază din clasa care conține atributul de tip pointer de bază
    - minim o funcție virtuală va fi specifică temei (i.e. nu simple citiri/afișări sau preluate din biblioteci i.e. draw/update/render)
    - constructori virtuali (clone): sunt necesari, dar nu se consideră funcții specifice temei
    - afișare virtuală, interfață non-virtuală
  - [x] apelarea constructorului din clasa de bază din constructori din derivate
  - [x] clasă cu atribut de tip pointer la o clasă de bază cu derivate; aici apelați funcțiile virtuale prin pointer de bază, eventual prin interfața non-virtuală din bază
    - [x] suprascris cc/op= pentru copieri/atribuiri corecte, copy and swap
    - [x] dynamic_cast/std::dynamic_pointer_cast pentru downcast cu sens
    - [x] smart pointers (recomandat, opțional)
- [x] excepții
  - [x] ierarhie proprie cu baza std::exception sau derivată din std::exception; minim 3 clase pentru erori specifice distincte
    - clasele de excepții trebuie să trateze categorii de erori distincte (exemplu de erori echivalente: citire fișiere cu diverse extensii)
  - [x] utilizare cu sens: de exemplu, throw în constructor (sau funcție care întoarce un obiect), try/catch în main
    - această ierarhie va fi complet independentă de ierarhia cu funcții virtuale
- [x] funcții și atribute static
- [x] STL
- [x] cât mai multe const
- [x] funcții de nivel înalt, de eliminat cât mai mulți getters/setters/funcții low-level
- [x] minim 75-80% din codul propriu să fie C++
- [x] la sfârșit: commit separat cu adăugarea unei noi clase derivate fără a modifica restul codului, pe lângă cele 3 derivate deja adăugate din aceeași ierarhie
  - noua derivată nu poate fi una existentă care a fost ștearsă și adăugată din nou
  - noua derivată va fi integrată în codul existent (adică va fi folosită, nu adăugată doar ca să fie)
- [x] tag de git pe commit cu toate bifele: de exemplu v0.2
- [ ] code review #2 2 proiecte

---

# Tema 3

## Cerințe

- [ ] 2 șabloane de proiectare (design patterns)  
- [ ] o clasă șablon cu sens; minim **2 instanțieri**  
- [ ] preferabil și o funcție șablon (template) cu sens; minim 2 instanțieri  
- [ ] minim 85% din codul propriu să fie C++  
- [ ] tag de `git` pe commit cu **toate bifele**: de exemplu `v0.3` sau `v1.0`  
- [ ] code review #3 – 2 proiecte  
