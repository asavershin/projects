package workspace.formulanodes;

public class PierceArrowNode extends BinNode{
    PierceArrowNode(PierceArrowNode node) {super(node);}

    public PierceArrowNode(FormulaNode left, FormulaNode right) {super(left, right);}

    @Override
    public boolean calc() {return !left.calc() && !right.calc();}

    @Override
    public String toString() {
        return String.format("(%s ^ %s)", left.toString(),right.toString());
    }

    @Override
    public FormulaNode create() {return new PierceArrowNode(this);}
}
