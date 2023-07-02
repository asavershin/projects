package workspace.formulanodes;

public abstract class BinNode implements FormulaNode {
    protected FormulaNode left;
    protected FormulaNode right;

    BinNode(BinNode node){
        this.left = node.left.create();
        this.right = node.right.create();
    }
    BinNode(FormulaNode left, FormulaNode right){
        this.left = left.create();
        this.right = right.create();
    }
}
