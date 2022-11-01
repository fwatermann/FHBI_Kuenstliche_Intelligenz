package constraints;

import aima.core.search.csp.Assignment;
import aima.core.search.csp.Constraint;
import aima.core.search.csp.Variable;

import java.util.List;
import java.util.Objects;

public class ValueConstraint<T> implements Constraint<Variable, Integer> {

    private final Variable var;
    private final T value;

    public ValueConstraint(Variable var, T value) {
        this.var = var;
        this.value = value;
    }

    @Override
    public List<Variable> getScope() {
        return List.of(var);
    }

    @Override
    public boolean isSatisfiedWith(Assignment<Variable, Integer> assignment) {
        boolean result = Objects.equals(assignment.getValue(var), value);
        //System.out.printf("Value Constraint\t\t %s (%s) = %s => %b%n", var.toString(), assignment.getValue(var), value.toString(), result);
        return result;
    }
}