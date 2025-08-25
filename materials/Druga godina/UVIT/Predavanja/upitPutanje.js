const http = require('http')
const url = require('url')

const port = 3000

// Zahtev: http://localhost:3000/ime=david?predmet=uvit

http.createServer(function (zahtev, odgovor) {
    odgovor.writeHead(200, {'Content-type' : 'text/plan'})
    odgovor.write('Veb server koristi node.js\n')
    odgovor.write(`Vreme na serveru: ${new Date()}\n`)
    odgovor.write(`URL: ${zahtev.url}\n`) // /ime=david?predmet=uvit
    let putanja = url.parse(zahtev.url).pathname
    let upit = url.parse(zahtev.url).query
    odgovor.write(`Putanja: ${putanja}\n`) // /ime=david
    odgovor.write(`Upit: ${upit}\n`) // predmet=uvit
    odgovor.end()
}).listen(port)

console.log(`Veb server sluša na portu ${port}`)