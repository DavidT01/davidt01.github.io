import java.io.File
import java.util
import java.util.Scanner
import java.util.concurrent.ThreadLocalRandom
import scala.collection.mutable.HashMap
import scala.collection.mutable.ArrayBuffer

class Kladionicar(ime : String,
                  novac : Int,
                  tiket : HashMap[String, Char],
                  utakmice : HashMap[String, (Float, Float, Float, Char)])
  extends Thread {
  var zarada : Float = 0
  override def run(): Unit = {
    // cekamo rezultate utakmica
    utakmice.synchronized {
      utakmice.wait()
    }

    var pogodjeno : Int = 0
    var ukupnaKvota : Float = 0
    for(kvp <- tiket) {
      if(kvp._2 == utakmice(kvp._1)._4) {
        println(s"$ime je pogodio utakmicu ${kvp._1} - ${kvp._2}")
        pogodjeno += 1
        if(kvp._2 == '1')
          ukupnaKvota += utakmice(kvp._1)._1
        else if(kvp._2 == 'x')
          ukupnaKvota += utakmice(kvp._1)._2
        else if(kvp._2 == '2')
          ukupnaKvota += utakmice(kvp._1)._3
      }
    }

    if(pogodjeno > 0)
      zarada = ukupnaKvota * novac

    println(s"Kladionicar $ime je zaradio $zarada dinara.")
  }
}

object Kladionica {
  def main(args : Array[String]): Unit = {
    val sc1 : Scanner = new Scanner(new File("utakmice.txt"))
    val sc2 : Scanner = new Scanner(new File("kladionicari.txt"))

    val utakmice = new HashMap[String, (Float, Float, Float, Char)]
    while(sc1.hasNextLine) {
      utakmice.put(sc1.nextLine(), (sc1.nextFloat(), sc1.nextFloat(), sc1.nextFloat(), '-'))
      sc1.nextLine()
    }
    sc1.close()

    val kladionicari = new ArrayBuffer[Kladionicar]()
    while(sc2.hasNextLine) {
      val ime = sc2.next()
      val novac = sc2.nextInt()
      val tiket = new HashMap[String, Char]
      for(i <- 0 until 5) {
        sc2.nextLine()
        tiket.put(sc2.nextLine(), sc2.next()(0))
      }
      kladionicari.append(new Kladionicar(ime, novac, tiket, utakmice))
    }

    kladionicari.foreach(_.start())

    println("Cekam rezultate utakmica...")
    Thread.sleep(4000)

    val moguciIshodi = Array('1', 'x', '2')
    for(kvp <- utakmice) {
      val ishod = moguciIshodi(ThreadLocalRandom.current().nextInt(0, 3))
      utakmice(kvp._1) = (kvp._2._1, kvp._2._2, kvp._2._3, ishod)
    }

    // signaliziramo svima koji cekaju utakmice da mogu da nastave dalje
    utakmice.synchronized {
      utakmice.notifyAll()
    }

    kladionicari.foreach(_.join())
  }
}