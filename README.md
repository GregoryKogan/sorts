# sorts

![Lines of code](https://tokei.ekzhang.com/b1/github/GregoryKogan/sorts)

## Description

This is a sorting algorithm visualizer. It is written in C++ and uses SDL2 for graphics. It is compiled to WASM using Emscripten and embedded in a Vue.js app.
You can see it in action [here](https://gregorykogan.github.io/sorts/).

## Benchmarks

Execution time of sorting algorithms on random sequences of integers. All times are in microseconds.

| Sequence length | Bubble Sort | Selection Sort | Insertion Sort | Merge Sort | Iterative Merge Sort | Quick Sort | Iterative Quick Sort | Heap Sort | Counting Sort | Cocktail Sort | Radix Sort | Shell Sort | Gnome Sort | Odd Even Sort | Comb Sort | Cycle Sort |
| --------------- | ----------- | -------------- | -------------- | ---------- | -------------------- | ---------- | -------------------- | --------- | ------------- | ------------- | ---------- | ---------- | ---------- | ------------- | --------- | ---------- |
| 500             | 2576        | 840            | 921            | 520        | 380                  | 144        | 103                  | 216       | 103           | 1012          | 71         | 66         | 1062       | 1161          | 69        | 2166       |
| 1000            | 5089        | 2125           | 2645           | 888        | 699                  | 257        | 206                  | 400       | 215           | 3735          | 149        | 150        | 4091       | 4425          | 164       | 8673       |
| 1500            | 11472       | 4717           | 5765           | 1454       | 1195                 | 394        | 344                  | 655       | 395           | 8298          | 281        | 249        | 9091       | 10183         | 272       | 19472      |
| 2000            | 20741       | 8455           | 10671          | 2013       | 1606                 | 533        | 512                  | 892       | 602           | 15415         | 420        | 347        | 16769      | 18145         | 405       | 34971      |
| 2500            | 32427       | 13058          | 16086          | 2647       | 2364                 | 678        | 714                  | 1138      | 860           | 23433         | 571        | 482        | 25345      | 29216         | 491       | 54994      |
| 3000            | 46733       | 18701          | 23303          | 3283       | 2853                 | 828        | 939                  | 1400      | 1167          | 33524         | 750        | 562        | 37054      | 41039         | 624       | 78073      |
| 3500            | 64386       | 25672          | 32524          | 3906       | 3295                 | 950        | 1161                 | 1671      | 1511          | 46597         | 953        | 660        | 49680      | 55674         | 748       | 105577     |
| 4000            | 83687       | 33064          | 42083          | 4731       | 3833                 | 1101       | 1429                 | 1936      | 1914          | 61321         | 1177       | 794        | 65918      | 71968         | 863       | 139237     |
| 4500            | 106623      | 42258          | 52102          | 5375       | 5324                 | 1289       | 1753                 | 2215      | 2342          | 76173         | 1426       | 925        | 81570      | 94342         | 1021      | 175363     |
| 5000            | 131531      | 51780          | 66319          | 6158       | 5852                 | 1459       | 2465                 | 2559      | 2907          | 96025         | 1701       | 1075       | 101923     | 113931        | 1177      | 216110     |
| 5500            | 159348      | 62595          | 80080          | 6931       | 6394                 | 1551       | 2363                 | 2776      | 3361          | 115442        | 1996       | 1155       | 124479     | 137856        | 1202      | 261840     |
| 6000            | 190167      | 74647          | 95260          | 7761       | 6995                 | 1736       | 2733                 | 3064      | 4035          | 137493        | 2309       | 1298       | 147215     | 164933        | 1403      | 314620     |
| 6500            | 223331      | 88574          | 113759         | 8577       | 7610                 | 1871       | 3155                 | 3348      | 4548          | 161977        | 2656       | 1413       | 174413     | 194374        | 1554      | 375627     |
| 7000            | 263399      | 102552         | 129494         | 9582       | 8186                 | 1985       | 3499                 | 3670      | 5228          | 188016        | 3016       | 1507       | 203878     | 226026        | 1618      | 427812     |
| 7500            | 296904      | 116720         | 148924         | 10296      | 8916                 | 2157       | 3952                 | 3959      | 5922          | 218871        | 3393       | 1655       | 233407     | 259288        | 1814      | 490053     |
| 8000            | 334156      | 131415         | 165817         | 11174      | 9575                 | 2336       | 4423                 | 4233      | 6697          | 242053        | 3788       | 1867       | 259779     | 297877        | 2074      | 551854     |
| 8500            | 383343      | 150682         | 188617         | 12172      | 13653                | 2461       | 4924                 | 4513      | 7551          | 277717        | 4247       | 1949       | 299317     | 335615        | 2130      | 623002     |
| 9000            | 425778      | 167278         | 214066         | 13120      | 14233                | 2586       | 5426                 | 4801      | 8479          | 310185        | 4757       | 2081       | 331603     | 376240        | 2124      | 696885     |
| 9500            | 474017      | 185893         | 236970         | 14114      | 14864                | 2809       | 6031                 | 5092      | 9479          | 344152        | 5277       | 2139       | 362626     | 420169        | 2281      | 779667     |
| 10000           | 526702      | 207652         | 261295         | 15152      | 15583                | 2897       | 6570                 | 5408      | 10572         | 382702        | 5806       | 2433       | 408214     | 468055        | 2506      | 863743     |

<p align="center">
    <img style="width: 100%" src="sorts/src/cpp/src/benchmark/results/all.png" />
    <img style="width: 100%" src="sorts/src/cpp/src/benchmark/results/fast.png" />
</p>
