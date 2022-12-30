Modyfing .xml certificates files to match with *rejestrcheb.mrit.gov.pl*
-

**Install requirements:**
```
sudo apt update
sudo apt install g++ cmake
```

**Build project**:
```
mkdir build
cmake -S . -B build/
cmake --build build -t CertAutoMake
```
**Run**:  `./build/firmware/CertAutoMake`

Odpalasz projekt w VS
On już napewno usuwa nazwe miejscowości z poczty
Zmienia województwo
Dodaje gmine i powiat
Czyta ulice, numer domu i numer lokalu

JEŚLI CHCESZ INNĄ GMINE ALBO POWIAT ZMIEŃ TYLKO IDENTYFIKATORY PRZED PĘTLĄ 
- ICH NAZWY ZNAJDZIESZ W PDF (folder dataAboutXML)
- JEŚLI NIE ZMIENIASZ ICH NADAL JE POPRAWNIE WCZYTAJ - TO POTRZEBNE DO NAZWY PLIKU NOWEGO

Numery domu i lokalu musisz substrami robić

Przed pętlą masz dwie zmienne których używasz do setprecission precyzjaDomu i precyzjaLokalu
Mówią one na ilu miejscach w docelowej zostanie zapisany nrDomu i nrLokalu

bierzesz binarke i wrzucasz tam gdzie XML, musi być w tym folderze plik _Miniatura.jpg inaczej nie zadziała