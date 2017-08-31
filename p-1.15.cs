using System;
using System.Diagnostics;
using System.Collections.Generic;

class Sudoku {
  static Random rand = new Random();

  public static int[,] generate(int blanks = 40) {
    //Generate a full matrix
    var m = new int[9,9];
    bool res = generate(m);
    output(m);
    Console.WriteLine("------------------");
    Trace.Assert(res && check(m));

    //Make some grids blank.
    if (blanks < 10) {
      blanks = 10;
    }
    else if (blanks > 60) {
      blanks = 60;
    }
    var indexes = new HashSet<int>();
    while (indexes.Count < blanks) {
      int x = rand_select(81);
      indexes.Add(x);
    }
    foreach (int t in indexes) {
      int i = t / 9;
      int j = t % 9;
      m[i,j] = 0;
    }

    return m;
  }

  public static bool check(int[,] m) {
    //check each row
    for (int i = 0; i < 9; i++) {
      var put = new int[10];
      for (int j = 0; j < 9; j++) {
        if (m[i,j] > 0 && ++put[m[i,j]] > 1)
          return false;
      }
    }
    //check each column
    for (int i = 0; i < 9; i++) {
      var put = new int[10];
      for (int j = 0; j < 9; j++) {
        if (m[j,i] > 0 && ++put[m[j,i]] > 1)
          return false;
      }
    }
    //check each 3x3 square
    for (int s = 0; s < 9; s++) {
      int r = (s / 3) * 3;
      int c = (s % 3) * 3;
      var put = new int[10];
      for (int i = r; i < r + 3; i++) {
        for (int j = c; j < c + 3; j++) {
          if (m[i,j] > 0 && ++put[m[i,j]] > 1)
            return false;
        }
      }
    }
    return true;
  }

  public static void output(int[,] m) {
    for (int i = 0; i < m.GetLength(0); i++) {
      for (int j = 0; j < m.GetLength(1); j++) {
        char ch = m[i,j] > 0 ? (char)('0' + m[i,j]) : '?';
        Console.Write(ch);
        Console.Write(' ');
      }
      Console.WriteLine();
    }
  }

  private static bool generate(int[,] m, int k = 0) {
    if (k == 81)
      return true;

    int i = k / 9;
    int j = k % 9;
    int r = rand_select(1000);
    for (int n = 0; n < 9; n++) {
      int n2 = (n + r) % 9 + 1;
      m[i,j] = n2;
      if (check(m) && generate(m, k + 1))
        return true;
    }
    m[i,j] = 0;
    return false;
  }

  private static int rand_select(int n) {
    return rand.Next(n);
  }

  static void Main() {
    string line;
    while ((line = Console.ReadLine()) != null) {
      int n = Int32.Parse(line);
      int[,] m = Sudoku.generate(n);
      Sudoku.output(m);
    }
  }
};


