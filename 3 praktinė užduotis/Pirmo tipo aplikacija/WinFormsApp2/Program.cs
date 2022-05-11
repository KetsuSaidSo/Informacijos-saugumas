namespace WinFormsApp2
{
    internal static class Program
    {
        /// <summary>
        ///  The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            ApplicationConfiguration.Initialize();
            Application.Run(new Form1());
        }
    }
}
/*
Sukurti RSA algoritmo šifravimo/dešifravimo sistemą. Galima pasirinkti kokio tipo sistemą kurti.

Pirmo tipo aplikacija, kurioje galima pasinaudoti kriptografijos biblioteka.

2 taškai – sukurtas įvedimo laukas, kuriame vartotojas įveda šifruojamą tekstą.

5 taškai – panaudojama kriptografijos biblioteka, kurios pagalba įvestas tekstas užšifruojamas RSA algoritmu.

Antro tipo aplikacija, kurioje negalima naudoti kriptografijos biblioteka.

3 taškai – pradinių duomenų įvedimas: du pirminiai skaičiai p ir q, pradinis tekstas x.

6 taškai – šifravimo/dešifravimo algoritmams reikalingų parametrų radimas. Viešojo rakto radimas, privačiojo rakto radimas, Euklido algoritmo realizavimas, Euklido išplėstinio algoritmo realizavimas. 

2 taškai – pradinio teksto užšifravimas.

2 taškai – užšifruoto teksto ir viešojo rakto išsaugojimas failų sistemoje/duomenų bazėje.

2 taškai – užšifruoto teksto nuskaitymas iš failų sistemos/duomenų bazės.

5 taškai – užšifruoto teksto dešifravimas.  Dešifravimo metodui reikalingas papildomas metodas, kuris turėdamas n turi surasti du pirminius skaičius, kurie reikalingi ieškant Φ[n] reikšmės.Turint Φ[n] ir e apskaičiuojamas privatusis raktas.

Užduotį patalpinti į Moodle aplinką ir atsiskaityti iki balandžio 15 d. 

Programėlės veikimo principas: Įvedamas tekstas, kuris konvertuojamas į ASCII/Unicode koduotės simbolius.
    Įvesti du pirminiai skaičiai leidžia apskaičiuoti n, o turint n randamas Φ[n]. Pasinaudojant Φ[n] apskaičiuojama viešosios eksponentės e reikšmė.
    Jau turimas viešasis raktas (n, e), kuris bus saugojamas duomenų bazėje. Galima vykdyti šifravimo metodą.
    Paimama pirmosios raidės ASCII/Unicode reikšmė ir jai pritaikomas šifravimo metodas ir taip kartojama visam tekstui. Apskaičiuojamas privatusis raktas.
    Dešifravimo metodui reikalingas papildomas metodas, kuris turėdamas n turi surasti du pirminius skaičius, kurie reikalingi ieškant Φ[n] reikšmės.Turint Φ[n] ir e apskaičiuojamas privatusis raktas.
    Paimamas dešifruotas tekstas ir kiekvienam ASCII/Unicode simboliui pritaikomas dešifravimo metodas.
*/