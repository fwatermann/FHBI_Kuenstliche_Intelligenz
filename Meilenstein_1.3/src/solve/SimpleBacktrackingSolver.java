package solve;

import aima.core.search.csp.Assignment;
import aima.core.search.csp.CSP;
import aima.core.search.csp.Variable;
import aima.core.search.csp.solver.AbstractBacktrackingSolver;
import aima.core.search.csp.solver.inference.InferenceLog;

import java.util.List;

public class SimpleBacktrackingSolver extends AbstractBacktrackingSolver<Variable, Integer> {

    @Override
    protected Variable selectUnassignedVariable(CSP<Variable, Integer> csp, Assignment<Variable, Integer> assignment) {
        List<Variable> vars = csp.getVariables().stream().filter(v -> !assignment.contains(v)).toList();
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
