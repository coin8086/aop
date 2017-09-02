using System;
using System.Diagnostics;
using System.Collections.Generic;
using System.Text.RegularExpressions;

class Solution {
  public struct Grid {
    public int first;
    public int second;
    public Grid(int x, int y) { first = x; second = y; }
  };

  public static Grid[] solve(char[,] b, Grid p1, Grid p2) {
    int m = b.GetLength(0);
    int n = b.GetLength(1);
    int s = p1.first * n + p1.second;
    int t = p2.first * n + p2.second;
    int total = m * n;
    var pred = new int[total];
    for (int i = 0; i < total; i++) {
      pred[i] = -1;
    }
    var found = new bool[total];
    var turn = new int[total];
    for (int i = 0; i < total; i++) {
      turn[i] = Int32.MaxValue;
    }
    var q = new Queue<int>();
    q.Enqueue(s);
    found[s] = true;
    turn[s] = -1;

    //Temporarily set target grid to '.' so that it can be reached by the BFS.
    char ch = b[p2.first, p2.second];
    b[p2.first, p2.second] = '.';

    var d = new int[4, 2] {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    //The BFS targets at the status of corners and numbers of grids on the path.
    //The algorithm meets the primary dimension(least corners) as the Book says.
    //However, for the secondary one, it ensures that by the enqueuing order of
    //"the same level" of grids.
    while (q.Count > 0) {
      int p = q.Peek();
      q.Dequeue();
      if (p == t) { //Optionally: (... || turn[p] > 2)
        break;
      }
      else {
        int i = p / n;
        int j = p % n;
        var stop = new bool[4];

        //Try one step in each of the four directions from (i, j). Then the next
        //step involves grids that are one step further from (i, j).
        for (int step = 1;; step++) {
          int k;
          for (k = 0; k < 4; k++) {
            if (stop[k]) {
              continue;
            }
            int x = i + d[k, 0] * step;
            int y = j + d[k, 1] * step;
            int l = x * n + y;
            if (x >= 0 && x < m && y >= 0 && y < n && b[x, y] == '.' && (!found[l] || turn[l] > turn[p])) {
              if (!found[l]) {
                q.Enqueue(l);
                found[l] = true;
                turn[l] = turn[p] + 1;
                pred[l] = p;
              }
              else {
                //Just "cross" the grid. And there must be ...
                Trace.Assert(turn[l] == turn[p] + 1);
              }
            }
            else {
              stop[k] = true;
            }
          }

          for (k = 0; k < 4; k++) {
            if (!stop[k])
              break;
          }
          if (k == 4) { //All stopped.
            break;
          }
        }
      }
    }

    //Set the old content back to target.
    b[p2.first, p2.second] = ch;

    //build path
    var res = new List<Grid>();
    if (pred[t] != -1) {
      int p = t;
      while (p != s) {
        res.Add(new Grid(p / n, p % n));
        p = pred[p];
      }
      res.Reverse();
    }
    return res.ToArray();
  }

  static void Main() {
    string line = Console.ReadLine();
    Match ma = Regex.Match(line, @"(\d+)\s+(\d+)");
    int m = Int32.Parse(ma.Groups[1].Value);
    int n = Int32.Parse(ma.Groups[2].Value);

    var b = new char[m, n];
    for (int i = 0; i < m; i++) {
      line = Console.ReadLine();
      for (int j = 0; j < n; j++) {
        b[i, j] = line[j];
      }
    }

    while ((line = Console.ReadLine()) != null) {
      ma = Regex.Match(line, @"(\d+)\s+(\d+)\s+(\d+)\s+(\d+)");
      int p1i = Int32.Parse(ma.Groups[1].Value);
      int p1j = Int32.Parse(ma.Groups[2].Value);
      int p2i = Int32.Parse(ma.Groups[3].Value);
      int p2j = Int32.Parse(ma.Groups[4].Value);

      Grid[] res = solve(b, new Grid(p1i, p1j), new Grid(p2i, p2j));
      if (res.Length == 0) {
        Console.Write("Impossible!");
      }
      else {
        for (int i = 0; i < res.Length; i++) {
          if (i != 0)
            Console.Write(' ');
          Console.Write($"({res[i].first},{res[i].second})");
        }
      }
      Console.WriteLine();
    }
  }
};


