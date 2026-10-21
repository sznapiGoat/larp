# Jak funguje Ligová tabulka (verze se 4 třídami)

## Soubory

Každá třída má dva soubory:
- `Trida.hpp` obsahuje deklaraci, tedy jaké má proměnné a metody (jen hlavičky funkcí),
- `Trida.cpp` obsahuje implementaci, tedy těla metod zapsaná jako `Trida::metoda() { ... }`.

`#pragma once` v každém `.hpp` zajistí, že se hlavička nevloží dvakrát. V `.hpp` se píše `std::string`, protože `using namespace std;` do hlaviček nepatří; v `.cpp` už se používá.

Kompilace (všechny `.cpp` najednou), spouštět ze složky s `matches.txt`:

```
g++ *.cpp -o liga
./liga
```

## Čtyři třídy

| Třída | Co dělá |
|---|---|
| `Match` | jeden zápas + rozparsování řádku ze souboru |
| `TeamStats` | jeden řádek tabulky (Z, V, R, P, góly, body) |
| `League` | načte soubor, spočítá týmy, seřadí tabulku |
| `App` | komunikace s uživatelem: výpis tabulky, dotaz, výpis zápasů |

## Pořadí volání

```
main()
 └ App::run()
    1. league.load("matches.txt")     čte soubor řádek po řádku
         └ Match::parse(line)         řádek -> objekt Match
    2. league.calculate()             každý zápas = 2x addResult, pak sort
    3. printTable()                   vypíše tabulku
    4. getline(cin, team)             zeptá se na tým
    5. printTeamMatches(team)         vypíše zápasy, nebo "v lize neni"
```

## Třídy jedna po druhé

### Match
Proměnné: `homeTeam`, `awayTeam`, `homeGoals`, `awayGoals`.
- `parse(line)` dělá **obě dělení** ze zadání: nejdřív `"Brno;Praha;2:1"` podle `;` na tři pole, pak třetí pole `"2:1"` podle `:` na dvě čísla (`stoi` převede text na číslo).
- `involves(team)` vrátí true, když tým hrál doma nebo venku.
- `scoreText()` vrátí `"2:1"` pro výpis.

### TeamStats
Jeden řádek tabulky: `played` (Z), `wins` (V), `draws` (R), `losses` (P), `goalsFor`, `goalsAgainst`.
- `addResult(scored, conceded)` započítá jeden zápas z pohledu tohoto týmu a podle gólů přičte výhru, remízu nebo prohru.
- `points()` = výhry × 3 + remízy × 1. Body se neukládají, vždy se dopočítají.
- `goalDifference()` = vstřelené − obdržené.

### League
Drží `vector<Match> matches` (kolekce objektů z bodu 1) a `vector<TeamStats> teams`.
- `load(fileName)` otevře soubor a každý řádek pošle do `Match::parse`. Odstraní `\r` na konci řádku (soubor z Windows) a přeskočí prázdné řádky. Když soubor nejde otevřít, vrátí `false`.
- `calculate()` projde zápasy a každý započítá **dvakrát**: domácím `(homeGoals, awayGoals)`, hostům obráceně. Nakonec zavolá `sort` s funkcí `compare`.
- `findOrCreate(name)` (private) najde tým podle jména, a když ještě není, přidá ho. Tak se splní „seznam týmů odvoďte ze zápasů“.
- `compare(a, b)` (private) vrací true, když má být `a` nad `b`: víc bodů, pak větší rozdíl, pak abecedně.
- `hasTeam(name)` zjistí, jestli tým existuje (bod 6).

### App
Má v sobě objekt `League league`.
- `run()` spojí vše v pořadí podle zadání. Tým se čte přes `getline`, ne `cin >>`, aby fungoval i název s mezerou.
- `printTable()` vypíše tabulku, `setw(n)` určí šířku sloupce, `left` pro název, `right` pro čísla.
- `printTeamMatches(team)` vypíše zápasy týmu ve formátu `Brno       - Praha     2:1`, nebo `Tym X v lize neni.`

## Mapování na zadání

| Bod | Kde v kódu |
|---|---|
| 1. načíst do kolekce objektů | `League::load` → `vector<Match>` |
| dělení dvakrát | `Match::parse` (`;` a pak `:`) |
| týmy odvodit ze zápasů | `League::findOrCreate` |
| 2. Z, V, R, P, skóre, body | `TeamStats::addResult`, `points()` |
| 3. seřadit | `League::compare` + `sort` v `calculate` |
| 4. tabulka do sloupců | `App::printTable` (`setw`) |
| 5. zeptat se a vypsat zápasy | `App::run`, `App::printTeamMatches` |
| 6. neznámý tým | `League::hasTeam`, hláška v `printTeamMatches` |
