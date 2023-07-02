package workspace.formulanodes;

public class XORNode extends BinNode{

    XORNode(XORNode node) {super(node);}

    public XORNode(FormulaNode left, FormulaNode right) {super(left, right);}

    @Override
    public boolean calc() {return ( !left.calc() && right.calc() ) || ( left.calc() && !right.calc() );}

    @Override
    public String toString() {return String.format("(%s + %s)", left.toString(),right.toString());}

    @Override
    public FormulaNode create() {return new XORNode(this);}
}
