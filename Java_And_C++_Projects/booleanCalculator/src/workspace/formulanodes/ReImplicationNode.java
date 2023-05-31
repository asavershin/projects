package workspace.formulanodes;

public class ReImplicationNode extends BinNode{
    ReImplicationNode(ReImplicationNode node) {super(node);}

    public ReImplicationNode(FormulaNode left, FormulaNode right) {super(left, right);}

    @Override
    public boolean calc() {return left.calc() || !right.calc();}

    @Override
    public String str() {return String.format("(%s < %s)", left.str(),right.str());}

    @Override
    public FormulaNode create() {return new ReImplicationNode(this);}
}
