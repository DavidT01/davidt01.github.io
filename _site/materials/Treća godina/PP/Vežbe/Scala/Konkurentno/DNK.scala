import java.io.File
import java.util.Scanner
import java.util.concurrent.ConcurrentHashMap
import scala.collection.mutable.ArrayBuffer

class Brojac(poc : Int, kr : Int, linije : ArrayBuffer[String], mapa : ConcurrentHashMap[Char, Int])
  extends Thread {
  override def run(): Unit = {
    for(i <- poc until kr)
      val a = linije(i).count(_ == 'A')
      val c = linije(i).count(_ == 'C')
      val g = linije(i).count(_ == 'G')
      val t = linije(i).count(_ == 'T')

      mapa.synchronized {
        mapa.replace('A', mapa.get('A') + a)
        mapa.replace('C', mapa.get('C') + c)
        mapa.replace('G', mapa.get('G') + g)
        mapa.replace('T', mapa.get('T') + t)
      }
  }
}

object DNK {
  def main(args : Array[String]): Unit = {
    val sc1 : Scanner = new Scanner(new File("bio.txt"))
    val sc2 : Scanner = new Scanner(System.in)

    println("Broj procesora: " + Runtime.getRuntime.availableProcessors())
    println("Unesi broj niti:")
    val n = sc2.nextInt()
    sc2.close()

    val linije = new ArrayBuffer[String]()
    while(sc1.hasNextLine)
      linije.append(sc1.nextLine())
    sc1.close()
    val brojLinija = linije.length

    val mapa = new ConcurrentHashMap[Char, Int](4, 4, n)
    mapa.put('A', 0)
    mapa.put('C', 0)
    mapa.put('G', 0)
    mapa.put('T', 0)

    val brojaci = new Array[Brojac](n)
    val korak = Math.ceil(brojLinija.toDouble / n.toDouble).toInt
    for(i <- 0 until n)
      brojaci(i) = new Brojac(i * korak, Math.min((i + 1) * korak, brojLinija), linije, mapa)

    brojaci.foreach(b => b.start())
    brojaci.foreach(_.join())

    println("Rezultati")
    println(s"A: ${mapa.get('A')}")
    println(s"C: ${mapa.get('C')}")
    println(s"G: ${mapa.get('G')}")
    println(s"T: ${mapa.get('T')}")
  }
}