import java.util.*;

class Sudoku {
  static Random rand = new Random();

  public static int[][] generate(int blanks) {
    //Generate a full matrix
    int[][] m = new int[9][9];
    boolean res = generate(m, 0);
    output(m);
    System.out.println("------------------");
    assert(res && check(m));

    //Make some grids blank.
    if (blanks < 10) {
      blanks = 10;
    }
    else if (blanks > 60) {
      blanks = 60;
    }
    Set<Integer> indexes = new HashSet<Integer>();
    while (indexes.size() < blanks) {
      int x = rand_select(81);
      indexes.add(x);
    }
    for (int t : indexes) {
      int i = t / 9;
      int j = t % 9;
      m[i][j] = 0;
    }

    return m;
  }

  public static boolean check(int[][] m) {
    //check each row
    for (int i = 0; i < 9; i++) {
      int[] put = new int[10];
      for (int j = 0; j < 9; j++) {
        if (m[i][j] > 0 && ++put[m[i][j]] > 1)
          return false;
      }
    }
    //check each column
    for (int i = 0; i < 9; i++) {
      int[] put = new int[10];
      for (int j = 0; j < 9; j++) {
        if (m[j][i] > 0 && ++put[m[j][i]] > 1)
          return false;
      }
    }
    //check each 3x3 square
    for (int s = 0; s < 9; s++) {
      int r = (s / 3) * 3;
      int c = (s % 3) * 3;
      int[] put = new int[10];
      for (int i = r; i < r + 3; i++) {
        for (int j = c; j < c + 3; j++) {
          if (m[i][j] > 0 && ++put[m[i][j]] > 1)
            return false;
        }
      }
    }
    return true;
  }

  public static void output(int[][] m) {
    for (int i = 0; i < m.length; i++) {
      for (int j = 0; j < m[i].length; j++) {
        char ch = m[i][j] > 0 ? (char)('0' + m[i][j]) : '?';
        System.out.print(ch);
        System.out.print(' ');
      }
      System.out.println();
    }
  }

  private static boolean generate(int[][] m, int k) {
    if (k == 81)
      return true;

    int i = k / 9;
    int j = k % 9;
    int r = rand_select(1000);
    for (int n = 0; n < 9; n++) {
      int n2 = (n + r) % 9 + 1;
      m[i][j] = n2;
      if (check(m) && generate(m, k + 1))
        return true;
    }
    m[i][j] = 0;
    return false;
  }

  private static int rand_select(int n) {
    return rand.nextInt(n);
  }

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    while (sc.hasNextInt()) {
      int n = sc.nextInt();
      int[][] m = Sudoku.generate(n);
      Sudoku.output(m);
    }
  }
};


