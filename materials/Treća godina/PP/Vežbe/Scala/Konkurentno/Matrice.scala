import java.util.Scanner
import java.io.{File, PrintWriter}
import scala.Array.ofDim

class MultiplierThread(vr : Array[Int],
                       mat : Array[Array[Int]],
                       res : Array[Int]) extends Thread {

  val m : Int = vr.length
  val k : Int = mat(0).length

  override def run(): Unit = {
    for (i <- 0 until k)
      res(i) = dotProduct(i)
  }

  def dotProduct(j : Int) : Int = {
    var t = 0
    for (i <- 0 until m)
      t += vr(i) * mat(i)(j)
    t
  }
}

object Main {
  def main(args: Array[String]): Unit = {
    val sc1 : Scanner = new Scanner(new File("1.txt"))
    val sc2 : Scanner = new Scanner(new File("2.txt"))
    val pw : PrintWriter = new PrintWriter(new File("res.txt"))

    val n = sc1.nextInt()
    val m1 = sc1.nextInt()
    val m2 = sc2.nextInt()
    val k = sc2.nextInt()

    if (m1 != m2) {
      println("Dimension missmatch!")
      return
    }

    val mat1 = ofDim[Int](n, m1)
    val mat2 = ofDim[Int](m2, k)
    val res = ofDim[Int](n, k)

    for (i <- 0 until n)
      for(j <- 0 until m1)
        mat1(i)(j) = sc1.nextInt()

    for (i <- 0 until m2)
      for (j <- 0 until k)
        mat2(i)(j) = sc2.nextInt()

    val ths = new Array[MultiplierThread](n)
    for (i <- 0 until n)
      ths(i) = new MultiplierThread(mat1(i), mat2, res(i))

    for (i <- 0 until n)
      ths(i).start()

    for (i <- 0 until n)
      ths(i).join()

    pw.println(s"$n $k")
    for (i <- 0 until n) {
      for (j <- 0 until k) {
        pw.append(res(i)(j).toString)
        pw.append(' ')
      }
      pw.println()
    }
    pw.close()
  }
}