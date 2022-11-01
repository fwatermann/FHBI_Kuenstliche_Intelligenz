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


        ZebraPuzzle puzzle = new ZebraPuzzle();
        long startTime = System.currentTimeMillis();

        //BackjumpingBacktrackingSolver<Variable, Integer> strategy = new BackjumpingBacktrackingSolver<>();
        //FlexibleBacktrackingSolver<Variable, Integer> strategy = new FlexibleBacktrackingSolver<>();
        //MinConflictsSolver<Variable, Integer> strategy = new MinConflictsSolver<>(100000);
        //SimpleBacktrackingSolver strategy = new SimpleBacktrackingSolver();
        //HeuristikBacktrackingSolver strategy = new HeuristikBacktrackingSolver();
        AC3SimpleBacktrackingSolver strategy = new AC3SimpleBacktrackingSolver();
        Optional<Assignment<Variable, Integer>> result = strategy.solve(puzzle);

        if (result.isEmpty()) {
            System.out.println("No solution found");
        } else {
            System.out.println(result.get().toString());
        }

        long endTime = System.currentTimeMillis();
        long duration = (endTime - startTime);
        System.out.printf("Time: %.3f sec%n", (duration / 1000.0));

    }

}