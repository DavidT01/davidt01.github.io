dekorisi = function(f, arg) {
    console.log(`Pozivam funkciju:\n${f}`)
    let rezultat = f(arg);
    console.log(`Funkcija je vratila vrednost ${rezultat} za argument ${arg}`);
}

kvadriraj = function (arg) {
    return arg * arg;
}

umanji = function(broj) {
    return --broj;
}

dekorisi(kvadriraj, 5)
dekorisi(umanji, 7)