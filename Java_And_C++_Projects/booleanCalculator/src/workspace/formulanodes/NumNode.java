package workspace.formulanodes;

public class NumNode implements FormulaNode{
    private boolean num;

    public NumNode(boolean num){
        this.num = num;
    }
    @Override
    public boolean calc() {
        return num;
    }

    @Override
    public String str() {;
        return String.format("(%x)", num?1:0);
    }

    @Override
    public FormulaNode create() {
        return new NumNode(num);
    }
}
