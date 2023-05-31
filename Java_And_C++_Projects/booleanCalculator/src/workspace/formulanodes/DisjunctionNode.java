package workspace.formulanodes;

public class DisjunctionNode extends BinNode{
    public DisjunctionNode(FormulaNode left, FormulaNode right){
        super(left,right);
    }
    public DisjunctionNode(DisjunctionNode node){
        super(node);
    }
    @Override
    public boolean calc() {return left.calc() || right.calc();}

    @Override
    public String str() {return String.format("(%s v %s)", left.str(),right.str());}

    @Override
    public FormulaNode create() {return new DisjunctionNode(this);}
}
