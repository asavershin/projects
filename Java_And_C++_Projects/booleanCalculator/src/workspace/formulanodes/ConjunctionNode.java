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
        return left.calc() && right.calc();
    }

    @Override
    public String str() {
        return String.format("(%s & %s)", left.str(),right.str());
    }

    @Override
    public FormulaNode create() {
        return new ConjunctionNode(this);
    }
}
