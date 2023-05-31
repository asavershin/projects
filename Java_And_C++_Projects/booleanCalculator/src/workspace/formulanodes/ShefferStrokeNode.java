package workspace.formulanodes;

public class ShefferStrokeNode extends BinNode{
    ShefferStrokeNode(ShefferStrokeNode node) {super(node);}

    public ShefferStrokeNode(FormulaNode left, FormulaNode right) {super(left, right);}

    @Override
    public boolean calc() {return !left.calc() || !right.calc();}

    @Override
    public String str() {return String.format("(%s | %s)", left.str(),right.str());}

    @Override
    public FormulaNode create() {return new ShefferStrokeNode(this);}
}
