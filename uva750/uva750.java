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

    static int a, b;
    static int lineCount;
    static int[] row;
    // which rows, left and right diagonals already have a queen
    static boolean[] takenRows, takenLeftDiag, takenRightDiag;

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
        if (c == 8 && row[b] == a) {
            pr.printf("%2d      ", lineCount++);
            int[] sol = row;
            for (int j = 0; j < 7; j++) {
                pr.print(sol[j] + 1 + " ");
            }
            pr.print(sol[7] + 1 + "\n");
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

        int tc = parseInt(br.readLine());

        for (int TC = 0; TC < tc; TC++) {
            br.readLine();
            String[] nums = br.readLine().split(" ");
            a = parseInt(nums[0]) - 1;
            b = parseInt(nums[1]) - 1;
            lineCount = 1;

            pr.println("SOLN       COLUMN");
            pr.println(" #      1 2 3 4 5 6 7 8\n");
            backtrack(0);
            if (TC < tc - 1) {
                pr.println();
            }
        }

        br.close();
        pr.close();
    }
}
