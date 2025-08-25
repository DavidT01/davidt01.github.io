let objekat1 = {
    ime: "David"
}

// po defaultu this referiše na objekat2 jer je pozdraviSe definisana u okviru njega
let objekat2 = {
    ime: "Marija",
    pozdraviSe: (poruka, godine) => console.log(this.ime + ' (' + godine + ") : " + poruka)
}

// BIND kreira novu funkciju i menja na šta referiše this
objekat2.pozdraviSe("cao", 20)
objekat2.pozdraviSe.bind(objekat1)("cao i tebi", 21)
console.log("--------------------------")

// CALL samo poziva već postojeću funkciju i menja na šta referiše
objekat2.pozdraviSe("hej :D", 20)
objekat2.pozdraviSe.call(objekat1, "cao :)", 21)
console.log("--------------------------")

// APPLY samo poziva već postojeću funkciju i menja na šta referiše this,
// ali ostali argumenti se prosleđuju kao niz
objekat2.pozdraviSe("hello", 20)
objekat2.pozdraviSe.apply(objekat1, ["hi", 21])