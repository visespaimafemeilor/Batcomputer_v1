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
- [ ] serviciu de integrare continuă (CI) cu **toate bifele**; exemplu: GitHub Ac

---

# Tema 2

## Cerințe

- [x] separarea codului din clase în `.h` (sau `.hpp`) și `.cpp`  
- [x] moșteniri:  
  - minim o clasă de bază și **3 clase derivate** din aceeași ierarhie (Batman → Criminal, Family, Batsuit)  
  - ierarhia trebuie să fie cu bază proprie, nu derivată dintr-o clasă predefinită  
  - [x] funcții virtuale (pure) apelate prin pointeri de bază din clasa care conține atributul de tip pointer de bază  
    - minim o funcție virtuală va fi **specifică temei**: `assessThreat()` - evaluare polimorfica a amenintarii  
    - constructori virtuali (clone): `clone()` implementat în toate clasele  
    - afișare virtuală, interfață non-virtuală: `displayInfo()` este virtuală pură  
  - [x] apelarea constructorului din clasa de bază din constructori din derivate  
  - [x] clasă cu atribut de tip pointer la o clasă de bază cu derivate: `std::vector<std::unique_ptr<Batman>> database`  
    - [x] suprascris cc/op= pentru copieri/atribuiri corecte, copy and swap (în toate clasele derivate)  
    - [x] `dynamic_cast` / `std::dynamic_pointer_cast` pentru downcast cu sens (disponibil pentru utilizare)  
    - [x] smart pointers: `std::unique_ptr<Batman>` în database  
- [x] excepții  
  - [x] ierarhie proprie cu baza `std::exception`: `BatcomputerException` → `FileLoadException`, `InvalidDataException`, `DatabaseOperationException`  
    - clasele de excepții tratează categorii distincte: I/O, validare date, operații database  
  - [x] utilizare cu sens: disponibil pentru `throw` în constructori, `try`/`catch` în `main`  
  - această ierarhie este complet independentă de ierarhia cu funcții virtuale (exceptions.h)  
- [x] funcții și atribute `static`: `totalEntities`, `criminalCount`, `familyMemberCount`, `suitPartCount` + getteri  
- [x] STL: `vector`, `string`, `unique_ptr`, `ifstream`, etc.  
- [x] cât mai multe `const`: getters, metode care nu modifică obiectul, parametri const  
- [x] funcții *de nivel înalt*: `assessThreat()`, `simulateBattle()`, `fightReport()`, `statusReport()`  
- [ ] minim 75-80% din codul propriu să fie C++  
- [ ] la sfârșit: commit separat cu adăugarea unei noi clase derivate fără a modifica restul codului, **pe lângă cele 3 derivate deja adăugate** din aceeași ierarhie  
  - noua derivată nu poate fi una existentă care a fost ștearsă și adăugată din nou  
  - noua derivată va fi integrată în codul existent (adică va fi folosită, nu adăugată doar ca să fie)  
- [ ] tag de `git` pe commit cu **toate bifele**: de exemplu `v0.2`  
- [ ] code review #2 – 2 proiecte  

---

# Tema 3

## Cerințe

- [ ] 2 șabloane de proiectare (design patterns)  
- [ ] o clasă șablon cu sens; minim **2 instanțieri**  
- [ ] preferabil și o funcție șablon (template) cu sens; minim 2 instanțieri  
- [ ] minim 85% din codul propriu să fie C++  
- [ ] tag de `git` pe commit cu **toate bifele**: de exemplu `v0.3` sau `v1.0`  
- [ ] code review #3 – 2 proiecte  
