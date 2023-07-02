package workspace.formulanodes;

public class ConjunctionNode extends BinNode{

    public ConjunctionNode(FormulaNode left, FormulaNode right){
        super(left,right);
    }
    public ConjunctionNode(ConjunctionNode node){
        super(node);
    }
    @Override
    public boolean calc() {
        return (left.calc() && right.calc());
    }

    @Override
    public String toString() {
        return String.format("(%s & %s)", left.toString(),right.toString());
    }

    @Override
    public FormulaNode create() {
        return new ConjunctionNode(this);
    }
}
