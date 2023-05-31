package workspace.formulanodes;

public class EquivalentNode extends BinNode{
    EquivalentNode(EquivalentNode node) {super(node);}

    public EquivalentNode(FormulaNode left, FormulaNode right) {super(left, right);}

    @Override
    public boolean calc() {return left.calc() == right.calc();}

    @Override
    public String str() {return String.format("(%s = %s)", left.str(),right.str());}

    @Override
    public FormulaNode create() {return new EquivalentNode(this);}
}
