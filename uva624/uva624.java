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
    static int N, t, bestLen;
    static int[] tracks, best;

    static void debug(Object x) {
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
        if (debugOn) {
            for (int i = 0; i < arr.length; i++) {
                pr.printf("%d ", arr[i]);
            }
            pr.println();
        }
    }

    static int parseInt(String s) {
        return Integer.parseInt(s);
    }

    static void backtrack(int[] curSol, int tIdx, int sIdx, int curLen) {
        if (tIdx >= t || sIdx >= t) { // check if sol is better than prevBest
            if (curLen > bestLen) {
                bestLen = curLen;
                best = curSol.clone();
            }
            return;
        }
        for (int i = tIdx; i < t; i++) {
            if (curLen + tracks[i] <= N) {
                curSol[sIdx] = tracks[i];
                backtrack(curSol.clone(), i + 1, sIdx + 1, curLen + tracks[i]);
            }
            else {
                if (curLen > bestLen) {
                    bestLen = curLen;
                    best = curSol.clone();
                }
            }
        }
    }

    public static void main(String[] args) throws Exception {
        while(br.ready()) {
            String line = br.readLine().trim();
            String[] parts = line.split(" ");
            if (line.length() == 0 || line == "" || line == "\n" || parts.length == 0 || parts[0] == "") {
                break;
            }
            N = parseInt(parts[0]);
            t = parseInt(parts[1]);
            tracks = new int[t];
            for (int i = 0; i < t; i++) {
                tracks[i] = parseInt(parts[2+i]);
            }

            bestLen = 0;
            int[] sol = new int[t]; // track lengths in current best solution
            best = new int[t];
            for (int i = 0; i < t; i++) {
                Arrays.fill(sol, -1);
                backtrack(sol, i, 0, 0);
            }

            int i = 0;
            while (i < t && best[i] > 0) {
                pr.printf("%d ", best[i++]);
            }
            pr.printf("sum:%d\n", bestLen);
        }

        br.close();
        pr.close();
    }
}
