const brojevi = [1, 6, 2, 9, 2, 13, 54, 205, 25, 26];

// forEach - izvršava funkciju za svaki element
// obična funkcija
brojevi.forEach(function(broj) {
    console.log(broj);
});

// lambda izraz
brojevi.forEach((broj) => {
    console.log(broj);
});

// find - vraća prvi element koji ispunjava neki uslov
const rez = brojevi.find(broj => broj >= 10);
console.log(rez);

// filter - vraća niz koji je podniz početnog
const brojevi2 = brojevi.filter(broj => broj < 10);

// map - pravi novi niz od početnog
const kvadratBrojeva = brojevi.map(function(broj) {
    return broj * broj;
});

// every - proverava da li svi elementi ispunjavaju uslov
if(brojevi.every(broj => broj % 2 === 0))
    console.log("Svi brojevi su parni");
else
    console.log("Nisu svi brojevi parni");

// some - proverava da li bar jedan element ispunjava uslov
if(brojevi.some(broj => broj % 2 === 0))
    console.log("Bar jedan broj je paran");
else
    console.log("Nijedan broj nije paran");

// sort - radi sortiranje prema datoj funkciji
brojevi.sort((a, b) => b - a); // opadajuće
console.log(brojevi);
brojevi.sort((a, b) => a - b); // rastuće
console.log(brojevi);

// reduce - niz svodi na jednu vrednost (na primer max ili suma)
// treba da ima 2 argumenta, pri čemu će prvi biti vrednost koju očekujemo na kraju
const max = brojevi.reduce((max, broj) => Math.max(max, broj));
console.log(max);