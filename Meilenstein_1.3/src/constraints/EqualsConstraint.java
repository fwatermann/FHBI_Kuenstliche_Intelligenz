package constraints;

import aima.core.search.csp.Assignment;
import aima.core.search.csp.Constraint;
import aima.core.search.csp.Variable;

import java.util.List;
import java.util.Objects;

public class EqualsConstraint implements Constraint<Variable, Integer> {

    private final Variable var1, var2;

    public EqualsConstraint(Variable var1, Variable var2) {
        this.var1 = var1;
        this.var2 = var2;
    }

    @Override
    public List<Variable> getScope() {
        return List.of(var1, var2);
    }

    @Override
    public boolean isSatisfiedWith(Assignment<Variable, Integer> assignment) {
        if ((assignment.getValue(var1) == null && assignment.getValue(var2) != null) || assignment.getValue(var2) == null && assignment.getValue(var1) != null) {
            return true;
        }
        boolean result = Objects.equals(assignment.getValue(var1), assignment.getValue(var2));
        //System.out.printf("EqualConstraint\t\t\t %s(%s) = %s(%s) => %b%n", var1.toString(), assignment.getValue(var1), var2.toString(), assignment.getValue(var2), result);
        return result;
    }
}
