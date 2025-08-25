import org.apache.spark.{SparkConf, SparkContext}
import scala.compat.Platform

object Main {
  def main(args: Array[String]): Unit = {
    //JavaLog()
    //Preuzimanja()
    //Pokloni()
    //Temperatura()
    Automobili()
  }

  def JavaLog(): Unit = {
    val conf = new SparkConf()
      .setAppName("App")
      .setMaster("local[4]")
    val sc = new SparkContext(conf)

    val res = sc
      .textFile("datoteke/log.txt")
      .filter(line => line.contains("java") && (line.startsWith("[info] ") || line.startsWith("[warn] ") || line.startsWith("[error] ")))
      .map(line => {
        val spl = line.split(" ")
        (spl(0), spl.drop(1).mkString(" "))
      })
      .groupByKey()
      .map(kvp => (kvp._1, kvp._2.size))
      .collect()

      sc.stop()

      res.foreach(kvp => println(kvp))
  }

  def Preuzimanja(): Unit = {
    val conf = new SparkConf()
      .setAppName("App")
      .setMaster("local[4]")
    val sc = new SparkContext(conf)

    val file = sc
      .textFile("datoteke/mavenLog.txt")
      .cache()

    val downloading = file
      .filter(_.startsWith("[Downloading"))
      .count()

    val downloaded = file
      .filter(_.startsWith("[Downloaded"))
      .count()

    sc.stop()

    println(downloaded.toDouble / downloading.toDouble)
  }

  def Pokloni(): Unit = {
    val conf = new SparkConf()
      .setAppName("App")
      .setMaster("local[4]")
    val sc = new SparkContext(conf)

    val res = sc
      .textFile("datoteke/zaposleni.txt")
      .map(line => {
        val spl = line.split(" ")
        (spl(0), spl(1), spl(6))
      })
      .filter(t => t._3 == "IT_PROG")
      .map(t => (t._1, t._2))
      .takeSample(false, 3, Platform.currentTime)

    sc.stop()

    res.foreach(kvp => println(s"${kvp._1} ${kvp._2}"))
  }

  def Temperatura(): Unit = {
    val conf = new SparkConf()
      .setAppName("App")
      .setMaster("local[4]")

    val sc = new SparkContext(conf)

    val res = sc
      .textFile("datoteke/temperatura.txt")
      .map(line => {
        val spl = line.split(" ")
        (spl(2).toInt, spl(3).toDouble)
      })
      .groupByKey()
      .map(kvp => {
        val tempF = kvp._2.sum / kvp._2.size
        val tempC = (tempF - 32.0) / 1.8
        (kvp._1, tempF)
      })
      .sortByKey()
      .collect()

    val res2 = sc
      .textFile("datoteke/temperatura.txt")
      .map(line => {
        val spl = line.split(" ")
        (spl(2).toInt, (spl(0).toInt, spl(1).toInt, spl(3).toDouble))
      })
      .aggregateByKey((0.0, 0))((acc, v) => (acc._1 + v._3, acc._2 + 1), (acc1, acc2) => (acc1._1 + acc2._1, acc1._2 + acc2._2))
      .map(kvp => {
        val tempF = kvp._2._1 / kvp._2._2
        val tempC = (tempF - 32.0) / 1.8
        (kvp._1, tempF)
      })
      .sortByKey()
      .collect()

    res.foreach(kvp => println(s"Prosecna temperatura ${kvp._1}. godine je ${kvp._2}"))
    res2.foreach(kvp => println(s"Prosecna temperatura ${kvp._1}. godine je ${kvp._2}"))

  }

  def Automobili () : Unit = {
    val conf = new SparkConf()
      .setAppName("Aplikacija")
      .setMaster("local[4]")

    val sc = new SparkContext(conf)

    val res = sc
      .textFile("cars.csv")
      .map(car => {
        val spl = car.split(",")
        // (pogon, godina, snaga, gorivo, prenos, potrosnja)
        (spl(0), spl(7).toInt, spl(8).toInt, spl(4), spl(2), spl(3).toInt)
      })
      .filter(car => car._2 > 2010) // nakon 2010. godine
      .filter(car => car._1 == "AWD") // AWD pogon
      .filter(car => car._3 > 100) // vise od 100 konjskih snaga
      .filter(car => car._4 == "Gasoline") // koriste benzin
      .filter(car => car._5.contains("Automatic")) // automatik
      .filter(car => {
        val spl = car._5.split(" ")
        spl(0).toInt >= 5
      }) // 5 brzina ili vise
      .map(car => car._6)

    val suma = res.sum()
    val broj = res.count()

    sc.stop()

    val prosek = suma.toDouble / broj.toDouble
    println(s"${prosek} mpg")
  }
}