package workspace.formulanodes;

public interface FormulaNode {
    public boolean calc();
    public String toString();

    public FormulaNode create();
}
