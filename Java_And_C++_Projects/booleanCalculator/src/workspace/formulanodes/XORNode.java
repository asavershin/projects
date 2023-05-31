package workspace.formulanodes;

public class XORNode extends BinNode{

    XORNode(XORNode node) {super(node);}

    public XORNode(FormulaNode left, FormulaNode right) {super(left, right);}

    @Override
    public boolean calc() {return ( !left.calc() && right.calc() ) || ( left.calc() && !right.calc() );}

    @Override
    public String str() {return String.format("(%s + %s)", left.str(),right.str());}

    @Override
    public FormulaNode create() {return new XORNode(this);}
}
