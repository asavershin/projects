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
    public String toString() {return String.format("(%s v %s)", left.toString(),right.toString());}

    @Override
    public FormulaNode create() {return new DisjunctionNode(this);}
}
