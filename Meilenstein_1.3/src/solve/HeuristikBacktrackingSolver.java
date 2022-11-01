package solve;

import aima.core.search.csp.Assignment;
import aima.core.search.csp.CSP;
import aima.core.search.csp.Variable;
import aima.core.search.csp.solver.AbstractBacktrackingSolver;
import aima.core.search.csp.solver.CspHeuristics;
import aima.core.search.csp.solver.inference.InferenceLog;

import java.util.List;

public class HeuristikBacktrackingSolver extends AbstractBacktrackingSolver<Variable, Integer> {

    private final CspHeuristics.MrvHeuristic<Variable, Integer> mrvHeuristic = new CspHeuristics.MrvHeuristic<>();
    private final CspHeuristics.DegHeuristic<Variable, Integer> degHeuristic = new CspHeuristics.DegHeuristic<>();

    @Override
    protected Variable selectUnassignedVariable(CSP<Variable, Integer> csp, Assignment<Variable, Integer> assignment) {
        List<Variable> vars = csp.getVariables().stream().filter(v -> !assignment.contains(v)).toList();
        vars = this.mrvHeuristic.apply(csp, vars);
        if(vars.size() > 1) {
            vars = this.degHeuristic.apply(csp, vars);
        }
        return vars.get(0);
    }

    @Override
    protected Iterable<Integer> orderDomainValues(CSP<Variable, Integer> csp, Assignment<Variable, Integer> assignment, Variable variable) {
        return csp.getDomain(variable);
    }

    @Override
    protected InferenceLog<Variable, Integer> inference(CSP<Variable, Integer> csp, Assignment<Variable, Integer> assignment, Variable variable) {
        return InferenceLog.emptyLog();
    }



}
