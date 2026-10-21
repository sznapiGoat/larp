# Co je core a co jde změnit (verze se 4 třídami)

## CORE: neměnit, jinak to nefunguje nebo nesplní zadání

| Kde | Proč |
|---|---|
| `Match::parse`: dělení podle `;` a pak podle `:` + `stoi` | obě dělení ze zadání |
| `League::load`: odstranění `\r` na konci řádku | soubor z Windows by jinak měl skóre `"2:1\r"` |
| `League::load`: přeskočení prázdných řádků | prázdný řádek na konci souboru by shodil `stoi` |
| `Match` ve `vector<Match>` | zadání chce „kolekci objektů“ |
| `TeamStats` | jeden řádek tabulky, bez něj nejde bod 2 |
| `addResult`: podmínky `>` / `==` / jinak | rozhoduje výhra / remíza / prohra |
| `points()` = `wins * 3 + draws` | body ze zadání 3 / 1 / 0 |
| `calculate()`: každý zápas 2x, hostům obráceně | jinak by hosté dostali góly domácích |
| `findOrCreate` | týmy nejsou v souboru, musí vzniknout ze zápasů |
| `compare`: pořadí body → rozdíl → název, znaménka `>` `>` `<` | bod 3; prohozené znaménko seřadí obráceně |
| `compare` musí být `static` | `sort` potřebuje obyčejnou funkci, ne metodu objektu |
| `calculate()` se volá až po `load()` | jinak by se počítalo z prázdného seznamu |
| `setw` ve výpisu | bod 4, zarovnání do sloupců |
| `hasTeam` + hláška | bod 6 |
| `getline(cin, team)` | `cin >>` by uřízl název s mezerou |
| Reference z `findOrCreate` neukládat do proměnné přes další `push_back` | vector se může přesunout v paměti a reference by byla neplatná |

## LZE ZMĚNIT: funkce zůstane

- **Všechny názvy** tříd, metod a proměnných (`homeTeam` → `domaci` apod.).
- **Texty výpisů** („Nacteno“, „Zadej tym“, „v lize neni“).
- **Šířky sloupců**: čísla v `setw(...)`.
- **Název souboru** `"matches.txt"` v `App::run`.
- `Match::scoreText()`: jde vypsat ručně `homeGoals << ":" << awayGoals`.
- `Match::involves()`: podmínku jde napsat přímo v `printTeamMatches`.
- `printTable` a `printTeamMatches` jde přesunout z `App` do `League`, pak by `App` jen volal.
- `App` jde úplně zrušit a obsah `run()` dát do `main()`, zbydou 3 třídy.

## Soubory: co hlídat

- Každý `.hpp` musí mít `#pragma once`.
- `League.hpp` includuje `Match.hpp` a `TeamStats.hpp`, `App.hpp` includuje `League.hpp`, protože je používají jako proměnné.
- Při kompilaci se musí předat **všechny** `.cpp` (`g++ *.cpp`), jinak linker hlásí „undefined reference“.
