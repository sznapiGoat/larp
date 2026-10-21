# Co je core a co jde změnit

## CORE: neměnit, jinak to nefunguje nebo nesplní zadání

| Kde | Proč |
|---|---|
| `MatchParser::parseLine`: dělení podle `;` | první dělení ze zadání |
| `Score::parse`: dělení podle `:` a `stoi` | druhé dělení ze zadání |
| `MatchLoader`: odstranění `\r` na konci řádku | soubor z Windows by jinak měl skóre `"2:1\r"` |
| `MatchLoader`: přeskočení prázdných řádků | prázdný řádek na konci souboru by shodil `stoi` |
| `Match` ve `vector<Match>` | zadání chce „kolekci objektů“ |
| `TeamStats` | jeden řádek tabulky, bez něj nejde bod 2 |
| `addResult`: podmínky `>` / `==` / jinak | rozhoduje výhra / remíza / prohra |
| `points()` = `wins * 3 + draws` | body ze zadání 3 / 1 / 0 |
| `calculate()`: každý zápas 2x, hostům obráceně | jinak by hosté dostali góly domácích |
| `findOrCreate` | týmy nejsou v souboru, musí vzniknout ze zápasů |
| `compare`: pořadí body → rozdíl → název, znaménka `>` `>` `<` | bod 3; prohozené znaménko seřadí obráceně |
| `setw` ve výpisu | bod 4, zarovnání do sloupců |
| `hasTeam` + hláška | bod 6 |
| `getline(cin, team)` | `cin >>` by uřízl název s mezerou |
| Reference z `findOrCreate` neukládat do proměnné přes další `push_back` | vector se může přesunout v paměti a reference by byla neplatná |

## LZE ZMĚNIT: funkce zůstane

- **Všechny názvy** tříd, metod a proměnných (`homeTeam` → `domaci` apod.).
- **Texty výpisů** („Nacteno“, „Zadej tym“, „v lize neni“).
- **Šířky sloupců**: čísla v `setw(...)`.
- **Název souboru** `"matches.txt"` v `App::run`.
- `Score::toString()`: jde vypsat ručně `home << ":" << away`.
- `Match::involves()`: podmínku jde napsat přímo v `TeamMatchesPrinter`.
- `findOrCreate` s vectorem jde nahradit `map<string, TeamStats>`, ale před řazením se pak musí překopírovat do vectoru.

## Jak ubrat tříd

Teď je jich 10. Sloučit jde takhle:

| Třída | Kam ji dát |
|---|---|
| `Score` | dva `int` přímo v `Match`, parse do `MatchParser` |
| `MatchParser` | funkce v `MatchLoader` nebo v `Match` |
| `MatchLoader` | obsah `load()` přímo do `App::run` |
| `TableSorter` | obyčejná funkce `compare()` mimo třídu |
| `TablePrinter` | metoda `printTable()` v `League` |
| `TeamMatchesPrinter` | metoda `printTeamMatches()` v `League` |
| `App` | obsah `run()` přímo do `main()` |

**Minimum**, které zadání chce: `Match` a `TeamStats`. Všechno ostatní může být klidně ve funkcích nebo v `main()`.
