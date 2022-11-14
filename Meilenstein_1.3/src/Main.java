import aima.core.search.csp.Assignment;
import aima.core.search.csp.Variable;
import aima.core.search.csp.solver.BackjumpingBacktrackingSolver;
import solve.AC3SimpleBacktrackingSolver;
import solve.HeuristikBacktrackingSolver;
import solve.SimpleBacktrackingSolver;

import java.util.Optional;

public class Main {

    //Zebra Puzzle
    public static void main(String[] args) {

        long totalTime = 0;

        /* BT_SEARCH */

        long btSearchTime = 0;
        int btSearchSuccess = 0;
        for(int i = 0; i < 100; i++) {
            ZebraPuzzle puzzle = new ZebraPuzzle();
            SimpleBacktrackingSolver bt = new SimpleBacktrackingSolver();
            long startTime = System.currentTimeMillis();
            Optional<Assignment<Variable, Integer>> solution = bt.solve(puzzle);
            long endTime = System.currentTimeMillis();
            if(solution.isPresent()) btSearchSuccess++;
            btSearchTime += endTime - startTime;
        }
        System.out.printf("BT_SEARCH: %.3f ms Successful: %d%n", (double) btSearchTime / 100, btSearchSuccess);

        /* Heuristik_BT_SEARCH */

        long heuristikBtSearchTime = 0;
        int heuristicSuccess = 0;
        for(int i = 0; i < 100; i++) {
            ZebraPuzzle puzzle = new ZebraPuzzle();
            HeuristikBacktrackingSolver bt = new HeuristikBacktrackingSolver();
            long startTime = System.currentTimeMillis();
            Optional<Assignment<Variable, Integer>> solution = bt.solve(puzzle);
            long endTime = System.currentTimeMillis();
            if(solution.isPresent()) heuristicSuccess++;
            heuristikBtSearchTime += endTime - startTime;
        }
        System.out.printf("Heuristik_BT_SEARCH: %.3f ms Successful: %d%n", (double) heuristikBtSearchTime / 100, heuristicSuccess);

        /* AC3_BT_SEARCH */

        long ac3BtSearchTime = 0;
        int ac3Success = 0;
        for(int i = 0; i < 100; i++) {
            ZebraPuzzle puzzle = new ZebraPuzzle();
            AC3SimpleBacktrackingSolver bt = new AC3SimpleBacktrackingSolver();
            long startTime = System.currentTimeMillis();
            Optional<Assignment<Variable, Integer>> solution = bt.solve(puzzle);
            long endTime = System.currentTimeMillis();
            if(solution.isPresent()) ac3Success++;
            ac3BtSearchTime += endTime - startTime;
        }
        System.out.printf("AC3_BT_SEARCH: %.3f ms Successful: %d%n", (double) ac3BtSearchTime / 100, ac3Success);

    }

}