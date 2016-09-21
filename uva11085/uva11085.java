import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.PrintWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.*;
import java.lang.Math;

class Main {
    static boolean debugOn = true;
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter pr = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

    static int[] row;
    // which rows, left and right diagonals already have a queen
    static boolean[] takenRows, takenLeftDiag, takenRightDiag;
    static ArrayList<int[]> solutions = new ArrayList<int[]>();

    static <T> void debug(T x) {
        if (debugOn) {
            pr.println(x);
        }
    }

    static void debug(String format, Object... x) {
        if (debugOn) {
            pr.printf(format, x);
        }
    }

    static void debug(int[] arr) {
        for (int i = 0; i < arr.length; i++) {
            pr.print(arr[i] + " ");
        }
        pr.println();
    }

    static int parseInt(String s) {
        return Integer.parseInt(s);
    }

    static void backtrack(int c) {
        if (c == 8) {
            solutions.add(row.clone());
        }
        for (int r = 0; r < 8; r++) { // try all possible rows for column c
            if (!takenRows[r] && !takenLeftDiag[r - c + 7] && !takenRightDiag[r + c]) {
                takenRows[r] = takenLeftDiag[r - c + 7] = takenRightDiag[r + c] = true;
                row[c] = r;
                backtrack(c + 1);
                takenRows[r] = takenLeftDiag[r - c + 7] = takenRightDiag[r + c] = false;
            }
        }
    }

    public static void main(String[] args) throws Exception {
        // precompute all 92 8 queens solutions and search for one that minimizes the distance

        row = new int[8];
        takenRows = new boolean[8];
        takenLeftDiag = new boolean[15];
        takenRightDiag = new boolean[15];
        backtrack(0);

        int tc = 1;
        int[] input;

        while (br.ready()) {
            input = new int[8];
            String[] nums = br.readLine().split(" ");
            for (int i = 0; i < nums.length; i++) {
                input[i] = parseInt(nums[i]) - 1;
            }

            int minMoves = 8;
            for (int i = 0; i < solutions.size(); i++) {
                int moves = 0;
                int[] sol = solutions.get(i);
                for (int j = 0; j < 8; j++) {
                    moves += sol[j] == input[j] ? 0 : 1;
                }
                minMoves = Math.min(moves, minMoves);
            }

            pr.printf("Case %d: %d\n", tc++, minMoves);
        }

        br.close();
        pr.close();
    }
}
