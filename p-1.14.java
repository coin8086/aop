import java.util.*;

class Solution {
  public static class Grid {
    public int first;
    public int second;
    public Grid(int x, int y) { first = x; second = y; }
  };

  public static Grid[] solve(char[][] b, Grid p1, Grid p2) {
    int m = b.length;
    int n = b[0].length;
    int s = p1.first * n + p1.second;
    int t = p2.first * n + p2.second;
    int total = m * n;
    int[] pred = new int[total];
    for (int i = 0; i < total; i++) {
      pred[i] = -1;
    }
    boolean[] found = new boolean[total];
    int[] turn = new int[total];
    for (int i = 0; i < total; i++) {
      turn[i] = Integer.MAX_VALUE;
    }
    Queue<Integer> q = new LinkedList<Integer>();
    q.add(s);
    found[s] = true;
    turn[s] = -1;

    //Temporarily set target grid to '.' so that it can be reached by the BFS.
    char ch = b[p2.first][p2.second];
    b[p2.first][p2.second] = '.';

    int[][] d = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    //The BFS targets at the status of corners and numbers of grids on the path.
    //The algorithm meets the primary dimension(least corners) as the Book says.
    //However, for the secondary one, it ensures that by the enqueuing order of
    //"the same level" of grids.
    while (q.size() > 0) {
      int p = q.peek();
      q.remove();
      if (p == t) { //Optionally: (... || turn[p] > 2)
        break;
      }
      else {
        int i = p / n;
        int j = p % n;
        boolean[] stop = new boolean[4];

        //Try one step in each of the four directions from (i, j). Then the next
        //step involves grids that are one step further from (i, j).
        for (int step = 1;; step++) {
          int k;
          for (k = 0; k < 4; k++) {
            if (stop[k]) {
              continue;
            }
            int x = i + d[k][0] * step;
            int y = j + d[k][1] * step;
            int l = x * n + y;
            if (x >= 0 && x < m && y >= 0 && y < n && b[x][y] == '.' && (!found[l] || turn[l] > turn[p])) {
              if (!found[l]) {
                q.add(l);
                found[l] = true;
                turn[l] = turn[p] + 1;
                pred[l] = p;
              }
              else {
                //Just "cross" the grid. And there must be ...
                assert(turn[l] == turn[p] + 1);
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
    b[p2.first][p2.second] = ch;

    //build path
    List<Grid> res = new ArrayList<Grid>();
    if (pred[t] != -1) {
      int p = t;
      while (p != s) {
        res.add(new Grid(p / n, p % n));
        p = pred[p];
      }
      Collections.reverse(res);
    }
    return res.toArray(new Grid[0]);
  }

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int m = sc.nextInt();
    int n = sc.nextInt();
    sc.nextLine(); //Move to next line! The result of this nextLine() should be blank.
    char[][] b = new char[m][n];
    for (int i = 0; i < m; i++) {
      String line = sc.nextLine();
      for (int j = 0; j < n; j++) {
        b[i][j] = line.charAt(j);
      }
    }

    while (sc.hasNextInt()) {
      int p1i = sc.nextInt();
      int p1j = sc.nextInt();
      int p2i = sc.nextInt();
      int p2j = sc.nextInt();

      Grid[] res = solve(b, new Grid(p1i, p1j), new Grid(p2i, p2j));
      if (res.length == 0) {
        System.out.println("Impossible!");
      }
      else {
        for (int i = 0; i < res.length; i++) {
          if (i != 0)
            System.out.print(' ');
          System.out.print(String.format("(%d,%d)", res[i].first, res[i].second));
        }
      }
      System.out.println();
    }
  }
};

