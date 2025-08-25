import java.io.File
import java.util.Scanner
import java.util.concurrent.ConcurrentLinkedQueue
import java.util.concurrent.atomic.AtomicLong
import java.util.concurrent.ThreadLocalRandom

class Sluzbenica(id : Int, kamata : Int, kapital : AtomicLong, red : ConcurrentLinkedQueue[Klijent], odobreni : ConcurrentLinkedQueue[Klijent]) extends Thread {
  override def run(): Unit = {
    while(true) {
      val k : Klijent = red.poll()
      if (k == null)
        return

      println(s"Klijent ${k.getIme} razgovara sa sluzbenicom $id...")
      Thread.sleep(ThreadLocalRandom.current().nextInt(1, 10) * 1000) // broj sekundi spavanja

      kapital.synchronized {
        if (k.getPozajmica > kapital.get())
          println(s"Klijent ${k.getIme} ne moze dobiti kredit")
        else {
          val nKap = kapital.get() - k.getPozajmica
          kapital.set(nKap)
          val dug = k.getPozajmica * ((100 + kamata.toFloat) / 100)
          k.setDug(dug)
          println(s"Klijent ${k.getIme} je dobio kredit u iznosu od ${k.getPozajmica} dinara. Ukupan dug sa kamatom je $dug dinara.")
          odobreni.add(k)
        }
      }
    }
  }
}

class Klijent(ime : String, pozajmica : Int) {
  var dug : Float = 0

  def getIme : String = ime
  def getPozajmica : Int = pozajmica
  def getDug : Float = dug

  def setDug(d : Float) : Unit = { dug = d }
}

object Banka {
  def main(args : Array[String]): Unit = {
    val sc1 : Scanner = new Scanner(System.in)
    println("Unesti pocetni kapital banke:")
    val kapital = new AtomicLong(sc1.nextLong()) // atomicke promenljive sa kojima rade niti
    val pocetniKapital : Float = kapital.get()

    println("Unesite kamatnu stopu:")
    val kamata = sc1.nextInt()

    println("Unesite broj sluzbenica u ekspozituri:")
    val n = sc1.nextInt()
    val sluzbenice = new Array[Sluzbenica](n)
    sc1.close()

    val sc2 : Scanner = new Scanner(new File("klijenti.txt"))
    val red : ConcurrentLinkedQueue[Klijent] = new ConcurrentLinkedQueue[Klijent]()
    val odobreni : ConcurrentLinkedQueue[Klijent] = new ConcurrentLinkedQueue[Klijent]()
    while(sc2.hasNextLine)
      red.add(new Klijent(sc2.next(), sc2.nextInt()))
    sc2.close()

    for(i <- sluzbenice.indices) // range svih indeksa
      sluzbenice(i) = new Sluzbenica(i + 1, kamata, kapital, red, odobreni)

    sluzbenice.foreach(_.start())
    sluzbenice.foreach(_.join())

    // red prebacimo u stream, klijente mapiramo u dug i saberemo
    val ukupanDug = odobreni.stream().mapToDouble(k => k.getDug.toDouble).sum()
    println(s"Ukupna dobit banke je ${ukupanDug - pocetniKapital} dinara.")
  }
}