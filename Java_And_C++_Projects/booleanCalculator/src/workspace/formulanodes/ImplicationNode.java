package workspace.formulanodes;

public class ImplicationNode extends BinNode{
    ImplicationNode(ImplicationNode node) {super(node);}

    public ImplicationNode(FormulaNode left, FormulaNode right) {super(left, right);}

    @Override
    public boolean calc() {return !(left.calc()) || right.calc();}

    @Override
    public String str() {return String.format("(%s > %s)", left.str(),right.str());}

    @Override
    public FormulaNode create() {return new ImplicationNode(this);}
}
