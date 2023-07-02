package workspace.formulanodes;

public class ReImplicationNode extends BinNode{
    ReImplicationNode(ReImplicationNode node) {super(node);}

    public ReImplicationNode(FormulaNode left, FormulaNode right) {super(left, right);}

    @Override
    public boolean calc() {return left.calc() || !right.calc();}

    @Override
    public String toString() {return String.format("(%s < %s)", left.toString(),right.toString());}

    @Override
    public FormulaNode create() {return new ReImplicationNode(this);}
}
