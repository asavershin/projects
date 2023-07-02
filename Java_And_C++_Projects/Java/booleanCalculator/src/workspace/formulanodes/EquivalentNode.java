package workspace.formulanodes;

public class EquivalentNode extends BinNode{
    EquivalentNode(EquivalentNode node) {super(node);}

    public EquivalentNode(FormulaNode left, FormulaNode right) {super(left, right);}

    @Override
    public boolean calc() {return left.calc() == right.calc();}

    @Override
    public String toString() {return String.format("(%s = %s)", left.toString(),right.toString());}

    @Override
    public FormulaNode create() {return new EquivalentNode(this);}
}
