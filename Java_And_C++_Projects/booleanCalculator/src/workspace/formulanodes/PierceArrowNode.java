package workspace.formulanodes;

public class PierceArrowNode extends BinNode{
    PierceArrowNode(PierceArrowNode node) {super(node);}

    public PierceArrowNode(FormulaNode left, FormulaNode right) {super(left, right);}

    @Override
    public boolean calc() {return !left.calc() && !right.calc();}

    @Override
    public String str() {
        return String.format("(%s ^ %s)", left.str(),right.str());
    }

    @Override
    public FormulaNode create() {return new PierceArrowNode(this);}
}
