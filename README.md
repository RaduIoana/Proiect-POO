# Proiect-POO

## Tema proiectului: magazin de aplicatii mobile

## Clase:

- IntVector : permite alocarea dinamica a unui vector de numere intregi si afisarea lui, adaugarea de elemente in vector, initializarea sa cu 0;
- String : permite alocarea dinamica a unui sir de caractere, introducerea lui de la tastatura, afisarea pe ecran, concatenarea cu un alt sir de caractere;
- Data : contine luna si anul unei date calendaristice si permite introducerea datei de la tastatura;
- date_card : memoreaza datele unui card de credit, permite modificarea soldului acestuia si introducerea datelor de la tastatura;
- Portofel : reprezinta portofelul unui cont de utilizator si permite adaugarea unui card de credit la cont, afisarea soldului cardului si pe cel al portofelului;
- Aplicatie : memoreaza date despre o aplicatie mobila si poate afisa aceste informatii;
- Utilizator : clasa principala, ce permite crearea unui cont implicit pentru testare, a unui cont custom cu nume de utilizator si parola, verificarea statusului abonamentului, adaugarea de bani in portofel, instalarea de aplicatii si afisarea listei de aplicatii a utilizatorului;

## Functionalitati:

La momentul actual, aplicatia poate memora o lista de aplicatii mobile, poate crea un cont de utilizator si adauga o metoda de plata la acesta, precum si bani in cont. Exista un abonament la pretul caruia se aplica o reducere la cumpararea unui pachet cu durata mai lunga. Exista aplicatii gratis si platite. Abonamentul aplica o reducere la pretul aplicatiilor platite. Cumpararea unei aplicatii sau al unui abonament verifica soldul contului de utilizator si il modifica corespunzator. Utilizatorul poate verifica informatii despre o aplicatie si o poate adauga la contul sau.

## Schimbari Etapa 2:

## Clase:

- String : vechea clasa String a fost inlocuita cu cea din biblioteca standard;
- Au fost adaugate doua ierarhii de mostenire, cu bazele metoda_plata si Aplicatie_gratis;
- metoda_plata : clasa de baza abstracta, ce contine soldul unei metode de plata, un getter si un setter pentru acesta, si o functie pur virtuala pentru afisarea informatiilor despre o metoda de plata;
- voucher : mosteneste metoda_plata, ce adauga un nume de voucher si o data de expirare, si implementeaza functia de afisare din baza;
- card : mosteneste voucher, anterior numita date_card. Adauga CVC si numarul cardului;
- Portofel : se permite acum adaugarea unui card si a unui voucher;
- Aplicatie_gratis : anterior numita Aplicatie, retine date despre o aplicatie mobila cu exceptia pretului. Contine metode virtuale de gestiune a pretului si a discountului pentru a permite declararea de pointeri de tip Aplicatie_gratis la obiecte de tip derivat si un destructor virtual;
- Aplicatie_cu_plata_initiala : mosteneste Aplicatie_gratis, adauga pret si discount (pentru conturi cu abonament la magazin);
- Aplicatie_cu_abonament : mosteneste Aplicatie_gratis, reprezinta o aplicatie care se poate instala gratuit dar contine un abonament in interiorul acesteia. Adauga un pret pe luna de abonament si discount (pentru conturi cu abonament la magazin);
- Aplicatie_abon_si_init : mosteneste Aplicatie_cu_plata_initiala si Aplicatie_cu_abonament si reprezinta o aplicatie care necesita plata la instalare si contine un abonament in interiorul acesteia;
- Cele trei clase derivate din Aplicatie_gratis contin metode de calcul a pretului si de afisare a informatiilor despre aplicatie;

## Functionalitati:

Un utilizator poate acum sa foloseasca un card si un voucher. Introducerea unui alt card/voucher inlocuieste datele cardul/voucherul anterior cu cel nou. Cand se adauga bani in portofel, se poate selecta un card sau un voucher. Folosirea unui voucher consuma toti banii de pe acesta, in timp ce cardul poate dona doar o parte din soldul sau. Inainte de plata unui abonament sau a unei aplicatii, se afiseaza suma finala pe ecran. Daca suma finala depaseste soldul din portofel, tranzactia va fi anulata si se va afisa un mesaj corespunzator pe ecran.

## Schimbari Etapa 3:

- Utilizatorul poate acum sa adauge oricate metode de plata doreste. Acestea pot fi de tip card sau voucher.
- La adaugarea de bani in portofel dintr-o metoda de plata, selectarea metodei dorite se face prin indiciele acesteia (ordinea in care se afiseaza pe ecran, incepand de la 0)
- Functie template pentru eliberarea memoriei unui vector
- Const correctness
- Functia de creare cont este acum independenta de clasa Utilizator si returneaza un unique_ptr
- Contul de utilizator este acum unique_ptr
- Aplicatiile din magazin sunt stocate ca pointeri const de tip clasa de baza
- Atunci cand o operatie modifica un vector din program, se apeleaza functia sort din <algorithm>
- Acum se pot dezinstala aplicatii din cont
