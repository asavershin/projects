package workspace.formulanodes;

public class ShefferStrokeNode extends BinNode{
    ShefferStrokeNode(ShefferStrokeNode node) {super(node);}

    public ShefferStrokeNode(FormulaNode left, FormulaNode right) {super(left, right);}

    @Override
    public boolean calc() {return !left.calc() || !right.calc();}

    @Override
    public String toString() {return String.format("(%s | %s)", left.toString(),right.toString());}

    @Override
    public FormulaNode create() {return new ShefferStrokeNode(this);}
}
