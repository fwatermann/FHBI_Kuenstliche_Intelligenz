import aima.core.search.csp.CSP;
import aima.core.search.csp.Domain;
import aima.core.search.csp.Variable;
import constraints.*;

import java.util.Arrays;
import java.util.HashMap;

public class ZebraPuzzle extends CSP<Variable, Integer> {

    public static final String[] variableNames = {"Rot", "Gelb", "Grün", "Blau", "Weiß", "England", "Spanien", "Ukraine", "Japan", "Norwegen", "Kaffee", "Tee", "Milch", "Orangensaft", "Wasser", "Kools", "Chesterfield", "OldGold", "Parliament", "LuckyStrike", "Fuchs", "Pferd", "Schnecken", "Hund", "Zebra"};
    private final HashMap<String, Variable> variables = new HashMap<>();
    private final Domain<Integer> domain;

    public ZebraPuzzle() {
        domain = new Domain<>(Arrays.asList(1, 2, 3, 4, 5));

        Arrays.stream(variableNames).forEach(varName -> {
            Variable var = new Variable(varName);
            addVariable(var);
            setDomain(var, domain);
            variables.put(varName, var);
            //System.out.println(var.toString() + " -> " + this.getDomain(var).toString());
        });

        this.addConstraint(new ValueConstraint<>(variables.get("Norwegen"), 1));
        this.addConstraint(new EqualsConstraint(variables.get("England"), variables.get("Rot")));
        this.addConstraint(new EqualsConstraint(variables.get("Spanien"), variables.get("Hund")));
        this.addConstraint(new EqualsConstraint(variables.get("Kaffee"), variables.get("Grün")));
        this.addConstraint(new EqualsConstraint(variables.get("Ukraine"), variables.get("Tee")));
        this.addConstraint(new IsSideNeighbour(variables.get("Grün"), variables.get("Weiß")));
        this.addConstraint(new EqualsConstraint(variables.get("OldGold"), variables.get("Schnecken")));
        this.addConstraint(new EqualsConstraint(variables.get("Kools"), variables.get("Gelb")));
        this.addConstraint(new ValueConstraint<>(variables.get("Milch"), 3));
        this.addConstraint(new NeighbourConstraint(variables.get("Chesterfield"), variables.get("Fuchs")));
        this.addConstraint(new NeighbourConstraint(variables.get("Kools"), variables.get("Pferd")));
        this.addConstraint(new EqualsConstraint(variables.get("LuckyStrike"), variables.get("Orangensaft")));
        this.addConstraint(new EqualsConstraint(variables.get("Japan"), variables.get("Parliament")));
        this.addConstraint(new NeighbourConstraint(variables.get("Norwegen"), variables.get("Blau")));
        this.addConstraint(new NeighbourConstraint(variables.get("Chesterfield"), variables.get("Wasser")));

        //Hinzufügen aller NotEqual Constraints. (Ein Haus kann nur eine Farbe, eine Nationalität, eine Zigarette-Marke, ein Getränk und ein Haustier haben)
        for(int i = 0; i < variableNames.length; i+=5) {
            for(int j = i; j < i+5; j ++) {
                for(int k = j+1; k < i+5; k++) {
                    this.addConstraint(new NotEqualConstraint(variables.get(variableNames[j]), variables.get(variableNames[k])));
                }
            }
        }

    }

}
