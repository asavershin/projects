package workspace.formulanodes;

public class NegationNode implements FormulaNode {
    FormulaNode node;
    public NegationNode(FormulaNode node){
        this.node = node.create();
    }
    public NegationNode(NegationNode node){
        this.node = new NegationNode(node.node.create());
    }
    public NegationNode(){
        node = null;
    }
    @Override
    public boolean calc() {
        return !node.calc();
    }

    @Override
    public String str() {
        return String.format("~%s", node.calc()?1:0);
    }

    @Override
    public FormulaNode create() {
        return new NegationNode(this);
    }
}
