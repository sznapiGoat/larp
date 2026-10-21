# Jak funguje main.cpp

## Pořadí volání

```
main()
 └ App::run()
    1. MatchLoader::load("matches.txt")   čte soubor řádek po řádku
         └ MatchParser::parseLine()       řádek -> objekt Match
              └ Score::parse()            "2:1" -> 2 a 1
    2. League(matches)                    konstruktor spočítá a seřadí
         ├ calculate()                    každý zápas = 2x addResult
         └ TableSorter::sort()            body, rozdíl, název
    3. TablePrinter::print()              vypíše tabulku
    4. getline(cin, team)                 zeptá se na tým
    5. TeamMatchesPrinter::print()        vypíše zápasy, nebo "v lize neni"
```

## Třídy jedna po druhé

### Score
Drží góly domácích (`home`) a hostů (`away`).
`parse("2:1")` dělí text podle `:` přes `getline(ss, part, ':')`, `stoi` udělá z textu číslo. To je **druhé dělení** ze zadání.
`toString()` vrátí zpět `"2:1"` pro výpis.

### Match
Jeden zápas: `homeTeam`, `awayTeam`, `score`. Všechny zápasy jsou ve `vector<Match>`, to je ta **kolekce objektů** z bodu 1.
`involves(team)` vrátí true, když tým hrál doma nebo venku.

### MatchParser
`parseLine("Brno;Praha;2:1")` dělí řádek podle `;` na tři pole (domácí, hosté, skóre). To je **první dělení** ze zadání. Třetí pole pošle do `Score::parse`.

### MatchLoader
`load()` otevře soubor a čte ho řádek po řádku.
- Když soubor nejde otevřít, vypíše hlášku a vrátí prázdný vektor.
- Odstraní `\r` na konci řádku (soubor uložený na Windows), jinak by skóre bylo `"2:1\r"`.
- Prázdné řádky přeskočí, jinak by `stoi` spadlo.

### TeamStats
Jeden řádek tabulky: `played` (Z), `wins` (V), `draws` (R), `losses` (P), `goalsFor`, `goalsAgainst`.
- `addResult(scored, conceded)` započítá jeden zápas z pohledu tohoto týmu a podle gólů přičte výhru, remízu nebo prohru.
- `points()` = výhry × 3 + remízy × 1. Body se neukládají, vždy se dopočítají.
- `goalDifference()` = vstřelené − obdržené.

### TableSorter
`compare(a, b)` vrací true, když má být `a` v tabulce nad `b`:
1. víc bodů je výš,
2. při shodě větší brankový rozdíl je výš,
3. při shodě podle názvu abecedně.

`sort()` jen zavolá `std::sort` s touto funkcí.

### League
Drží všechny zápasy i všechny týmy. Konstruktor rovnou spočítá a seřadí, takže po vytvoření je tabulka hotová.
- `findOrCreate(name)` najde tým podle jména, a když ještě není, přidá ho. Tak se splní „seznam týmů odvoďte ze zápasů“.
- `calculate()` projde zápasy a každý započítá **dvakrát**: domácím `(home, away)`, hostům obráceně `(away, home)`.
- `hasTeam(name)` zjistí, jestli tým existuje (bod 6).

### TablePrinter
Vypíše tabulku. `setw(n)` určí, že další hodnota zabere n znaků, tím lícují sloupce. `left` pro název týmu, `right` pro čísla. Skóre se nejdřív složí do jednoho textu `"9:8"`, aby se zarovnalo celé. Pořadí se vypisuje jako `i + 1`, aby začínalo od 1.

### TeamMatchesPrinter
Když tým neexistuje, vypíše `Tym X v lize neni.` a skončí. Jinak projde všechny zápasy a vypíše ty, kde tým hrál, ve formátu `Brno       - Praha     2:1`.

### App
`run()` spojí vše dohromady v pořadí podle zadání. Tým se čte přes `getline`, ne `cin >>`, aby fungoval i název s mezerou.

## Mapování na zadání

| Bod | Kde v kódu |
|---|---|
| 1. načíst do kolekce objektů | `MatchLoader::load` → `vector<Match>` |
| dělení dvakrát | `MatchParser::parseLine` (`;`) a `Score::parse` (`:`) |
| týmy odvodit ze zápasů | `League::findOrCreate` |
| 2. Z, V, R, P, skóre, body | `TeamStats::addResult`, `points()` |
| 3. seřadit | `TableSorter::compare` |
| 4. tabulka do sloupců | `TablePrinter::print` (`setw`) |
| 5. zeptat se a vypsat zápasy | `App::run`, `TeamMatchesPrinter::print` |
| 6. neznámý tým | `League::hasTeam`, hláška v `TeamMatchesPrinter` |
